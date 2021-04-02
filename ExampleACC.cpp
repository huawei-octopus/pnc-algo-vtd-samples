// ExampleConsole.cpp : Defines the entry point for the console application.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/ioctl.h>
#include "RDBHandler.hh"

#define DEFAULT_PORT_TC     48190   /* for image port it should be 48192 */
#define DEFAULT_PORT_SENSOR 48195   
#define DEFAULT_BUFFER_SIZE 204800
#define MAX_CONNECTIONS     2       /* maximum number of bi-directional TCP connections */


// type definition for connection handling
typedef struct
{
    int           id;               // unique connection ID
    char          serverAddr[128];  // Server to connect to
    int           port;             // Port on server to connect to
    int           desc;             // client (socket) descriptor
    unsigned int  bytesInBuffer;    // used size of receive buffer
    size_t        bufferSize;       // total size of receive buffer;
    unsigned char *pData;           // pointer to receive buffer
} Connection_t;

// connection instances
Connection_t sConnection[MAX_CONNECTIONS];

// globally store nearest object
RDB_OBJECT_STATE_t mNearestObject;
RDB_OBJECT_STATE_t mOwnObject;

static const unsigned int scMainConnection   = 0;
static const unsigned int scSensorConnection = 1;

static const unsigned int scOwnId = 1;  // ID of own vehicle
static const double scOwnPreferredSpeed = 30.0;     // default preferred speed of own vehicle
double lastUpdateTimeSensorObject = 0.0;


// function prototypes
int openPort( int & descriptor, int portNo, const char* serverAddr );
void initConnections();
void initConnection( Connection_t & conn );
void readConnection( Connection_t & conn, bool waitForMessage, bool verbose );

void parseRDBMessage( Connection_t & conn, RDB_MSG_t* msg );
void parseRDBMessageEntry( Connection_t & conn, const double & simTime, const unsigned int & simFrame, RDB_MSG_ENTRY_HDR_t* entryHdr );
void handleRDBitem( const double & simTime, const unsigned int & simFrame, RDB_OBJECT_STATE_t & item, bool isExtended, bool isSensor, bool firstElement );
void sendDriverCtrl( int & sendSocket, const double & simTime, const unsigned int & simFrame );


//
// Function: usage:
//
// Description:
//    Print usage information and exit
//
void usage()
{
    printf("usage: client [-t:x] [-s:IP]\n\n");
    printf("       -t:x      taskControl port\n");
    printf("       -s:x      sensor port\n");
    printf("       -T:IP     taskControl IPv4 address\n");
    printf("       -S:IP     sensor IPv4 address\n");
    exit(1);
}

//
// Function: ValidateArgs
//
// Description:
//    Parse the command line arguments, and set some global flags
//    to indicate what actions to perform
//
void ValidateArgs(int argc, char **argv)
{
    for(int i = 1; i < argc; i++)
    {
        if ((argv[i][0] == '-') || (argv[i][0] == '/'))
        {
            switch (argv[i][1])
            {
                case 't':        // Remote port taskControl
                    if (strlen(argv[i]) > 3)
                        sConnection[0].port = atoi(&argv[i][3]);
                    break;
                case 's':        // Remote port sensor
                    if (strlen(argv[i]) > 3)
                        sConnection[1].port = atoi(&argv[i][3]);
                    break;
                case 'T':       // TC server
                    if (strlen(argv[i]) > 3)
                        strcpy(sConnection[0].serverAddr, &argv[i][3]);
                    break;
                case 'S':       // sensor server
                    if (strlen(argv[i]) > 3)
                        strcpy(sConnection[1].serverAddr, &argv[i][3]);
                    break;
                default:
                    usage();
                    break;
            }
        }
    }
}

