/* ===================================================
 *  file:       RDBHandler.hh
 * ---------------------------------------------------
 *  purpose:	collection of RDB routines
 * ---------------------------------------------------
 *  first edit:	24.01.2012 by M. Dupuis @ VIRES GmbH
 * ===================================================
 */
#ifndef _FRAMEWORK_RDB_HANDLER_HH
#define _FRAMEWORK_RDB_HANDLER_HH

/* ====== INCLUSIONS ====== */
#include <string>
#include <vector>
#include <TC_VtdFramework/viRDBIcd.h>

namespace Framework
{
class RDBHandler 
{
    public:
        /**
        * convert a package ID to the corresponding element size
        * @param  pkgId          id of the package whose size is to be determined
        * @param  extended       true if the size of the extended package is to be determined
        * @return size of the package
        */
        static size_t pkgId2size( unsigned int pkgId, bool extended = false );

        /**
        * convert a package ID to the corresponding name
        * @param  pkgId          id of the package whose name is to be determined
        * @return name of the package
        */
        static std::string pkgId2string( unsigned int pkgId );
        
        /**
        * convert a coord type to the corresponding name
        * @param  type          id of the coordinate type whose name is to be determined
        * @return name of the package
        */
        static std::string coordType2string( unsigned int type );
        
        /**
        * convert an object category into a string
        * @param  id          id of the category
        * @return name of the category
        */
        static std::string objectCategory2string( unsigned int id );
        
        /**
        * convert an object category string into the numeric category
        * @param  name    name of the category 
        * @return id of the category
        */
        static unsigned int objectString2category( const std::string & name );
        
        /**
        * convert an object type into a string
        * @param  id          id of the type
        * @return name of the type
        */
        static std::string objectType2string( unsigned int id );
        
        /**
        * convert an object type string into the numeric type
        * @param  name    name of the type 
        * @return id of the type
        */
        static unsigned int objectString2type( const std::string & name );
        
        /**
        * print the contents of an RDB message
        * @param msg       pointer to the message which is to be printed; 0 for current internal message
        * @param details   if true, print the details, not only the headers
        * @param binDump   create a binary dump of the message
        * @param csv       print CSV version of the message
        * @param csvHeader print CSV header information only
        */
        static void printMessage( RDB_MSG_t* msg = 0, bool details = false, bool binDump = false, bool csv = false, bool csvHeader = false );

        /**
        * print the contents of an RDB message entry
        * @param entryHdr pointer to the entry header whose contents are to be printed
        * @param details  if true, print the details, not only the headers
        * @param csv       print CSV version of the entry
        * @param csvHeader print CSV header information only
        */
        static void printMessageEntry( RDB_MSG_ENTRY_HDR_t* entryHdr, bool details = false, bool csv = false, bool csvHeader = false );

        /**
        * print the contents of a single element of an RDB message entry
        * @param entryHdr  pointer to the entry header belonging to the element
        * @param dataPtr   pointer to the element's content
        * @param ident     number of identation blanks to be used for printing
        * @param csv       print CSV version of the entry
        * @param csvHeader print CSV header information only
        * @return true if element was printed
        */
        static bool printMessageEntryElement( RDB_MSG_ENTRY_HDR_t* entryHdr, void* dataPtr, unsigned char ident = 0, bool csv = false, bool csvHeader = false );

        /**
        * retrieve the primary numberic ID field of an element (to be used for filtering etc.)
        * @param elementType     numeric identifier of the element type
        * @param element         pointer to the element itself
        * @param[OUT] primaryId  the primary ID that has been retrieved
        * @return true if primary element ID could be retrieved
        */
        static bool retrievePrimaryId( unsigned short elementType, void* element, unsigned int & primaryId );

        /**
        * add a packet or series of packets to an RDB message
        * @param  msg            pointer to the message that is to be extended / composed (0 for new message); may be altered!
        * @param  simTime        simulation time for which to compose the package
        * @param  simFrame       simulation frame for which to compose the package
        * @param  pkgId          id of the package that is to be added to the message 
        * @param  noElements     number of elements of given package ID type that are to be added
        * @param  extended       true if an extended element is to be inserted
        * @param  trailingData   size of trailing data of each element
        * @param  isCustom       if true, message is considered a custom message and size per element will be derived from argument "trailingData"
        * @return pointer where to start inserting the data, otherwise 0; message pointer may be altered!
        */
        static void* addPackage( RDB_MSG_t* & msg,   const double & simTime, const unsigned int & simFrame, 
                                 unsigned int pkgId, unsigned int noElements, bool extended, size_t trailingData, bool isCustom = false );
                
        /**
        * add a custom packet or series of packets to an RDB message
        * @param  msg            pointer to the message that is to be extended / composed (0 for new message); may be altered!
        * @param  simTime        simulation time for which to compose the package
        * @param  simFrame       simulation frame for which to compose the package
        * @param  pkgId          id of the package that is to be added to the message 
        * @param  noElements     number of elements of given package ID type that are to be added
        * @param  elementSize    data size of each element
        * @return pointer where to start inserting the data, otherwise 0; message pointer may be altered!
        */
        static void* addCustomPackage( RDB_MSG_t* & msg, const double & simTime, const unsigned int & simFrame, 
                                       unsigned int pkgId, unsigned int noElements, size_t elementSize );
                
