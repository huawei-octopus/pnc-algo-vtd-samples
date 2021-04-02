/**
* this set of routines maps incoming RDB data to a data vector
* of constant size (32bit word alignment)
* (c)2011 by VIRES Simulationstechnologie GmbH, Germany
*/

/* ------------- includes ------------- */
#include <stdlib.h>
#include <string.h>

/*#define BIG_ENDIAN_TARGET*/
#ifdef BIG_ENDIAN_TARGET
#include "viRDBIcdBigEndian.h"
#else
#include "viRDBIcd.h"
#include "viRDBaddOn.h"
#endif

/* ------------- local variables ------------- */
/* define a data buffer for incoming data */
static char*  sDataBuffer          = 0;
static char*  sDefaultDataBuffer   = 0;
static size_t sDataBufferTotalSize = 0;
static size_t sDataBufferUsedSize  = 0;
static char   sHoldOneMessageOnly  = 1;
static char   sCompensateEndian    = 0;
static unsigned int sDebugValue01  = 888;

typedef struct
{
    double dist;
    void* obj;
} ElDistStruct;

/* ------------- public methods ------------- */

/* ------------- local methods ------------- */
/**
* initialize the RDB mapper
* @return 1 if successful, otherwise 0
*/
static int rdbMapperInit( void );

/**
* terminate the RDB mapper
* @return 1 if successful, otherwise 0
*/
static int rdbMapperTerminate( void );

/**
* clear the message buffer
* @return 1 if successful, otherwise 0
*/
static int rdbMapperClearBuffer( void );

/**
* resync the message buffer so that there really is a message at the beginning
* @return 1 if successful, otherwise 0
*/
static int rdbMapperReSyncBuffer( void );

/**
* handle incoming data (stream) which has been read from the network
* by the calling routine
* @param data       pointer to the incoming data
* @param dataSize   size of the incoming data [bytes]
* @return 1 if successful, otherwise 0
*/
static int rdbMapperHandleIncomingData( void* data, unsigned int dataSize );

/**
* get available data of dynamic objects
* @param data       pointer to the incoming data
* @param dataSize   size of the incoming data [bytes]
* @param ownID      numeric ID of own vehicle
* @param ownX       own x co-ordinate
* @param ownY       own y co-ordinate
* @return number of valid objects
*/
static unsigned int rdbMapperGetDynamicObjects( void* target, size_t maxSize, unsigned int ownId, double ownX, double ownY );
static unsigned int rdbMapperGetStaticObjects( void* target, size_t maxSize, unsigned int ownId, double ownX, double ownY );
static unsigned int rdbMapperGetObjects( void* target, size_t maxSize, unsigned int ownId, double ownX, double ownY, int dynOb );

/**
* terminate the current RDB frame and get ready for the next message;
* this modifies the internal buffer
* @return 1 if RDB frame has been processed
*/
static int rdbMapperTerminateFrame( void );

/**
* push data into the RDB data buffer
* @param data       pointer to the data which is to be stored
* @param dataSize   size of the data that shall be pushed into the buffer
* @return 1 if successful, otherwise 0
*/
static int rdbMapperPushData( void* data, size_t dataSize );

/**
* pop data from the RDB data buffer
* @param dataSize   size of the data that shall be popped out of the buffer
* @return 1 if successful, otherwise 0
*/
static int rdbMapperPopData( size_t dataSize );

/**
* do I have a complete message in the buffer?
* @return 1 if complete message is available, otherwise 0
*/
static int rdbMapperMessageIsAvailable( void );

/**
* access the first element of a given type
* @param dataType   type of the data that is to be searched for
* @param extended   search for extended packages of the given data type
* @param noElements pointer to a variable where to store the number of available elements
* @param noElements pointer to a variable where to store the size of an element
* @return pointer to the first element
*/
static char* rdbMapperAccessFirstElementOfType( unsigned short dataType, char extended, unsigned int *noElements, size_t *elSize );

static int rdbMapperMessageGetTimeAndFrame( double* simTime, unsigned int *simFrame );
static unsigned int rdbMapperGetBufferUsage( void );
static unsigned int rdbMapperGetMagicNo( void );
static int rdbMapperSetBuffer( void* bufPtr, unsigned int bufSize );

