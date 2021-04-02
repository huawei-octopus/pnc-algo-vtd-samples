/* ===================================================
 *  file:       RDBHandler.cc
 * ---------------------------------------------------
 *  purpose:	collection of RDB routines
 * ---------------------------------------------------
 *  first edit:	24.01.2012 by M. Dupuis @ VIRES GmbH
 *  last mod.:  24.01.2012 by M. Dupuis @ VIRES GmbH
 * ===================================================
 */
/* ====== INCLUSIONS ====== */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "RDBHandler.hh"

namespace Framework 
{
    
size_t
RDBHandler::pkgId2size( unsigned int pkgId, bool extended )
{
    switch( pkgId )
    {
        case RDB_PKG_ID_START_OF_FRAME: 
        case RDB_PKG_ID_END_OF_FRAME:
            return 0;
            
        case RDB_PKG_ID_COORD_SYSTEM:
            return sizeof( RDB_COORD_SYSTEM_t );
            
        case RDB_PKG_ID_COORD:
            return sizeof( RDB_COORD_t );
            
        case RDB_PKG_ID_ROAD_POS:
            return sizeof( RDB_ROAD_POS_t );
            
        case RDB_PKG_ID_LANE_INFO:
            return sizeof( RDB_LANE_INFO_t );
            
        case RDB_PKG_ID_ROADMARK:
            return sizeof( RDB_ROADMARK_t );
            
        case RDB_PKG_ID_OBJECT_CFG:
            return sizeof( RDB_OBJECT_CFG_t );
            
        case RDB_PKG_ID_OBJECT_STATE:
            return ( extended ? sizeof( RDB_OBJECT_STATE_t ) : sizeof ( RDB_OBJECT_STATE_BASE_t ) );
            
        case RDB_PKG_ID_VEHICLE_SYSTEMS:
            return sizeof( RDB_VEHICLE_SYSTEMS_t );
            
        case RDB_PKG_ID_VEHICLE_SETUP:
            return sizeof( RDB_VEHICLE_SETUP_t );
            
        case RDB_PKG_ID_ENGINE:
            return ( extended ? sizeof( RDB_ENGINE_t ) : sizeof( RDB_ENGINE_BASE_t ) );
            
        case RDB_PKG_ID_DRIVETRAIN:
            return ( extended ? sizeof( RDB_DRIVETRAIN_t ) : sizeof( RDB_DRIVETRAIN_BASE_t ) );
            
        case RDB_PKG_ID_WHEEL:
            return ( extended ? sizeof( RDB_WHEEL_t ) : sizeof( RDB_WHEEL_BASE_t ) );
            
        case RDB_PKG_ID_PED_ANIMATION:
            return sizeof( RDB_PED_ANIMATION_t );
            
        case RDB_PKG_ID_SENSOR_STATE:
            return sizeof( RDB_SENSOR_STATE_t );
            
        case RDB_PKG_ID_SENSOR_OBJECT:
            return sizeof( RDB_SENSOR_OBJECT_t );
            
        case RDB_PKG_ID_CAMERA:
            return sizeof( RDB_CAMERA_t );
            
        case RDB_PKG_ID_CONTACT_POINT:
            return sizeof( RDB_CONTACT_POINT_t );
            
        case RDB_PKG_ID_TRAFFIC_SIGN:
            return sizeof( RDB_TRAFFIC_SIGN_t );
            
        case RDB_PKG_ID_ROAD_STATE:
            return sizeof( RDB_ROAD_STATE_t );
            
        case RDB_PKG_ID_IMAGE:
        case RDB_PKG_ID_LIGHT_MAP:
        case RDB_PKG_ID_OCCLUSION_MATRIX:
            return sizeof( RDB_IMAGE_t );
            
        case RDB_PKG_ID_LIGHT_SOURCE:
            return ( extended ? sizeof( RDB_LIGHT_SOURCE_t ) : sizeof( RDB_LIGHT_SOURCE_BASE_t ) );
            
        case RDB_PKG_ID_ENVIRONMENT:
            return sizeof( RDB_ENVIRONMENT_t );
            
        case RDB_PKG_ID_TRIGGER:
            return sizeof( RDB_TRIGGER_t );
            
        case RDB_PKG_ID_DRIVER_CTRL:
            return sizeof( RDB_DRIVER_CTRL_t );
            
        case RDB_PKG_ID_TRAFFIC_LIGHT:
            return ( extended ? sizeof( RDB_TRAFFIC_LIGHT_t ) : sizeof( RDB_TRAFFIC_LIGHT_BASE_t ) );
            
        case RDB_PKG_ID_SYNC:
            return sizeof( RDB_SYNC_t );
            
        case RDB_PKG_ID_DRIVER_PERCEPTION:
            return sizeof( RDB_DRIVER_PERCEPTION_t );
            
        case RDB_PKG_ID_TONE_MAPPING:
            return sizeof( RDB_FUNCTION_t );            
            
        case RDB_PKG_ID_ROAD_QUERY:
            return sizeof( RDB_ROAD_QUERY_t );
            
        case RDB_PKG_ID_SCP:
            return sizeof( RDB_SCP_t );
            
        case RDB_PKG_ID_TRAJECTORY:
            return sizeof( RDB_TRAJECTORY_t );
            
        case RDB_PKG_ID_DYN_2_STEER:
            return sizeof( RDB_DYN_2_STEER_t );
            
        case RDB_PKG_ID_STEER_2_DYN:
            return sizeof( RDB_STEER_2_DYN_t );
            
        case RDB_PKG_ID_PROXY:
            return sizeof( RDB_PROXY_t );
            
        case RDB_PKG_ID_MOTION_SYSTEM:
            return sizeof( RDB_MOTION_SYSTEM_t );
            
        case RDB_PKG_ID_FREESPACE:
            return sizeof( RDB_FREESPACE_t );
            
        case RDB_PKG_ID_DYN_EL_SWITCH:
            return sizeof( RDB_DYN_EL_SWITCH_t );
            
        case RDB_PKG_ID_DYN_EL_DOF:
            return sizeof( RDB_DYN_EL_DOF_t );
            
        case RDB_PKG_ID_CUSTOM_SCORING:
            return sizeof( RDB_CUSTOM_SCORING_t );
            
        case RDB_PKG_ID_IG_FRAME:
            return sizeof( RDB_IG_FRAME_t );
            
        case RDB_PKG_ID_RT_PERFORMANCE:
            return sizeof( RDB_RT_PERFORMANCE_t );
            
        case RDB_PKG_ID_RAY:
            return sizeof( RDB_RAY_t );
            
        case RDB_PKG_ID_SYMBOL_STATE:
            return sizeof( RDB_SYMBOL_STATE_t );
            
        case RDB_PKG_ID_CUSTOM_OBJECT_CTRL_TRACK:
            return sizeof( RDB_CUSTOM_OBJECT_CTRL_TRACK_t );
            
        case RDB_PKG_ID_CUSTOM_LOOK_AHEAD:
            return sizeof( RDB_CUSTOM_LOOK_AHEAD_t );

        case RDB_PKG_ID_RADAR_HIT_POINT:
            return sizeof( RDB_RADAR_HIT_POINT_t );
            
        default:
            //fprintf( stderr, "RDBHandler::pkgId2size: request for size of unknown package <%d>. Returning zero", pkgId );
            return 0;
    }
}

std::string
RDBHandler::pkgId2string( unsigned int pkgId )
{
    switch( pkgId )
    {
        case RDB_PKG_ID_START_OF_FRAME: 
            return std::string( "RDB_PKG_ID_START_OF_FRAME" );

        case RDB_PKG_ID_END_OF_FRAME:
            return std::string( "RDB_PKG_ID_END_OF_FRAME" );
            
        case RDB_PKG_ID_COORD_SYSTEM:
            return std::string( "RDB_PKG_ID_COORD_SYSTEM" );
            
        case RDB_PKG_ID_COORD:
            return std::string( "RDB_PKG_ID_COORD" );
            
        case RDB_PKG_ID_ROAD_POS:
            return std::string( "RDB_PKG_ID_ROAD_POS" );
            
        case RDB_PKG_ID_LANE_INFO:
            return std::string( "RDB_PKG_ID_LANE_INFO" );
            
        case RDB_PKG_ID_ROADMARK:
            return std::string( "RDB_PKG_ID_ROADMARK" );
            
        case RDB_PKG_ID_OBJECT_CFG:
            return std::string( "RDB_PKG_ID_OBJECT_CFG" );
            
        case RDB_PKG_ID_OBJECT_STATE:
            return std::string( "RDB_PKG_ID_OBJECT_STATE" );
            
        case RDB_PKG_ID_VEHICLE_SYSTEMS:
            return std::string( "RDB_PKG_ID_VEHICLE_SYSTEMS" );
            
        case RDB_PKG_ID_VEHICLE_SETUP:
            return std::string( "RDB_PKG_ID_VEHICLE_SETUP" );
            
        case RDB_PKG_ID_ENGINE:
            return std::string( "RDB_PKG_ID_ENGINE" );
            
        case RDB_PKG_ID_DRIVETRAIN:
            return std::string( "RDB_PKG_ID_DRIVETRAIN" );
            
        case RDB_PKG_ID_WHEEL:
            return std::string( "RDB_PKG_ID_WHEEL" );
            
        case RDB_PKG_ID_PED_ANIMATION:
            return std::string( "RDB_PKG_ID_PED_ANIMATION" );
            
        case RDB_PKG_ID_SENSOR_STATE:
            return std::string( "RDB_PKG_ID_SENSOR_STATE" );
            
        case RDB_PKG_ID_SENSOR_OBJECT:
            return std::string( "RDB_PKG_ID_SENSOR_OBJECT" );
            
        case RDB_PKG_ID_CAMERA:
            return std::string( "RDB_PKG_ID_CAMERA" );
            
        case RDB_PKG_ID_CONTACT_POINT:
            return std::string( "RDB_PKG_ID_CONTACT_POINT" );
            
        case RDB_PKG_ID_TRAFFIC_SIGN:
            return std::string( "RDB_PKG_ID_TRAFFIC_SIGN" );
            
        case RDB_PKG_ID_ROAD_STATE:
            return std::string( "RDB_PKG_ID_ROAD_STATE" );
            
        case RDB_PKG_ID_IMAGE:
            return std::string( "RDB_PKG_ID_IMAGE" );
            
        case RDB_PKG_ID_LIGHT_SOURCE:
             return std::string( "RDB_PKG_ID_LIGHT_SOURCE" );
            
        case RDB_PKG_ID_ENVIRONMENT:
            return std::string( "RDB_PKG_ID_ENVIRONMENT" );
            
        case RDB_PKG_ID_TRIGGER:
            return std::string( "RDB_PKG_ID_TRIGGER" );
            
        case RDB_PKG_ID_DRIVER_CTRL:
            return std::string( "RDB_PKG_ID_DRIVER_CTRL" );
            
        case RDB_PKG_ID_TRAFFIC_LIGHT:
            return std::string( "RDB_PKG_ID_TRAFFIC_LIGHT" );
            
        case RDB_PKG_ID_SYNC:
            return std::string( "RDB_PKG_ID_SYNC" );
            
        case RDB_PKG_ID_DRIVER_PERCEPTION:
            return std::string( "RDB_PKG_ID_DRIVER_PERCEPTION" );
            
        case RDB_PKG_ID_LIGHT_MAP:
            return std::string( "RDB_PKG_ID_LIGHT_MAP" );
            
        case RDB_PKG_ID_TONE_MAPPING:
            return std::string( "RDB_PKG_ID_TONE_MAPPING" );
            
        case RDB_PKG_ID_ROAD_QUERY:
            return std::string( "RDB_PKG_ROAD_QUERY" );
            
        case RDB_PKG_ID_SCP:
            return std::string( "RDB_PKG_ID_SCP" );
            
        case RDB_PKG_ID_TRAJECTORY:
            return std::string( "RDB_PKG_ID_TRAJECTORY" );
            
        case RDB_PKG_ID_DYN_2_STEER:
            return std::string( "RDB_PKG_ID_DYN_2_STEER" );
            
        case RDB_PKG_ID_STEER_2_DYN:
            return std::string( "RDB_PKG_ID_STEER_2_DYN" );
            
        case RDB_PKG_ID_PROXY:
            return std::string( "RDB_PKG_ID_PROXY" );

        case RDB_PKG_ID_MOTION_SYSTEM:
            return std::string( "RDB_PKG_ID_MOTION_SYSTEM" );
            
        case RDB_PKG_ID_OCCLUSION_MATRIX:
            return std::string( "RDB_PKG_ID_OCCLUSION_MATRIX" );
            
        case RDB_PKG_ID_FREESPACE:
            return std::string( "RDB_PKG_ID_FREESPACE" );
            
        case RDB_PKG_ID_DYN_EL_SWITCH:
            return std::string( "RDB_PKG_ID_DYN_EL_SWITCH" );
            
        case RDB_PKG_ID_DYN_EL_DOF:
            return std::string( "RDB_PKG_ID_DYN_EL_DOF" );
            
        case RDB_PKG_ID_IG_FRAME:
            return std::string( "RDB_PKG_ID_IG_FRAME" );
            
        case RDB_PKG_ID_RT_PERFORMANCE:
            return std::string( "RDB_PKG_ID_RT_PERFORMANCE" );
            
        case RDB_PKG_ID_RAY:
            return std::string( "RDB_PKG_ID_RAY" );
            
        case RDB_PKG_ID_SYMBOL_STATE:
            return std::string( "RDB_PKG_ID_SYMBOL_STATE" );
            
        case RDB_PKG_ID_CUSTOM_SCORING:
            return std::string( "RDB_PKG_ID_CUSTOM_SCORING" );
            
        case RDB_PKG_ID_CUSTOM_OBJECT_CTRL_TRACK:
             return std::string( "RDB_PKG_ID_CUSTOM_OBJECT_CTRL_TRACK" );
            
        case RDB_PKG_ID_CUSTOM_AUDI_FORUM:
            return std::string( "RDB_PKG_ID_CUSTOM_AUDI_FORUM" );
            
        case RDB_PKG_ID_CUSTOM_OPTIX_START:
            return std::string( "RDB_PKG_ID_CUSTOM_OPTIX_START" );
            
        case RDB_PKG_ID_CUSTOM_OPTIX_END:
            return std::string( "RDB_PKG_ID_CUSTOM_OPTIX_END" );
            
        case RDB_PKG_ID_CUSTOM_LOOK_AHEAD:
            return std::string( "RDB_PKG_ID_CUSTOM_LOOK_AHEAD" );

        case RDB_PKG_ID_RADAR_HIT_POINT:
            return std::string( "RDB_PKG_ID_RADAR_HIT_POINT" );
            
        default:
            return std::string( "unknown" );
    }
}

std::string
RDBHandler::coordType2string( unsigned int type )
{
    switch( type )
    {
        case RDB_COORD_TYPE_INERTIAL: 
            return std::string( "RDB_COORD_TYPE_INERTIAL" );

        case RDB_COORD_TYPE_RESERVED_1:
            return std::string( "RDB_COORD_TYPE_RESERVED_1" );
            
        case RDB_COORD_TYPE_PLAYER:
            return std::string( "RDB_COORD_TYPE_PLAYER" );
            
        case RDB_COORD_TYPE_SENSOR:
            return std::string( "RDB_COORD_TYPE_SENSOR" );
            
        case RDB_COORD_TYPE_USK:
            return std::string( "RDB_COORD_TYPE_USK" );
            
        case RDB_COORD_TYPE_USER:
            return std::string( "RDB_COORD_TYPE_USER" );
            
        case RDB_COORD_TYPE_WINDOW:
            return std::string( "RDB_COORD_TYPE_WINDOW" );
            
        case RDB_COORD_TYPE_TEXTURE:
            return std::string( "RDB_COORD_TYPE_TEXTURE" );
            
        case RDB_COORD_TYPE_RELATIVE_START:
            return std::string( "RDB_COORD_TYPE_RELATIVE_START" );
            
        case RDB_COORD_TYPE_GEO:
            return std::string( "RDB_COORD_TYPE_GEO" );
           
        default:
            return std::string( "unknown" );
    }
}

std::string
RDBHandler::objectCategory2string( unsigned int id )
{
    switch( id )
    {
        case RDB_OBJECT_CATEGORY_NONE: 
            return std::string( "RDB_OBJECT_CATEGORY_NONE" );

        case RDB_OBJECT_CATEGORY_PLAYER:
            return std::string( "RDB_OBJECT_CATEGORY_PLAYER" );
            
        case RDB_OBJECT_CATEGORY_SENSOR:
            return std::string( "RDB_OBJECT_CATEGORY_SENSOR" );
            
        case RDB_OBJECT_CATEGORY_CAMERA:
            return std::string( "RDB_OBJECT_CATEGORY_CAMERA" );
            
        case RDB_OBJECT_CATEGORY_LIGHT_POINT:
            return std::string( "RDB_OBJECT_CATEGORY_LIGHT_POINT" );
            
        case RDB_OBJECT_CATEGORY_COMMON:
            return std::string( "RDB_OBJECT_CATEGORY_COMMON" );
            
        case RDB_OBJECT_CATEGORY_OPENDRIVE:
            return std::string( "RDB_OBJECT_CATEGORY_OPENDRIVE" );
            
        default:
            return std::string( "unknown" );
    }
}

unsigned int
RDBHandler::objectString2category( const std::string & name )
{
    if ( name == std::string( "RDB_OBJECT_CATEGORY_NONE" ) )
        return RDB_OBJECT_CATEGORY_NONE;

    if ( name == std::string( "RDB_OBJECT_CATEGORY_PLAYER" ) )
        return RDB_OBJECT_CATEGORY_PLAYER;

    if ( name == std::string( "RDB_OBJECT_CATEGORY_SENSOR" ) )
        return RDB_OBJECT_CATEGORY_SENSOR;

    if ( name == std::string( "RDB_OBJECT_CATEGORY_CAMERA" ) )
        return RDB_OBJECT_CATEGORY_CAMERA;

    if ( name == std::string( "RDB_OBJECT_CATEGORY_LIGHT_POINT" ) )
        return RDB_OBJECT_CATEGORY_LIGHT_POINT;

    if ( name == std::string( "RDB_OBJECT_CATEGORY_COMMON" ) )
        return RDB_OBJECT_CATEGORY_COMMON;

    if ( name == std::string( "RDB_OBJECT_CATEGORY_OPENDRIVE" ) )
        return RDB_OBJECT_CATEGORY_OPENDRIVE;
    
    return RDB_OBJECT_CATEGORY_NONE;
}

std::string
RDBHandler::objectType2string( unsigned int id )
{
    switch( id )
    {
        case RDB_OBJECT_TYPE_PLAYER_NONE:
            return std::string( "RDB_OBJECT_TYPE_PLAYER_NONE" );
            
        case RDB_OBJECT_TYPE_PLAYER_CAR:
            return std::string( "RDB_OBJECT_TYPE_PLAYER_CAR" );
            
        case RDB_OBJECT_TYPE_PLAYER_TRUCK:
            return std::string( "RDB_OBJECT_TYPE_PLAYER_TRUCK" );
            
        case RDB_OBJECT_TYPE_PLAYER_VAN:
            return std::string( "RDB_OBJECT_TYPE_PLAYER_VAN" );
            
        case RDB_OBJECT_TYPE_PLAYER_BIKE:
            return std::string( "RDB_OBJECT_TYPE_PLAYER_BIKE" );
            
        case RDB_OBJECT_TYPE_PLAYER_PEDESTRIAN:
            return std::string( "RDB_OBJECT_TYPE_PLAYER_PEDESTRIAN" );
            
        case RDB_OBJECT_TYPE_PLAYER_PED_GROUP:
            return std::string( "RDB_OBJECT_TYPE_PLAYER_PED_GROUP" );
            
        case RDB_OBJECT_TYPE_POLE:
            return std::string( "RDB_OBJECT_TYPE_POLE" );
            
        case RDB_OBJECT_TYPE_TREE:
            return std::string( "RDB_OBJECT_TYPE_TREE" );
            
        case RDB_OBJECT_TYPE_BARRIER:
            return std::string( "RDB_OBJECT_TYPE_BARRIER" );
            
        case RDB_OBJECT_TYPE_OPT1:
            return std::string( "RDB_OBJECT_TYPE_OPT1" );
            
        case RDB_OBJECT_TYPE_OPT2:
            return std::string( "RDB_OBJECT_TYPE_OPT2" );
            
        case RDB_OBJECT_TYPE_OPT3:
            return std::string( "RDB_OBJECT_TYPE_OPT3" );
            
        case RDB_OBJECT_TYPE_PLAYER_MOTORBIKE:
            return std::string( "RDB_OBJECT_TYPE_PLAYER_MOTORBIKE" );
            
        case RDB_OBJECT_TYPE_PLAYER_BUS:
            return std::string( "RDB_OBJECT_TYPE_PLAYER_BUS" );
            
        case RDB_OBJECT_TYPE_STREET_LAMP:
            return std::string( "RDB_OBJECT_TYPE_STREET_LAMP" );
            
        case RDB_OBJECT_TYPE_TRAFFIC_SIGN:
            return std::string( "RDB_OBJECT_TYPE_TRAFFIC_SIGN" );
            
        case RDB_OBJECT_TYPE_HEADLIGHT:
            return std::string( "RDB_OBJECT_TYPE_HEADLIGHT" );
            
        case RDB_OBJECT_TYPE_PLAYER_TRAILER:
            return std::string( "RDB_OBJECT_TYPE_PLAYER_TRAILER" );
            
        case RDB_OBJECT_TYPE_BUILDING:
            return std::string( "RDB_OBJECT_TYPE_BUILDING" );
            
        case RDB_OBJECT_TYPE_PARKING_SPACE:
            return std::string( "RDB_OBJECT_TYPE_PARKING_SPACE" );
            
        case RDB_OBJECT_TYPE_ROAD_WORKS:
            return std::string( "RDB_OBJECT_TYPE_ROAD_WORKS" );
            
        case RDB_OBJECT_TYPE_ROAD_MISC:
            return std::string( "RDB_OBJECT_TYPE_ROAD_MISC" );
            
        case RDB_OBJECT_TYPE_TUNNEL:
            return std::string( "RDB_OBJECT_TYPE_TUNNEL" );
            
        case RDB_OBJECT_TYPE_LEGACY:
            return std::string( "RDB_OBJECT_TYPE_LEGACY" );
            
        case RDB_OBJECT_TYPE_VEGETATION:
            return std::string( "RDB_OBJECT_TYPE_VEGETATION" );
            
        case RDB_OBJECT_TYPE_MISC_MOTORWAY:
            return std::string( "RDB_OBJECT_TYPE_MISC_MOTORWAY" );
            
        case RDB_OBJECT_TYPE_MISC_TOWN:
            return std::string( "RDB_OBJECT_TYPE_MISC_TOWN" );
            
        case RDB_OBJECT_TYPE_PATCH:
            return std::string( "RDB_OBJECT_TYPE_PATCH" );
            
        case RDB_OBJECT_TYPE_OTHER:
            return std::string( "RDB_OBJECT_TYPE_OTHER" );
            
        case RDB_OBJECT_PLAYER_SEMI_TRAILER:
            return std::string( "RDB_OBJECT_PLAYER_SEMI_TRAILER" );
            
        case RDB_OBJECT_PLAYER_RAILCAR:
            return std::string( "RDB_OBJECT_PLAYER_RAILCAR" );
            
        case RDB_OBJECT_PLAYER_RAILCAR_SEMI_HEAD:
            return std::string( "RDB_OBJECT_PLAYER_RAILCAR_SEMI_HEAD" );
            
        case RDB_OBJECT_PLAYER_RAILCAR_SEMI_BACK:
            return std::string( "RDB_OBJECT_PLAYER_RAILCAR_SEMI_BACK" );
            
        default:
            return std::string( "unknown" );
    }
}

unsigned int
RDBHandler::objectString2type( const std::string & name )
{
    if ( name == std::string( "RDB_OBJECT_TYPE_PLAYER_NONE" ) )
        return RDB_OBJECT_TYPE_PLAYER_NONE;
    
    if ( name == std::string( "RDB_OBJECT_TYPE_PLAYER_CAR" ) )
        return RDB_OBJECT_TYPE_PLAYER_CAR;
    
    if ( name == std::string( "RDB_OBJECT_TYPE_PLAYER_TRUCK" ) )
        return RDB_OBJECT_TYPE_PLAYER_TRUCK;
    
    if ( name == std::string( "RDB_OBJECT_TYPE_PLAYER_VAN" ) )
        return RDB_OBJECT_TYPE_PLAYER_VAN;
    
    if ( name == std::string( "RDB_OBJECT_TYPE_PLAYER_BIKE" ) )
        return RDB_OBJECT_TYPE_PLAYER_BIKE;
    
    if ( name == std::string( "RDB_OBJECT_TYPE_PLAYER_PEDESTRIAN" ) )
        return RDB_OBJECT_TYPE_PLAYER_PEDESTRIAN;
    
    if ( name == std::string( "RDB_OBJECT_TYPE_PLAYER_PED_GROUP" ) )
        return RDB_OBJECT_TYPE_PLAYER_PED_GROUP;
    
    if ( name == std::string( "RDB_OBJECT_TYPE_POLE" ) )
        return RDB_OBJECT_TYPE_POLE;
    
    if ( name == std::string( "RDB_OBJECT_TYPE_TREE" ) )
        return RDB_OBJECT_TYPE_TREE;
    
    if ( name == std::string( "RDB_OBJECT_TYPE_BARRIER" ) )
        return RDB_OBJECT_TYPE_BARRIER;
    
    if ( name == std::string( "RDB_OBJECT_TYPE_OPT1" ) )
        return RDB_OBJECT_TYPE_OPT1;
    
    if ( name == std::string( "RDB_OBJECT_TYPE_OPT2" ) )
        return RDB_OBJECT_TYPE_OPT2;
    
    if ( name == std::string( "RDB_OBJECT_TYPE_OPT3" ) )
        return RDB_OBJECT_TYPE_OPT3;
    
    if ( name == std::string( "RDB_OBJECT_TYPE_PLAYER_MOTORBIKE" ) )
        return RDB_OBJECT_TYPE_PLAYER_MOTORBIKE;
    
    if ( name == std::string( "RDB_OBJECT_TYPE_PLAYER_BUS" ) )
        return RDB_OBJECT_TYPE_PLAYER_BUS;
    
    if ( name == std::string( "RDB_OBJECT_TYPE_STREET_LAMP" ) )
        return RDB_OBJECT_TYPE_STREET_LAMP;
    
    if ( name == std::string( "RDB_OBJECT_TYPE_TRAFFIC_SIGN" ) )
        return RDB_OBJECT_TYPE_TRAFFIC_SIGN;
    
    if ( name == std::string( "RDB_OBJECT_TYPE_HEADLIGHT" ) )
        return RDB_OBJECT_TYPE_HEADLIGHT;
    
    if ( name == std::string( "RDB_OBJECT_TYPE_PLAYER_TRAILER" ) )
        return RDB_OBJECT_TYPE_PLAYER_TRAILER;
    
    if ( name == std::string( "RDB_OBJECT_TYPE_BUILDING" ) )
        return RDB_OBJECT_TYPE_BUILDING;
    
    if ( name == std::string( "RDB_OBJECT_TYPE_PARKING_SPACE" ) )
        return RDB_OBJECT_TYPE_PARKING_SPACE;
    
    if ( name == std::string( "RDB_OBJECT_TYPE_ROAD_WORKS" ) )
        return RDB_OBJECT_TYPE_ROAD_WORKS;
    
    if ( name == std::string( "RDB_OBJECT_TYPE_ROAD_MISC" ) )
        return RDB_OBJECT_TYPE_ROAD_MISC;
    
    if ( name == std::string( "RDB_OBJECT_TYPE_TUNNEL" ) )
        return RDB_OBJECT_TYPE_TUNNEL;
    
    if ( name == std::string( "RDB_OBJECT_TYPE_LEGACY" ) )
        return RDB_OBJECT_TYPE_LEGACY;
    
    if ( name == std::string( "RDB_OBJECT_TYPE_VEGETATION" ) )
        return RDB_OBJECT_TYPE_VEGETATION;
    
    if ( name == std::string( "RDB_OBJECT_TYPE_MISC_MOTORWAY" ) )
        return RDB_OBJECT_TYPE_MISC_MOTORWAY;
    
    if ( name == std::string( "RDB_OBJECT_TYPE_MISC_TOWN" ) )
        return RDB_OBJECT_TYPE_MISC_TOWN;
    
    if ( name == std::string( "RDB_OBJECT_TYPE_PATCH" ) )
        return RDB_OBJECT_TYPE_PATCH;
    
    if ( name == std::string( "RDB_OBJECT_TYPE_OTHER" ) )
        return RDB_OBJECT_TYPE_OTHER;
    
    if ( name == std::string( "RDB_OBJECT_PLAYER_SEMI_TRAILER" ) )
        return RDB_OBJECT_PLAYER_SEMI_TRAILER;
    
    if ( name == std::string( "RDB_OBJECT_PLAYER_RAILCAR" ) )
        return RDB_OBJECT_PLAYER_RAILCAR;
    
    if ( name == std::string( "RDB_OBJECT_PLAYER_RAILCAR_SEMI_HEAD" ) )
        return RDB_OBJECT_PLAYER_RAILCAR_SEMI_HEAD;
    
    if ( name == std::string( "RDB_OBJECT_PLAYER_RAILCAR_SEMI_BACK" ) )
        return RDB_OBJECT_PLAYER_RAILCAR_SEMI_BACK;
    
    return RDB_OBJECT_TYPE_PLAYER_NONE;
}

void
RDBHandler::printMessage( RDB_MSG_t* msg, bool details, bool binDump, bool csv, bool csvHeader )
{
    if ( !msg )
    {
        fprintf( stderr, "RDBHandler::printMessage: no message available\n" );
        return;
    }
    
    if ( !csv && !csvHeader )
    {
        fprintf( stderr, "\nRDBHandler::printMessage: ---- %s ----- BEGIN\n", details ? "full info" : "short info" );
        fprintf( stderr, "  message: version = 0x%04x, simTime = %.3f, simFrame = %d, headerSize = %d, dataSize = %d\n",
                                       msg->hdr.version, msg->hdr.simTime, msg->hdr.frameNo, msg->hdr.headerSize, msg->hdr.dataSize );
    }
                               
    if ( !msg->hdr.dataSize )
        return;
    
    RDB_MSG_ENTRY_HDR_t* entry = ( RDB_MSG_ENTRY_HDR_t* ) ( ( ( char* ) msg ) + msg->hdr.headerSize );
    uint32_t remainingBytes    = msg->hdr.dataSize;
        
    while ( remainingBytes )
    {
        if ( entry->pkgId == RDB_PKG_ID_START_OF_FRAME )
        {
            if ( csvHeader )
                fprintf( stderr, "%23s,%23s,", "simTime", "simFrame" );
            else if ( csv ) 
                fprintf( stderr, "%+.16e,%23d,", msg->hdr.simTime, msg->hdr.frameNo );
        }
        
        printMessageEntry( entry, details, csv, csvHeader );

        remainingBytes -= ( entry->headerSize + entry->dataSize );
        
        if ( remainingBytes )
          entry = ( RDB_MSG_ENTRY_HDR_t* ) ( ( ( ( char* ) entry ) + entry->headerSize + entry->dataSize ) );
    }
    
    // create a binary dump?
    if ( binDump )
    {
        fprintf( stderr, "RDBHandler::printMessage: ---- binary dump ----- \n" );
        
        uint32_t remainingBytes = msg->hdr.dataSize + msg->hdr.headerSize;
        unsigned char* dataPtr = ( unsigned char* ) msg;
        
        for ( unsigned int i = 1; i <= remainingBytes; i++ )
        {
            fprintf( stderr, "%02x ", *dataPtr );
            
            dataPtr++;
            
            if ( !( i % 16 ) )
                fprintf( stderr, "\n" );
        }
        fprintf( stderr, "\n" );
    }
    
    if ( !csv )
        fprintf( stderr, "RDBHandler::printMessage: ---- %s ----- END\n", details ? "full info" : "short info" );
}


void
RDBHandler::printMessageEntry( RDB_MSG_ENTRY_HDR_t* entryHdr, bool details, bool csv, bool csvHeader )
{
    if ( !entryHdr )
        return;
    
    int noElements = entryHdr->elementSize ? ( entryHdr->dataSize / entryHdr->elementSize ) : 0;
    
    if ( !csv && !csvHeader )
    {
        fprintf( stderr, "    entry: pkgId = %2d (%s), headersize = %d, dataSize = %d, elementSize = %d, noElements = %d, flags = 0x%x\n",
                         entryHdr->pkgId, pkgId2string( entryHdr->pkgId ).c_str(), entryHdr->headerSize, 
                         entryHdr->dataSize, entryHdr->elementSize, noElements, entryHdr->flags );
    }
    else if ( entryHdr->pkgId == RDB_PKG_ID_END_OF_FRAME )
        fprintf( stderr, "\n" );
    
    if ( details )
    {
        unsigned char ident   = 6;
        char*         dataPtr = ( char* ) entryHdr;
        
        dataPtr += entryHdr->headerSize;
        
        while ( noElements-- )
        {
            bool printedMsg = printMessageEntryElement( entryHdr, dataPtr, ident,  csv, csvHeader );

            dataPtr += entryHdr->elementSize;
            
            if ( noElements && printedMsg && !csv )
                fprintf( stderr, "\n" );
        }            
    }
}

bool
RDBHandler::printMessageEntryElement( RDB_MSG_ENTRY_HDR_t* entryHdr, void* dataPtr, unsigned char ident, bool csv, bool csvHeader )
{
    if ( !entryHdr || !dataPtr )
        return false;
    
    switch ( entryHdr->pkgId )
    {
        case RDB_PKG_ID_COORD_SYSTEM:
            print( *( ( RDB_COORD_SYSTEM_t* ) dataPtr ), ident, csv, csvHeader );
            break;
            
        case RDB_PKG_ID_COORD:
            print( *( ( RDB_COORD_t* ) dataPtr ), ident, csv, csvHeader );
            break;
            
        case RDB_PKG_ID_ROAD_POS:
            print( *( ( RDB_ROAD_POS_t* ) dataPtr ), ident, csv, csvHeader );
            break;
            
        case RDB_PKG_ID_LANE_INFO:
            print( *( ( RDB_LANE_INFO_t* ) dataPtr ), ident, csv, csvHeader );
            break;
            
        case RDB_PKG_ID_ROADMARK:
            print( *( ( RDB_ROADMARK_t* ) dataPtr ), ident, csv, csvHeader );
            break;
            
        case RDB_PKG_ID_OBJECT_CFG:
            print( *( ( RDB_OBJECT_CFG_t* ) dataPtr ), ident, csv, csvHeader );
            break;
            
        case RDB_PKG_ID_OBJECT_STATE:
            print( *( ( RDB_OBJECT_STATE_t* ) dataPtr ), entryHdr->flags & RDB_PKG_FLAG_EXTENDED, ident, csv, csvHeader );
            break;
            
        case RDB_PKG_ID_VEHICLE_SYSTEMS:
            print( *( ( RDB_VEHICLE_SYSTEMS_t* ) dataPtr ), ident, csv, csvHeader );
            break;
            
        case RDB_PKG_ID_VEHICLE_SETUP:
            print( *( ( RDB_VEHICLE_SETUP_t* ) dataPtr ), ident, csv, csvHeader );
            break;
            
        case RDB_PKG_ID_ENGINE:
            print( *( ( RDB_ENGINE_t* ) dataPtr ), entryHdr->flags & RDB_PKG_FLAG_EXTENDED, ident, csv, csvHeader );
            break;
            
        case RDB_PKG_ID_DRIVETRAIN:
            print( *( ( RDB_DRIVETRAIN_t* ) dataPtr ), entryHdr->flags & RDB_PKG_FLAG_EXTENDED, ident, csv, csvHeader );
            break;
            
        case RDB_PKG_ID_WHEEL:
            print( *( ( RDB_WHEEL_t* ) dataPtr ), entryHdr->flags & RDB_PKG_FLAG_EXTENDED, ident, csv, csvHeader );
            break;

        case RDB_PKG_ID_PED_ANIMATION:
            print( *( ( RDB_PED_ANIMATION_t* ) dataPtr ), ident, csv, csvHeader );
            break;

        case RDB_PKG_ID_SENSOR_STATE:
            print( *( ( RDB_SENSOR_STATE_t* ) dataPtr ), ident, csv, csvHeader );
            break;

        case RDB_PKG_ID_SENSOR_OBJECT:
            print( *( ( RDB_SENSOR_OBJECT_t* ) dataPtr ), ident, csv, csvHeader );
            break;
            
        case RDB_PKG_ID_CAMERA:
            print( *( ( RDB_CAMERA_t* ) dataPtr ), ident, csv, csvHeader );
            break;
            
        case RDB_PKG_ID_CONTACT_POINT:
            print( *( ( RDB_CONTACT_POINT_t* ) dataPtr ), ident, csv, csvHeader );
            break;
            
        case RDB_PKG_ID_TRAFFIC_SIGN:
            print( *( ( RDB_TRAFFIC_SIGN_t* ) dataPtr ), ident, csv, csvHeader );
            break;
            
        case RDB_PKG_ID_ROAD_STATE:
            print( *( ( RDB_ROAD_STATE_t* ) dataPtr ), ident, csv, csvHeader );
            break;
            
        case RDB_PKG_ID_IMAGE:
        case RDB_PKG_ID_LIGHT_MAP:
            print( *( ( RDB_IMAGE_t* ) dataPtr ), ident, csv, csvHeader );
            break;
            
        case RDB_PKG_ID_OCCLUSION_MATRIX:
            {
                RDB_IMAGE_t* pImage = ( RDB_IMAGE_t* ) dataPtr; 
                print( *pImage, ident );
                
                // print also the contents?
                if ( pImage->pixelSize == 32 ) // works only for 32bit integer!
                {
                    unsigned char* pData = ( unsigned char* ) dataPtr;
                    
                    printMatrix( ( int * ) ( pData + sizeof( RDB_IMAGE_t ) ), pImage->width, pImage->height, csv, csvHeader );
                }
            }
            break;
            
        case RDB_PKG_ID_LIGHT_SOURCE:
            print( *( ( RDB_LIGHT_SOURCE_t* ) dataPtr ), entryHdr->flags & RDB_PKG_FLAG_EXTENDED, ident, csv, csvHeader );
            break;
            
        case RDB_PKG_ID_ENVIRONMENT:
            print( *( ( RDB_ENVIRONMENT_t* ) dataPtr ), ident, csv, csvHeader );
            break;
            
        case RDB_PKG_ID_TRIGGER:
            print( *( ( RDB_TRIGGER_t* ) dataPtr ), ident, csv, csvHeader );
            break;
            
        case RDB_PKG_ID_DRIVER_CTRL:
            print( *( ( RDB_DRIVER_CTRL_t* ) dataPtr ), ident, csv, csvHeader );
            break;
            
        case RDB_PKG_ID_TRAFFIC_LIGHT:
            print( *( ( RDB_TRAFFIC_LIGHT_t* ) dataPtr ), entryHdr->flags & RDB_PKG_FLAG_EXTENDED, ident, csv, csvHeader );
            break;
            
        case RDB_PKG_ID_SYNC:
            print( *( ( RDB_SYNC_t* ) dataPtr ), ident, csv, csvHeader );
            break;
            
        case RDB_PKG_ID_DRIVER_PERCEPTION:
            print( *( ( RDB_DRIVER_PERCEPTION_t* ) dataPtr ), ident, csv, csvHeader );
            break;
            
        case RDB_PKG_ID_TONE_MAPPING:
            print( *( ( RDB_FUNCTION_t* ) dataPtr ), ident, csv, csvHeader );
            break;
            
        case RDB_PKG_ID_ROAD_QUERY:
            print( *( ( RDB_ROAD_QUERY_t* ) dataPtr ), ident, csv, csvHeader );
            break;
            
        case RDB_PKG_ID_TRAJECTORY:
            print( *( ( RDB_TRAJECTORY_t* ) dataPtr ), ident, csv, csvHeader );
            break;

        case RDB_PKG_ID_DYN_2_STEER:
            print( *( ( RDB_DYN_2_STEER_t* ) dataPtr ), ident, csv, csvHeader );
            break;

        case RDB_PKG_ID_STEER_2_DYN:
            print( *( ( RDB_STEER_2_DYN_t* ) dataPtr ), ident, csv, csvHeader );
            break;

        case RDB_PKG_ID_PROXY:
            print( *( ( RDB_PROXY_t* ) dataPtr ), ident, csv, csvHeader );
            break;

        case RDB_PKG_ID_MOTION_SYSTEM:
            print( *( ( RDB_MOTION_SYSTEM_t* ) dataPtr ), ident, csv, csvHeader );
            break;

        case RDB_PKG_ID_FREESPACE:
            print( *( ( RDB_FREESPACE_t* ) dataPtr ), ident, csv, csvHeader );
            break;

        case RDB_PKG_ID_DYN_EL_SWITCH:
            print( *( ( RDB_DYN_EL_SWITCH_t* ) dataPtr ), ident, csv, csvHeader );
            break;

        case RDB_PKG_ID_DYN_EL_DOF:
            print( *( ( RDB_DYN_EL_DOF_t* ) dataPtr ), ident, csv, csvHeader );
            break;

        case RDB_PKG_ID_IG_FRAME:
            print( *( ( RDB_IG_FRAME_t* ) dataPtr ), ident, csv, csvHeader );
            break;

        case RDB_PKG_ID_RT_PERFORMANCE:
            print( *( ( RDB_RT_PERFORMANCE_t* ) dataPtr ), ident, csv, csvHeader );
            break;

        case RDB_PKG_ID_CUSTOM_SCORING:
            print( *( ( RDB_CUSTOM_SCORING_t* ) dataPtr ), ident, csv, csvHeader );
            break;

        case RDB_PKG_ID_CUSTOM_OBJECT_CTRL_TRACK:
            print( *( ( RDB_CUSTOM_OBJECT_CTRL_TRACK_t* ) dataPtr ), ident, csv, csvHeader );
            break;

        case RDB_PKG_ID_RAY:
            print( *( ( RDB_RAY_t* ) dataPtr ), ident, csv, csvHeader );
            break;

        case RDB_PKG_ID_SYMBOL_STATE:
            print( *( ( RDB_SYMBOL_STATE_t* ) dataPtr ), ident, csv, csvHeader );
            break;

        case RDB_PKG_ID_RADAR_HIT_POINT:
            print( *( ( RDB_RADAR_HIT_POINT_t* ) dataPtr ), ident, csv, csvHeader );
            break;

        default:
            return false;
            break;
    }
    
    return true;
}

bool
RDBHandler::retrievePrimaryId( unsigned short elementType, void* element, unsigned int & primaryId )
{
    if ( !element )
        return false;

    switch ( elementType )
    {
        case RDB_PKG_ID_ROAD_POS:
            primaryId = ( ( RDB_ROAD_POS_t* ) element )->playerId;
            break;
            
        case RDB_PKG_ID_LANE_INFO:
            primaryId = ( ( RDB_LANE_INFO_t* ) element )->playerId;
            break;
            
        case RDB_PKG_ID_ROADMARK:
            primaryId = ( ( RDB_ROADMARK_t* ) element )->playerId;
            break;
            
        case RDB_PKG_ID_OBJECT_CFG:
            primaryId = ( ( RDB_OBJECT_CFG_t* ) element )->id;
            break;
            
        case RDB_PKG_ID_OBJECT_STATE:
            primaryId = ( ( RDB_OBJECT_STATE_t* ) element )->base.id;
            break;
            
        case RDB_PKG_ID_VEHICLE_SYSTEMS:
            primaryId = ( ( RDB_VEHICLE_SYSTEMS_t* ) element )->playerId;
            break;
            
        case RDB_PKG_ID_VEHICLE_SETUP:
            primaryId = ( ( RDB_VEHICLE_SETUP_t* ) element )->playerId;
            break;
            
        case RDB_PKG_ID_ENGINE:
            primaryId = ( ( RDB_ENGINE_t* ) element )->base.playerId;
            break;
            
        case RDB_PKG_ID_DRIVETRAIN:
            primaryId = ( ( RDB_DRIVETRAIN_t* ) element )->base.playerId;
            break;
            
        case RDB_PKG_ID_WHEEL:
            primaryId = ( ( RDB_WHEEL_t* ) element )->base.playerId;
            break;

        case RDB_PKG_ID_PED_ANIMATION:
            primaryId = ( ( RDB_PED_ANIMATION_t* ) element )->playerId;
            break;

        case RDB_PKG_ID_SENSOR_STATE:
            primaryId = ( ( RDB_SENSOR_STATE_t* ) element )->id;
            break;

        case RDB_PKG_ID_SENSOR_OBJECT:
            primaryId = ( ( RDB_SENSOR_OBJECT_t* ) element )->id;
            break;
            
        case RDB_PKG_ID_CAMERA:
            primaryId = ( ( RDB_CAMERA_t* ) element )->id;
            break;
            
        case RDB_PKG_ID_CONTACT_POINT:
            primaryId = ( ( RDB_CONTACT_POINT_t* ) element )->id;
            break;
            
        case RDB_PKG_ID_TRAFFIC_SIGN:
            primaryId = ( ( RDB_TRAFFIC_SIGN_t* ) element )->id;
            break;
            
        case RDB_PKG_ID_ROAD_STATE:
            primaryId = ( ( RDB_ROAD_STATE_t* ) element )->playerId;
            break;
            
        case RDB_PKG_ID_LIGHT_SOURCE:
            primaryId = ( ( RDB_LIGHT_SOURCE_t* ) element )->base.id;
            break;
            
        case RDB_PKG_ID_DRIVER_CTRL:
            primaryId = ( ( RDB_DRIVER_CTRL_t* ) element )->playerId;
            break;
            
        case RDB_PKG_ID_TRAFFIC_LIGHT:
            primaryId = ( ( RDB_TRAFFIC_LIGHT_t* ) element )->base.id;
            break;
            
        case RDB_PKG_ID_DRIVER_PERCEPTION:
            primaryId = ( ( RDB_DRIVER_PERCEPTION_t* ) element )->playerId;
            break;
            
        case RDB_PKG_ID_ROAD_QUERY:
            primaryId = ( ( RDB_ROAD_QUERY_t* ) element )->id;
            break;
            
        case RDB_PKG_ID_TRAJECTORY:
            primaryId = ( ( RDB_TRAJECTORY_t* ) element )->playerId;
            break;

        case RDB_PKG_ID_DYN_2_STEER:
            primaryId = ( ( RDB_DYN_2_STEER_t* ) element )->playerId;
            break;

        case RDB_PKG_ID_STEER_2_DYN:
            primaryId = ( ( RDB_STEER_2_DYN_t* ) element )->playerId;
            break;

        case RDB_PKG_ID_MOTION_SYSTEM:
            primaryId = ( ( RDB_MOTION_SYSTEM_t* ) element )->playerId;
            break;

        case RDB_PKG_ID_FREESPACE:
            primaryId = ( ( RDB_FREESPACE_t* ) element )->playerId;
            break;

        case RDB_PKG_ID_DYN_EL_SWITCH:
            primaryId = ( ( RDB_DYN_EL_SWITCH_t* ) element )->objectId;
            break;

        case RDB_PKG_ID_DYN_EL_DOF:
            primaryId = ( ( RDB_DYN_EL_DOF_t* ) element )->objectId;
            break;

        case RDB_PKG_ID_CUSTOM_SCORING:
            primaryId = ( ( RDB_CUSTOM_SCORING_t* ) element )->playerId;
            break;

        case RDB_PKG_ID_CUSTOM_OBJECT_CTRL_TRACK:
            primaryId = ( ( RDB_CUSTOM_OBJECT_CTRL_TRACK_t* ) element )->playerId;
            break;

        case RDB_PKG_ID_RAY:
            primaryId = ( ( RDB_RAY_t* ) element )->id;
            break;

        case RDB_PKG_ID_SYMBOL_STATE:
            primaryId = ( ( RDB_SYMBOL_STATE_t* ) element )->id;
            break;

        case RDB_PKG_ID_RADAR_HIT_POINT:
            primaryId = ( ( RDB_RADAR_HIT_POINT_t* ) element )->objectId;
            break;

        default:
            return false;
            break;
    }
    
    return true;
}


void*
RDBHandler::addPackage( RDB_MSG_t* & msg,   const double & simTime, const unsigned int & simFrame, 
                        unsigned int pkgId, unsigned int noElements, bool extended, size_t trailingData, 
                        bool isCustom )
{
    if ( !noElements )
        return 0;
    
    bool autoExtend = true;
    bool newEntry   = true;
    
    // get current size
    uint32_t dataSize      = msg ? msg->hdr.dataSize : 0;
    uint32_t totalSize     = dataSize + sizeof( RDB_MSG_HDR_t );
    uint32_t lastEntrySize = 0;  // current size of element if it already exists

    bool newMsg = ( !msg );
    
    uint32_t elemSize      = ( isCustom ? 0 : pkgId2size( pkgId, extended ) ) + trailingData;
    uint32_t addOnDataSize = noElements * elemSize;
    uint32_t addOnSize     = addOnDataSize;
    
    // is the package type and size the same as the last one? If so, extend the previous package instead
    // of including another entry headerSize
    if ( autoExtend && !newMsg )
    {
        char*                dataPtr   = ( ( char* ) msg ) + msg->hdr.headerSize;
        RDB_MSG_ENTRY_HDR_t* lastEntry = ( RDB_MSG_ENTRY_HDR_t* ) ( dataPtr );
        lastEntrySize                  = lastEntry->headerSize + lastEntry->dataSize;
        uint32_t remainingBytes        = msg->hdr.dataSize - lastEntrySize;
        
        while ( remainingBytes )
        {
            dataPtr        += lastEntrySize;
            lastEntry       = ( RDB_MSG_ENTRY_HDR_t* ) ( dataPtr );
            lastEntrySize   = lastEntry->headerSize + lastEntry->dataSize;
            remainingBytes -= lastEntrySize;
        }
        
        newEntry = ( lastEntry->pkgId != pkgId ) || ( lastEntry->elementSize != elemSize );
    }
    
    // a new header is required in-between
    if ( newEntry )
        addOnSize += sizeof( RDB_MSG_ENTRY_HDR_t );
    
    RDB_MSG_t* pNewMsg = ( RDB_MSG_t* ) ( realloc( msg, totalSize + addOnSize ) );
        
    if ( !pNewMsg )
    {
        fprintf( stderr, "RDBHandler::RDBaddPackage: out of memory.\n" );
        return 0;
    }
    
    //fprintf( stderr, "RDBHandler::RDBaddPackage: msg = %p, pNewMsg = %p\n", msg, pNewMsg );
    // now, message can be found at the new location
    msg = pNewMsg;
    
    // set header info (it might be new)
    msg->hdr.dataSize = dataSize + addOnSize;
    
    if ( newMsg )
    {
        msg->hdr.headerSize = sizeof( RDB_MSG_HDR_t );
        msg->hdr.version    = RDB_VERSION;
        msg->hdr.magicNo    = RDB_MAGIC_NO;
        msg->hdr.frameNo    = simFrame;
        msg->hdr.simTime    = simTime;
    }
    
    // now initialize the package itself
    char* dataPtr = ( char* ) msg;
    dataPtr += sizeof( RDB_MSG_HDR_t ) + dataSize;
    
    if ( !newEntry )
        dataPtr -= lastEntrySize;
        
    RDB_MSG_ENTRY_HDR_t* pEntry = ( RDB_MSG_ENTRY_HDR_t* ) ( dataPtr );
        
    // set entry parameters
    pEntry->headerSize  = sizeof( RDB_MSG_ENTRY_HDR_t );
    pEntry->dataSize    = newEntry ? addOnDataSize : ( pEntry->dataSize + addOnDataSize );
    pEntry->elementSize = elemSize;
    pEntry->pkgId       = pkgId;
    pEntry->flags       = extended ? RDB_PKG_FLAG_EXTENDED : RDB_PKG_FLAG_NONE;

    // initialize the trailing data
    dataPtr += newEntry ? pEntry->headerSize : lastEntrySize;
    
    if ( addOnDataSize )
        memset( dataPtr, 0, addOnDataSize );
    
    // compute new pointer for insertion of data
    return dataPtr;
}

void*
RDBHandler::addCustomPackage( RDB_MSG_t* & msg,   const double & simTime, const unsigned int & simFrame, 
                              unsigned int pkgId, unsigned int noElements, size_t elementSize )
{
    return addPackage( msg, simTime, simFrame, pkgId, noElements, false, elementSize, true );
}

void*
RDBHandler::getFirstEntry( const RDB_MSG_t* msg, unsigned int pkgId, unsigned int & noElements, bool extended )
{
    RDB_MSG_ENTRY_HDR_t* entryHdr = getEntryHdr( msg, pkgId, extended );
    
    if ( !entryHdr )
        return 0;
    
    noElements = entryHdr->elementSize ? ( entryHdr->dataSize / entryHdr->elementSize ) : 0;
                
    if ( !noElements && ( pkgId != RDB_PKG_ID_END_OF_FRAME ) && ( pkgId != RDB_PKG_ID_START_OF_FRAME ) )
        return 0;
                
    return ( ( char* ) entryHdr ) + entryHdr->headerSize;
}

RDB_MSG_ENTRY_HDR_t*
RDBHandler::getEntryHdr( const RDB_MSG_t* msg, unsigned int pkgId, bool extended )
{
    if ( !msg )
        return 0;

    size_t remainingBytes = msg->hdr.dataSize;
    char* dataPtr = ( char* ) &( msg->entryHdr );
    
    while ( remainingBytes )
    {
        RDB_MSG_ENTRY_HDR_t* entryHdr = ( RDB_MSG_ENTRY_HDR_t* ) dataPtr;

        if ( entryHdr->pkgId == pkgId )
        {
            if ( ( !extended && !( entryHdr->flags & RDB_PKG_FLAG_EXTENDED ) ) || ( extended && ( entryHdr->flags & RDB_PKG_FLAG_EXTENDED ) ) )
                return entryHdr;
        }
        
        dataPtr += ( entryHdr->headerSize + entryHdr->dataSize );
        remainingBytes -= ( entryHdr->headerSize + entryHdr->dataSize );
    }
    
    return 0;
}

char*
RDBHandler::getIdentString( unsigned char ident )
{
    unsigned int lastIdent = 255;
    static char  sIdentStr[256];

    if ( ident != lastIdent )
    {
        memset( sIdentStr, 0, 256 );
        memset( sIdentStr, ' ', ident );
    }
    
    return sIdentStr;
}

void
RDBHandler::print( const RDB_GEOMETRY_t & info, unsigned char ident, bool csv, bool csvHeader )
{
    if ( csvHeader )
    {
        fprintf( stderr, "%23s,%23s,%23s,%23s,%23s,%23s,", "dimX", "dimY", "dimZ", "offX", "offY", "offZ" );
        return;
    }
    
    if ( csv )
    {
        fprintf( stderr, "%+.16e,%+.16e,%+.16e,%+.16e,%+.16e,%+.16e,", info.dimX, info.dimY, info.dimZ, info.offX, info.offY, info.offZ );
        return;
    }
    
    char* identStr = getIdentString( ident );
    
    fprintf( stderr, "%sdim x / y / z = %.3f / %.3f / %.3f\n", identStr, info.dimX, info.dimY, info.dimZ ); 
    fprintf( stderr, "%soff x / y / z = %.3f / %.3f / %.3f\n", identStr, info.offX, info.offY, info.offZ ); 
}

void
RDBHandler::print( const RDB_COORD_SYSTEM_t & info, unsigned char ident, bool csv, bool csvHeader )
{
    if ( csvHeader )
    {
        fprintf( stderr, "%23s,", "id" );
        print( info.pos, ident + 4, csv, csvHeader );
        return;
    }
    
    if ( csv )
    {
        fprintf( stderr, "%23d,", info.id );
        print( info.pos, ident + 4, csv, csvHeader );
        return;
    }

    fprintf( stderr, "%sid = %d\n", getIdentString( ident ), info.id ); 
    fprintf( stderr, "%sposition\n", getIdentString( ident ) ); 
    print( info.pos, ident + 4 );
}

void
RDBHandler::print( const RDB_COORD_t & info, unsigned char ident, bool csv, bool csvHeader )
{ 
    if ( csvHeader )
    {
        fprintf( stderr, "%23s,%23s,%23s,%23s,%23s,%23s,%23s,%23s,%23s,", "x", "y", "z", "h", "p", "r", "flags", "type", "system" );
        return;
    }
    
    if ( csv )
    {
        fprintf( stderr, "%+.16e,%+.16e,%+.16e,%+.16e,%+.16e,%+.16e,%#23x,%23d,%23d,", info.x, info.y, info.z, 
                                                                                        info.h, info.p, info.r,
                                                                                        info.flags, info.type, info.system );
        return;
    }

    char* identStr = getIdentString( ident );
    
    fprintf( stderr, "%sx/y/z = %.6f / %.6f / %.6f\n", identStr, info.x, info.y, info.z ); 
    fprintf( stderr, "%sh/p/r = %.6f / %.6f / %.6f\n", identStr, info.h, info.p, info.r ); 
    fprintf( stderr, "%sflags = 0x%x, type = %s, system = %d\n", identStr, info.flags, coordType2string( info.type ).c_str(), info.system ); 
}

void
RDBHandler::print( const RDB_ROAD_POS_t & info, unsigned char ident, bool csv, bool csvHeader )
{
    if ( csvHeader )
    {
        fprintf( stderr, "%23s,%23s,%23s,%23s,%23s,%23s,%23s,%23s,%23s,%23s,%23s,%23s,", 
                         "playerId", "roadId", "laneId", "flags", "roadS", "roadT", 
                         "laneOffset", "hdgRel", "pitchRel", "rollRel", "roadType", "pathS" );        
        return;
    }
    
    if ( csv )
    {
        fprintf( stderr, "%23d,%23d,%23d,%#23x,%+.16e,%+.16e,%+.16e,%+.16e,%+.16e,%+.16e,%23d,%+.16e,", 
                         info.playerId, info.roadId, info.laneId, info.flags, info.roadS, info.roadT, 
                         info.laneOffset, info.hdgRel, info.pitchRel, info.rollRel, info.roadType, info.pathS );
        return;
    }
    
    char* identStr = getIdentString( ident );

    fprintf( stderr, "%splayerId roadId laneId flags      roadS       roadT   laneOffset     hdgRel   pitchRel    rollRel roadType      pathS\n", identStr );
    fprintf( stderr, "%s%8d %6d %6d  0x%02x %+10.3f %+10.3f   %+10.3f %+10.3f %+10.3f %+10.3f %9d %+10.3f\n", 
                      identStr, info.playerId, info.roadId, info.laneId, info.flags, 
                      info.roadS, info.roadT, info.laneOffset, info.hdgRel, info.pitchRel, 
                      info.rollRel, info.roadType, info.pathS ); 
/*
    fprintf( stderr, "%splayerId   = %d\n",    identStr, info.playerId   ); 
    fprintf( stderr, "%sroadId     = %d\n",    identStr, info.roadId     ); 
    fprintf( stderr, "%slaneId     = %d\n",    identStr, info.laneId     ); 
    fprintf( stderr, "%sflags      = 0x%x\n",  identStr, info.flags      ); 
    fprintf( stderr, "%sroadS      = %.3f\n",  identStr, info.roadS      ); 
    fprintf( stderr, "%sroadT      = %.3f\n",  identStr, info.roadT      ); 
    fprintf( stderr, "%slaneOffset = %.3f\n",  identStr, info.laneOffset ); 
    fprintf( stderr, "%shdgRel     = %.3f\n",  identStr, info.hdgRel     ); 
    fprintf( stderr, "%spitchRel   = %.3f\n",  identStr, info.pitchRel   ); 
    fprintf( stderr, "%srollRel    = %.3f\n",  identStr, info.rollRel    ); 
    fprintf( stderr, "%sroadType   = %d\n",    identStr, info.roadType   ); 
    fprintf( stderr, "%spathS      = %.3f\n",  identStr, info.pathS      ); 
*/
}

void
RDBHandler::print( const RDB_LANE_INFO_t & info, unsigned char ident, bool csv, bool csvHeader )
{
    if ( csvHeader )
    {
        fprintf( stderr, "%23s,%23s,%23s,%23s,%23s,%23s,%23s,%23s,%23s,%23s,%23s,%23s,%23s,%23s,", 
                         "roadId", "id", "neighborMask", "leftLaneId", "rightLaneId", "borderType", "material", 
                         "status", "width", "curvVert", "curvVertDot", "curvHor", "curvHorDot", "playerId" );        
        return;
    }
    
    if ( csv )
    {
        fprintf( stderr, "%23d,%23d,%#23x,%23d,%23d,%23d,%23d,%23d,%+.16e,%+.16e,%+.16e,%+.16e,%+.16e,%23d,", 
                         info.roadId, info.id, info.neighborMask, info.leftLaneId, info.rightLaneId, info.borderType, info.material, 
                         info.status, info.width, info.curvVert, info.curvVertDot, info.curvHor, info.curvHorDot, info.playerId );
        return;
    }
    
    char* identStr = getIdentString( ident );
    
    fprintf( stderr, "%splayerId roadId     id neighborMask leftLaneId rightLaneId   borderType material   status width    curvVert curvVertDot      curvHor  curvHorDot    type\n", identStr );
    fprintf( stderr, "%s%8d %6d %6d  0x%02x %+10d %+10d %+8d %+8d %+8d %+10.3f %+10.6f %+10.6f %+10.6f %+10.6f %+8d\n", 
                     identStr, info.playerId, info.roadId, info.id, info.neighborMask, info.leftLaneId, info.rightLaneId, info.borderType, 
                     info.material, info.status, info.width, info.curvVert, info.curvVertDot, info.curvHor, info.curvHorDot, info.type );

/*
    fprintf( stderr, "%sroadId       = %d\n",    identStr, info.roadId       ); 
    fprintf( stderr, "%sid           = %d\n",    identStr, info.id           ); 
    fprintf( stderr, "%sneighborMask = 0x%x\n",  identStr, info.neighborMask ); 
    fprintf( stderr, "%sleftLaneId   = %d\n",    identStr, info.leftLaneId   ); 
    fprintf( stderr, "%srightLaneId  = %d\n",    identStr, info.rightLaneId  ); 
    fprintf( stderr, "%sborderType   = %d\n",    identStr, info.borderType   ); 
    fprintf( stderr, "%smaterial     = %d\n",    identStr, info.material     ); 
    fprintf( stderr, "%sstatus       = %d\n",    identStr, info.status       ); 
    fprintf( stderr, "%swidth        = %.3f\n",  identStr, info.width        ); 
    fprintf( stderr, "%scurvVert     = %.6lf\n", identStr, info.curvVert     ); 
    fprintf( stderr, "%scurvVertDot  = %.6lf\n", identStr, info.curvVertDot  ); 
    fprintf( stderr, "%scurvHor      = %.6lf\n", identStr, info.curvHor      ); 
    fprintf( stderr, "%scurvHorDot   = %.6lf\n", identStr, info.curvHorDot   ); 
    fprintf( stderr, "%splayerId     = %d\n",    identStr, info.playerId     );
    */
}

void
RDBHandler::print( const RDB_ROADMARK_t & info, unsigned char ident, bool csv, bool csvHeader )
{
    if ( csvHeader )
    {
        fprintf( stderr, "%23s,%23s,%23s,%23s,%23s,%23s,%23s,%23s,%23s,%23s,%23s,%23s,%23s,%23s,%23s,%23s,", 
                         "playerId", "id", "prevId", "nextId", "lateralDist", "yawRel", "curvHor", "curvHorDot", 
                         "startDx", "previewDx", "width", "height", "curvVert", "curvVertDot", "type", "color" );        
        return;
    }
    
    if ( csv )
    {
        fprintf( stderr, "%23d,%23d,%23d,%23d,%+.16e,%+.16e,%+.16e,%+.16e,%+.16e,%+.16e,%+.16e,%+.16e,%+.16e,%+.16e,%23d,%23d,", 
                         info.playerId, info.id, info.prevId, info.nextId, info.lateralDist, info.yawRel, info.curvHor, info.curvHorDot, 
                         info.startDx, info.previewDx, info.width, info.height, info.curvVert, info.curvVertDot,  info.type, info.color );
        return;
    }
    
    char* identStr = getIdentString( ident );
    
    fprintf( stderr, "%splayerId     = %d\n",    identStr, info.playerId     ); 
    fprintf( stderr, "%sid           = %d\n",    identStr, info.id           ); 
    fprintf( stderr, "%sprevId       = %d\n",    identStr, info.prevId       ); 
    fprintf( stderr, "%snextId       = %d\n",    identStr, info.nextId       ); 
    fprintf( stderr, "%slateralDist  = %.3f\n",  identStr, info.lateralDist  ); 
    fprintf( stderr, "%syawRel       = %.3f\n",  identStr, info.yawRel       ); 
    fprintf( stderr, "%scurvHor      = %.6f\n",  identStr, info.curvHor      ); 
    fprintf( stderr, "%scurvHorDot   = %.6f\n",  identStr, info.curvHorDot   ); 
    fprintf( stderr, "%sstartDx      = %.3f\n",  identStr, info.startDx      ); 
    fprintf( stderr, "%spreviewDx    = %.3f\n",  identStr, info.previewDx    ); 
    fprintf( stderr, "%swidth        = %.3f\n",  identStr, info.width        ); 
    fprintf( stderr, "%sheight       = %.3f\n",  identStr, info.height       ); 
    fprintf( stderr, "%scurvVert     = %.6f\n",  identStr, info.curvVert     ); 
    fprintf( stderr, "%scurvVertDot  = %.6f\n",  identStr, info.curvVertDot  ); 
    fprintf( stderr, "%stype         = %d\n",    identStr, info.type         ); 
    fprintf( stderr, "%scolor        = %d\n",    identStr, info.color        ); 
    fprintf( stderr, "%sroadId       = %d\n",    identStr, info.roadId       ); 
    fprintf( stderr, "%slaneId       = %d\n",    identStr, info.laneId       ); 
    fprintf( stderr, "%snoDataPoints = %d\n",    identStr, info.noDataPoints );

    if ( info.noDataPoints )
    {
        RDB_POINT_t* pt = ( RDB_POINT_t* ) ( ( ( unsigned char* ) ( &info ) ) + sizeof( RDB_ROADMARK_t ) );
                            
        for ( int i = 0; i < info.noDataPoints; i++ )
            print( pt[i], ident + 4 );
    }
}

void
RDBHandler::print( const RDB_OBJECT_CFG_t & info, unsigned char ident, bool csv, bool csvHeader )
{
    if ( csvHeader )
    {
        fprintf( stderr, "%23s,%23s,%23s,%23s,%23s,%23s,%23s,%23s,", 
                         "id", "category", "type", "modelId", "name", "modelName", "fileName", "flags" );        
        return;
    }
    
    if ( csv )
    {
        fprintf( stderr, "%23d,%23d,%23d,%23d,%23s,%23s,%23s,%#23x,", 
                         info.id, info.category, info.type, info.modelId, info.name, info.modelName, info.fileName, info.flags );
        return;
    }
    
    char* identStr = getIdentString( ident );
    
    fprintf( stderr, "%sid        = %d\n",    identStr, info.id        ); 
    fprintf( stderr, "%scategory  = %s\n",    identStr, objectCategory2string( info.category ).c_str() ); 
    fprintf( stderr, "%stype      = %s\n",    identStr, objectType2string( info.type ).c_str()         ); 
    fprintf( stderr, "%smodelId   = %d\n",    identStr, info.modelId   ); 
    fprintf( stderr, "%sname      = %s\n",    identStr, info.name      ); 
    fprintf( stderr, "%smodelName = %s\n",    identStr, info.modelName ); 
    fprintf( stderr, "%sfileName  = %s\n",    identStr, info.fileName  ); 
    fprintf( stderr, "%sflags     = 0x%x\n",  identStr, info.flags     ); 
}

void
RDBHandler::print( const RDB_OBJECT_STATE_t & state, bool extended, unsigned char ident, bool csv, bool csvHeader )
{
    if ( csvHeader )
    {
        fprintf( stderr, "%23s,%23s,%23s,%23s,%23s,", "objectId", "category", "type", "vismask", "name" );
        
        print( state.base.geo, ident + 4,  csv, csvHeader );
        print( state.base.pos, ident + 4,  csv, csvHeader );

        if ( !extended )
            return;
        
        print( state.ext.speed, ident + 4, csv, csvHeader );
        print( state.ext.accel, ident + 4, csv, csvHeader );
        
        fprintf( stderr, "%23s,", "distance" ); // added, see ticket #5906
        return;
    }
    
    if ( csv )
    {
        fprintf( stderr, "%+23d,%23d,%23d,%#23x,%23s,", state.base.id, state.base.category, state.base.type,
                                                       state.base.visMask, state.base.name);
        print( state.base.geo, ident + 4,  csv, csvHeader );
        print( state.base.pos, ident + 4,  csv, csvHeader );

        if ( !extended )
            return;
        
        print( state.ext.speed, ident + 4, csv, csvHeader );
        print( state.ext.accel, ident + 4, csv, csvHeader );

        fprintf( stderr, "%+.16e,", state.ext.traveledDist ); // added, see ticket #5906
        return;
    }

    char* identStr = getIdentString( ident );
    
    fprintf( stderr, "%sid       = %d\n",   identStr, state.base.id       ); 
    fprintf( stderr, "%scategory = %s\n",   identStr, objectCategory2string( state.base.category ).c_str() ); 
    fprintf( stderr, "%stype     = %s\n",   identStr, objectType2string( state.base.type ).c_str()         ); 
    fprintf( stderr, "%svisMask  = 0x%x\n", identStr, state.base.visMask  ); 
    fprintf( stderr, "%sname     = %s\n",   identStr, state.base.name     ); 
    
    fprintf( stderr, "%sgeometry\n", getIdentString( ident ) ); 
    print( state.base.geo, ident + 4 );
    
    fprintf( stderr, "%sposition\n", getIdentString( ident ) ); 
    print( state.base.pos, ident + 4 );
    
    identStr = getIdentString( ident );
    fprintf( stderr, "%sparent     = %d\n",   identStr, state.base.parent     ); 
    fprintf( stderr, "%scfgFlags   = 0x%x\n", identStr, state.base.cfgFlags   ); 
    fprintf( stderr, "%scfgModelId = %d\n",   identStr, state.base.cfgModelId ); 
    
    if ( !extended )
        return;

    fprintf( stderr, "%sspeed\n", getIdentString( ident ) ); 
    print( state.ext.speed, ident + 4 );
    
    fprintf( stderr, "%sacceleration\n", getIdentString( ident ) ); 
    print( state.ext.accel, ident + 4 );
    
    fprintf( stderr, "%sdistance = %.3f\n", getIdentString( ident ), state.ext.traveledDist ); 
}

void
RDBHandler::print( const RDB_VEHICLE_SYSTEMS_t & info, unsigned char ident, bool csv, bool csvHeader )
{
    if ( csvHeader )
    {
        fprintf( stderr, "%23s,%23s,%23s,%23s,%23s,%23s,%23s,%23s,%23s,%23s,",
                         "playerId", "lightMask", "steering", "steeringWheelTorque",
                         "accMask", "accSpeed", "batteryState", "batteryRate", "displayLightMask", "fuelGauge");      // Ticket #11664
        return;
    }
    
    if ( csv )
    {
        fprintf( stderr, "%23d,%#23x,%+.16e,%+.16e,%#23x,%23d,%23d,%23d,%#23x,%23d,",
                         info.playerId, info.lightMask, info.steering, info.steeringWheelTorque,
                         info.accMask,  info.accSpeed, info.batteryState, info.batteryRate, info.displayLightMask, info.fuelGauge );    // Ticket #11664
        return;
    }
    
    char* identStr = getIdentString( ident );
    fprintf( stderr, "%splayerId            = %d\n",   identStr, info.playerId            ); 
    fprintf( stderr, "%slightMask           = 0x%x\n", identStr, info.lightMask           );
    fprintf( stderr, "%ssteering            = %.3f\n", identStr, info.steering            ); 
    fprintf( stderr, "%ssteeringWheelTorque = %.3f\n", identStr, info.steeringWheelTorque ); 
    fprintf( stderr, "%saccMask             = 0x%x\n", identStr, info.accMask             );    // Ticket #11664
    fprintf( stderr, "%saccSpeed            = %d\n",   identStr, info.accSpeed            );    // Ticket #11664
    fprintf( stderr, "%sbatteryState        = %d\n",   identStr, info.batteryState        );    // Ticket #11664
    fprintf( stderr, "%sbatteryRate         = %d\n",   identStr, info.batteryRate         );    // Ticket #11664
    fprintf( stderr, "%sdisplayLightMask    = 0x%x\n", identStr, info.displayLightMask    );    // Ticket #11664
    fprintf( stderr, "%sfuelGauge           = %d\n",   identStr, info.fuelGauge           );    // Ticket #11664

}

void
RDBHandler::print( const RDB_VEHICLE_SETUP_t & info, unsigned char ident, bool csv, bool csvHeader )
{
    if ( csvHeader )
    {
        fprintf( stderr, "%23s,%23s,%23s,", 
                         "playerId", "mass", "wheelBase" );        
        return;
    }
    
    if ( csv )
    {
        fprintf( stderr, "%23d,%+.16e,%+.16e,", 
                         info.playerId, info.mass, info.wheelBase );
        return;
    }
    
    char* identStr = getIdentString( ident );
    
    fprintf( stderr, "%splayerId  = %d\n",   identStr, info.playerId  ); 
    fprintf( stderr, "%smass      = %.3f\n", identStr, info.mass      ); 
    fprintf( stderr, "%swheelBase = %.3f\n", identStr, info.wheelBase ); 
}

void
RDBHandler::print( const RDB_ENGINE_t & info, bool extended, unsigned char ident, bool csv, bool csvHeader )
{
    if ( csvHeader )
    {
        fprintf( stderr, "%23s,%23s,%23s,", 
                         "playerId", "rps", "load" );
        
        if ( !extended )
            return;
        
        fprintf( stderr, "%23s,%23s,%23s,%23s,%23s,%23s,%23s,", 
                         "rpsStart", "torque", "torqueInner", "torqueMax", "torqueFriction", "fuelCurrent", "fuelAverage" );

        return;
    }
    
    if ( csv )
    {
        fprintf( stderr, "%23d,%+.16e,%+.16e,", 
                         info.base.playerId, info.base.rps, info.base.load );

        if ( !extended )
            return;
        
        fprintf( stderr, "%+.16e,%+.16e,%+.16e,%+.16e,%+.16e,%+.16e,%+.16e,", 
                         info.ext.rpsStart, info.ext.torque, info.ext.torqueInner, info.ext.torqueMax, info.ext.torqueFriction, 
                         info.ext.fuelCurrent, info.ext.fuelAverage );

        return;
    }
    
    char* identStr = getIdentString( ident );
    
    fprintf( stderr, "%splayerId        = %d\n",   identStr, info.base.playerId ); 
    fprintf( stderr, "%srps             = %.3f\n", identStr, info.base.rps      ); 
    fprintf( stderr, "%sload            = %.3f\n", identStr, info.base.load     );
    
    if ( !extended )
        return;

    fprintf( stderr, "%srpsStart        = %.3f\n", identStr, info.ext.rpsStart       ); 
    fprintf( stderr, "%storque          = %.3f\n", identStr, info.ext.torque         );
    fprintf( stderr, "%storqueInner     = %.3f\n", identStr, info.ext.torqueInner    ); 
    fprintf( stderr, "%storqueMax       = %.3f\n", identStr, info.ext.torqueMax      );
    fprintf( stderr, "%storqueFriction  = %.3f\n", identStr, info.ext.torqueFriction ); 
    fprintf( stderr, "%sfuelCurrent     = %.3f\n", identStr, info.ext.fuelCurrent    );
    fprintf( stderr, "%sfuelAverage     = %.3f\n", identStr, info.ext.fuelAverage    ); 
}

void
RDBHandler::print( const RDB_DRIVETRAIN_t & info, bool extended, unsigned char ident, bool csv, bool csvHeader )
{
    if ( csvHeader )
    {
        fprintf( stderr, "%23s,%23s,%23s,%23s,", 
                         "playerId", "gearBoxType", "driveTrainType", "gear" );
        
        if ( !extended )
            return;
        
        fprintf( stderr, "%23s,%23s,%23s,", 
                         "torqueGearBoxIn", "torqueCenterDiffOut", "torqueShaft" );

        return;
    }
    
    if ( csv )
    {
        fprintf( stderr, "%23d,%23d,%23d,%23d,", 
                         info.base.playerId, info.base.gearBoxType, info.base.driveTrainType, info.base.gear );

        if ( !extended )
            return;
        
        fprintf( stderr, "%+.16e,%+.16e,%+.16e,", 
                         info.ext.torqueGearBoxIn, info.ext.torqueCenterDiffOut, info.ext.torqueShaft );

        return;
    }
    
    char* identStr = getIdentString( ident );
    
    fprintf( stderr, "%splayerId            = %d\n",   identStr, info.base.playerId       ); 
    fprintf( stderr, "%sgearBoxType         = %d\n",   identStr, info.base.gearBoxType    ); 
    fprintf( stderr, "%sdriveTrainType      = %d\n",   identStr, info.base.driveTrainType ); 
    fprintf( stderr, "%sgear                = %d\n",   identStr, info.base.gear           ); 

    if ( !extended )
        return;

    fprintf( stderr, "%storqueGearBoxIn     = %.3f\n", identStr, info.ext.torqueGearBoxIn     ); 
    fprintf( stderr, "%storqueCenterDiffOut = %.3f\n", identStr, info.ext.torqueCenterDiffOut );
    fprintf( stderr, "%storqueShaft         = %.3f\n", identStr, info.ext.torqueShaft         ); 
}

void
RDBHandler::print( const RDB_WHEEL_t & info, bool extended, unsigned char ident, bool csv, bool csvHeader )
{
    if ( csvHeader )
    {
        fprintf( stderr, "%23s,%23s,%23s,%23s,%23s,%23s,%23s,%23s,", 
                         "playerId", "id", "flags", "radiusStatic", "springCompression", "rotAngle", "slip", "steeringAngle" );
        
        if ( !extended )
            return;
        
        fprintf( stderr, "%23s,%23s,%23s,%23s,%23s,%23s,%23s,%23s,%23s,%23s,%23s,%23s,%23s,%23s,%23s,", 
                         "vAngular", "forceZ", "forceLat", "forceLong", "forceTireWheelX", "forceTireWheelY", "forceTireWheelZ", 
                         "radiusDynamic", "brakePressure", "torqueDriveShaft", "damperSpeed", "vAngular", "forceZ", "forceLat", "forceLong" );

        return;
    }
    
    if ( csv )
    {
        fprintf( stderr, "%23d,%23d,%#23x,%+.16e,%+.16e,%+.16e,%+.16e,%+.16e,", 
                         info.base.playerId, info.base.id, info.base.flags, info.base.radiusStatic, 
                         info.base.springCompression, info.base.rotAngle, info.base.slip, info.base.steeringAngle );

        if ( !extended )
            return;
        
        fprintf( stderr, "%+.16e,%+.16e,%+.16e,%+.16e,%+.16e,%+.16e,%+.16e,%+.16e,%+.16e,%+.16e,%+.16e,%+.16e,%+.16e,%+.16e,%+.16e,", 
                         info.ext.vAngular, info.ext.forceZ, info.ext.forceLat, info.ext.forceLong, info.ext.forceTireWheelXYZ[0], 
                         info.ext.forceTireWheelXYZ[1], info.ext.forceTireWheelXYZ[2], info.ext.radiusDynamic, info.ext.brakePressure, info.ext.torqueDriveShaft, 
                         info.ext.damperSpeed, info.ext.vAngular, info.ext.forceZ, info.ext.forceLat, info.ext.forceLong );

        return;
    }

    char* identStr = getIdentString( ident );
    
    fprintf( stderr, "%splayerId             = %d\n",   identStr, info.base.playerId          ); 
    fprintf( stderr, "%sid                   = %d\n",   identStr, info.base.id                ); 
    fprintf( stderr, "%sflags                = 0x%x\n", identStr, info.base.flags             ); 
    fprintf( stderr, "%sradiusStatic         = %.3f\n", identStr, info.base.radiusStatic      ); 
    fprintf( stderr, "%sspringCompression    = %.3f\n", identStr, info.base.springCompression ); 
    fprintf( stderr, "%srotAngle             = %.3f\n", identStr, info.base.rotAngle          ); 
    fprintf( stderr, "%sslip                 = %.3f\n", identStr, info.base.slip              ); 
    fprintf( stderr, "%ssteeringAngle        = %.3f\n", identStr, info.base.steeringAngle     ); 

    if ( !extended )
        return;

    fprintf( stderr, "%svAngular             = %.3f\n", identStr, info.ext.vAngular             ); 
    fprintf( stderr, "%sforceZ               = %.3f\n", identStr, info.ext.forceZ               ); 
    fprintf( stderr, "%sforceLat             = %.3f\n", identStr, info.ext.forceLat             ); 
    fprintf( stderr, "%sforceLong            = %.3f\n", identStr, info.ext.forceLong            ); 
    fprintf( stderr, "%sforceTireWheelXYZ[0] = %.3f\n", identStr, info.ext.forceTireWheelXYZ[0] ); 
    fprintf( stderr, "%sforceTireWheelXYZ[1] = %.3f\n", identStr, info.ext.forceTireWheelXYZ[1] ); 
    fprintf( stderr, "%sforceTireWheelXYZ[2] = %.3f\n", identStr, info.ext.forceTireWheelXYZ[2] ); 
    fprintf( stderr, "%sradiusDynamic        = %.3f\n", identStr, info.ext.radiusDynamic        ); 
    fprintf( stderr, "%sbrakePressure        = %.3f\n", identStr, info.ext.brakePressure        ); 
    fprintf( stderr, "%storqueDriveShaft     = %.3f\n", identStr, info.ext.torqueDriveShaft     ); 
    fprintf( stderr, "%sdamperSpeed          = %.3f\n", identStr, info.ext.damperSpeed          ); 
    fprintf( stderr, "%svAngular             = %.3f\n", identStr, info.ext.vAngular             ); 
    fprintf( stderr, "%sforceZ               = %.3f\n", identStr, info.ext.forceZ               ); 
    fprintf( stderr, "%sforceLat             = %.3f\n", identStr, info.ext.forceLat             ); 
    fprintf( stderr, "%sforceLong            = %.3f\n", identStr, info.ext.forceLong            ); 
}

void
RDBHandler::print( const RDB_PED_ANIMATION_t & info, unsigned char ident, bool csv, bool csvHeader )
{
    if ( csvHeader )
    {
        fprintf( stderr, "%23s", "pedAnimation" );
        return;
    }

    if ( csv )
    {
        fprintf( stderr, "%23s", "n/a" );
        return;
    }

    char* identStr = getIdentString( ident );
    
    fprintf( stderr, "%splayerId = %d\n",   identStr, info.playerId ); 

    fprintf( stderr, "%sposition\n", identStr ); 
    print( info.pos, ident + 4 );
    
    fprintf( stderr, "%snoCoords = %d\n", getIdentString( ident ), info.noCoords ); 
    fprintf( stderr, "%sdataSize = %d\n", getIdentString( ident ), info.dataSize ); 
}

void
RDBHandler::print( const RDB_SENSOR_STATE_t & info, unsigned char ident, bool csv, bool csvHeader )
{
    if ( csvHeader )
    {
        fprintf( stderr, "%23s,%23s,%23s,%23s,%23s,%23s,%23s,%23s,", 
                         "id", "type", "hostCategory", "name", "fovH", "fovV", "clipNear", "clipFar" );
        print( info.pos,            ident + 4, csv, csvHeader );
        print( info.originCoordSys, ident + 4, csv, csvHeader );
        return;
    }
    
    if ( csv )
    {
        fprintf( stderr, "%23d,%23d,%23d,%23s,%+.16e,%+.16e,%+.16e,%+.16e,", 
                 info.id, info.type, info.hostCategory, info.name, info.fovHV[0], info.fovHV[1], info.clipNF[0], info.clipNF[1] );
        print( info.pos,            ident + 4, csv, csvHeader );
        print( info.originCoordSys, ident + 4, csv, csvHeader );
        return;
    }
    
    char* identStr = getIdentString( ident );
    
    fprintf( stderr, "%sid           = %d\n",   identStr, info.id           ); 
    fprintf( stderr, "%stype         = %d\n",   identStr, info.type         ); 
    fprintf( stderr, "%shostCategory = %d\n",   identStr, info.hostCategory ); 
    fprintf( stderr, "%sname         = %s\n",   identStr, info.name         ); 
    fprintf( stderr, "%sfovHV[0]     = %.3f\n", identStr, info.fovHV[0]     ); 
    fprintf( stderr, "%sfovHV[1]     = %.3f\n", identStr, info.fovHV[1]     ); 
    fprintf( stderr, "%sfovOffHV[0]  = %.3f\n", identStr, info.fovOffHV[0]  ); 
    fprintf( stderr, "%sfovOffHV[1]  = %.3f\n", identStr, info.fovOffHV[1]  ); 
    fprintf( stderr, "%sclipNF[0]    = %.3f\n", identStr, info.clipNF[0]    ); 
    fprintf( stderr, "%sclipNF[1]    = %.3f\n", identStr, info.clipNF[1]    ); 

    fprintf( stderr, "%sposition\n", identStr ); 
    print( info.pos, ident + 4 );
    
    fprintf( stderr, "%soriginCoordSys\n", getIdentString( ident ) ); 
    print( info.originCoordSys, ident + 4 );
}

void
RDBHandler::print( const RDB_SENSOR_OBJECT_t & info, unsigned char ident, bool csv, bool csvHeader )
{
    if ( csvHeader )
    {
        fprintf( stderr, "%23s,%23s,%23s,%23s,%23s,%23s,%23s,%23s,", 
                         "category", "type", "flags", "id", "sensorId", "dist", "occlusion", "deltaLane" );
        print( info.sensorPos, ident + 4, csv, csvHeader );
        return;
    }
    
    if ( csv )
    {
        fprintf( stderr, "%23d,%23d,%#23x,%23d,%23d,%+.16e,%23d,%23d,", 
                 info.category, info.type, info.flags, info.id, info.sensorId, info.dist, info.occlusion, info.deltaLanePos );
        print( info.sensorPos, ident + 4, csv, csvHeader );
        return;
    }
    
    char* identStr = getIdentString( ident );
    
    fprintf( stderr, "%scategory = %d\n",    identStr, info.category ); 
    fprintf( stderr, "%stype     = %d\n",    identStr, info.type     ); 
    fprintf( stderr, "%sflags    = 0x%x\n",  identStr, info.flags    ); 
    fprintf( stderr, "%sid       = %d\n",    identStr, info.id       ); 
    fprintf( stderr, "%ssensorId = %d\n",    identStr, info.sensorId ); 
    fprintf( stderr, "%sdist     = %.3f\n",  identStr, info.dist     ); 

    fprintf( stderr, "%ssensorPos\n", identStr ); 
    print( info.sensorPos, ident + 4 );
    
    fprintf( stderr, "%socclusion    = %d\n", getIdentString( ident ), info.occlusion ); 
    fprintf( stderr, "%sdeltaLanePos = %d\n", getIdentString( ident ), info.deltaLanePos ); 
}

void
RDBHandler::print( const RDB_CAMERA_t & info, unsigned char ident, bool csv, bool csvHeader )
{
    if ( csvHeader )
    {
        fprintf( stderr, "%23s,%23s,%23s,%23s,%23s,%23s,%23s,%23s,%23s,", 
                         "id", "width", "height", "clipNear", "clipFar", "focalX", "focalY", "principalX", "principalY" );
        print( info.pos, ident + 4, csv, csvHeader );
        return;
    }
    
    if ( csv )
    {
        fprintf( stderr, "%23d,%23d,%23d,%+.16e,%+.16e,%+.16e,%+.16e,%+.16e,%+.16e,", 
                 info.id, info.width, info.height, info.clipNear, info.clipFar, info.focalX, info.focalY, info.principalX, info.principalY );
        print( info.pos, ident + 4, csv, csvHeader );
        return;
    }
    
    char* identStr = getIdentString( ident );
    
    fprintf( stderr, "%sid         = %d\n",   identStr, info.id         );
    fprintf( stderr, "%swidth      = %d\n",   identStr, info.width      );
    fprintf( stderr, "%sheight     = %d\n",   identStr, info.height     );
    fprintf( stderr, "%sclipNear   = %.3f\n", identStr, info.clipNear   );
    fprintf( stderr, "%sclipFar    = %.3f\n", identStr, info.clipFar    );
    fprintf( stderr, "%sfocalX     = %.3f\n", identStr, info.focalX     );
    fprintf( stderr, "%sfocalY     = %.3f\n", identStr, info.focalY     );
    fprintf( stderr, "%sprincipalX = %.3f\n", identStr, info.principalX );
    fprintf( stderr, "%sprincipalY = %.3f\n", identStr, info.principalY );

    fprintf( stderr, "%sposition\n", identStr ); 
    print( info.pos, ident + 4 );
}

void
RDBHandler::print( const RDB_CONTACT_POINT_t & info, unsigned char ident, bool csv, bool csvHeader )
{
    if ( csvHeader )
    {
        fprintf( stderr, "%23s,%23s,", "id", "flags" );
        print( info.roadDataIn, ident + 4, csv, csvHeader );
        fprintf( stderr, "%23s,%23s,", "friction", "playerId" );
        return;
    }
    
    if ( csv )
    {
        fprintf( stderr, "%23d,%#23x,", info.id, info.flags );
        print( info.roadDataIn, ident + 4, csv, csvHeader );
        fprintf( stderr, "%+.16e,%23d,", info.friction, info.playerId );
        return;
    }
    
    char* identStr = getIdentString( ident );
    
    fprintf( stderr, "%sid        = %d\n",   identStr, info.id    );
    fprintf( stderr, "%sflags     = 0x%x\n", identStr, info.flags );

    fprintf( stderr, "%sroadDataIn\n", identStr ); 
    print( info.roadDataIn, ident + 4 );

    fprintf( stderr, "%sfriction  = %.3f\n", getIdentString( ident ), info.friction );
    fprintf( stderr, "%splayerId  = %d\n",   getIdentString( ident ), info.playerId );
}

void
RDBHandler::print( const RDB_TRAFFIC_SIGN_t & info, unsigned char ident, bool csv, bool csvHeader )
{
    if ( csvHeader )
    {
        fprintf( stderr, "%23s,%23s,%23s,", "id", "playerId", "roadDist" );
        print( info.pos, ident + 4, csv, csvHeader );
        fprintf( stderr, "%23s,%23s,%23s,%23s,%23s,%23s,%23s,%23s,%23s,", "type", "subType", "value", "state", 
                                                                          "readability", "occlusion", "addOnId",
                                                                          "minLane", "maxLane" );
        return;
    }
    
    if ( csv )
    {
        fprintf( stderr, "%23d,%23d,%+.16e,", info.id, info.playerId, info.roadDist );
        print( info.pos, ident + 4, csv, csvHeader );
        fprintf( stderr, "%23d,%23d,%+.16e,%23d,%23d,%23d,%23d,%23d,%23d,", 
                         info.type, info.subType, info.value, info.state, info.readability, 
                         info.occlusion, info.addOnId, info.minLane, info.maxLane );
        return;
    }
    
    char* identStr = getIdentString( ident );
    
    fprintf( stderr, "%sid          = %d\n",   identStr, info.id       );
    fprintf( stderr, "%splayerId    = %d\n",   identStr, info.playerId );
    fprintf( stderr, "%sroadDist    = %.3f\n", identStr, info.roadDist );

    fprintf( stderr, "%sposition\n", identStr ); 
    print( info.pos, ident + 4 );
    
    identStr = getIdentString( ident );
    fprintf( stderr, "%stype        = %d\n",   identStr, info.type        );
    fprintf( stderr, "%ssubType     = %d\n",   identStr, info.subType     );
    fprintf( stderr, "%svalue       = %.3f\n", identStr, info.value       );
    fprintf( stderr, "%sstate       = %d\n",   identStr, info.state       );
    fprintf( stderr, "%sreadability = %d\n",   identStr, info.readability );
    fprintf( stderr, "%socclusion   = %d\n",   identStr, info.occlusion   );
    fprintf( stderr, "%saddOnId     = %d\n",   identStr, info.addOnId     );
    fprintf( stderr, "%sminLane     = %d\n",   identStr, info.minLane     );
    fprintf( stderr, "%smaxLane     = %d\n",   identStr, info.maxLane     );
}

void
RDBHandler::print( const RDB_ROAD_STATE_t & info, unsigned char ident, bool csv, bool csvHeader )
{
    if ( csvHeader )
    {
        fprintf( stderr, "%23s,%23s,%23s,%23s,%23s,%23s,%23s", "playerId", "wheelId", "roadId", "defaultSpeed", "waterLevel", "eventMask", "distToJunc" );
        return;
    }
    
    if ( csv )
    {
        fprintf( stderr, "%23d,%23d,%23d,%+.16e,%+.16e,%#23x,%+.16e", info.playerId, info.wheelId, info.roadId, info.defaultSpeed, info.waterLevel, info.eventMask, info.distToJunc );
        return;
    }
    
    char* identStr = getIdentString( ident );
    
    fprintf( stderr, "%splayerId     = %d\n",   identStr, info.playerId     );
    fprintf( stderr, "%swheelId      = %d\n",   identStr, info.wheelId      );
    fprintf( stderr, "%sroadId       = %d\n",   identStr, info.roadId       );
    fprintf( stderr, "%sdefaultSpeed = %.3f\n", identStr, info.defaultSpeed );
    fprintf( stderr, "%swaterLevel   = %.3f\n", identStr, info.waterLevel   );
    fprintf( stderr, "%seventMask    = 0x%x\n", identStr, info.eventMask    );
    fprintf( stderr, "%sdistToJunc   = %.3f\n", identStr, info.distToJunc    );
}
void
RDBHandler::print( const RDB_IMAGE_t & info, unsigned char ident, bool csv, bool csvHeader )
{
    if ( csvHeader )
    {
        fprintf( stderr, "%23s,%23s,%23s,%23s,%23s,%23s,%23s,%23s,%23s,%23s,%23s,", 
                         "id", "width", "height", "pixelSize", "pixelFormat", 
                         "cameraId", "imgSize", "colorR", "colorG", "colorB", "colorA" );
        return;
    }
    
    if ( csv )
    {
        fprintf( stderr, "%23d,%23d,%23d,%23d,%23d,%23d,%23d,%23d,%23d,%23d,%23d,", 
                         info.id, info.width, info.height, info.pixelSize, info.pixelFormat, info.cameraId, 
                         info.imgSize, info.color[0], info.color[1], info.color[2], info.color[3] );
        return;
    }
    
    char* identStr = getIdentString( ident );
    
    fprintf( stderr, "%sid               = %d\n",          identStr, info.id          ); 
    fprintf( stderr, "%swidth            = %d\n",          identStr, info.width       ); 
    fprintf( stderr, "%sheight           = %d\n",          identStr, info.height      ); 
    fprintf( stderr, "%spixelSize        = %d\n",          identStr, info.pixelSize   ); 
    fprintf( stderr, "%spixelFormat      = %d\n",          identStr, info.pixelFormat ); 
    fprintf( stderr, "%scameraId         = %d\n",          identStr, info.cameraId    ); 
    fprintf( stderr, "%simgSize          = %d\n",          identStr, info.imgSize     ); 
    fprintf( stderr, "%scolor            = %d/%d/%d/%d\n", identStr, info.color[0], info.color[1], info.color[2], info.color[3] ); 
}

void
RDBHandler::print( const RDB_LIGHT_SOURCE_t & info, bool extended, unsigned char ident, bool csv, bool csvHeader )
{
    if ( csvHeader )
    {
        fprintf( stderr, "%23s,%23s,%23s,%23s,%23s,", 
                         "id", "templateId", "state", "playerId", "flags" );

        print( info.base.pos, ident + 4, csv, csvHeader );
        
        if ( !extended )
            return;
    
        fprintf( stderr, "%23s,%23s,%23s,%23s,%23s,%23s,%23s,%23s,%23s,%23s,%23s,%23s,", 
                         "near", "far", "left", "right", "bottom", "top", "int1", "int2", "int3", "atten0", "atten1", "atten2" );

        return;
    }
    
    if ( csv )
    {
        fprintf( stderr, "%23d,%23d,%23d,%23d,%23d,", 
                         info.base.id, info.base.templateId, info.base.state, info.base.playerId, info.base.flags );
        
        print( info.base.pos, ident + 4, csv, csvHeader );

        if ( !extended )
            return;
    
        fprintf( stderr, "%+.16e,%+.16e,%+.16e,%+.16e,%+.16e,%+.16e,%+.16e,%+.16e,%+.16e,%+.16e,%+.16e,%+.16e,", 
                         info.ext.nearFar[0], info.ext.nearFar[1], info.ext.frustumLRBT[0], info.ext.frustumLRBT[1], info.ext.frustumLRBT[2], info.ext.frustumLRBT[3],
                         info.ext.intensity[0], info.ext.intensity[1], info.ext.intensity[2], info.ext.atten[0], info.ext.atten[1], info.ext.atten[2] );
        
        return;
    }
    
    char* identStr = getIdentString( ident );
    
    fprintf( stderr, "%sid         = %d\n", identStr, info.base.id         ); 
    fprintf( stderr, "%stemplateId = %d\n", identStr, info.base.templateId ); 
    fprintf( stderr, "%sstate      = %d\n", identStr, info.base.state      ); 
    fprintf( stderr, "%splayerId   = %d\n", identStr, info.base.playerId   ); 

    fprintf( stderr, "%sposition\n", identStr ); 
    print( info.base.pos, ident + 4 );
    
    identStr = getIdentString( ident );
    fprintf( stderr, "%sflags      = 0x%x\n", identStr, info.base.flags );
    
    if ( !extended )
        return;
    
    fprintf( stderr, "%snearFar     = %.3f / %.3f\n",               identStr, info.ext.nearFar[0], info.ext.nearFar[1] ); 
    fprintf( stderr, "%sfrustumLRBT = %.3f / %.3f / %.3f / %.3f\n", identStr, info.ext.frustumLRBT[0], info.ext.frustumLRBT[1], info.ext.frustumLRBT[2], info.ext.frustumLRBT[3] ); 
    fprintf( stderr, "%sintensity   = %.3f / %.3f / %.3f\n",        identStr, info.ext.intensity[0], info.ext.intensity[1], info.ext.intensity[2] ); 
    fprintf( stderr, "%satten       = %.3f / %.3f / %.3f\n",        identStr, info.ext.atten[0], info.ext.atten[1], info.ext.atten[2] );                                         
}                                                                                                                                                                                

void
RDBHandler::print( const RDB_ENVIRONMENT_t & info, unsigned char ident, bool csv, bool csvHeader )
{
    if ( csvHeader )
    {
        fprintf( stderr, "%23s,%23s,%23s,%23s,%23s,%23s,%23s,",
                         "visibility", "timeOfDay", "brightness", "precipitation", "cloudState", "flags", "frictionScale" );
        return;
    }
    
    if ( csv )
    {
        fprintf( stderr, "%+.16e,%23d,%+.16e,%23d,%23d,%#23x,%+.16e,",
                         info.visibility, info.timeOfDay, info.brightness, info.precipitation, info.cloudState, info.flags, info.frictionScale );
        return;
    }
    
    char* identStr = getIdentString( ident );
    
    fprintf( stderr, "%svisibility    = %.3f\n", identStr, info.visibility    ); 
    fprintf( stderr, "%stimeOfDay     = %d\n",   identStr, info.timeOfDay     ); 
    fprintf( stderr, "%sbrightness    = %.3f\n", identStr, info.brightness    ); 
    fprintf( stderr, "%sprecipitation = %d\n",   identStr, info.precipitation ); 
    fprintf( stderr, "%scloudState    = %d\n",   identStr, info.cloudState    ); 
    fprintf( stderr, "%sflags         = 0x%x\n", identStr, info.flags         );
    fprintf( stderr, "%sfrictionScale = %f\n",   identStr, info.frictionScale );
}

void
RDBHandler::print( const RDB_TRIGGER_t & info, unsigned char ident, bool csv, bool csvHeader )
{
    if ( csvHeader )
    {
        fprintf( stderr, "%23s,%23s,", "deltaT", "frameNo" );
        return;
    }
    
    if ( csv )
    {
        fprintf( stderr, "%+.16e,%23d,", info.deltaT, info.frameNo );
        return;
    }
    
    char* identStr = getIdentString( ident );
    
    fprintf( stderr, "%sdeltaT  = %.3f\n", identStr, info.deltaT  ); 
    fprintf( stderr, "%sframeNo = %d\n",   identStr, info.frameNo ); 
}

void
RDBHandler::print( const RDB_DRIVER_CTRL_t & info, unsigned char ident, bool csv, bool csvHeader )
{
    if ( csvHeader )
    {
        fprintf( stderr, "%23s,%23s,%23s,%23s,%23s,%23s,%23s,%23s,%23s,%23s,%23s,%23s,%23s,%23s,%23s,%23s,%23s,%23s,%23s,%23s,%23s,%23s,%23s,%23s,%23s,%23s,%23s,%23s,%23s",
                         "playerId", "steeringWheelV", "steeringWheel", "steeringSpeedV", "steeringSpeed",  
                         "throttlePedalV", "throttlePedal", "brakePedalV", "brakePedal",
                         "clutchPedalV", "clutchPedal", "accelTgtV", "accelTgt",
                         "steeringTgtV", "steeringTgt", "curvatureTgtV", "curvatureTgt",
                         "steeringTorqueV", "steeringTorque", "engineTorqueTgtV", "engineTorqueTgt",
                         "speedTgtV", "speedTgt", "gearV", "gear", "flagsV", "flags",
                         "sourceId", "validityFlags" );
        return;
    }
    
    if ( csv )
    {
        fprintf( stderr, "%23d,%23d,%+.16e,%23d,%+.16e,%23d,%+.16e,%23d,%+.16e,%23d,%+.16e,%23d,%+.16e,%23d,%+.16e,%23d,%+.16e,%23d,%+.16e,%23d,%+.16e,%23d,%+.16e,%23d,%23d,%23d,%#23x,%23d,%#23x,",
                 info.playerId, 
                 ( info.validityFlags & RDB_DRIVER_INPUT_VALIDITY_STEERING_WHEEL )  ? 1 : 0, info.steeringWheel,
                 ( info.validityFlags & RDB_DRIVER_INPUT_VALIDITY_STEERING_SPEED )  ? 1 : 0, info.steeringSpeed, 
                 ( info.validityFlags & RDB_DRIVER_INPUT_VALIDITY_THROTTLE )        ? 1 : 0, info.throttlePedal, 
                 ( info.validityFlags & RDB_DRIVER_INPUT_VALIDITY_BRAKE )           ? 1 : 0, info.brakePedal, 
                 ( info.validityFlags & RDB_DRIVER_INPUT_VALIDITY_CLUTCH )          ? 1 : 0, info.clutchPedal, 
                 ( info.validityFlags & RDB_DRIVER_INPUT_VALIDITY_TGT_ACCEL )       ? 1 : 0, info.accelTgt, 
                 ( info.validityFlags & RDB_DRIVER_INPUT_VALIDITY_TGT_STEERING )    ? 1 : 0, info.steeringTgt, 
                 ( info.validityFlags & RDB_DRIVER_INPUT_VALIDITY_CURVATURE )       ? 1 : 0, info.curvatureTgt, 
                 ( info.validityFlags & RDB_DRIVER_INPUT_VALIDITY_STEERING_TORQUE ) ? 1 : 0, info.steeringTorque, 
                 ( info.validityFlags & RDB_DRIVER_INPUT_VALIDITY_ENGINE_TORQUE )   ? 1 : 0, info.engineTorqueTgt, 
                 ( info.validityFlags & RDB_DRIVER_INPUT_VALIDITY_TGT_SPEED )       ? 1 : 0, info.speedTgt, 
                 ( info.validityFlags & RDB_DRIVER_INPUT_VALIDITY_GEAR )            ? 1 : 0, info.gear, 
                 ( info.validityFlags & RDB_DRIVER_INPUT_VALIDITY_FLAGS )           ? 1 : 0, info.flags, info.sourceId, info.validityFlags ); 
        return;
    }
    
    char* identStr = getIdentString( ident );
    
    fprintf( stderr, "%splayerId        = %d\n",       identStr, info.playerId ); 
    fprintf( stderr, "%ssteeringWheel   = %d, %.3f\n", identStr, ( info.validityFlags & RDB_DRIVER_INPUT_VALIDITY_STEERING_WHEEL )  ? 1 : 0, info.steeringWheel   );     
    fprintf( stderr, "%ssteeringSpeed   = %d, %.3f\n", identStr, ( info.validityFlags & RDB_DRIVER_INPUT_VALIDITY_STEERING_SPEED )  ? 1 : 0, info.steeringSpeed   );     
    fprintf( stderr, "%sthrottlePedal   = %d, %.3f\n", identStr, ( info.validityFlags & RDB_DRIVER_INPUT_VALIDITY_THROTTLE )        ? 1 : 0, info.throttlePedal   );     
    fprintf( stderr, "%sbrakePedal      = %d, %.3f\n", identStr, ( info.validityFlags & RDB_DRIVER_INPUT_VALIDITY_BRAKE )           ? 1 : 0, info.brakePedal      );     
    fprintf( stderr, "%sclutchPedal     = %d, %.3f\n", identStr, ( info.validityFlags & RDB_DRIVER_INPUT_VALIDITY_CLUTCH )          ? 1 : 0, info.clutchPedal     );     
    fprintf( stderr, "%saccelTgt        = %d, %.3f\n", identStr, ( info.validityFlags & RDB_DRIVER_INPUT_VALIDITY_TGT_ACCEL )       ? 1 : 0, info.accelTgt        );     
    fprintf( stderr, "%ssteeringTgt     = %d, %.3f\n", identStr, ( info.validityFlags & RDB_DRIVER_INPUT_VALIDITY_TGT_STEERING )    ? 1 : 0, info.steeringTgt     ); 
    fprintf( stderr, "%scurvatureTgt    = %d, %.3f\n", identStr, ( info.validityFlags & RDB_DRIVER_INPUT_VALIDITY_CURVATURE )       ? 1 : 0, info.curvatureTgt    ); 
    fprintf( stderr, "%ssteeringTorque  = %d, %.3f\n", identStr, ( info.validityFlags & RDB_DRIVER_INPUT_VALIDITY_STEERING_TORQUE ) ? 1 : 0, info.steeringTorque  ); 
    fprintf( stderr, "%sengineTorqueTgt = %d, %.3f\n", identStr, ( info.validityFlags & RDB_DRIVER_INPUT_VALIDITY_ENGINE_TORQUE )   ? 1 : 0, info.engineTorqueTgt ); 
    fprintf( stderr, "%sspeedTgt        = %d, %.3f\n", identStr, ( info.validityFlags & RDB_DRIVER_INPUT_VALIDITY_TGT_SPEED )       ? 1 : 0, info.speedTgt        ); 
    fprintf( stderr, "%sgear            = %d, %d\n",   identStr, ( info.validityFlags & RDB_DRIVER_INPUT_VALIDITY_GEAR )            ? 1 : 0, info.gear            ); 
    fprintf( stderr, "%sflags           = %d, 0x%x\n", identStr, ( info.validityFlags & RDB_DRIVER_INPUT_VALIDITY_FLAGS )           ? 1 : 0, info.flags           ); 
    fprintf( stderr, "%smockupInput0    = %d, %d\n",   identStr, ( info.validityFlags & RDB_DRIVER_INPUT_VALIDITY_MOCKUP_INPUT0 )   ? 1 : 0, info.mockupInput0    ); 
    fprintf( stderr, "%smockupInput1    = %d, %d\n",   identStr, ( info.validityFlags & RDB_DRIVER_INPUT_VALIDITY_MOCKUP_INPUT1 )   ? 1 : 0, info.mockupInput1    ); 
    fprintf( stderr, "%smockupInput2    = %d, %d\n",   identStr, ( info.validityFlags & RDB_DRIVER_INPUT_VALIDITY_MOCKUP_INPUT2 )   ? 1 : 0, info.mockupInput2    ); 
    fprintf( stderr, "%ssourceId        = %d\n",       identStr, info.sourceId     ); 
    fprintf( stderr, "%svalidityFlags   = 0x%x\n",     identStr, info.validityFlags     ); 
}

void
RDBHandler::print( const RDB_TRAFFIC_LIGHT_t & info, bool extended, unsigned char ident, bool csv, bool csvHeader )
{
    if ( csvHeader )
    {
        fprintf( stderr, "%23s,%23s,%23s,", "id", "state", "stateMask" );

        if ( !extended )
            return;
    
        fprintf( stderr, "%23s,%23s,%23s,", "ctrlId", "cycleTime", "noPhases" );

        return;
    }
    
    if ( csv )
    {
        fprintf( stderr, "%23d,%+.16e,%#23x,", info.base.id, info.base.state, info.base.stateMask );
        
        if ( !extended )
            return;
    
        fprintf( stderr, "%23d,%+.16e,%23d,", info.ext.ctrlId, info.ext.cycleTime, info.ext.noPhases );
        
        return;
    }
    
    char* identStr = getIdentString( ident );
    
    fprintf( stderr, "%sid        = %d\n",   identStr, info.base.id        ); 
    fprintf( stderr, "%sstate     = %.3f\n", identStr, info.base.state     ); 
    fprintf( stderr, "%sstateMask = 0x%x\n", identStr, info.base.stateMask );
    
    if ( !extended )
        return;

    fprintf( stderr, "%sctrlId    = %d\n",   identStr, info.ext.ctrlId    ); 
    fprintf( stderr, "%scycleTime = %.3f\n", identStr, info.ext.cycleTime ); 
    fprintf( stderr, "%snoPhases  = %d\n",   identStr, info.ext.noPhases  ); 
    fprintf( stderr, "%sdataSize  = %d\n",   identStr, info.ext.dataSize  ); 

    RDB_TRAFFIC_LIGHT_PHASE_t* phasePtr = ( RDB_TRAFFIC_LIGHT_PHASE_t* ) ( ( ( char* ) &info ) + sizeof( RDB_TRAFFIC_LIGHT_t ) );

    for ( unsigned int j = 0; j < info.ext.noPhases; j++ )
    {
        fprintf( stderr, "   phase  %d, duration = %.3f, type = %d\n", j, phasePtr->duration, phasePtr->type );
        phasePtr++;
    }
}

void
RDBHandler::print( const RDB_SYNC_t & info, unsigned char ident, bool csv, bool csvHeader )
{
    if ( csvHeader )
    {
        fprintf( stderr, "%23s,%23s,%23s,", "mask", "cmdMask", "systemTime" );
        return;
    }
    
    if ( csv )
    {
        fprintf( stderr, "%#23x,%#23x,%+.16e,", info.mask, info.cmdMask, info.systemTime );
        return;
    }
    
    char* identStr = getIdentString( ident );
    
    fprintf( stderr, "%smask       = 0x%x\n",  identStr, info.mask       );
    fprintf( stderr, "%scmdMask    = 0x%x\n",  identStr, info.cmdMask    );
    fprintf( stderr, "%ssystemTime = %.4f\n",  identStr, info.systemTime );
}

void
RDBHandler::print( const RDB_DRIVER_PERCEPTION_t & info, unsigned char ident, bool csv, bool csvHeader )
{
    if ( csvHeader )
    {
        fprintf( stderr, "%23s,%23s,%23s,%23s,", "playerId", "speedFromRules", "distToSpeed", "flags" );
        return;
    }
    
    if ( csv )
    {
        fprintf( stderr, "%23d,%+.16e,%+.16e,%#23x,", info.playerId, info.speedFromRules, info.distToSpeed, info.flags );
        return;
    }
    
    char* identStr = getIdentString( ident );

    fprintf( stderr, "%splayerId       = %d\n",   identStr, info.playerId       );
    fprintf( stderr, "%sspeedFromRules = %.3f\n", identStr, info.speedFromRules );
    fprintf( stderr, "%sdistToSpeed    = %.3f\n", identStr, info.distToSpeed    );
    fprintf( stderr, "%sflags          = 0x%x\n", identStr, info.flags          );
    
}

void
RDBHandler::print( const RDB_FUNCTION_t & info, unsigned char ident, bool csv, bool csvHeader )
{
    if ( csvHeader )
    {
        fprintf( stderr, "%23s", "function" );
        return;
    }

    if ( csv )
    {
        fprintf( stderr, "%23s", "n/a" );
        return;
    }

    char* identStr = getIdentString( ident );

    fprintf( stderr, "%sid        = %d\n", identStr, info.id        );
    fprintf( stderr, "%stype      = %d\n", identStr, info.type      );
    fprintf( stderr, "%sdimension = %d\n", identStr, info.dimension );
    fprintf( stderr, "%sdataSize  = %d\n", identStr, info.dataSize  );
}

void
RDBHandler::print( const RDB_ROAD_QUERY_t & info, unsigned char ident, bool csv, bool csvHeader )
{
    if ( csvHeader )
    {
        fprintf( stderr, "%23s,%23s,%23s,%23s,", "id", "flags", "x", "y" );
        return;
    }
    
    if ( csv )
    {
        fprintf( stderr, "%23d,%#23x,%+.16e,%+.16e,", info.id, info.flags, info.x, info.y );
        return;
    }
    
    char* identStr = getIdentString( ident );
    
    fprintf( stderr, "%sid    = %d\n",    identStr, info.id    );
    fprintf( stderr, "%sflags = 0x%x\n",  identStr, info.flags );
    fprintf( stderr, "%sx     = %.3f\n",  identStr, info.x     );
    fprintf( stderr, "%sy     = %.3f\n",  identStr, info.y     );
}

void
RDBHandler::print( const RDB_POINT_t & info, unsigned char ident, bool csv, bool csvHeader )
{
    if ( csvHeader )
    {
        fprintf( stderr, "%23s,%23s,%23s,%23s,%23s,%23s,", "x", "y", "z", "flags", "type", "system" );
        return;
    }
    
    if ( csv )
    {
        fprintf( stderr, "%+.16e,%+.16e,%+.16e,%#23x,%23d,%23d,", info.x, info.y, info.z, info.flags, info.type, info.system );
        return;
    }
    
    char* identStr = getIdentString( ident );
    
    fprintf( stderr, "%sx/y/z = %.3f / %.3f / %.3f\n", identStr, info.x, info.y, info.z ); 
    fprintf( stderr, "%sflags = 0x%x, type = %s, system = %d\n", identStr, info.flags, coordType2string( info.type ).c_str(), info.system ); 
}

void
RDBHandler::print( const RDB_TRAJECTORY_t & info, unsigned char ident, bool csv, bool csvHeader )
{
    if ( csvHeader )
    {
        fprintf( stderr, "%23s,%23s,%23s,%23s,", "playerId", "spacing", "flags", "noDataPoints" );
        
        if ( info.noDataPoints )
        {
            RDB_POINT_t* pt = ( RDB_POINT_t* ) ( ( ( unsigned char* ) ( &info ) ) + sizeof( RDB_TRAJECTORY_t ) );
                                
            for ( int i = 0; i < info.noDataPoints; i++ )
                print( pt[i], ident + 4, csv, csvHeader );
        }
        return;
    }
    
    if ( csv )
    {
        fprintf( stderr, "%23d,%+.16e,%#23x,%23d,", info.playerId, info.spacing, info.flags, info.noDataPoints );
        
        if ( info.noDataPoints )
        {
            RDB_POINT_t* pt = ( RDB_POINT_t* ) ( ( ( unsigned char* ) ( &info ) ) + sizeof( RDB_TRAJECTORY_t ) );
                                
            for ( int i = 0; i < info.noDataPoints; i++ )
                print( pt[i], ident + 4, csv, csvHeader );
        }
        return;
    }
    
    char* identStr = getIdentString( ident );
    
    fprintf( stderr, "%splayerId     = %d\n",    identStr, info.playerId     ); 
    fprintf( stderr, "%sspacing      = %.3f\n",  identStr, info.spacing      ); 
    fprintf( stderr, "%sflags        = 0x%x\n",  identStr, info.flags        ); 
    fprintf( stderr, "%snoDataPoints = %d\n",    identStr, info.noDataPoints );

    if ( info.noDataPoints )
    {
        RDB_POINT_t* pt = ( RDB_POINT_t* ) ( ( ( unsigned char* ) ( &info ) ) + sizeof( RDB_TRAJECTORY_t ) );
                            
        for ( int i = 0; i < info.noDataPoints; i++ )
            print( pt[i], ident + 4 );
    }
}

void
RDBHandler::print( const RDB_DYN_2_STEER_t & info, unsigned char ident, bool csv, bool csvHeader )
{
    if ( csvHeader )
    {
        fprintf( stderr, "%23s,%23s,%23s,%23s,%23s,%23s,%23s,%23s,%23s,%23s,", 
                 "playerId", "state", "cmd", "effects", "torque", "friction", "damping", "stiffness", "velocity", "angle" );
        return;
    }
    
    if ( csv )
    {
        fprintf( stderr, "%23d,%#23x,%#23x,%#23x,%+.16e,%+.16e,%+.16e,%+.16e,%+.16e,%+.16e,", 
                 info.playerId, info.state, info.cmd, info.effects, info.torque, info.friction, info.damping, info.stiffness, info.velocity, info.angle );
        return;
    }
    
    char* identStr = getIdentString( ident );

    fprintf( stderr, "%splayerId         = %d\n",   identStr, info.playerId         ); 
    fprintf( stderr, "%sstate            = 0x%x\n", identStr, info.state            ); 
    fprintf( stderr, "%scmd              = 0x%x\n", identStr, info.cmd              ); 
    fprintf( stderr, "%seffects          = 0x%x\n", identStr, info.effects          ); 
    fprintf( stderr, "%storque           = %.6f\n", identStr, info.torque           );
    fprintf( stderr, "%sfriction         = %.6f\n", identStr, info.friction         );
    fprintf( stderr, "%sdamping          = %.6f\n", identStr, info.damping          );
    fprintf( stderr, "%sstiffness        = %.6f\n", identStr, info.stiffness        );
    fprintf( stderr, "%svelocity         = %.6f\n", identStr, info.velocity         );
    fprintf( stderr, "%sangle            = %.6f\n", identStr, info.angle            );
    fprintf( stderr, "%sneutralPos       = %.6f\n", identStr, info.neutralPos       );
    fprintf( stderr, "%sdampingMaxTorque = %.6f\n", identStr, info.dampingMaxTorque );
}

void
RDBHandler::print( const RDB_STEER_2_DYN_t & info, unsigned char ident, bool csv, bool csvHeader )
{
    if ( csvHeader )
    {
        fprintf( stderr, "%23s,%23s,%23s,%23s,%23s,", "playerId", "state", "angle", "rev", "torque" );
        return;
    }
    
    if ( csv )
    {
        fprintf( stderr, "%23d,%#23x,%+.16e,%+.16e,%+.16e,", 
                 info.playerId, info.state, info.angle, info.rev, info.torque );
        return;
    }
    
    char* identStr = getIdentString( ident );
    
    fprintf( stderr, "%splayerId  = %d\n",   identStr, info.playerId ); 
    fprintf( stderr, "%sstate     = 0x%x\n", identStr, info.state    ); 
    fprintf( stderr, "%sangle     = %.3f\n", identStr, info.angle    );
    fprintf( stderr, "%srev       = %.3f\n", identStr, info.rev      );
    fprintf( stderr, "%storque    = %.3f\n", identStr, info.torque   );
}

void
RDBHandler::print( const RDB_PROXY_t & info, unsigned char ident, bool csv, bool csvHeader )
{
    if ( csvHeader )
    {
        fprintf( stderr, "%23s,%23s,%23s,", "protocol", "pkgId", "dataSize" );
        return;
    }
    
    if ( csv )
    {
        fprintf( stderr, "%23d,%23d,%23d,", info.protocol, info.pkgId, info.dataSize );
        return;
    }
    
    char* identStr = getIdentString( ident );
    
    fprintf( stderr, "%sprotocol = %d\n", identStr, info.protocol ); 
    fprintf( stderr, "%spkgId    = %d\n", identStr, info.pkgId    ); 
    fprintf( stderr, "%sdataSize = %d\n", identStr, info.dataSize );
}

void
RDBHandler::print( const RDB_MOTION_SYSTEM_t & info, unsigned char ident, bool csv, bool csvHeader )
{
    if ( csvHeader )
    {
        fprintf( stderr, "%23s,%23s,", "playerId", "flags" );
        print( info.pos, ident + 4, csv, csvHeader );
        print( info.speed, ident + 4, csv, csvHeader );
        return;
    }
    
    if ( csv )
    {
        fprintf( stderr, "%23d,%#23x,", info.playerId, info.flags );
        print( info.pos, ident + 4, csv, csvHeader );
        print( info.speed, ident + 4, csv, csvHeader );
        return;
    }
    
    char* identStr = getIdentString( ident );
 
    fprintf( stderr, "%splayerId  = %d\n",   identStr, info.playerId ); 
    fprintf( stderr, "%sflags     = 0x%x\n", identStr, info.flags    ); 
   
    fprintf( stderr, "%spos:\n", identStr ); 
    print( info.pos, ident + 4 );

    fprintf( stderr, "%sspeed:\n", identStr ); 
    print( info.speed, ident + 4 );
}

void
RDBHandler::print( const RDB_CUSTOM_SCORING_t & info, unsigned char ident, bool csv, bool csvHeader )
{
    if ( csvHeader )
    {
        fprintf( stderr, "%23s,%23s,%23s,%23s,%23s,%23s,%23s,", "playerId", "pathS", "roadS", "fuelCurrent", "fuelAverage", "stateFlags", "slip" );
        return;
    }
    
    if ( csv )
    {
        fprintf( stderr, "%23d,%+.16e,%+.16e,%+.16e,%+.16e,%#23x,%+.16e,", 
                 info.playerId, info.pathS,  info.roadS, info.fuelCurrent, info.fuelAverage, info.stateFlags, info.slip );
        return;
    }
    
    char* identStr = getIdentString( ident );
 
    fprintf( stderr, "%splayerId    = %d\n",   identStr, info.playerId    ); 
    fprintf( stderr, "%spathS       = %.3f\n", identStr, info.pathS       ); 
    fprintf( stderr, "%sroadS       = %.3f\n", identStr, info.roadS       ); 
    fprintf( stderr, "%sfuelCurrent = %.3f\n", identStr, info.fuelCurrent ); 
    fprintf( stderr, "%sfuelAverage = %.3f\n", identStr, info.fuelAverage ); 
    fprintf( stderr, "%sstateFlags  = 0x%x\n", identStr, info.stateFlags  ); 
    fprintf( stderr, "%sslip        = %.3f\n", identStr, info.slip        ); 
}

void
RDBHandler::print( const RDB_CUSTOM_OBJECT_CTRL_TRACK_t & info, unsigned char ident, bool csv, bool csvHeader )
{
    if ( csvHeader )
    {
        fprintf( stderr, "%23s,%23s,%23s,%23s,%23s,%23s,%23s,", "playerId", "flags", "posType", "dir", "roadId", "initialRoadDeltaS", "targetRoadT" );
        return;
    }
    
    if ( csv )
    {
        fprintf( stderr, "%23d,%#23x,%23d,%23d,%23d,%+.16e,%+.16e,", 
                 info.playerId, info.flags, info.posType, info.dir, info.roadId, info.initialRoadDeltaS, info.targetRoadT );
        return;
    }
    
    char* identStr = getIdentString( ident );
 
    fprintf( stderr, "%splayerId          = %d\n",   identStr, info.playerId          ); 
    fprintf( stderr, "%sflags             = 0x%x\n", identStr, info.flags             ); 
    fprintf( stderr, "%sposType           = %d\n",   identStr, info.posType           ); 
    fprintf( stderr, "%sdir               = %d\n",   identStr, info.dir               ); 
    fprintf( stderr, "%sroadId            = %d\n",   identStr, info.roadId            ); 
    fprintf( stderr, "%sinitialRoadDeltaS = %.3f\n", identStr, info.initialRoadDeltaS ); 
    fprintf( stderr, "%stargetRoadT       = %.3f\n", identStr, info.targetRoadT       ); 
    fprintf( stderr, "%sspeedTgtS         = %.3f\n", identStr, info.speedTgtS         ); 
    fprintf( stderr, "%sminAccelS         = %.3f\n", identStr, info.minAccelS         ); 
    fprintf( stderr, "%smaxAccelS         = %.3f\n", identStr, info.maxAccelS         ); 
    fprintf( stderr, "%saccelTgt          = %.3f\n", identStr, info.accelTgt          ); 
    fprintf( stderr, "%svalidityFlags     = 0x%x\n", identStr, info.validityFlags     );         
}

void
RDBHandler::print( const RDB_SCP_t & info, unsigned char ident, bool csv, bool csvHeader )
{
    if ( csvHeader )
    {
        fprintf( stderr, "%23s", "scp" );
        return;
    }

    if ( csv )
    {
        fprintf( stderr, "%23s", "n/a" );
        return;
    }

    char* identStr = getIdentString( ident );

    fprintf( stderr, "%sversion  = %d\n", identStr, info.version  ); 
    fprintf( stderr, "%ssender   = %s\n", identStr, info.sender   ); 
    fprintf( stderr, "%sreceiver = %s\n", identStr, info.receiver ); 
    fprintf( stderr, "%sdataSize = %d\n", identStr, info.dataSize ); 
}

void
RDBHandler::print( const RDB_FREESPACE_t & info, unsigned char ident, bool csv, bool csvHeader )
{
    if ( csvHeader )
    {
        fprintf( stderr, "%23s,%23s,%23s,%23s,%23s,%23s,%23s,%23s,%23s,%23s,", 
                         "playerId", "distance", "angleLeft", "angleRight", "distanceLeft", "distanceRight", 
                         "stateLeft", "stateRight", "stateDistance", "noVisibleObjects" );
        return;
    }
    
    if ( csv )
    {
        fprintf( stderr, "%23d,%+.16e,%+.16e,%+.16e,%+.16e,%+.16e,%23d,%23d,%23d,%23d,", 
                         info.playerId, info.distance, info.angleLeft, info.angleRight, info.distanceLeft, info.distanceRight, 
                         info.stateLeft, info.stateRight, info.stateDistance, info.noVisibleObjects );
        return;
    }
    
    char* identStr = getIdentString( ident );
    
    fprintf( stderr, "%splayerId         = %d\n",   identStr, info.playerId         ); 
    fprintf( stderr, "%sdistance         = %.3f\n", identStr, info.distance         ); 
    fprintf( stderr, "%sangleLeft;       = %.3f\n", identStr, info.angleLeft        ); 
    fprintf( stderr, "%sangleRight       = %.3f\n", identStr, info.angleRight       ); 
    fprintf( stderr, "%sdistanceLeft     = %.3f\n", identStr, info.distanceLeft     ); 
    fprintf( stderr, "%sdistanceRight    = %.3f\n", identStr, info.distanceRight    ); 
    fprintf( stderr, "%sstateLeft        = %d\n",   identStr, info.stateLeft        ); 
    fprintf( stderr, "%sstateRight       = %d\n",   identStr, info.stateRight       ); 
    fprintf( stderr, "%sstateDistance    = %d\n",   identStr, info.stateDistance    ); 
    fprintf( stderr, "%snoVisibleObjects = %d\n",   identStr, info.noVisibleObjects ); 
}

void
RDBHandler::print( const RDB_DYN_EL_SWITCH_t & info, unsigned char ident, bool csv, bool csvHeader )
{
    if ( csvHeader )
    {
        fprintf( stderr, "%23s,%23s,%23s,%23s,", "objectId", "elementId", "scope", "state" );
        return;
    }
    
    if ( csv )
    {
        fprintf( stderr, "%23d,%23d,%23d,%#23x,", 
                         info.objectId, info.elementId, info.scope, info.state );
        return;
    }
    
    char* identStr = getIdentString( ident );
    
    fprintf( stderr, "%sobjectId  = %d\n",   identStr, info.objectId  ); 
    fprintf( stderr, "%selementId = %d\n",   identStr, info.elementId ); 
    fprintf( stderr, "%sscope     = %d\n",   identStr, info.scope     ); 
    fprintf( stderr, "%sstate     = 0x%x\n", identStr, info.state     ); 
}

void
RDBHandler::print( const RDB_DYN_EL_DOF_t & info, unsigned char ident, bool csv, bool csvHeader )
{
    if ( csvHeader )
    {
        fprintf( stderr, "%23s,%23s,%23s,%23s,%23s,", "objectId", "elementId", "scope", "validity", "nValues" );
        return;
    }
    
    if ( csv )
    {
        fprintf( stderr, "%23d,%23d,%23d,%23d,%23d,", 
                         info.objectId, info.elementId, info.scope, info.validity, info.nValues );
        return;
    }
    
    char* identStr = getIdentString( ident );
    
    fprintf( stderr, "%sobjectId  = %d\n",   identStr, info.objectId  ); 
    fprintf( stderr, "%selementId = %d\n",   identStr, info.elementId ); 
    fprintf( stderr, "%sscope     = %d\n",   identStr, info.scope     ); 
    fprintf( stderr, "%svalidity  = %d\n",   identStr, info.validity  ); 
    fprintf( stderr, "%snValues   = %d\n",   identStr, info.nValues   ); 
}

void
RDBHandler::print( const RDB_IG_FRAME_t & info, unsigned char ident, bool csv, bool csvHeader )
{
    if ( csvHeader )
    {
        fprintf( stderr, "%23s,%23s,", "deltaT", "frameNo" );
        return;
    }
    
    if ( csv )
    {
        fprintf( stderr, "%+.16e,%23d,", info.deltaT, info.frameNo );
        return;
    }
    
    char* identStr = getIdentString( ident );
    
    fprintf( stderr, "%sdeltaT  = %.3f\n", identStr, info.deltaT  ); 
    fprintf( stderr, "%sframeNo = %d\n",   identStr, info.frameNo ); 
}

void
RDBHandler::print( const RDB_RT_PERFORMANCE_t & info, unsigned char ident, bool csv, bool csvHeader )
{
    if ( csvHeader )
    {
        fprintf( stderr, "%23s,%23s,%23s,%23s,%23s,%23s,", "noOverruns", "noUnderruns", "noMeasurements", "tolerance", "nominalFrameTime", "actualFrameTime" );
        return;
    }
    
    if ( csv )
    {
        fprintf( stderr, "%23d,%23d,%23d,%+.16e,%+.16e,%+.16e,", info.noOverruns, info.noUnderruns, info.noMeasurements, info.tolerance, info.nominalFrameTime, info.actualFrameTime );
        return;
    }
    
    char* identStr = getIdentString( ident );
    
    fprintf( stderr, "%snoMeasurements   = %d\n",     identStr, info.noMeasurements ); 
    fprintf( stderr, "%snoUnderruns      = %d\n",     identStr, info.noUnderruns ); 
    fprintf( stderr, "%snoOverruns       = %d\n",     identStr, info.noOverruns ); 
    fprintf( stderr, "%stolerance        = %.3f\n",   identStr, info.tolerance ); 
    fprintf( stderr, "%snominalFrameTime = %.3fms\n", identStr, info.nominalFrameTime * 1000.0f ); 
    fprintf( stderr, "%sactualFrameTime  = %.3fms\n", identStr, info.actualFrameTime * 1000.0f ); 
}

void
RDBHandler::printMatrix( int *pData, unsigned int width, unsigned int height, bool csv, bool csvHeader )
{
    if ( csvHeader )
        return;

    if ( csv )
        return;

    for ( unsigned int h = 0; h < height; h++ )
    {
        for ( unsigned int w = 0; w < width; w++ )
        {
            fprintf( stderr, "%5d", *pData );
            pData++;
        }
        fprintf( stderr, "\n" );
    }
}
        
void
RDBHandler::print( const RDB_RAY_t & info, unsigned char ident, bool csv, bool csvHeader )
{
    if ( csvHeader )
    {
        fprintf( stderr, "%23s,%23s,%23s,%23s,", "id", "emitterId", "type", "length" );
        
        print( info.ray, ident + 4,  csv, csvHeader );
        return;
    }
    
    if ( csv )
    {
        fprintf( stderr, "%+23d,%23d,%23d,%+.16e,", info.id, info.emitterId, info.type, info.length );
        print( info.ray, ident + 4,  csv, csvHeader );
        return;
    }

    char* identStr = getIdentString( ident );
    
    fprintf( stderr, "%sid        = %d\n",   identStr, info.id        ); 
    fprintf( stderr, "%semitterId = %d\n",   identStr, info.emitterId ); 
    fprintf( stderr, "%stype      = %d\n",   identStr, info.type      ); 
    fprintf( stderr, "%slength    = %.6f\n", identStr, info.length    ); 
    
    fprintf( stderr, "%sray data\n", getIdentString( ident ) ); 
    print( info.ray, ident + 4 );
}

void
RDBHandler::print( const RDB_SYMBOL_STATE_t & info, unsigned char ident, bool csv, bool csvHeader )
{
    if ( csvHeader )
    {
        fprintf( stderr, "%23s,", "id" );
        
        print( info.pos,   ident + 4,  csv, csvHeader );
        print( info.scale, ident + 4,  csv, csvHeader );
        return;
    }
    
    if ( csv )
    {
        fprintf( stderr, "%+23d,", info.id );
        print( info.pos,   ident + 4,  csv, csvHeader );
        print( info.scale, ident + 4,  csv, csvHeader );
        return;
    }

    char* identStr = getIdentString( ident );
    
    fprintf( stderr, "%sid        = %d\n",   identStr, info.id ); 
    fprintf( stderr, "%spos\n", getIdentString( ident ) ); 
    print( info.pos, ident + 4 );
    fprintf( stderr, "%sscale\n", getIdentString( ident ) ); 
    print( info.scale, ident + 4 );
}

void
RDBHandler::print( const RDB_RADAR_HIT_POINT_t & info, unsigned char ident, bool csv, bool csvHeader )
{
    if ( csvHeader )
    {
        fprintf( stderr, "%23s,%23s,%23s,%23s,%23s,", "objectId", "distance",
                         "radialVelocity", "azimuthAngle", "elevationAngle");
        return;
    }

    if ( csv )
    {
        fprintf( stderr, "%23d,%+.16e,%+.16e,%+.16e,%+.16e,",
                         info.objectId, info.distance, info.radialVelocity,
                         info.azimuthAngle, info.elevationAngle );
        return;
    }

    char* identStr = getIdentString( ident );

    fprintf( stderr, "%sobjectId distance radialVelocity azimuthAngle      elevationAngle\n", identStr );
    fprintf( stderr, "%s%8d %+10.3f %+10.3f %+10.3f %+10.3f\n",
                      identStr, info.objectId, info.distance, info.radialVelocity,
                      info.azimuthAngle, info.elevationAngle );
}

RDBHandler::RDBHandler() : mMsg( 0 ),
                           mShmHdr( 0 )                          
{
     //std::cerr << "RDBHandler::RDBHandler: CTOR called, this=" << this << std::endl;
}

RDBHandler::~RDBHandler()
{
     //std::cerr << "RDBHandler::~RDBHandler: DTOR called, this=" << this << std::endl;
     if ( mMsg )
         free( mMsg );
}

void
RDBHandler::initMsg()
{
    if ( mMsg )
        free( mMsg );
    
    mMsg = 0;
}

void*
RDBHandler::addPackage( const double & simTime, const unsigned int & simFrame, 
                        unsigned int pkgId,     unsigned int noElements,       
                        bool extended, size_t trailingData, bool isCustom )
{
    // extend the internal message if no other is given
    return addPackage( mMsg, simTime, simFrame, pkgId, noElements, extended, trailingData, isCustom );
}

void*
RDBHandler::addCustomPackage( const double & simTime, const unsigned int & simFrame, 
                              unsigned int pkgId, unsigned int noElements, size_t elementSize )
{
    // extend the internal message if no other is given
    return addCustomPackage( mMsg, simTime, simFrame, pkgId, noElements, elementSize );
}

RDB_MSG_t*
RDBHandler::getMsg()
{
    return mMsg;
}

RDB_MSG_HDR_t*
RDBHandler::getMsgHdr()
{
    if ( !mMsg )
        return 0;
    
    return &( mMsg->hdr );
}

size_t
RDBHandler::getMsgTotalSize()
{
    if ( !mMsg )
        return 0;
    
    return mMsg->hdr.headerSize + mMsg->hdr.dataSize;
}

void*
RDBHandler::getFirstEntry( unsigned int pkgId, unsigned int & noElements, bool extended )
{
    return getFirstEntry( mMsg, pkgId, noElements, extended );
}

RDB_MSG_ENTRY_HDR_t*
RDBHandler::getEntryHdr( unsigned int pkgId, bool extended )
{
    return getEntryHdr( mMsg, pkgId, extended );
}

bool
RDBHandler::shmConfigure( void *startPtr, unsigned int noBuffers, unsigned int totalSize )
{
    if ( !startPtr || !noBuffers )
        return false;
    
    mShmHdr = ( RDB_SHM_HDR_t* ) ( startPtr );
    
    memset( mShmHdr, 0, totalSize );
    
    mShmHdr->headerSize = sizeof( RDB_SHM_HDR_t );
    mShmHdr->noBuffers  = noBuffers;

    RDB_SHM_BUFFER_INFO_t* info  = ( RDB_SHM_BUFFER_INFO_t* ) ( ( ( char* ) mShmHdr ) + mShmHdr->headerSize );
    
    // compute the size of a single buffer
    unsigned int bufferSize = 0;
    
    if ( totalSize > 0 )
    {
        if ( totalSize <= ( mShmHdr->noBuffers * sizeof( RDB_SHM_BUFFER_INFO_t ) + mShmHdr->headerSize ) )
            fprintf( stderr, "RDBHandler::shmConfigure: insufficient data size for shared memory!\n" );
        else
            bufferSize = ( totalSize - ( mShmHdr->noBuffers * sizeof( RDB_SHM_BUFFER_INFO_t ) + mShmHdr->headerSize ) ) / mShmHdr->noBuffers;

    }
    
    for ( int i = 0; i < mShmHdr->noBuffers; i++ )
    {
        //fprintf( stderr, "RDBHandler::shmConfigure: configuring buffer %d with %d bytes!\n", i, bufferSize );
    
        info[i].thisSize   = sizeof( RDB_SHM_BUFFER_INFO_t );
        info[i].bufferSize = bufferSize;
        info[i].offset     = mShmHdr->noBuffers * sizeof( RDB_SHM_BUFFER_INFO_t ) + mShmHdr->headerSize + i * bufferSize;
    }
    
    return true;
}

bool
RDBHandler::shmSetAddress( void* shmAddr )
{
    mShmHdr = ( RDB_SHM_HDR_t* ) shmAddr;
    
    return mShmHdr != 0;
}

RDB_SHM_HDR_t*
RDBHandler::shmGetHdr()
{
    return mShmHdr;
}

RDB_SHM_BUFFER_INFO_t*
RDBHandler::shmBufferGetInfo( unsigned int index )
{
    if ( !mShmHdr )
        return 0;
    
    if ( index >= mShmHdr->noBuffers )
        return 0;
    
    RDB_SHM_BUFFER_INFO_t* info = ( RDB_SHM_BUFFER_INFO_t* ) ( ( ( char* ) mShmHdr ) + mShmHdr->headerSize );
    
    return &( info[index] );
}

void*
RDBHandler::shmBufferGetPtr( unsigned int index )
{
    RDB_SHM_BUFFER_INFO_t* info = shmBufferGetInfo( index );
    
    if ( !info )
        return 0;
    
    return ( ( ( char* ) mShmHdr ) + info->offset );
}

void
RDBHandler::shmHdrUpdate()
{
    if ( !mShmHdr )
        return;
    
    // access the first buffer
    RDB_SHM_BUFFER_INFO_t* info     = shmBufferGetInfo( 0 );
    RDB_SHM_BUFFER_INFO_t* prevInfo = 0;
    
    if ( !info )
        return;

    // compute total data size of the shared memory buffers
    unsigned int totalSize = 0;
    
    // we assume that one buffer is written after another so that a buffer's offset
    // can be computed from the predecessor's offset and its size
    
    for ( int i = 0; i < mShmHdr->noBuffers; i++ )
    {
        totalSize += info->thisSize + info->bufferSize;
        
        if ( prevInfo )
            info->offset = prevInfo->offset + prevInfo->bufferSize;
            
        prevInfo = info;
        info++;
    }
    mShmHdr->dataSize = totalSize;    
}

void
RDBHandler::shmBufferSetSize( unsigned int index, size_t size )
{
    RDB_SHM_BUFFER_INFO_t* info = shmBufferGetInfo( index );
    
    if ( !info )
        return;
    
    info->bufferSize = size;
}

size_t
RDBHandler::shmBufferGetSize( unsigned int index )
{
    RDB_SHM_BUFFER_INFO_t* info = shmBufferGetInfo( index );
    
    if ( !info )
        return 0;
    
    return info->bufferSize;
}

void
RDBHandler::shmBufferSetId( unsigned int index, unsigned int id )
{
    RDB_SHM_BUFFER_INFO_t* info = shmBufferGetInfo( index );
    
    if ( !info )
        return;
    
    info->id = id;
}

void
RDBHandler::shmBufferSetFlags( unsigned int index, unsigned int flags )
{
    RDB_SHM_BUFFER_INFO_t* info = shmBufferGetInfo( index );
    
    if ( !info )
        return;
    
    info->flags = flags;
}

void
RDBHandler::shmBufferAddFlags( unsigned int index, unsigned int flags )
{
    RDB_SHM_BUFFER_INFO_t* info = shmBufferGetInfo( index );
    
    if ( !info )
        return;
    
    info->flags |= flags;
}

void
RDBHandler::shmBufferReleaseFlags( unsigned int index, unsigned int flags )
{
    RDB_SHM_BUFFER_INFO_t* info = shmBufferGetInfo( index );
    
    if ( !info )
        return;
    
    info->flags &= ~flags;
}

unsigned int
RDBHandler::shmBufferGetFlags( unsigned int index )
{
    RDB_SHM_BUFFER_INFO_t* info = shmBufferGetInfo( index );
    
    if ( !info )
        return 0;
    
    return info->flags;
}

bool
RDBHandler::shmBufferHasFlags( unsigned int index, unsigned int mask )
{
    RDB_SHM_BUFFER_INFO_t* info = shmBufferGetInfo( index );
    
    if ( !info )
        return false;
    
    return ( info->flags & mask ) == mask;
}

bool
RDBHandler::mapMsgToShm( unsigned int index, bool relocateBuffers )
{
    void* tgt = shmBufferGetPtr( index );
    
    if ( !tgt || !mMsg )
        return false;

    if ( relocateBuffers )
    {
        // total size of buffer is determined by message size 
        shmBufferSetSize( index, getMsgTotalSize() );
    
        // buffer size has changed, so compute the header information again
        shmHdrUpdate();
    }

    // copy the local message data to the target location
    if ( shmBufferGetSize( index ) >= getMsgTotalSize() )
        memcpy( tgt, getMsg(), getMsgTotalSize() );
    
    return true;
}

bool
RDBHandler::addMsgToShm( unsigned int index, RDB_MSG_t* msg )
{
    char* tgt = ( char* ) shmBufferGetPtr( index );
    
    if ( !tgt || !msg )
        return false;
    
    unsigned int msgTotalSize = msg->hdr.headerSize + msg->hdr.dataSize;
    
    // get the current usage of the buffer
    unsigned int usedSize = shmBufferGetUsedSize( index );

    // copy the local message data to the target location
    if ( shmBufferGetSize( index ) < ( usedSize + msgTotalSize ) )
        return false;
    
    memcpy( ( tgt + usedSize ), msg, msgTotalSize );
    
    return true;
}

unsigned int
RDBHandler::shmBufferGetUsedSize( unsigned int index )
{
    char* tgt = ( char* ) shmBufferGetPtr( index );
    
    if ( !tgt )
        return 0;
    
    unsigned int noBytes = 0;
    
    while ( 1 )
    {
        RDB_MSG_t* msg = ( RDB_MSG_t* ) tgt;
        
        if ( msg->hdr.magicNo != RDB_MAGIC_NO )
            break;
        
        unsigned int msgSize = msg->hdr.headerSize + msg->hdr.dataSize;
        
        noBytes += msgSize;
        tgt     += msgSize;
    }
    
    return noBytes;
}

bool
RDBHandler::shmBufferClear( unsigned int index, bool force )
{
    // check if buffer is locked
    if ( !force && shmBufferIsLocked( index ) )
        return false;
    
    char* tgt = ( char* ) shmBufferGetPtr( index );
    
    if ( !tgt )
        return false;
    
    memset( tgt, 0, shmBufferGetSize( index ) );
    
    return true;
}

bool
RDBHandler::shmBufferIsLocked( unsigned int index )
{
    // check if buffer is locked
    RDB_SHM_BUFFER_INFO_t* info = shmBufferGetInfo( index );
    
    if ( !info )
        return true;
    
    //fprintf( stderr, "RDBHandler::shmBufferIsLocked: buffer %d, flags = 0x%x, isLocked = 0x%x\n", 
    //                 index, info->flags, info->flags & RDB_SHM_BUFFER_FLAG_LOCK );

    return ( ( info->flags & RDB_SHM_BUFFER_FLAG_LOCK ) != 0 );
}

bool
RDBHandler::shmBufferLock( unsigned int index )
{
    RDB_SHM_BUFFER_INFO_t* info = shmBufferGetInfo( index );
    
    if ( !info )
        return false;
    
    info->flags |= RDB_SHM_BUFFER_FLAG_LOCK;

    //fprintf( stderr, "RDBHandler::shmBufferLock: mShmHdr %p locking buffer %d, flags = 0x%x\n", mShmHdr, index, info->flags );
    
    return true;
}

bool
RDBHandler::shmBufferRelease( unsigned int index )
{
    RDB_SHM_BUFFER_INFO_t* info = shmBufferGetInfo( index );
    
    if ( !info )
        return false;
 
    info->flags &= ~RDB_SHM_BUFFER_FLAG_LOCK;
    
    //fprintf( stderr, "RDBHandler::shmBufferRelease: mShmHdr %p releasing buffer %d, flags = 0x%x\n", mShmHdr, index, info->flags );
 
    return true;
}


unsigned int
RDBHandler::shmGetNoBuffers()
{
    if ( !mShmHdr )
        return 0;
    
    return mShmHdr->noBuffers;
}

void
RDBHandler::printPackageSizes()
{
    fprintf( stderr, "RDBHandler::printPackageSizes: sizes of all known packages\n" );
    
    for ( int i = RDB_PKG_ID_START_OF_FRAME; i <= RDB_PKG_ID_TONE_MAPPING; i++ )
    {
        bool hasExtended = pkgId2size( i ) != pkgId2size( i, true );
        
        fprintf( stderr, "%40s, size = %4d", pkgId2string( i ).c_str(), ( int ) pkgId2size( i ) );

        if ( hasExtended )
            fprintf( stderr, " ( %4d )", ( int ) pkgId2size( i, true ) );

        fprintf( stderr, "\n" );
    }
}

void
RDBHandler::parseMessage( RDB_MSG_t* msg )
{
    if ( !msg )
        return;

    if ( !msg->hdr.dataSize )
        return;
    
    RDB_MSG_ENTRY_HDR_t* entry = ( RDB_MSG_ENTRY_HDR_t* ) ( ( ( char* ) msg ) + msg->hdr.headerSize );
    uint32_t remainingBytes    = msg->hdr.dataSize;
        
    while ( 1 )
    {
        parseMessageEntry( entry, msg->hdr.simTime, msg->hdr.frameNo );

        remainingBytes -= ( entry->headerSize + entry->dataSize );
        
        if ( !remainingBytes )
            return;
        
        entry = ( RDB_MSG_ENTRY_HDR_t* ) ( ( ( ( char* ) entry ) + entry->headerSize + entry->dataSize ) );
    }
}

void
RDBHandler::parseMessageEntry( RDB_MSG_ENTRY_HDR_t* entryHdr, const double & simTime, const unsigned int & simFrame )
{
    if ( !entryHdr )
        return;
    
    unsigned int noElements = entryHdr->elementSize ? ( entryHdr->dataSize / entryHdr->elementSize ) : 0;
    
    // some packages may not have an active element
    if ( !noElements )
    {
        switch ( entryHdr->pkgId )
        {
            case RDB_PKG_ID_START_OF_FRAME:
                parseStartOfFrame( simTime, simFrame );
                break;
                
            case RDB_PKG_ID_END_OF_FRAME:
                parseEndOfFrame( simTime, simFrame );
                break;
        }        
        return;
    }
        
    char* dataPtr = ( char* ) entryHdr;
    dataPtr += entryHdr->headerSize;
        
    for ( unsigned int i = 0; i < noElements; i++ )
    {
        switch ( entryHdr->pkgId )
        {
            case RDB_PKG_ID_START_OF_FRAME:
                parseStartOfFrame( simTime, simFrame );
                break;
                
            case RDB_PKG_ID_END_OF_FRAME:
                parseEndOfFrame( simTime, simFrame );
                break;
                
            case RDB_PKG_ID_COORD_SYSTEM:
                parseEntry( ( RDB_COORD_SYSTEM_t* ) dataPtr, simTime, simFrame, entryHdr->pkgId, entryHdr->flags, i, noElements );
                break;
                
            case RDB_PKG_ID_COORD:
                parseEntry( ( RDB_COORD_t* ) dataPtr, simTime, simFrame, entryHdr->pkgId, entryHdr->flags, i, noElements );
                break;
                
            case RDB_PKG_ID_ROAD_POS:
                parseEntry( ( RDB_ROAD_POS_t* ) dataPtr, simTime, simFrame, entryHdr->pkgId, entryHdr->flags, i, noElements );
                break;
                
            case RDB_PKG_ID_LANE_INFO:
                parseEntry( ( RDB_LANE_INFO_t* ) dataPtr, simTime, simFrame, entryHdr->pkgId, entryHdr->flags, i, noElements );
                break;
                
            case RDB_PKG_ID_ROADMARK:
                parseEntry( ( RDB_ROADMARK_t* ) dataPtr, simTime, simFrame, entryHdr->pkgId, entryHdr->flags, i, noElements );
                break;
                
            case RDB_PKG_ID_OBJECT_CFG:
                parseEntry( ( RDB_OBJECT_CFG_t* ) dataPtr, simTime, simFrame, entryHdr->pkgId, entryHdr->flags, i, noElements );
                break;
                
            case RDB_PKG_ID_OBJECT_STATE:
                parseEntry( ( RDB_OBJECT_STATE_t* ) dataPtr, simTime, simFrame, entryHdr->pkgId, entryHdr->flags, i, noElements );
                break;
                
            case RDB_PKG_ID_VEHICLE_SYSTEMS:
                parseEntry( ( RDB_VEHICLE_SYSTEMS_t* ) dataPtr, simTime, simFrame, entryHdr->pkgId, entryHdr->flags, i, noElements );
                break;
                
            case RDB_PKG_ID_VEHICLE_SETUP:
                parseEntry( ( RDB_VEHICLE_SETUP_t* ) dataPtr, simTime, simFrame, entryHdr->pkgId, entryHdr->flags, i, noElements );
                break;
                
            case RDB_PKG_ID_ENGINE:
                parseEntry( ( RDB_ENGINE_t* ) dataPtr, simTime, simFrame, entryHdr->pkgId, entryHdr->flags, i, noElements );
                break;
                
            case RDB_PKG_ID_DRIVETRAIN:
                parseEntry( ( RDB_DRIVETRAIN_t* ) dataPtr, simTime, simFrame, entryHdr->pkgId, entryHdr->flags, i, noElements );
                break;
                
            case RDB_PKG_ID_WHEEL:
                parseEntry( ( RDB_WHEEL_t* ) dataPtr, simTime, simFrame, entryHdr->pkgId, entryHdr->flags, i, noElements );
                break;
    
            case RDB_PKG_ID_PED_ANIMATION:
                parseEntry( ( RDB_PED_ANIMATION_t* ) dataPtr, simTime, simFrame, entryHdr->pkgId, entryHdr->flags, i, noElements );
                break;
    
            case RDB_PKG_ID_SENSOR_STATE:
                parseEntry( ( RDB_SENSOR_STATE_t* ) dataPtr, simTime, simFrame, entryHdr->pkgId, entryHdr->flags, i, noElements );
                break;
    
            case RDB_PKG_ID_SENSOR_OBJECT:
                parseEntry( ( RDB_SENSOR_OBJECT_t* ) dataPtr, simTime, simFrame, entryHdr->pkgId, entryHdr->flags, i, noElements );
                break;
                
            case RDB_PKG_ID_CAMERA:
                parseEntry( ( RDB_CAMERA_t* ) dataPtr, simTime, simFrame, entryHdr->pkgId, entryHdr->flags, i, noElements );
                break;
                
            case RDB_PKG_ID_CONTACT_POINT:
                parseEntry( ( RDB_CONTACT_POINT_t* ) dataPtr, simTime, simFrame, entryHdr->pkgId, entryHdr->flags, i, noElements );
                break;
                
            case RDB_PKG_ID_TRAFFIC_SIGN:
                parseEntry( ( RDB_TRAFFIC_SIGN_t* ) dataPtr, simTime, simFrame, entryHdr->pkgId, entryHdr->flags, i, noElements );
                break;
                
            case RDB_PKG_ID_ROAD_STATE:
                parseEntry( ( RDB_ROAD_STATE_t* ) dataPtr, simTime, simFrame, entryHdr->pkgId, entryHdr->flags, i, noElements );
                break;
                
            case RDB_PKG_ID_IMAGE:
            case RDB_PKG_ID_LIGHT_MAP:
            case RDB_PKG_ID_OCCLUSION_MATRIX:
                parseEntry( ( RDB_IMAGE_t* ) dataPtr, simTime, simFrame, entryHdr->pkgId, entryHdr->flags, i, noElements );
                break;
                
            case RDB_PKG_ID_LIGHT_SOURCE:
                parseEntry( ( RDB_LIGHT_SOURCE_t* ) dataPtr, simTime, simFrame, entryHdr->pkgId, entryHdr->flags, i, noElements );
                break;
                
            case RDB_PKG_ID_ENVIRONMENT:
                parseEntry( ( RDB_ENVIRONMENT_t* ) dataPtr, simTime, simFrame, entryHdr->pkgId, entryHdr->flags, i, noElements );
                break;
                
            case RDB_PKG_ID_TRIGGER:
                parseEntry( ( RDB_TRIGGER_t* ) dataPtr, simTime, simFrame, entryHdr->pkgId, entryHdr->flags, i, noElements );
                break;
                
            case RDB_PKG_ID_DRIVER_CTRL:
                parseEntry( ( RDB_DRIVER_CTRL_t* ) dataPtr, simTime, simFrame, entryHdr->pkgId, entryHdr->flags, i, noElements );
                break;
                
            case RDB_PKG_ID_TRAFFIC_LIGHT:
                parseEntry( ( RDB_TRAFFIC_LIGHT_t* ) dataPtr, simTime, simFrame, entryHdr->pkgId, entryHdr->flags, i, noElements );
                break;
                
            case RDB_PKG_ID_SYNC:
                parseEntry( ( RDB_SYNC_t* ) dataPtr, simTime, simFrame, entryHdr->pkgId, entryHdr->flags, i, noElements );
                break;
                
            case RDB_PKG_ID_DRIVER_PERCEPTION:
                parseEntry( ( RDB_DRIVER_PERCEPTION_t* ) dataPtr, simTime, simFrame, entryHdr->pkgId, entryHdr->flags, i, noElements );
                break;
                
            case RDB_PKG_ID_TONE_MAPPING:
                parseEntry( ( RDB_FUNCTION_t* ) dataPtr, simTime, simFrame, entryHdr->pkgId, entryHdr->flags, i, noElements );
                break;
                
            case RDB_PKG_ID_ROAD_QUERY:
                parseEntry( ( RDB_ROAD_QUERY_t* ) dataPtr, simTime, simFrame, entryHdr->pkgId, entryHdr->flags, i, noElements );
                break;
                
            case RDB_PKG_ID_TRAJECTORY:
                parseEntry( ( RDB_TRAJECTORY_t* ) dataPtr, simTime, simFrame, entryHdr->pkgId, entryHdr->flags, i, noElements );
                break;

            case RDB_PKG_ID_CUSTOM_SCORING:
                parseEntry( ( RDB_CUSTOM_SCORING_t* ) dataPtr, simTime, simFrame, entryHdr->pkgId, entryHdr->flags, i, noElements );
                break;

            case RDB_PKG_ID_DYN_2_STEER:
                parseEntry( ( RDB_DYN_2_STEER_t* ) dataPtr, simTime, simFrame, entryHdr->pkgId, entryHdr->flags, i, noElements );
                break;

            case RDB_PKG_ID_SCP:
                parseEntry( ( RDB_SCP_t* ) dataPtr, simTime, simFrame, entryHdr->pkgId, entryHdr->flags, i, noElements );
                break;

            case RDB_PKG_ID_STEER_2_DYN:
                parseEntry( ( RDB_STEER_2_DYN_t* ) dataPtr, simTime, simFrame, entryHdr->pkgId, entryHdr->flags, i, noElements );
                break;
                
            case RDB_PKG_ID_PROXY:
                parseEntry( ( RDB_PROXY_t* ) dataPtr, simTime, simFrame, entryHdr->pkgId, entryHdr->flags, i, noElements );
                break;

            case RDB_PKG_ID_MOTION_SYSTEM:
                parseEntry( ( RDB_MOTION_SYSTEM_t* ) dataPtr, simTime, simFrame, entryHdr->pkgId, entryHdr->flags, i, noElements );
                break;
                
            case RDB_PKG_ID_FREESPACE:
                parseEntry( ( RDB_FREESPACE_t* ) dataPtr, simTime, simFrame, entryHdr->pkgId, entryHdr->flags, i, noElements );
                break;
                
            case RDB_PKG_ID_DYN_EL_SWITCH:
                parseEntry( ( RDB_DYN_EL_SWITCH_t* ) dataPtr, simTime, simFrame, entryHdr->pkgId, entryHdr->flags, i, noElements );
                break;
                
            case RDB_PKG_ID_DYN_EL_DOF:
                parseEntry( ( RDB_DYN_EL_DOF_t* ) dataPtr, simTime, simFrame, entryHdr->pkgId, entryHdr->flags, i, noElements );
                break;
                
            case RDB_PKG_ID_IG_FRAME:
                parseEntry( ( RDB_IG_FRAME_t* ) dataPtr, simTime, simFrame, entryHdr->pkgId, entryHdr->flags, i, noElements );
                break;
                
            case RDB_PKG_ID_RT_PERFORMANCE:
                parseEntry( ( RDB_RT_PERFORMANCE_t* ) dataPtr, simTime, simFrame, entryHdr->pkgId, entryHdr->flags, i, noElements );
                break;
                
            case RDB_PKG_ID_CUSTOM_OBJECT_CTRL_TRACK:
                parseEntry( ( RDB_CUSTOM_OBJECT_CTRL_TRACK_t* ) dataPtr, simTime, simFrame, entryHdr->pkgId, entryHdr->flags, i, noElements );
                break;
                
            case RDB_PKG_ID_RAY:
                parseEntry( ( RDB_RAY_t* ) dataPtr, simTime, simFrame, entryHdr->pkgId, entryHdr->flags, i, noElements );
                break;
                
            case RDB_PKG_ID_SYMBOL_STATE:
                parseEntry( ( RDB_SYMBOL_STATE_t* ) dataPtr, simTime, simFrame, entryHdr->pkgId, entryHdr->flags, i, noElements );
                break;

            case RDB_PKG_ID_RADAR_HIT_POINT:
                parseEntry( ( RDB_RADAR_HIT_POINT_t* ) dataPtr, simTime, simFrame, entryHdr->pkgId, entryHdr->flags, i, noElements );
                break;
                
            default:
                fprintf( stderr, "RDBHandler::parseMessageEntry: unhandled pkgId = %d\n", entryHdr->pkgId );
                break;
        }
        dataPtr += entryHdr->elementSize;
    }
}
        
void
RDBHandler::parseMessageEntryInfo( const double & simTime, const unsigned int & simFrame, const unsigned short & pkgId, const unsigned short & flags, const unsigned int & elemId, const unsigned int & totalElem )
{
    fprintf( stderr, "RDBHandler::parseMessageEntryInfo: simTime = %.3f, simFrame = %d, pkgId = %d, flags = 0x%x, elemId = %d, totalElem = %d\n",
                     simTime, simFrame, pkgId, flags, elemId, totalElem );
}

void
RDBHandler::parseStartOfFrame( const double & simTime, const unsigned int & simFrame )
{
    fprintf( stderr, "RDBHandler::parseStartOfFrame: simTime = %.3f, simFrame = %d\n", simTime, simFrame );
}

void
RDBHandler::parseEndOfFrame( const double & simTime, const unsigned int & simFrame )
{
    fprintf( stderr, "RDBHandler::parseEndOfFrame: simTime = %.3f, simFrame = %d\n", simTime, simFrame );
}

void
RDBHandler::parseEntry( RDB_GEOMETRY_t *data, const double & simTime, const unsigned int & simFrame, const unsigned short & pkgId, const unsigned short & flags, const unsigned int & elemId, const unsigned int & totalElem )
{
    parseMessageEntryInfo( simTime, simFrame, pkgId, flags, elemId, totalElem );
    print( *data, 4 );
}

void
RDBHandler::parseEntry( RDB_COORD_SYSTEM_t *data, const double & simTime, const unsigned int & simFrame, const unsigned short & pkgId, const unsigned short & flags, const unsigned int & elemId, const unsigned int & totalElem )
{
    parseMessageEntryInfo( simTime, simFrame, pkgId, flags, elemId, totalElem );
    print( *data, 4 );
}

void
RDBHandler::parseEntry( RDB_COORD_t *data, const double & simTime, const unsigned int & simFrame, const unsigned short & pkgId, const unsigned short & flags, const unsigned int & elemId, const unsigned int & totalElem )
{
    parseMessageEntryInfo( simTime, simFrame, pkgId, flags, elemId, totalElem );
    print( *data, 4 );
}

void
RDBHandler::parseEntry( RDB_ROAD_POS_t *data, const double & simTime, const unsigned int & simFrame, const unsigned short & pkgId, const unsigned short & flags, const unsigned int & elemId, const unsigned int & totalElem )
{
    parseMessageEntryInfo( simTime, simFrame, pkgId, flags, elemId, totalElem );
    print( *data, 4 );
}

void
RDBHandler::parseEntry( RDB_LANE_INFO_t *data, const double & simTime, const unsigned int & simFrame, const unsigned short & pkgId, const unsigned short & flags, const unsigned int & elemId, const unsigned int & totalElem )
{
    parseMessageEntryInfo( simTime, simFrame, pkgId, flags, elemId, totalElem );
    print( *data, 4 );
}

void
RDBHandler::parseEntry( RDB_ROADMARK_t *data, const double & simTime, const unsigned int & simFrame, const unsigned short & pkgId, const unsigned short & flags, const unsigned int & elemId, const unsigned int & totalElem )
{
    parseMessageEntryInfo( simTime, simFrame, pkgId, flags, elemId, totalElem );
    print( *data, 4 );
}

void
RDBHandler::parseEntry( RDB_OBJECT_CFG_t *data, const double & simTime, const unsigned int & simFrame, const unsigned short & pkgId, const unsigned short & flags, const unsigned int & elemId, const unsigned int & totalElem )
{
    parseMessageEntryInfo( simTime, simFrame, pkgId, flags, elemId, totalElem );
    print( *data, 4 );
}

void
RDBHandler::parseEntry( RDB_OBJECT_STATE_t *data, const double & simTime, const unsigned int & simFrame, const unsigned short & pkgId, const unsigned short & flags, const unsigned int & elemId, const unsigned int & totalElem )
{
    parseMessageEntryInfo( simTime, simFrame, pkgId, flags, elemId, totalElem );
    print( *data, 4 );
}

void
RDBHandler::parseEntry( RDB_VEHICLE_SYSTEMS_t *data, const double & simTime, const unsigned int & simFrame, const unsigned short & pkgId, const unsigned short & flags, const unsigned int & elemId, const unsigned int & totalElem )
{
    parseMessageEntryInfo( simTime, simFrame, pkgId, flags, elemId, totalElem );
    print( *data, 4 );
}

void
RDBHandler::parseEntry( RDB_VEHICLE_SETUP_t *data, const double & simTime, const unsigned int & simFrame, const unsigned short & pkgId, const unsigned short & flags, const unsigned int & elemId, const unsigned int & totalElem )
{
    parseMessageEntryInfo( simTime, simFrame, pkgId, flags, elemId, totalElem );
    print( *data, 4 );
}

void
RDBHandler::parseEntry( RDB_ENGINE_t *data, const double & simTime, const unsigned int & simFrame, const unsigned short & pkgId, const unsigned short & flags, const unsigned int & elemId, const unsigned int & totalElem )
{
    parseMessageEntryInfo( simTime, simFrame, pkgId, flags, elemId, totalElem );
    print( *data, 4 );
}

void
RDBHandler::parseEntry( RDB_DRIVETRAIN_t *data, const double & simTime, const unsigned int & simFrame, const unsigned short & pkgId, const unsigned short & flags, const unsigned int & elemId, const unsigned int & totalElem )
{
    parseMessageEntryInfo( simTime, simFrame, pkgId, flags, elemId, totalElem );
    print( *data, 4 );
}

void
RDBHandler::parseEntry( RDB_WHEEL_t *data, const double & simTime, const unsigned int & simFrame, const unsigned short & pkgId, const unsigned short & flags, const unsigned int & elemId, const unsigned int & totalElem )
{
    parseMessageEntryInfo( simTime, simFrame, pkgId, flags, elemId, totalElem );
    print( *data, 4 );
}

void
RDBHandler::parseEntry( RDB_PED_ANIMATION_t *data, const double & simTime, const unsigned int & simFrame, const unsigned short & pkgId, const unsigned short & flags, const unsigned int & elemId, const unsigned int & totalElem )
{
    parseMessageEntryInfo( simTime, simFrame, pkgId, flags, elemId, totalElem );
    print( *data, 4 );
}

void
RDBHandler::parseEntry( RDB_SENSOR_STATE_t *data, const double & simTime, const unsigned int & simFrame, const unsigned short & pkgId, const unsigned short & flags, const unsigned int & elemId, const unsigned int & totalElem )
{
    parseMessageEntryInfo( simTime, simFrame, pkgId, flags, elemId, totalElem );
    print( *data, 4 );
}

void
RDBHandler::parseEntry( RDB_SENSOR_OBJECT_t *data, const double & simTime, const unsigned int & simFrame, const unsigned short & pkgId, const unsigned short & flags, const unsigned int & elemId, const unsigned int & totalElem )
{
    parseMessageEntryInfo( simTime, simFrame, pkgId, flags, elemId, totalElem );
    print( *data, 4 );
}

void
RDBHandler::parseEntry( RDB_CAMERA_t *data, const double & simTime, const unsigned int & simFrame, const unsigned short & pkgId, const unsigned short & flags, const unsigned int & elemId, const unsigned int & totalElem )
{
    parseMessageEntryInfo( simTime, simFrame, pkgId, flags, elemId, totalElem );
    print( *data, 4 );
}

void
RDBHandler::parseEntry( RDB_CONTACT_POINT_t *data, const double & simTime, const unsigned int & simFrame, const unsigned short & pkgId, const unsigned short & flags, const unsigned int & elemId, const unsigned int & totalElem )
{
    parseMessageEntryInfo( simTime, simFrame, pkgId, flags, elemId, totalElem );
    print( *data, 4 );
}

void
RDBHandler::parseEntry( RDB_TRAFFIC_SIGN_t *data, const double & simTime, const unsigned int & simFrame, const unsigned short & pkgId, const unsigned short & flags, const unsigned int & elemId, const unsigned int & totalElem )
{
    parseMessageEntryInfo( simTime, simFrame, pkgId, flags, elemId, totalElem );
    print( *data, 4 );
}

void
RDBHandler::parseEntry( RDB_ROAD_STATE_t *data, const double & simTime, const unsigned int & simFrame, const unsigned short & pkgId, const unsigned short & flags, const unsigned int & elemId, const unsigned int & totalElem )
{
    parseMessageEntryInfo( simTime, simFrame, pkgId, flags, elemId, totalElem );
    print( *data, 4 );
}

void
RDBHandler::parseEntry( RDB_IMAGE_t *data, const double & simTime, const unsigned int & simFrame, const unsigned short & pkgId, const unsigned short & flags, const unsigned int & elemId, const unsigned int & totalElem )
{
    parseMessageEntryInfo( simTime, simFrame, pkgId, flags, elemId, totalElem );
    print( *data, 4 );
}

void
RDBHandler::parseEntry( RDB_LIGHT_SOURCE_t *data, const double & simTime, const unsigned int & simFrame, const unsigned short & pkgId, const unsigned short & flags, const unsigned int & elemId, const unsigned int & totalElem )
{
    parseMessageEntryInfo( simTime, simFrame, pkgId, flags, elemId, totalElem );
    print( *data, 4 );
}

void
RDBHandler::parseEntry( RDB_ENVIRONMENT_t *data, const double & simTime, const unsigned int & simFrame, const unsigned short & pkgId, const unsigned short & flags, const unsigned int & elemId, const unsigned int & totalElem )
{
    parseMessageEntryInfo( simTime, simFrame, pkgId, flags, elemId, totalElem );
    print( *data, 4 );
}

void
RDBHandler::parseEntry( RDB_TRIGGER_t *data, const double & simTime, const unsigned int & simFrame, const unsigned short & pkgId, const unsigned short & flags, const unsigned int & elemId, const unsigned int & totalElem )
{
    parseMessageEntryInfo( simTime, simFrame, pkgId, flags, elemId, totalElem );
    print( *data, 4 );
}

void
RDBHandler::parseEntry( RDB_DRIVER_CTRL_t *data, const double & simTime, const unsigned int & simFrame, const unsigned short & pkgId, const unsigned short & flags, const unsigned int & elemId, const unsigned int & totalElem )
{
    parseMessageEntryInfo( simTime, simFrame, pkgId, flags, elemId, totalElem );
    print( *data, 4 );
}

void
RDBHandler::parseEntry( RDB_TRAFFIC_LIGHT_t *data, const double & simTime, const unsigned int & simFrame, const unsigned short & pkgId, const unsigned short & flags, const unsigned int & elemId, const unsigned int & totalElem )
{
    parseMessageEntryInfo( simTime, simFrame, pkgId, flags, elemId, totalElem );
    print( *data, 4 );
}

void
RDBHandler::parseEntry( RDB_SYNC_t *data, const double & simTime, const unsigned int & simFrame, const unsigned short & pkgId, const unsigned short & flags, const unsigned int & elemId, const unsigned int & totalElem )
{
    parseMessageEntryInfo( simTime, simFrame, pkgId, flags, elemId, totalElem );
    print( *data, 4 );
}

void
RDBHandler::parseEntry( RDB_DRIVER_PERCEPTION_t * data, const double & simTime, const unsigned int & simFrame, const unsigned short & pkgId, const unsigned short & flags, const unsigned int & elemId, const unsigned int & totalElem )
{
    parseMessageEntryInfo( simTime, simFrame, pkgId, flags, elemId, totalElem );
    print( *data, 4 );
}

void
RDBHandler::parseEntry( RDB_FUNCTION_t *data, const double & simTime, const unsigned int & simFrame, const unsigned short & pkgId, const unsigned short & flags, const unsigned int & elemId, const unsigned int & totalElem )
{
    parseMessageEntryInfo( simTime, simFrame, pkgId, flags, elemId, totalElem );
    print( *data, 4 );
}

void
RDBHandler::parseEntry( RDB_ROAD_QUERY_t *data, const double & simTime, const unsigned int & simFrame, const unsigned short & pkgId, const unsigned short & flags, const unsigned int & elemId, const unsigned int & totalElem )
{
    parseMessageEntryInfo( simTime, simFrame, pkgId, flags, elemId, totalElem );
    print( *data, 4 );
}

void
RDBHandler::parseEntry( RDB_POINT_t *data, const double & simTime, const unsigned int & simFrame, const unsigned short & pkgId, const unsigned short & flags, const unsigned int & elemId, const unsigned int & totalElem )
{
    parseMessageEntryInfo( simTime, simFrame, pkgId, flags, elemId, totalElem );
    print( *data, 4 );
}

void
RDBHandler::parseEntry( RDB_TRAJECTORY_t *data, const double & simTime, const unsigned int & simFrame, const unsigned short & pkgId, const unsigned short & flags, const unsigned int & elemId, const unsigned int & totalElem )
{
    parseMessageEntryInfo( simTime, simFrame, pkgId, flags, elemId, totalElem );
    print( *data, 4 );
}

void
RDBHandler::parseEntry( RDB_CUSTOM_SCORING_t *data, const double & simTime, const unsigned int & simFrame, const unsigned short & pkgId, const unsigned short & flags, const unsigned int & elemId, const unsigned int & totalElem )
{
    parseMessageEntryInfo( simTime, simFrame, pkgId, flags, elemId, totalElem );
    print( *data, 4 );
}

void
RDBHandler::parseEntry( RDB_DYN_2_STEER_t *data, const double & simTime, const unsigned int & simFrame, const unsigned short & pkgId, const unsigned short & flags, const unsigned int & elemId, const unsigned int & totalElem )
{
    parseMessageEntryInfo( simTime, simFrame, pkgId, flags, elemId, totalElem );
    print( *data, 4 );
}

void
RDBHandler::parseEntry( RDB_SCP_t *data, const double & simTime, const unsigned int & simFrame, const unsigned short & pkgId, const unsigned short & flags, const unsigned int & elemId, const unsigned int & totalElem )
{
    parseMessageEntryInfo( simTime, simFrame, pkgId, flags, elemId, totalElem );
    print( *data, 4 );
}

void
RDBHandler::parseEntry( RDB_STEER_2_DYN_t *data, const double & simTime, const unsigned int & simFrame, const unsigned short & pkgId, const unsigned short & flags, const unsigned int & elemId, const unsigned int & totalElem )
{
    parseMessageEntryInfo( simTime, simFrame, pkgId, flags, elemId, totalElem );
    print( *data, 4 );
}

void
RDBHandler::parseEntry( RDB_PROXY_t *data, const double & simTime, const unsigned int & simFrame, const unsigned short & pkgId, const unsigned short & flags, const unsigned int & elemId, const unsigned int & totalElem )
{
    parseMessageEntryInfo( simTime, simFrame, pkgId, flags, elemId, totalElem );
    print( *data, 4 );
}

void
RDBHandler::parseEntry( RDB_MOTION_SYSTEM_t *data, const double & simTime, const unsigned int & simFrame, const unsigned short & pkgId, const unsigned short & flags, const unsigned int & elemId, const unsigned int & totalElem )
{
    parseMessageEntryInfo( simTime, simFrame, pkgId, flags, elemId, totalElem );
    print( *data, 4 );
}

void
RDBHandler::parseEntry( RDB_FREESPACE_t *data, const double & simTime, const unsigned int & simFrame, const unsigned short & pkgId, const unsigned short & flags, const unsigned int & elemId, const unsigned int & totalElem )
{
    parseMessageEntryInfo( simTime, simFrame, pkgId, flags, elemId, totalElem );
    print( *data, 4 );
}

void
RDBHandler::parseEntry( RDB_DYN_EL_SWITCH_t *data, const double & simTime, const unsigned int & simFrame, const unsigned short & pkgId, const unsigned short & flags, const unsigned int & elemId, const unsigned int & totalElem )
{
    parseMessageEntryInfo( simTime, simFrame, pkgId, flags, elemId, totalElem );
    print( *data, 4 );
}

void
RDBHandler::parseEntry( RDB_DYN_EL_DOF_t *data, const double & simTime, const unsigned int & simFrame, const unsigned short & pkgId, const unsigned short & flags, const unsigned int & elemId, const unsigned int & totalElem )
{
    parseMessageEntryInfo( simTime, simFrame, pkgId, flags, elemId, totalElem );
    print( *data, 4 );
}

void
RDBHandler::parseEntry( RDB_IG_FRAME_t *data, const double & simTime, const unsigned int & simFrame, const unsigned short & pkgId, const unsigned short & flags, const unsigned int & elemId, const unsigned int & totalElem )
{
    parseMessageEntryInfo( simTime, simFrame, pkgId, flags, elemId, totalElem );
    print( *data, 4 );
}

void
RDBHandler::parseEntry( RDB_RT_PERFORMANCE_t *data, const double & simTime, const unsigned int & simFrame, const unsigned short & pkgId, const unsigned short & flags, const unsigned int & elemId, const unsigned int & totalElem )
{
    parseMessageEntryInfo( simTime, simFrame, pkgId, flags, elemId, totalElem );
    print( *data, 4 );
}

void
RDBHandler::parseEntry( RDB_CUSTOM_OBJECT_CTRL_TRACK_t *data, const double & simTime, const unsigned int & simFrame, const unsigned short & pkgId, const unsigned short & flags, const unsigned int & elemId, const unsigned int & totalElem )
{
    parseMessageEntryInfo( simTime, simFrame, pkgId, flags, elemId, totalElem );
    print( *data, 4 );
}

void
RDBHandler::parseEntry( RDB_RAY_t *data, const double & simTime, const unsigned int & simFrame, const unsigned short & pkgId, const unsigned short & flags, const unsigned int & elemId, const unsigned int & totalElem )
{
    parseMessageEntryInfo( simTime, simFrame, pkgId, flags, elemId, totalElem );
    print( *data, 4 );
}

void
RDBHandler::parseEntry( RDB_SYMBOL_STATE_t *data, const double & simTime, const unsigned int & simFrame, const unsigned short & pkgId, const unsigned short & flags, const unsigned int & elemId, const unsigned int & totalElem )
{
    parseMessageEntryInfo( simTime, simFrame, pkgId, flags, elemId, totalElem );
    print( *data, 4 );
}

void
RDBHandler::parseEntry( RDB_RADAR_HIT_POINT_t *data, const double & simTime, const unsigned int & simFrame, const unsigned short & pkgId, const unsigned short & flags, const unsigned int & elemId, const unsigned int & totalElem )
{
    parseMessageEntryInfo( simTime, simFrame, pkgId, flags, elemId, totalElem );
    print( *data, 4 );
}

} // namespace Framework
