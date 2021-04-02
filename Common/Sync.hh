/**
 * ===================================================
 *  file:	    Sync.hh
 * ---------------------------------------------------
 *  purpose:	basic class for sync signal handling
 * ---------------------------------------------------
 *  first edit:	26.07.2005 by M. Dupuis @ VIRES GmbH
 *  last mod.:  26.07.2005 by M. Dupuis @ VIRES GmbH
 * ===================================================
 */
#ifndef _UTIL_SYNC_HH
#define _UTIL_SYNC_HH

/* ====== INCLUSIONS ====== */
#include <signal.h>

/* ====== CLASSES ====== */
namespace Util {

class Sync {

    /**
    *  private section, do not enter
    */
    private:
        /**
        * time for synchronization in [ms]
        */
        double mFrameTime;

        /**
        * initialization level
        */
        int mInitLevel;
        
        /**
        * operating in free run?
        */
        bool mFreeRun; 
        
        struct sigaction mOldAction;
        sigset_t mOldSigMask;

    public:
        /**
        * constructor
        **/
        explicit Sync();

        /**
        ** Destroy the class.
        **/
        virtual ~Sync();

        /**
        * set the synchronization time
        * @param   frame time in [s]
        */
        void setFrameTime( const double & time );

        /**
        * member access function
        * @return   frame time in [s]
        */
        const double &  getFrameTime() const;

        /**
        * wait for the next frame
        */
        void wait();

        /**
        * start synchronization process
        */
        bool start();

        /**
        * stop synchronization process
        */
        void stop();
        
        /**
        * is the sync active?
        * @return true if synchronization is active
        */
        bool isActive();
};

} // namespace Util

#endif /* _UTIL_SYNC_HH */
