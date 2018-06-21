#include "PinEventListener.h"

PinEventListener::PinEventListener(uint8_t pin, EventAction action, uint8_t debounce) : EventListener(action), m_Pin(pin), m_Debounce(debounce), m_StartState(false) {}

void PinEventListener::setupListener() {
   m_StartState = digitalRead(m_Pin);
}

bool PinEventListener::isEventTriggered() const {
   bool pinState = digitalRead(m_Pin);

   // Debounce check if we were triggered earlier
   if(m_FirstNoticed) {
      const uint32_t curMillis = millis();
      if(curMillis > m_FirstNoticed + m_Debounce) {
         // Debounce time expired, check again

         // Reset Watcher
         m_FirstNoticed = 0;

         // Check
         if(pinState == m_TargetValue) {
            return true;
         } else {
            return false;
         }
      } else {
         // Waiting for debouncer to finish
         return false;
      }
   }

   if(mustStartOpposite && (m_StartState == m_TargetValue)) {
      /* This is a waiting loop to wait for the pin to change to the opposite state before sensing */
      /* Q - do I need to debounce mustStartOpposite? */
      if(pinState == m_StartState) {
         // Do nothing
      } else {
         m_StartState = pinState;
      }

      return false;
   } else {
      /* This is the real deal */
      if(pinState == m_TargetValue) {
         if(m_Debounce == 0) {
            return true;
         } else {
            m_FirstNoticed = millis();
            return false;
         }
      } else {
         return false;
      }
   }
}