int main( int argc, char* argv[] )
{
    static bool sVerbose = false;
    
    // initialize the connections
    initConnections();

    // Parse the command line
    ValidateArgs(argc, argv);
    
    // reset the information about the nearest and own object
    memset( &mNearestObject, 0, sizeof( RDB_OBJECT_STATE_t ) );
    memset( &mOwnObject, 0, sizeof( RDB_OBJECT_STATE_t ) );
    
    // open TC port
    if ( !openPort( sConnection[0].desc, sConnection[0].port, sConnection[0].serverAddr ) )
        return -1;
    
    // open sensor port
    if ( !openPort( sConnection[1].desc, sConnection[1].port, sConnection[1].serverAddr ) )
        return -1;
    
    // Send and receive data - forever!
    //
    for(;;)
    {
        readConnection( sConnection[0], false, sVerbose );
        readConnection( sConnection[1], false, sVerbose );
        
        usleep( 1 );    // do not overload the system
    }

    return 0;
}

void parseRDBMessage( Connection_t & conn, RDB_MSG_t* msg )
{
    if ( !msg )
      return;

    if ( !msg->hdr.dataSize )
        return;
    
    RDB_MSG_ENTRY_HDR_t* entry = ( RDB_MSG_ENTRY_HDR_t* ) ( ( ( char* ) msg ) + msg->hdr.headerSize );
    uint32_t remainingBytes    = msg->hdr.dataSize;
        
    while ( remainingBytes )
    {
        parseRDBMessageEntry( conn, msg->hdr.simTime, msg->hdr.frameNo, entry );

        remainingBytes -= ( entry->headerSize + entry->dataSize );
        
        if ( remainingBytes )
          entry = ( RDB_MSG_ENTRY_HDR_t* ) ( ( ( ( char* ) entry ) + entry->headerSize + entry->dataSize ) );
    }
}

void parseRDBMessageEntry( Connection_t & conn, const double & simTime, const unsigned int & simFrame, RDB_MSG_ENTRY_HDR_t* entryHdr )
{
    if ( !entryHdr )
        return;
    
    int noElements = entryHdr->elementSize ? ( entryHdr->dataSize / entryHdr->elementSize ) : 0;
    
    if ( !noElements )  // some elements require special treatment
    {
        switch ( entryHdr->pkgId )
        {
            case RDB_PKG_ID_START_OF_FRAME:
                fprintf( stderr, "void parseRDBMessageEntry: connection %d: got start of frame\n",  conn.id );
                
                if ( conn.id == scSensorConnection )            // reset information about sensor object if a new sensor frame starts.
                     memset( &mNearestObject, 0, sizeof( RDB_OBJECT_STATE_t ) );;
                break;
                
            case RDB_PKG_ID_END_OF_FRAME:
                fprintf( stderr, "void parseRDBMessageEntry: connection %d: got end of frame\n", conn.id );
		        // only connection to taskControl shall send driver control commands
                
                if ( conn.id == scMainConnection )
                    sendDriverCtrl( conn.desc, simTime, simFrame );
                break;
                
            default:
                return;
                break;
        }
        return;
    }

    unsigned char ident   = 6;
    char*         dataPtr = ( char* ) entryHdr;
    bool          firstElement = true;
        
    dataPtr += entryHdr->headerSize;
        
    while ( noElements-- )
    {
        bool printedMsg = true;
            
        switch ( entryHdr->pkgId )
        {
            case RDB_PKG_ID_OBJECT_STATE:
                // only first object state in sensor (i.e. nearest object ) is relevant
                if ( ( conn.id == scSensorConnection ) && ( entryHdr->flags & RDB_PKG_FLAG_EXTENDED ) )
                {
                    handleRDBitem( simTime, simFrame, *( ( RDB_OBJECT_STATE_t* ) dataPtr ), entryHdr->flags & RDB_PKG_FLAG_EXTENDED, ( conn.id == scSensorConnection ), firstElement );
                    firstElement = false;
                }
                break;
                    
            default:
                printedMsg = false;
                break;
        }
        dataPtr += entryHdr->elementSize;
     }
}

