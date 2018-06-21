#include "EventContext.h"
#include "EventListener.h"


#define MAX_LISTENERS 20

EventContext::EventContext() : data(nullptr)
{}

void EventContext::loopIteration() {
   for(int i=0; i < m_ListenerCount; i++) {
      if(m_Listeners[i]) { // Make sure it isn't deleted  
         if(m_Listeners[i]->isEventTriggered()) { // If we are triggered, run the action
            if(m_Listeners[i]->performTriggerAction(this)) { // If the action returns true, stop the chain
               return;
            }
         }
      }
   }
}

void EventContext::setupContext() {
   if(data) {
      delete data;
   }
   if(m_Listeners) {
      for(int i=0; i<m_ListenerCount; i++) {
         if(m_Listeners[i]) {
            delete m_Listeners[i];
         }
      }
      delete m_Listeners;
   }

   m_Listeners = new EventListener *[MAX_LISTENERS];
   m_ListenerCount = 0;
}

void EventContext::addListener(EventListener *listener) {
   for(int i = 0; i < m_ListenerCount; i++) { // Try to add in empty slot
      if(m_Listeners[m_ListenerCount] == 0) {
         m_Listeners[m_ListenerCount] = listener;
         return;
      }
   }

   // No empty slot, just add it
   m_Listeners[m_ListenerCount] = listener;
   listener->setupListener();
   m_ListenerCount++;
}

void EventContext::removeListener(const EventListener *listener) {
   for(int i=0; i<m_ListenerCount; i++) {
      if(m_Listeners[i] == listener) {
         delete listener;
         m_Listeners[i] = 0;
      }
   }
}
