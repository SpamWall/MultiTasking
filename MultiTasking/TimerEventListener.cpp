#include "TimerEventListener.h"
#include <limits.h>


TimerEventListener::TimerEventListener(uint32_t time, bool multiFire, EventAction t) : EventListener(t),
                                                                                          m_Millis(time),
                                                                                          m_StartMillis(0),
                                                                                          m_MultiFire(multiFire)
{
}

void TimerEventListener::setupListener()
{
   m_StartMillis = ::millis();
}

bool TimerEventListener::isEventTriggered() const
{
   const unsigned long curTime = ::millis();
   bool shouldFire = false;
   if (curTime >= m_StartMillis) {  /* Normal */
      if (curTime - m_StartMillis > m_Millis) {
         shouldFire = true;
      }
   } else {
      /* Wrap-Around! */
      if (((ULONG_MAX - m_StartMillis) + curTime) > m_Millis) {
         shouldFire = true;
      }
   }

   return shouldFire;
}

bool TimerEventListener::performTriggerAction(EventContext* c)
{
   bool returnval = (*getTriggerAction())(this, c);
   if (m_MultiFire) {
      // On multifire, setup to receive the event again
      setupListener();
     
      returnval = false;   // On multifire, we shouldn't stop the event chain no matter what, since we are just restarting in this context
   }
 
   return returnval;
}
