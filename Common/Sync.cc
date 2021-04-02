/* ===================================================
 *  file:       Clock.cpp
 * ---------------------------------------------------
 *  purpose:	an clock utility class
 * ---------------------------------------------------
 *  first edit:	27.04.2003 by M. Dupuis @ VIRES GmbH
 *  last mod.:  27.04.2003 by M. Dupuis @ VIRES GmbH
 * ===================================================
 */

// ====== INCLUSIONS ======
#include <math.h>
#include <iostream>
#include <sys/time.h>
#include "Sync.hh"

extern "C" {
    static volatile sig_atomic_t sGotSignal = 0;

    static void SyncHandleAlarm( int aSignal ) {
        if ( aSignal == SIGALRM ) {
            ++sGotSignal;
        }
    }
}

namespace Util {

Sync::Sync() : mFrameTime( 0.01 ),
               mInitLevel( 0 ),
               mFreeRun( true )
{
}

Sync::~Sync()
{
}

void 
Sync::setFrameTime( const double & time )
{
    mFrameTime = time;
}

const double & 
Sync::getFrameTime() const
{
    return mFrameTime;
}

void 
Sync::wait()
{
    if( mFreeRun )
        return;

    // wait until timer interrupt
    sigset_t zeromask;
        ::sigemptyset( &zeromask );
    while ( sGotSignal == 0 )
        ::sigsuspend( &zeromask );
    --sGotSignal;
}

bool 
Sync::start()
{
    sGotSignal = 0;
    mInitLevel = 0;
    
    if ( mFrameTime < 1.E-3 )
    {
        std::cerr << "WARNING: Sync::start: frametime under 1ms not supported! Switching to mode <free run>." << std::endl;
        stop();
        return false;
    }

    // set SIGALRM handler
    if( mInitLevel < 1 ) 
    {
        struct sigaction act;
        act.sa_handler = SyncHandleAlarm;
        ::sigemptyset( &act.sa_mask );
        act.sa_flags = 0;
        if ( ::sigaction( SIGALRM, &act, &mOldAction ) < 0 )
        {
            std::cerr << "Sync::start: sigaction error" << std::endl;
            return false;
        }
        mInitLevel = 1;
    }

    // block signal
    if( mInitLevel < 2 ) 
    {
        sigset_t newmask;
        ::sigemptyset( &newmask );
        ::sigaddset( &newmask, SIGALRM );
        if ( ::sigprocmask( SIG_BLOCK, &newmask, &mOldSigMask ) < 0 )
        {
            std::cerr << "Sync::start: sigprocmask error" << std::endl;
            return false;
        }
        mInitLevel = 2;
    }

    // set interval timer
    struct itimerval itval;
    // avoid int overflows
    time_t isec = static_cast<time_t>( floor( mFrameTime ) );
    int iusec   = static_cast<int>( floor( ( mFrameTime - isec ) * 1000000.0 + 0.5 ) );
    
    while ( iusec >= 1000000 ) 
    {
        iusec -= 1000000;
        isec += 1;
    }
    
    itval.it_interval.tv_sec  = isec;
    itval.it_interval.tv_usec = iusec;
    itval.it_value = itval.it_interval;

    if ( ::setitimer( ITIMER_REAL, &itval, 0 ) < 0 )
    {
        std::cerr << "Sync::start: setitimer error" << std::endl;
        return false;
    }

    mInitLevel = 3;

    // test the timer interval
    struct itimerval itvalSet;
    if( ::getitimer( ITIMER_REAL, &itvalSet ) < 0 )
    {
        std::cerr << "Sync::start: getitimer error" << std::endl;
        return false;
    }
    
    mFreeRun = false;
    
    return true;
}

void 
Sync::stop()
{
    if ( mInitLevel >= 3 ) 
    {
	// clear interval timer
	    struct itimerval itval;
        itval.it_interval.tv_sec  = 0;
        itval.it_interval.tv_usec = 0;
        itval.it_value.tv_sec     = 0;
        itval.it_value.tv_usec     = 0;
        ::setitimer( ITIMER_REAL, &itval, 0 );
    }
    
    if ( mInitLevel >= 2 ) 
    {
        // reset signal mask
        ::sigprocmask( SIG_SETMASK, &mOldSigMask, 0 );
    }
    
    if ( mInitLevel >= 1 ) 
    {
        // reset alarm handler
        if( mOldAction.sa_handler )
            ::sigaction( SIGALRM, &mOldAction, 0 );
    }
    mInitLevel = 0;
    mFreeRun   = true;
}

bool
Sync::isActive()
{
    return !mFreeRun;
}

}; //namespace Util
