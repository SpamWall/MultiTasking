#include "EventListener.h"

inline bool EventListener::performTriggerAction(EventContext *ctx) {
   return (*m_TriggerAction)(this, ctx);
}

inline void *EventListener::setUserData(void *userData) {
   void *oldUserData = m_UserData;
   m_UserData = userData;

   return oldUserData;
}

inline void *EventListener::getUserData() const {
   return m_UserData;
}

bool operator== (const EventListener &left, const EventListener &right)
{
   bool retVal = false;
   if (((left.m_UserData == nullptr) && (right.m_UserData == nullptr)) ||
        (left.m_UserData != nullptr) && (right.m_UserData != nullptr)) {
      if (left.m_TriggerAction == right.m_TriggerAction) {
         retVal = true;
      }
   }

   return retVal;
}

bool operator!= (const EventListener &left, const EventListener &right)
{
   return !(left == right);
}