        /**
        * retrieve the pointer to the first entry of a given type from a given message
        * @param  msg            pointer to the message that is to be searched for the entry
        * @param  pkgId          id (i.e. type) of the entry that is to be retrieved 
        * @param  noElements     number of elements of given entry type that have been found (will be altered)
        * @param  extended       true if an extended element is to be retrieved
        * @return pointer to first element of the requested entry type or 0 if none has been found.
        */
        static void* getFirstEntry( const RDB_MSG_t* msg, unsigned int pkgId, unsigned int & noElements, bool extended );

        /**
        * retrieve the pointer to the first entry header of a given type from a given message
        * @param  msg            pointer to the message that is to be searched for the entry
        * @param  pkgId          id (i.e. type) of the entry that is to be retrieved 
        * @param  extended       true if an extended element is to be retrieved
        * @return pointer to first entry header of the requested entry type or 0 if none has been found.
        */
        static RDB_MSG_ENTRY_HDR_t* getEntryHdr( const RDB_MSG_t* msg, unsigned int pkgId, bool extended );

        /**
        * create an ident string of given length
        * @param ident number of spaces to use for identing
        * @return pointer to ident character string
        */
        static char* getIdentString( unsigned char ident );
                
        /**
        * print a geometry info
        * @param info      the info which is to be printed
        * @param ident     number of spaces to use for identing
        * @param csv       print CSV version of the data
        * @param csvHeader print CSV header information only
        */
        static void print( const RDB_GEOMETRY_t & info, unsigned char ident = 0, bool csv = false, bool csvHeader = false );
                
        /**
        * print a coordinate system
        * @param info      the info which is to be printed
        * @param ident     number of spaces to use for identing
        * @param csv       print CSV version of the data
        * @param csvHeader print CSV header information only
        */
        static void print( const RDB_COORD_SYSTEM_t & state, unsigned char ident = 0, bool csv = false, bool csvHeader = false );
                
        /**
        * print a co-ordinate
        * @param info      the info which is to be printed
        * @param ident     number of spaces to use for identing
        * @param csv       print CSV version of the data
        * @param csvHeader print CSV header information only
        */
        static void print( const RDB_COORD_t & info, unsigned char ident = 0, bool csv = false, bool csvHeader = false );
                
        /**
        * print the whole bunch of road information
        * @param info      reference to the road information
        * @param ident     number of spaces to use for identing
        * @param csv       print CSV version of the data
        * @param csvHeader print CSV header information only
        */
        static void print( const RDB_ROAD_POS_t & info, unsigned char ident = 0, bool csv = false, bool csvHeader = false );
        
        /**
        * print information about lanes
        * @param info      reference to the lane information
        * @param ident     number of spaces to use for identing
        * @param csv       print CSV version of the data
        * @param csvHeader print CSV header information only
        */
        static void print( const RDB_LANE_INFO_t & info, unsigned char ident = 0, bool csv = false, bool csvHeader = false );
        
        /**
        * print the whole bunch of road mark information
        * @param info      reference to the road mark information
        * @param ident     number of spaces to use for identing
        * @param csv       print CSV version of the data
        * @param csvHeader print CSV header information only
        */
        static void print( const RDB_ROADMARK_t & info, unsigned char ident = 0, bool csv = false, bool csvHeader = false );
        
        /**
        * print an object configuration
        * @param info      the configuration which is to be printed
        * @param ident     number of spaces to use for identing
        * @param csv       print CSV version of the data
        * @param csvHeader print CSV header information only
        */
        static void print( const RDB_OBJECT_CFG_t & info, unsigned char ident = 0, bool csv = false, bool csvHeader = false );
                
        /**
        * print an object state
        * @param state     the state which is to be printed
        * @param extended  true if extened object state is to be printed
        * @param ident     number of spaces to use for identing
        * @param csv       print CSV version of the data
        * @param csvHeader print CSV header information only
        */
        static void print( const RDB_OBJECT_STATE_t & state, bool extended = false, unsigned char ident = 0, bool csv = false, bool csvHeader = false );
                
        /**
        * print information about vehicle systems
        * @param info      reference to the data object
        * @param ident     number of spaces to use for identing
        * @param csv       print CSV version of the data
        * @param csvHeader print CSV header information only
        */
        static void print( const RDB_VEHICLE_SYSTEMS_t & info, unsigned char ident = 0, bool csv = false, bool csvHeader = false );
        
        /**
        * print a vehicle's setup
        * @param info      the info which is to be printed
        * @param ident     number of spaces to use for identing
        * @param csv       print CSV version of the data
        * @param csvHeader print CSV header information only
        */
        static void print( const RDB_VEHICLE_SETUP_t & info, unsigned char ident = 0, bool csv = false, bool csvHeader = false );
                
        /**
        * print engine information
        * @param info      the info which is to be printed
        * @param extended  true if extened object state is to be printed
        * @param ident     number of spaces to use for identing
        * @param csv       print CSV version of the data
        * @param csvHeader print CSV header information only
        */
        static void print( const RDB_ENGINE_t & info, bool extended = false, unsigned char ident = 0, bool csv = false, bool csvHeader = false );
                
        /**
        * print drivetrain information
        * @param info      the info which is to be printed
        * @param extended  true if extened object state is to be printed
        * @param ident     number of spaces to use for identing
        * @param csv       print CSV version of the data
        * @param csvHeader print CSV header information only
        */
        static void print( const RDB_DRIVETRAIN_t & info, bool extended = false, unsigned char ident = 0, bool csv = false, bool csvHeader = false );
                
        /**
        * print wheel information
        * @param info      the info which is to be printed
        * @param extended  true if extened object state is to be printed
        * @param ident     number of spaces to use for identing
        * @param csv       print CSV version of the data
        * @param csvHeader print CSV header information only
        */
        static void print( const RDB_WHEEL_t & info, bool extended = false, unsigned char ident = 0, bool csv = false, bool csvHeader = false );
                