void handleRDBitem( const double & simTime, const unsigned int & simFrame, RDB_OBJECT_STATE_t & item, bool isExtended, bool isSensor, bool firstElement )
{
    // own object?
    if ( item.base.id == scOwnId )
        memcpy( &mOwnObject, &item, sizeof( RDB_OBJECT_STATE_t ) );
    else if ( isSensor && firstElement )
        memcpy( &mNearestObject, &item, sizeof( RDB_OBJECT_STATE_t ) );
    
  fprintf( stderr, "handleRDBitem: handling object state\n" );
  fprintf( stderr, "    simTime = %.3lf, simFrame = %ld\n", simTime, simFrame );
  fprintf( stderr, "    object = %s, id = %d\n", item.base.name, item.base.id );
  fprintf( stderr, "    position = %.3lf / %.3lf / %.3lf\n", item.base.pos.x, item.base.pos.y, item.base.pos.z );

  if ( isExtended )
    fprintf( stderr, "    speed = %.3lf / %.3lf / %.3lf\n", item.ext.speed.x, item.ext.speed.y, item.ext.speed.z );
}

void sendDriverCtrl( int & sendSocket, const double & simTime, const unsigned int & simFrame )
{
  Framework::RDBHandler myHandler;

  myHandler.initMsg();

  RDB_DRIVER_CTRL_t *myDriver = ( RDB_DRIVER_CTRL_t* ) myHandler.addPackage( simTime, simFrame, RDB_PKG_ID_DRIVER_CTRL );

  if ( !myDriver )
    return;
    
  // do we have a valid nearest object?
  bool haveSensorObject = ( mNearestObject.base.id > 0 );   // sensor object must not be older than 1.0s
  
  double ownSpeed = sqrt( mOwnObject.ext.speed.x * mOwnObject.ext.speed.x + mOwnObject.ext.speed.y * mOwnObject.ext.speed.y );

  double accelTgtDist  = 0.0;
  double accelTgtSpeed = ( 30.0 - ownSpeed ) / 5.0;   // default speed should be own preferred speed
  
  if ( haveSensorObject )
  {
    // let's go for the same speed as preceding vehicle: 
    if ( mNearestObject.ext.speed.x < -1.0e-3 )
      accelTgtSpeed = 2.0 * mNearestObject.ext.speed.x / 5.0;
    else
      accelTgtSpeed = 0.0;

    // let's go for a 2s distance
    double tgtDist = ownSpeed * 2.0;
  
    if ( tgtDist < 10.0 )   // minimum  distance to keep
        tgtDist = 10.0;
        
    accelTgtDist = ( mNearestObject.base.pos.x - tgtDist ) / 10.0;    
  }
    
  fprintf( stderr, "sendDriverCtrl: accelDist = %.5lf, accelSpeed = %.5lf\n", accelTgtDist, accelTgtSpeed );
    
  myDriver->playerId      = 1;
  myDriver->accelTgt      = accelTgtDist + accelTgtSpeed;
  myDriver->validityFlags = RDB_DRIVER_INPUT_VALIDITY_TGT_ACCEL | RDB_DRIVER_INPUT_VALIDITY_ADD_ON;

  int retVal = send( sendSocket, ( const char* ) ( myHandler.getMsg() ), myHandler.getMsgTotalSize(), 0 );

  if ( !retVal )
    fprintf( stderr, "sendDriverCtrl: could not send driver control\n" );
  else
    fprintf( stderr, "sentDriverCtrl\n" );

}

void initConnections()
{
    memset( sConnection, 0, MAX_CONNECTIONS * sizeof( Connection_t ) );
    
    // general initialization
    for ( int i = 0; i < MAX_CONNECTIONS; i++ )
    {
        initConnection( sConnection[i] );
        sConnection[i].id = i;
    }
    
    // additional individual initalization
    sConnection[0].port = DEFAULT_PORT_TC;
    sConnection[1].port = DEFAULT_PORT_SENSOR;
}

void initConnection( Connection_t & conn )
{
    strcpy( conn.serverAddr, "127.0.0.1" );

    conn.desc       = -1;
    conn.bufferSize = sizeof ( RDB_MSG_t );
    conn.pData      = ( unsigned char* ) calloc( 1, conn.bufferSize );
}