/**
 * compute the number of messages which are currently in the message buffer
 * @param  noPkg pointer where to store the total number of packages 
 * @return number of messages in buffer
 */
static int rdbMapperGetNoOfMsgInBuffer( unsigned int *noPkg );

/* ------------- implementation ------------- */
static int rdbMapperInit( void )
{
    if ( sDefaultDataBuffer )
        free( sDefaultDataBuffer );
        
    sDataBuffer          = 0;
    sDataBufferTotalSize = 10000 * sizeof( int );
    sDataBufferUsedSize  = 0;
    
    sDefaultDataBuffer = calloc( 1, sDataBufferTotalSize );
    sDataBuffer        = sDefaultDataBuffer;
    
    return 1;
}

static int rdbMapperTerminate( void )
{
    if ( sDefaultDataBuffer )
        free( sDefaultDataBuffer );
        
    sDataBuffer          = 0;
    sDataBufferTotalSize = 0;
    sDataBufferUsedSize  = 0;
    
    return 1;
}

static int rdbMapperClearBuffer( void )
{    
    sDataBufferUsedSize  = 0;
    return 1;
}

static int rdbMapperSetBuffer( void* bufPtr, unsigned int bufSize )
{   
    if ( bufPtr )
        sDataBuffer = ( char* )bufPtr;

    sDataBufferUsedSize  = bufSize;
    sDataBufferTotalSize = bufSize;
   
    return 1;
}

static int rdbMapperReSyncBuffer( void )
{    
    char* checkPtr      = sDataBuffer;
    int nCheckedBytes   = 0;
    int maxCheckedBytes = sDataBufferUsedSize - sizeof( RDB_MSG_HDR_t );
    
    // do not check more than 1000 bytes
    if ( maxCheckedBytes > 10000 )
        maxCheckedBytes = 10000;
    
    while ( nCheckedBytes < maxCheckedBytes )
    {
        RDB_MSG_HDR_t* hdr = ( RDB_MSG_HDR_t* )( checkPtr );
        
        if ( hdr->magicNo == RDB_MAGIC_NO )
        {
            // found the start of a new message, pop the "irrelevant" bytes from the buffer
            rdbMapperPopData( nCheckedBytes );
            return 1;
        }
        nCheckedBytes++;
        checkPtr++;
    }
    
    if ( sDataBufferUsedSize > sizeof( RDB_MSG_HDR_t ) )
        rdbMapperClearBuffer();
    
    return 0;
}

static int rdbMapperHandleIncomingData( void* data, unsigned int dataSize )
{
    if ( dataSize == 0 )
        return 0;
    
    if ( sHoldOneMessageOnly )
        rdbMapperClearBuffer();
        
    /* first: push the data into the data buffer */
    return rdbMapperPushData( data, dataSize );
}

static int rdbMapperTerminateFrame( void )
{
    RDB_MSG_HDR_t* msgHdr = ( RDB_MSG_HDR_t* )( sDataBuffer );
    
    if ( !rdbMapperMessageIsAvailable() )
        return 0;
        
    /* remove the message from the buffer */
    return rdbMapperPopData( msgHdr->headerSize + msgHdr->dataSize );
}

static int rdbMapperPushData( void* data, size_t dataSize )
{
    char* writePtr = NULL;
    
    /* grow the buffer if necessary */
    if ( ( sDataBufferUsedSize + dataSize ) > sDataBufferTotalSize )
    {
        return 0;
        
        //sDataBuffer          = ( char* ) realloc( sDataBuffer, sDataBufferUsedSize + dataSize );
        //sDataBufferTotalSize = sDataBufferUsedSize + dataSize;
    }
        
    if ( !sDataBuffer )
        return 0;
        
    writePtr  = sDataBuffer;
    writePtr += sDataBufferUsedSize;
    
    memcpy( writePtr, data, dataSize );
    
    sDataBufferUsedSize += dataSize;

    return 1;
}