        /**
        * print pedestrian animation information
        * @param info      the info which is to be printed
        * @param ident     number of spaces to use for identing
        * @param csv       print CSV version of the data
        * @param csvHeader print CSV header information only
        */
        static void print( const RDB_PED_ANIMATION_t & info, unsigned char ident = 0, bool csv = false, bool csvHeader = false );
                
        /**
        * print information about a sensor
        * @param info  reference to the sensor state
        * @param ident number of spaces to use for identing
        * @param csv       print CSV version of the data
        * @param csvHeader print CSV header information only
        */
        static void print( const RDB_SENSOR_STATE_t & info, unsigned char ident = 0, bool csv = false, bool csvHeader = false );
        
        /**
        * print information about sensor objects
        * @param info      reference to the sensor object
        * @param ident     number of spaces to use for identing
        * @param csv       print CSV version of the data
        * @param csvHeader print CSV header information only
        */
        static void print( const RDB_SENSOR_OBJECT_t & info, unsigned char ident = 0, bool csv = false, bool csvHeader = false );
        
        /**
        * print the whole bunch of camera information
        * @param info  reference to the camera information
        * @param ident number of spaces to use for identing
        * @param csv       print CSV version of the data
        * @param csvHeader print CSV header information only
        */
        static void print( const RDB_CAMERA_t & info, unsigned char ident = 0, bool csv = false, bool csvHeader = false );
        
        /**
        * print the whole bunch of contact point information
        * @param info      reference to the contact point information
        * @param ident     number of spaces to use for identing
        * @param csv       print CSV version of the data
        * @param csvHeader print CSV header information only
        */
        static void print( const RDB_CONTACT_POINT_t & info, unsigned char ident = 0, bool csv = false, bool csvHeader = false );
        
        /**
        * print information about a single traffic sign
        * @param info      reference to the traffic sign's information
        * @param ident     number of spaces to use for identing
        * @param csv       print CSV version of the data
        * @param csvHeader print CSV header information only
        */
        static void print( const RDB_TRAFFIC_SIGN_t & info, unsigned char ident = 0, bool csv = false, bool csvHeader = false );
        
        /**
        * print information about a single road state
        * @param info      reference to the road state's information
        * @param ident     number of spaces to use for identing
        * @param csv       print CSV version of the data
        * @param csvHeader print CSV header information only
        */
        static void print( const RDB_ROAD_STATE_t & info, unsigned char ident = 0, bool csv = false, bool csvHeader = false );
        
        /**
        * print information about an image data block
        * @param info      reference to the data object
        * @param ident     number of spaces to use for identing
        * @param csv       print CSV version of the data
        * @param csvHeader print CSV header information only
        */
        static void print( const RDB_IMAGE_t & info, unsigned char ident = 0, bool csv = false, bool csvHeader = false );
        
        /**
        * print information about an light source
        * @param info  reference to the data object
        * @param ident number of spaces to use for identing
        * @param csv       print CSV version of the data
        * @param csvHeader print CSV header information only
        */
        static void print( const RDB_LIGHT_SOURCE_t & info, bool extended = false, unsigned char ident = 0, bool csv = false, bool csvHeader = false );
        
        /**
        * print information about environment package
        * @param info      reference to the information
        * @param ident     number of spaces to use for identing
        * @param csv       print CSV version of the data
        * @param csvHeader print CSV header information only
        */
        static void print( const RDB_ENVIRONMENT_t & info, unsigned char ident = 0, bool csv = false, bool csvHeader = false );
        
        /**
        * print information about trigger package
        * @param info      reference to the information
        * @param ident     number of spaces to use for identing
        * @param csv       print CSV version of the data
        * @param csvHeader print CSV header information only
        */
        static void print( const RDB_TRIGGER_t & info, unsigned char ident = 0, bool csv = false, bool csvHeader = false );
        
        /**
        * print information about driver controls
        * @param info      reference to the driver control information
        * @param ident     number of spaces to use for identing
        * @param csv       print CSV version of the data
        * @param csvHeader print CSV header information only
        */
        static void print( const RDB_DRIVER_CTRL_t & info, unsigned char ident = 0, bool csv = false, bool csvHeader = false );

        /**
        * print information about a single traffic light
        * @param info      reference to the traffic light's information
        * @param extended  if true, print extended state
        * @param ident     number of spaces to use for identing
        * @param csv       print CSV version of the data
        * @param csvHeader print CSV header information only
        */
        static void print( const RDB_TRAFFIC_LIGHT_t & info, bool extended = false, unsigned char ident = 0, bool csv = false, bool csvHeader = false );
        
        /**
        * print information about sync package
        * @param info      reference to the information
        * @param ident     number of spaces to use for identing
        * @param csv       print CSV version of the data
        * @param csvHeader print CSV header information only
        */
        static void print( const RDB_SYNC_t & info, unsigned char ident = 0, bool csv = false, bool csvHeader = false );
        
        /**
        * print information about driver perception package
        * @param info      reference to the information
        * @param ident     number of spaces to use for identing
        * @param csv       print CSV version of the data
        * @param csvHeader print CSV header information only
        */
        static void print( const RDB_DRIVER_PERCEPTION_t & info, unsigned char ident = 0, bool csv = false, bool csvHeader = false );
        
        /**
        * print information about tone mapping package
        * @param info      reference to the information
        * @param ident     number of spaces to use for identing
        * @param csv       print CSV version of the data
        * @param csvHeader print CSV header information only
        */
        static void print( const RDB_FUNCTION_t & info, unsigned char ident = 0, bool csv = false, bool csvHeader = false );
        