int openPort( int & descriptor, int portNo, const char* serverAddr )
{
    struct sockaddr_in server;
    struct hostent    *host = NULL;

    //
    // Create the socket, and attempt to connect to the server
    //
    descriptor = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    
    if ( descriptor == -1 )
    {
        fprintf( stderr, "openPort: socket() failed: %s\n", strerror( errno ) );
        return 0;
    }
    
    int opt = 1;
    setsockopt ( descriptor, IPPROTO_TCP, TCP_NODELAY, &opt, sizeof( opt ) );

    server.sin_family      = AF_INET;
    server.sin_port        = htons( portNo );
    server.sin_addr.s_addr = inet_addr( serverAddr );
    
    //
    // If the supplied server address wasn't in the form
    // "aaa.bbb.ccc.ddd" it's a hostname, so try to resolve it
    //
    if ( server.sin_addr.s_addr == INADDR_NONE )
    {
        host = gethostbyname( serverAddr );
        
        if ( host == NULL )
        {
            fprintf( stderr, "openPort: unable to resolve server: %s\n", serverAddr );
            return 0;
        }
        memcpy( &server.sin_addr, host->h_addr_list[0], host->h_length );
    }
    
    //   set to non blocking
    opt = 1;
    ioctl( descriptor, FIONBIO, &opt );
    
	// wait for connection
	bool bConnected = false;

    while ( !bConnected )
    {
        if (connect( descriptor, (struct sockaddr *)&server, sizeof( server ) ) == -1 )
        {
            fprintf( stderr, "connect() failed: %s\n", strerror( errno ) );
            sleep( 1 );
        }
        else
            bConnected = true;
    }

    fprintf( stderr, "port % d connected!\n", portNo );
    
    return 1;
}

void readConnection( Connection_t & conn, bool waitForMessage, bool verbose )
{
    // receive buffer
    static char* szBuffer = ( char* ) calloc( 1, DEFAULT_BUFFER_SIZE );
    int ret = -1;
    
    bool bMsgComplete = false;
    
    if ( verbose )
        fprintf( stderr, "readConnection: start reading connection %d\n", conn.id );
    
    // read a complete message
    do
    {
        ret = recv( conn.desc, szBuffer, DEFAULT_BUFFER_SIZE, 0 );
        
        if ( verbose )
            fprintf( stderr, "readConnection: connection %d, ret = %d\n", conn.id, ret );

        if ( ret > 0 )
        {
            // do we have to grow the buffer??
            if ( ( conn.bytesInBuffer + ret ) > conn.bufferSize )
            {
                conn.pData      = ( unsigned char* ) realloc( conn.pData, conn.bytesInBuffer + ret );
                conn.bufferSize = conn.bytesInBuffer + ret;
            }

            memcpy( conn.pData + conn.bytesInBuffer, szBuffer, ret );
            conn.bytesInBuffer += ret;

            // already complete messagae?
            if ( conn.bytesInBuffer >= sizeof( RDB_MSG_HDR_t ) )
            {
                RDB_MSG_HDR_t* hdr = ( RDB_MSG_HDR_t* ) conn.pData;

                // is this message containing the valid magic number?
                if ( hdr->magicNo != RDB_MAGIC_NO )
                {
                    printf( "message receiving is out of sync; discarding data" );
                    conn.bytesInBuffer = 0;
                }

                while ( conn.bytesInBuffer >= ( hdr->headerSize + hdr->dataSize ) )
                {
                    unsigned int msgSize = hdr->headerSize + hdr->dataSize;
                    
                    // print the message
                    if ( verbose )
                        Framework::RDBHandler::printMessage( ( RDB_MSG_t* ) conn.pData, true );
                    
                    // now parse the message    
                    parseRDBMessage( conn, ( RDB_MSG_t* ) conn.pData );

                    // remove message from queue
                    memmove( conn.pData, conn.pData + msgSize, conn.bytesInBuffer - msgSize );
                    conn.bytesInBuffer -= msgSize;

                    bMsgComplete = true;
                }
            }
        }
    } while ( ( ret > 0 ) && ( !waitForMessage || bMsgComplete ) );
    
    if ( verbose )
        fprintf( stderr, "readConnection: finished reading connection %d\n", conn.id );
}