static int rdbMapperPopData( size_t dataSize )
{
    char* dataPtr = 0;
    
    if ( !dataSize )
        return 0;
    
    /* do not move more data than is available */    
    if ( dataSize > sDataBufferUsedSize )
        dataSize = sDataBufferUsedSize;
    
    /* --- move remaining contents --- */
    dataPtr  = sDataBuffer;
    dataPtr += dataSize;
    
    memmove( sDataBuffer, dataPtr, sDataBufferTotalSize - dataSize );
    
    sDataBufferUsedSize -= dataSize;
    
    /* --- re-initialize the remaining bits of the buffer --- */
    dataPtr  = sDataBuffer;
    dataPtr += sDataBufferUsedSize;
    
    memset( dataPtr, 0, sDataBufferTotalSize - sDataBufferUsedSize );
    
    return 1;
}

static int rdbMapperMessageIsAvailable( void )
{
    RDB_MSG_HDR_t* msgHdr = ( RDB_MSG_HDR_t* )( sDataBuffer );
    
    if ( !sDataBuffer || ( sDataBufferUsedSize < sizeof( RDB_MSG_HDR_t ) ) )
        return 0;
    
    // ok, sometimes dSPACE may overrun and skip part of messages, in this case we have
    // to re-sync to the message frames
    if ( !sHoldOneMessageOnly )
    {
    if ( msgHdr->magicNo != RDB_MAGIC_NO )
    {
        rdbMapperReSyncBuffer();
        
        if ( sDataBufferUsedSize < sizeof( RDB_MSG_HDR_t ) )
           return 0;
    }
    }
    return ( sDataBufferUsedSize >= ( msgHdr->headerSize + msgHdr->dataSize ) );
}

static int rdbMapperMessageGetMagicNo( void )
{
    RDB_MSG_HDR_t* msgHdr = ( RDB_MSG_HDR_t* )( sDataBuffer );
    unsigned short *magicNoPtr = ( unsigned short* ) sDataBuffer;
    
    if ( sDataBufferUsedSize < sizeof( RDB_MSG_HDR_t ) )
        return 0;
    
    return msgHdr->magicNo;
}

static int rdbMapperMessageGetTimeAndFrame( double* simTime, unsigned int *simFrame )
{
    RDB_MSG_HDR_t* msgHdr = ( RDB_MSG_HDR_t* )( sDataBuffer );
    
    if ( !rdbMapperMessageIsAvailable() )
        return 0;
    
    if ( !simTime || !simFrame )
        return 0;
    
    *simTime  = msgHdr->simTime;
    *simFrame = msgHdr->frameNo;
    
    return 1;
}

static unsigned int rdbMapperGetBufferUsage( void )
{
    return sDataBufferUsedSize;
}

static char* rdbMapperAccessFirstElementOfType( unsigned short dataType, char extended, unsigned int *noElements, size_t *elSize )
{
    RDB_MSG_HDR_t*       msgHdr      = ( RDB_MSG_HDR_t* )( sDataBuffer );
    RDB_MSG_ENTRY_HDR_t* entryHdr    = 0;
    unsigned int         checkedSize = 0;

    if ( !noElements )
        return NULL;
        
    /* for sure, we do not yet have any elements */
    *noElements = 0;
    *elSize     = 0;
        
    if ( !rdbMapperMessageIsAvailable() )
        return 0;
        
    /* go to the first entry header */
    entryHdr = ( RDB_MSG_ENTRY_HDR_t* )( sDataBuffer + msgHdr->headerSize );
        
    while ( checkedSize < msgHdr->dataSize )
    {
        if ( entryHdr->pkgId == dataType )
        {
            int entryIsExtended = ( entryHdr->flags & RDB_PKG_FLAG_EXTENDED ) != 0;
                          
            if ( entryIsExtended == extended )
            {
                if ( entryHdr->elementSize )
                    *noElements = entryHdr->dataSize / entryHdr->elementSize;
                    
                *elSize = entryHdr->elementSize;
 
                return ( ( char* ) entryHdr ) + entryHdr->headerSize;
            }
        }
        
        /* let's go to the next entry */
        checkedSize += entryHdr->headerSize + entryHdr->dataSize;
        entryHdr = ( RDB_MSG_ENTRY_HDR_t* )( ( ( char* ) entryHdr ) + entryHdr->headerSize + entryHdr->dataSize );
    }
    return NULL;
}