        /**
        * print information about road query package
        * @param info      reference to the information
        * @param ident     number of spaces to use for identing
        * @param csv       print CSV version of the data
        * @param csvHeader print CSV header information only
        */
        static void print( const RDB_ROAD_QUERY_t & info, unsigned char ident = 0, bool csv = false, bool csvHeader = false );
        
        /**
        * print point information
        * @param info      reference to the information
        * @param ident     number of spaces to use for identing
        * @param csv       print CSV version of the data
        * @param csvHeader print CSV header information only
        */
        static void print( const RDB_POINT_t & info, unsigned char ident = 0, bool csv = false, bool csvHeader = false );

        /**
        * print a trajectory information
        * @param info      reference to the trajectory information
        * @param ident     number of spaces to use for identing
        * @param csv       print CSV version of the data
        * @param csvHeader print CSV header information only
        */
        static void print( const RDB_TRAJECTORY_t & info, unsigned char ident = 0, bool csv = false, bool csvHeader = false );

        /**
        * print an information from dynamics to steering
        * @param info      reference to the information
        * @param ident     number of spaces to use for identing
        * @param csv       print CSV version of the data
        * @param csvHeader print CSV header information only
        */
        static void print( const RDB_DYN_2_STEER_t & info, unsigned char ident = 0, bool csv = false, bool csvHeader = false );

        /**
        * print an information from steering to dynamics
        * @param info      reference to the information
        * @param ident     number of spaces to use for identing
        * @param csv       print CSV version of the data
        * @param csvHeader print CSV header information only
        */
        static void print( const RDB_STEER_2_DYN_t & info, unsigned char ident = 0, bool csv = false, bool csvHeader = false );

        /**
        * print a proxy information
        * @param info      reference to the information
        * @param ident     number of spaces to use for identing
        * @param csv       print CSV version of the data
        * @param csvHeader print CSV header information only
        */
        static void print( const RDB_PROXY_t & info, unsigned char ident = 0, bool csv = false, bool csvHeader = false );
        
        /**
        * print a motion system information
        * @param info      reference to the information
        * @param ident     number of spaces to use for identing
        * @param csv       print CSV version of the data
        * @param csvHeader print CSV header information only
        */
        static void print( const RDB_MOTION_SYSTEM_t & info, unsigned char ident = 0, bool csv = false, bool csvHeader = false );
        
        /**
        * print a scoring information
        * @param info      reference to the information
        * @param ident     number of spaces to use for identing
        * @param csv       print CSV version of the data
        * @param csvHeader print CSV header information only
        */
        static void print( const RDB_CUSTOM_SCORING_t & info, unsigned char ident = 0, bool csv = false, bool csvHeader = false );
        
        /**
        * print a track control information
        * @param info      reference to the information
        * @param ident     number of spaces to use for identing
        * @param csv       print CSV version of the data
        * @param csvHeader print CSV header information only
        */
        static void print( const RDB_CUSTOM_OBJECT_CTRL_TRACK_t & info, unsigned char ident = 0, bool csv = false, bool csvHeader = false );
        
        /**
        * print an SCP information
        * @param info      reference to the information
        * @param ident     number of spaces to use for identing
        * @param csv       print CSV version of the data
        * @param csvHeader print CSV header information only
        */
        static void print( const RDB_SCP_t & info, unsigned char ident = 0, bool csv = false, bool csvHeader = false );
        
        /**
        * print the a FREESPACE information
        * @param info      reference to the information
        * @param ident     number of spaces to use for identing
        * @param csv       print CSV version of the data
        * @param csvHeader print CSV header information only
        */
        static void print( const RDB_FREESPACE_t & info, unsigned char ident = 0, bool csv = false, bool csvHeader = false );
        
        /**
        * print a DYN_EL_SWITCH information
        * @param info      reference to the information
        * @param ident     number of spaces to use for identing
        * @param csv       print CSV version of the data
        * @param csvHeader print CSV header information only
        */
        static void print( const RDB_DYN_EL_SWITCH_t & info, unsigned char ident = 0, bool csv = false, bool csvHeader = false );
        
        /**
        * print a DYN_EL_DOF information
        * @param info      reference to the information
        * @param ident     number of spaces to use for identing
        * @param csv       print CSV version of the data
        * @param csvHeader print CSV header information only
        */
        static void print( const RDB_DYN_EL_DOF_t & info, unsigned char ident = 0, bool csv = false, bool csvHeader = false );
        
        /**
        * print an IG_FRAME information
        * @param info      reference to the information
        * @param ident     number of spaces to use for identing
        * @param csv       print CSV version of the data
        * @param csvHeader print CSV header information only
        */
        static void print( const RDB_IG_FRAME_t & info, unsigned char ident = 0, bool csv = false, bool csvHeader = false );
        
        /**
        * print the real-time performance information
        * @param info      reference to the information
        * @param ident     number of spaces to use for identing
        * @param csv       print CSV version of the data
        * @param csvHeader print CSV header information only
        */
        static void print( const RDB_RT_PERFORMANCE_t & info, unsigned char ident = 0, bool csv = false, bool csvHeader = false );
        
        /**
        * print information about a matrix
        * @param pData     pointer to the data structure
        * @param width     width of the matrix
        * @param height    height of the matrix
        * @param csv       print CSV version of the data
        * @param csvHeader print CSV header information only
        */
        static void printMatrix( int *pData, unsigned int width, unsigned int height, bool csv = false, bool csvHeader = false );
        
        /**
        * print information about a ray-tracing ray
        * @param info      reference to the information
        * @param ident     number of spaces to use for identing
        * @param csv       print CSV version of the data
        * @param csvHeader print CSV header information only
        */
        static void print( const RDB_RAY_t & info, unsigned char ident = 0, bool csv = false, bool csvHeader = false );
        
        /**
        * print information about a symbol state
        * @param info      reference to the information
        * @param ident     number of spaces to use for identing
        * @param csv       print CSV version of the data
        * @param csvHeader print CSV header information only
        */
        static void print( const RDB_SYMBOL_STATE_t & info, unsigned char ident = 0, bool csv = false, bool csvHeader = false );

        /**
        * print information about a radar hit point
        * @param info      reference to the information
        * @param ident     number of spaces to use for identing
        * @param csv       print CSV version of the data
        * @param csvHeader print CSV header information only
        */
        static void print( const RDB_RADAR_HIT_POINT_t & info, unsigned char ident = 0, bool csv = false, bool csvHeader = false );
        
    public:
        /**
        * constructor
        */
        explicit RDBHandler();

        /**
        * Destroy the class. 
        */
        virtual ~RDBHandler();
        
        /**
        * (re-) initialize the RDB message, i.e. internally held data
        */
        void initMsg();
        
        /**
        * add a packet or series of packets to an RDB message
        * @param  simTime        simulation time for which to compose the package
        * @param  simFrmae       simulation frame for which to compose the package
        * @param  pkgId          id of the package that is to be added to the message 
        * @param  noElements     number of elements of given package ID type that are to be added
        * @param  extended       true if an extended element is to be inserted
        * @param  trailingData   size of trailing data of each element
        * @param  isCustom       if true, package is considered a custom package and size per element will be derived from argument "trailingData"
        * @return pointer where to start inserting the data, otherwise 0
        */
        void* addPackage( const double & simTime, const unsigned int & simFrame, 
                          unsigned int pkgId, unsigned int noElements = 1, bool extended = false, 
                          size_t trailingData = 0, bool isCustom = false );
        
        /**
        * add a custom packet or series of packets to an RDB message
        * @param  simTime        simulation time for which to compose the package
        * @param  simFrmae       simulation frame for which to compose the package
        * @param  pkgId          id of the package that is to be added to the message 
        * @param  noElements     number of elements of given package ID type that are to be added
        * @param  elementSize    size of each element [byte]
        * @return pointer where to start inserting the data, otherwise 0
        */
        void* addCustomPackage( const double & simTime, const unsigned int & simFrame, 
                                unsigned int pkgId, unsigned int noElements = 1, size_t elementSize = 0 );
        
        /**
        * get a pointer to the message that is currently being composed
        * @return pointer to current RDB message
        */
        RDB_MSG_t* getMsg();
       
        /**
        * get a pointer to the message header that is currently being composed
        * @return pointer to current RDB message header
        */
        RDB_MSG_HDR_t* getMsgHdr();
        
        /**
        * get the total size of the current message
        * @return total size of the message which is currently being composed
        */
        size_t getMsgTotalSize();
        
        /**
        * retrieve the pointer to the first entry of a given type from the internally held message
        * @param  pkgId          id (i.e. type) of the entry that is to be retrieved 
        * @param  noElements     number of elements of given entry type that have been found (will be altered)
        * @param  extended       true if an extended element is to be retrieved
        * @return pointer to first element of the requested entry type or 0 if none has been found.
        */
        void* getFirstEntry( unsigned int pkgId, unsigned int & noElements, bool extended );

        /**
        * retrieve the pointer to the first entry header of a given type from the internally held message
        * @param  pkgId          id (i.e. type) of the entry that is to be retrieved 
        * @param  extended       true if an extended element is to be retrieved
        * @return pointer to first entry header of the requested entry type or 0 if none has been found.
        */
        RDB_MSG_ENTRY_HDR_t* getEntryHdr( unsigned int pkgId, bool extended );

        /**
        * configure a shared memory segment for the use with RDB
        * @param startPtr   pointer to the start of the shared memory segment
        * @param noBuffers  number of buffers which are to be placed within the segment
        * @param totalSize  total size of SHM segment
        * @return true if successful
        */
        bool shmConfigure( void *startPtr, unsigned int noBuffers, unsigned int totalSize = 0 );
            
        /**
        * set the shared memory pointer
        * @param shmAddr address of the shared memory segment
        * @return true if successful
        */
        bool shmSetAddress( void* shmAddr );
            
        /**
        * get the pointer to the shared memory header
        */
        RDB_SHM_HDR_t* shmGetHdr();
            
        /**
        * get the pointer to a shared memory buffer's info segment
        * @param index  index of the buffer
        * @return pointer to the info segment of the respective shared memory buffer
        */
        RDB_SHM_BUFFER_INFO_t* shmBufferGetInfo( unsigned int index );
        
        /**
        * get the pointer to a shared memory buffer's data segment
        * @param index  index of the buffer
        * @return pointer to the data segment of the respective shared memory buffer
        */
        void* shmBufferGetPtr( unsigned int index );
        
        /**
        * update the header information of the shared memory according to buffer data
        */
        void shmHdrUpdate();
                
        /**
        * set the size of a shared memory buffer's data segment
        * @param index  index of the buffer
        * @param size   size of the buffer's data segment
        */
        void shmBufferSetSize( unsigned int index, size_t size );
                
        /**
        * get the size of a shared memory buffer's data segment
        * @param index  index of the buffer
        */
        size_t shmBufferGetSize( unsigned int index );
                