static int rdbMapperGetNoOfMsgInBuffer( unsigned int *noPkg )
{
    RDB_MSG_HDR_t*       msgHdr         = ( RDB_MSG_HDR_t* )( sDataBuffer );
    RDB_MSG_ENTRY_HDR_t* entryHdr       = 0;
    unsigned int         checkedBufSize = 0;
    unsigned int         noMsg          = 0;
    
    if ( !noPkg )
        return 0;
    
    *noPkg = 0;

    if ( !rdbMapperMessageIsAvailable() )
        return 0;
    
    while ( checkedBufSize < sDataBufferUsedSize )
    {
        unsigned int checkedMsgSize = 0;
        noMsg++;
        
        /* go to the first entry header in current message */
        entryHdr = ( RDB_MSG_ENTRY_HDR_t* )( ( ( char* ) msgHdr ) + msgHdr->headerSize );
        
        while ( checkedMsgSize < msgHdr->dataSize )
        {
            *noPkg += 1;
            
            /* let's go to the next entry */
            checkedMsgSize += entryHdr->headerSize + entryHdr->dataSize;
            entryHdr = ( RDB_MSG_ENTRY_HDR_t* )( ( ( char* ) entryHdr ) + entryHdr->headerSize + entryHdr->dataSize );
        }
        
        /* now go to the next message */
        checkedBufSize += msgHdr->headerSize + msgHdr->dataSize;
        msgHdr = ( RDB_MSG_HDR_t* )( ( ( char* ) msgHdr ) + msgHdr->headerSize + msgHdr->dataSize );
    }
    return noMsg;
}

static unsigned int rdbMapperGetDynamicObjects( void* target, size_t maxSize, unsigned int ownId, double ownX, double ownY )
{
    return rdbMapperGetObjects( target, maxSize, ownId, ownX, ownY, 1 );
}

static unsigned int rdbMapperGetStaticObjects( void* target, size_t maxSize, unsigned int ownId, double ownX, double ownY )
{
    return rdbMapperGetObjects( target, maxSize, ownId, ownX, ownY, 0 );
}

static unsigned int rdbMapperGetObjects( void* target, size_t maxSize, unsigned int ownId, double ownX, double ownY, int dynOb )
{
    unsigned int             noElements     = 0;
    size_t                   elSize         = 0;
    size_t                   copiedSize     = 0;
    size_t                   copiedElements = 0;
    char*                    tgtPtr         = ( char* ) target;
    RDB_OBJECT_STATE_t*      objState       = 0;
    RDB_OBJECT_STATE_BASE_t* objStateBase   = 0;
    ElDistStruct             objList[100];
    ElDistStruct             tmpList;
    unsigned int             objId;
    int i;
    int j;
    
    if ( !target )
        return 0;
    
    if ( dynOb )
        objState = ( RDB_OBJECT_STATE_t* ) rdbMapperAccessFirstElementOfType( RDB_PKG_ID_OBJECT_STATE, 1, &noElements, &elSize );
    else
        objStateBase = ( RDB_OBJECT_STATE_BASE_t* ) rdbMapperAccessFirstElementOfType( RDB_PKG_ID_OBJECT_STATE, 0, &noElements, &elSize );
    
    /* hold a list of all object states vs. distance to ownship */
    if ( noElements > 100 )
        noElements = 100;
        
    /* sort elements in order of distance to ownship */
    for ( i = 0; i < noElements; i++ )
    {
        RDB_OBJECT_STATE_BASE_t *basePtr = dynOb ? &( objState[i].base ) : &( objStateBase[i] );
        double objX;
        double objY;
        double dx;
        double dy;
        char* dataPtr = ( char* )basePtr;
        
        if ( sCompensateEndian )
        {
            char* xPtr = ( char* )&objX;
            char* yPtr = ( char* )&objY;
            
            // for this target machine you have to map the double values in pairs of 4 bytes
            xPtr[0] = dataPtr[68];
            xPtr[1] = dataPtr[69];
            xPtr[2] = dataPtr[70];
            xPtr[3] = dataPtr[71];
            xPtr[4] = dataPtr[64];
            xPtr[5] = dataPtr[65];
            xPtr[6] = dataPtr[66];
            xPtr[7] = dataPtr[67];

            yPtr[0] = dataPtr[76];
            yPtr[1] = dataPtr[77];
            yPtr[2] = dataPtr[78];
            yPtr[3] = dataPtr[79];
            yPtr[4] = dataPtr[72];
            yPtr[5] = dataPtr[73];
            yPtr[6] = dataPtr[74];
            yPtr[7] = dataPtr[75];
        }
        else
        {
            objX = basePtr->pos.x;
            objY = basePtr->pos.y;
        }
       
        dx = ownX - objX;
        dy = ownY - objY;
        
        objList[i].obj = basePtr;
        objList[i].dist = dx * dx + dy * dy;    // using the square of dist is fine also and saves some time
    }
    
    /* bubble sort the stuff */
    for ( i = 0; i < noElements; i++ )
    {
        for ( j = i + 1; j < noElements; j++ )
        {
            if ( objList[j].dist < objList[i].dist )
            {
                size_t copySize = sizeof( ElDistStruct );
                memcpy( &tmpList, &( objList[i] ),        copySize );
                memcpy( &( objList[i] ), &( objList[j] ), copySize );
                memcpy( &( objList[j] ), &tmpList,        copySize );
            }
        }
    }

    for ( i = 0; ( i < noElements ) && ( ( copiedSize + elSize ) < maxSize ); i++ )
    {
        RDB_OBJECT_STATE_BASE_t *basePtr = ( RDB_OBJECT_STATE_BASE_t* ) objList[i].obj;
      
        memcpy( &objId, basePtr, sizeof( int ) );

        if ( objId != ownId )
        {
            memcpy( tgtPtr, objList[i].obj, elSize );

            copiedSize += elSize;
            tgtPtr     += elSize;
            copiedElements++;
        }
    }    
    return copiedElements;
}