        /**
        * set the id of a shared memory buffer
        * @param index  index of the buffer
        * @param id   id of the buffer
        */
        void shmBufferSetId( unsigned int index, unsigned int id );
                
        /**
        * set the flags of a shared memory buffer
        * @param index  index of the buffer
        * @param flags   flags of the buffer
        */
        void shmBufferSetFlags( unsigned int index, unsigned int flags );
        
        /**
        * add the flags of a shared memory buffer
        * @param index  index of the buffer
        * @param flags   flags of the buffer
        */
        void shmBufferAddFlags( unsigned int index, unsigned int flags );
        
        /**
        * release the flags of a shared memory buffer
        * @param index  index of the buffer
        * @param flags   flags of the buffer
        */
        void shmBufferReleaseFlags( unsigned int index, unsigned int flags );
        
        /**
        * get the flags of a shared memory buffer
        * @param index  index of the buffer
        * @return  flags of the buffer
        */
        unsigned int shmBufferGetFlags( unsigned int index );
        
        /**
        * check the flags of a shared memory buffer for a given mask
        * @param index  index of the buffer
        * @param mask   mask against which to check
        * @return true if mask is contained in shm flags
        */
        bool shmBufferHasFlags( unsigned int index, unsigned int mask );
        
        /**
        * copy the current message to the shared memory, replacing existing data
        * @param index  index of the buffer to which the message shall be copied
        * @param relocateBuffers  if true, buffer locations (i.e. offsets) will be adjusted to size of copied data; this requires buffers to be filled sequentially!
        * @return true if successful
        */
        bool mapMsgToShm( unsigned int index, bool relocateBuffers = true );
        
        /**
        * add a message to the shared memory, extending existing data
        * @param index  index of the buffer to which the message shall be copied
        * @param msg    pointer to the message that is to be transferred to SHM
        * @return true if successful
        */
        bool addMsgToShm( unsigned int index, RDB_MSG_t* msg );
        
        /**
        * get the usage of an SHM buffer
        * @param index  index of the buffer which shall be queried
        * @return number of bytes occupied in the buffer
        */
        unsigned int shmBufferGetUsedSize( unsigned int index );
        
        /**
        * clear the given SHM buffer
        * @param index  index of the buffer to which is to be cleared
        * @param force  force clearing of locked buffers
        * @return true if successful
        */
        bool shmBufferClear( unsigned int index, bool force = false );
        
        /**
        * check if a given SHM buffer is locked
        * @param index  index of the buffer to which is to be checked
        * @return true if buffer is locked
        */
        bool shmBufferIsLocked( unsigned int index );
        
        /**
        * lock a given SHM buffer 
        * @param index  index of the buffer to which is to be locked
        * @return true if buffer could be locked
        */
        bool shmBufferLock( unsigned int index );
        
        /**
        * release the lock of a given SHM buffer 
        * @param index  index of the buffer to which is to be released
        * @return true if buffer could be released
        */
        bool shmBufferRelease( unsigned int index );
        
        /**
        * get the number of buffers in the SHM segment
        * @return number of buffers in SHM segment
        */
        unsigned int shmGetNoBuffers();
        
        /**
        * print sizes of all structures
        */
        void printPackageSizes();
        
        /**
        * parse an RDB message
        * @param msg      pointer to the message which is to be parsed;
        */
        virtual void parseMessage( RDB_MSG_t* msg );
        
        /**
        * parse an RDB message entry
        * @param entry      pointer to the message entry which is to be parsed;
        * @param simTime    simulation time of the message
        * @param simFrame   simulation frame of the message
        */
        virtual void parseMessageEntry( RDB_MSG_ENTRY_HDR_t* entryHdr, const double & simTime, const unsigned int & simFrame );
        
    protected:
        /**
        * parse the information of a message entry
        * @param simTime    simulation time of the message
        * @param simFrame   simulation frame of the message
        * @param pkgId      id of the package
        * @param flags      flags of the message entry (e.g. EXTENDED message entry)
        * @param elemId     id (index) of the current element in the vector of elements of this specific type as contained in the message
        * @param totalElem  total number of elements in the vector of this specific type as contained in the message
        */
        virtual void parseMessageEntryInfo( const double & simTime, const unsigned int & simFrame, const unsigned short & pkgId, const unsigned short & flags, const unsigned int & elemId, const unsigned int & totalElem );
        
        /**
        * parse routines for the frame limits
        * @param simTime    simulation time of the message
        * @param simFrame   simulation frame of the message
        */
        virtual void parseStartOfFrame( const double & simTime, const unsigned int & simFrame );
        virtual void parseEndOfFrame(   const double & simTime, const unsigned int & simFrame );
        
        /**
        * parse routines for the various message types
        * @param msg        pointer to the message which is to be parsed;
        * @param data       pointer to the entry data that is to be parsed
        * @param simTime    simulation time of the message
        * @param simFrame   simulation frame of the message
        * @param pkgId      id of the package
        * @param flags      flags of the message entry (e.g. EXTENDED message entry)
        * @param elemId     id (index) of the current element in the vector of elements of this specific type as contained in the message
        * @param totalElem  total number of elements in the vector of this specific type as contained in the message
        */
        virtual void parseEntry( RDB_GEOMETRY_t *                 data, const double & simTime, const unsigned int & simFrame, const unsigned short & pkgId, const unsigned short & flags, const unsigned int & elemId, const unsigned int & totalElem );
        virtual void parseEntry( RDB_COORD_SYSTEM_t *             data, const double & simTime, const unsigned int & simFrame, const unsigned short & pkgId, const unsigned short & flags, const unsigned int & elemId, const unsigned int & totalElem );
        virtual void parseEntry( RDB_COORD_t *                    data, const double & simTime, const unsigned int & simFrame, const unsigned short & pkgId, const unsigned short & flags, const unsigned int & elemId, const unsigned int & totalElem );
        virtual void parseEntry( RDB_ROAD_POS_t *                 data, const double & simTime, const unsigned int & simFrame, const unsigned short & pkgId, const unsigned short & flags, const unsigned int & elemId, const unsigned int & totalElem );
        virtual void parseEntry( RDB_LANE_INFO_t *                data, const double & simTime, const unsigned int & simFrame, const unsigned short & pkgId, const unsigned short & flags, const unsigned int & elemId, const unsigned int & totalElem );
        virtual void parseEntry( RDB_ROADMARK_t *                 data, const double & simTime, const unsigned int & simFrame, const unsigned short & pkgId, const unsigned short & flags, const unsigned int & elemId, const unsigned int & totalElem );
        virtual void parseEntry( RDB_OBJECT_CFG_t *               data, const double & simTime, const unsigned int & simFrame, const unsigned short & pkgId, const unsigned short & flags, const unsigned int & elemId, const unsigned int & totalElem );
        virtual void parseEntry( RDB_OBJECT_STATE_t *             data, const double & simTime, const unsigned int & simFrame, const unsigned short & pkgId, const unsigned short & flags, const unsigned int & elemId, const unsigned int & totalElem );
        virtual void parseEntry( RDB_VEHICLE_SYSTEMS_t *          data, const double & simTime, const unsigned int & simFrame, const unsigned short & pkgId, const unsigned short & flags, const unsigned int & elemId, const unsigned int & totalElem );
        virtual void parseEntry( RDB_VEHICLE_SETUP_t *            data, const double & simTime, const unsigned int & simFrame, const unsigned short & pkgId, const unsigned short & flags, const unsigned int & elemId, const unsigned int & totalElem );
        virtual void parseEntry( RDB_ENGINE_t *                   data, const double & simTime, const unsigned int & simFrame, const unsigned short & pkgId, const unsigned short & flags, const unsigned int & elemId, const unsigned int & totalElem );
        virtual void parseEntry( RDB_DRIVETRAIN_t *               data, const double & simTime, const unsigned int & simFrame, const unsigned short & pkgId, const unsigned short & flags, const unsigned int & elemId, const unsigned int & totalElem );
        virtual void parseEntry( RDB_WHEEL_t *                    data, const double & simTime, const unsigned int & simFrame, const unsigned short & pkgId, const unsigned short & flags, const unsigned int & elemId, const unsigned int & totalElem );
        virtual void parseEntry( RDB_PED_ANIMATION_t *            data, const double & simTime, const unsigned int & simFrame, const unsigned short & pkgId, const unsigned short & flags, const unsigned int & elemId, const unsigned int & totalElem );
        virtual void parseEntry( RDB_SENSOR_STATE_t *             data, const double & simTime, const unsigned int & simFrame, const unsigned short & pkgId, const unsigned short & flags, const unsigned int & elemId, const unsigned int & totalElem );
        virtual void parseEntry( RDB_SENSOR_OBJECT_t *            data, const double & simTime, const unsigned int & simFrame, const unsigned short & pkgId, const unsigned short & flags, const unsigned int & elemId, const unsigned int & totalElem );
        virtual void parseEntry( RDB_CAMERA_t *                   data, const double & simTime, const unsigned int & simFrame, const unsigned short & pkgId, const unsigned short & flags, const unsigned int & elemId, const unsigned int & totalElem );
        virtual void parseEntry( RDB_CONTACT_POINT_t *            data, const double & simTime, const unsigned int & simFrame, const unsigned short & pkgId, const unsigned short & flags, const unsigned int & elemId, const unsigned int & totalElem );
        virtual void parseEntry( RDB_TRAFFIC_SIGN_t *             data, const double & simTime, const unsigned int & simFrame, const unsigned short & pkgId, const unsigned short & flags, const unsigned int & elemId, const unsigned int & totalElem );
        virtual void parseEntry( RDB_ROAD_STATE_t *               data, const double & simTime, const unsigned int & simFrame, const unsigned short & pkgId, const unsigned short & flags, const unsigned int & elemId, const unsigned int & totalElem );
        virtual void parseEntry( RDB_IMAGE_t *                    data, const double & simTime, const unsigned int & simFrame, const unsigned short & pkgId, const unsigned short & flags, const unsigned int & elemId, const unsigned int & totalElem );
        virtual void parseEntry( RDB_LIGHT_SOURCE_t *             data, const double & simTime, const unsigned int & simFrame, const unsigned short & pkgId, const unsigned short & flags, const unsigned int & elemId, const unsigned int & totalElem );
        virtual void parseEntry( RDB_ENVIRONMENT_t *              data, const double & simTime, const unsigned int & simFrame, const unsigned short & pkgId, const unsigned short & flags, const unsigned int & elemId, const unsigned int & totalElem );
        virtual void parseEntry( RDB_TRIGGER_t *                  data, const double & simTime, const unsigned int & simFrame, const unsigned short & pkgId, const unsigned short & flags, const unsigned int & elemId, const unsigned int & totalElem );
        virtual void parseEntry( RDB_DRIVER_CTRL_t *              data, const double & simTime, const unsigned int & simFrame, const unsigned short & pkgId, const unsigned short & flags, const unsigned int & elemId, const unsigned int & totalElem );
        virtual void parseEntry( RDB_TRAFFIC_LIGHT_t *            data, const double & simTime, const unsigned int & simFrame, const unsigned short & pkgId, const unsigned short & flags, const unsigned int & elemId, const unsigned int & totalElem );
        virtual void parseEntry( RDB_SYNC_t *                     data, const double & simTime, const unsigned int & simFrame, const unsigned short & pkgId, const unsigned short & flags, const unsigned int & elemId, const unsigned int & totalElem );
        virtual void parseEntry( RDB_DRIVER_PERCEPTION_t *        data, const double & simTime, const unsigned int & simFrame, const unsigned short & pkgId, const unsigned short & flags, const unsigned int & elemId, const unsigned int & totalElem );
        virtual void parseEntry( RDB_FUNCTION_t *                 data, const double & simTime, const unsigned int & simFrame, const unsigned short & pkgId, const unsigned short & flags, const unsigned int & elemId, const unsigned int & totalElem );
        virtual void parseEntry( RDB_ROAD_QUERY_t *               data, const double & simTime, const unsigned int & simFrame, const unsigned short & pkgId, const unsigned short & flags, const unsigned int & elemId, const unsigned int & totalElem );
        virtual void parseEntry( RDB_POINT_t *                    data, const double & simTime, const unsigned int & simFrame, const unsigned short & pkgId, const unsigned short & flags, const unsigned int & elemId, const unsigned int & totalElem );
        virtual void parseEntry( RDB_TRAJECTORY_t *               data, const double & simTime, const unsigned int & simFrame, const unsigned short & pkgId, const unsigned short & flags, const unsigned int & elemId, const unsigned int & totalElem );
        virtual void parseEntry( RDB_CUSTOM_SCORING_t *           data, const double & simTime, const unsigned int & simFrame, const unsigned short & pkgId, const unsigned short & flags, const unsigned int & elemId, const unsigned int & totalElem );
        virtual void parseEntry( RDB_DYN_2_STEER_t *              data, const double & simTime, const unsigned int & simFrame, const unsigned short & pkgId, const unsigned short & flags, const unsigned int & elemId, const unsigned int & totalElem );
        virtual void parseEntry( RDB_SCP_t *                      data, const double & simTime, const unsigned int & simFrame, const unsigned short & pkgId, const unsigned short & flags, const unsigned int & elemId, const unsigned int & totalElem );
        virtual void parseEntry( RDB_STEER_2_DYN_t *              data, const double & simTime, const unsigned int & simFrame, const unsigned short & pkgId, const unsigned short & flags, const unsigned int & elemId, const unsigned int & totalElem );
        virtual void parseEntry( RDB_PROXY_t *                    data, const double & simTime, const unsigned int & simFrame, const unsigned short & pkgId, const unsigned short & flags, const unsigned int & elemId, const unsigned int & totalElem );
        virtual void parseEntry( RDB_MOTION_SYSTEM_t *            data, const double & simTime, const unsigned int & simFrame, const unsigned short & pkgId, const unsigned short & flags, const unsigned int & elemId, const unsigned int & totalElem );
        virtual void parseEntry( RDB_FREESPACE_t *                data, const double & simTime, const unsigned int & simFrame, const unsigned short & pkgId, const unsigned short & flags, const unsigned int & elemId, const unsigned int & totalElem );
        virtual void parseEntry( RDB_DYN_EL_SWITCH_t *            data, const double & simTime, const unsigned int & simFrame, const unsigned short & pkgId, const unsigned short & flags, const unsigned int & elemId, const unsigned int & totalElem );
        virtual void parseEntry( RDB_DYN_EL_DOF_t *               data, const double & simTime, const unsigned int & simFrame, const unsigned short & pkgId, const unsigned short & flags, const unsigned int & elemId, const unsigned int & totalElem );
        virtual void parseEntry( RDB_IG_FRAME_t *                 data, const double & simTime, const unsigned int & simFrame, const unsigned short & pkgId, const unsigned short & flags, const unsigned int & elemId, const unsigned int & totalElem );
        virtual void parseEntry( RDB_RT_PERFORMANCE_t *           data, const double & simTime, const unsigned int & simFrame, const unsigned short & pkgId, const unsigned short & flags, const unsigned int & elemId, const unsigned int & totalElem );
        virtual void parseEntry( RDB_CUSTOM_OBJECT_CTRL_TRACK_t * data, const double & simTime, const unsigned int & simFrame, const unsigned short & pkgId, const unsigned short & flags, const unsigned int & elemId, const unsigned int & totalElem );
        virtual void parseEntry( RDB_RAY_t *                      data, const double & simTime, const unsigned int & simFrame, const unsigned short & pkgId, const unsigned short & flags, const unsigned int & elemId, const unsigned int & totalElem );
        virtual void parseEntry( RDB_SYMBOL_STATE_t *             data, const double & simTime, const unsigned int & simFrame, const unsigned short & pkgId, const unsigned short & flags, const unsigned int & elemId, const unsigned int & totalElem );
        virtual void parseEntry( RDB_RADAR_HIT_POINT_t *          data, const double & simTime, const unsigned int & simFrame, const unsigned short & pkgId, const unsigned short & flags, const unsigned int & elemId, const unsigned int & totalElem );

    private:
        /**
        * the actual RDB message that is composed
        */
        RDB_MSG_t* mMsg;
        
        /**
        * pointer to the start of the shared memory segment
        */
        RDB_SHM_HDR_t* mShmHdr;
};
} // namespace Framework
#endif /* _FRAMEWORK_RDB_HANDLER_HH */