static unsigned int rdbMapperGetElementsOfType( void* target, size_t maxSize, int elType )
{
    unsigned int noElements  = 0;
    unsigned int maxElements = 0;
    size_t       elSize      = 0;
    char*        tgtPtr      = ( char* ) target;
    void*        srcPtr      = 0;
    
    if ( !target )
        return 0;
    
    srcPtr = rdbMapperAccessFirstElementOfType( elType, 0, &noElements, &elSize );
    
    if ( !srcPtr || !noElements )
        return 0;
    
    // do not copy more than there is space available
    maxElements = maxSize / elSize;
    
    if ( noElements > maxElements )
        noElements = maxElements;
    
    memcpy( tgtPtr, srcPtr, noElements * elSize );
    
    return noElements;
}

static unsigned int rdbMapperGetOwnElementsOfType( unsigned int ownId, void* target, size_t maxSize, int elType )
{
    unsigned int noElements   = 0;
    unsigned int maxElements  = 0;
    unsigned int usedElements = 0;
    size_t       elSize       = 0;
    char*        tgtPtr       = ( char* ) target;
    void*        srcPtr       = 0;
    char*        scanPtr      = 0;
    unsigned int i;
    
    if ( !target )
        return 0;
    
    srcPtr = rdbMapperAccessFirstElementOfType( elType, 0, &noElements, &elSize );
    
    if ( !srcPtr || !noElements )
        return 0;
    
    // do not copy more than there is space available
    maxElements = maxSize / elSize;
    
    scanPtr = ( char* ) srcPtr;
    
    for ( i = 0; ( i < noElements ) && ( maxElements ); i++ )
    {
        char useElement = 0;

        switch( elType )
        {
            case RDB_PKG_ID_CONTACT_POINT:
            {
                RDB_CONTACT_POINT_t* cp = ( RDB_CONTACT_POINT_t* ) scanPtr;
                
                useElement = ( cp->playerId == ownId );
            }
            break;
            
            case RDB_PKG_ID_ENVIRONMENT:
                useElement = 1;
            break;

            case RDB_PKG_ID_DRIVER_CTRL:
            {
                RDB_DRIVER_CTRL_t* ctrl = ( RDB_DRIVER_CTRL_t* ) scanPtr;
                
                useElement = ( ctrl->playerId == ownId );
            }
            break;
        }
        
        if ( useElement )
        {
            memcpy( tgtPtr, scanPtr, elSize );
            tgtPtr += elSize;
            maxElements--;
            usedElements++;
        }
        
        if ( maxElements )
            scanPtr += elSize;
    }
        
    return usedElements;
}
