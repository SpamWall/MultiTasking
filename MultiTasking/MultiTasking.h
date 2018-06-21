#pragma once

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "TimerEventListener.h"  // Needed so programs have access to the TimerEventListener class without having to directly include it also.
#include "PinEventListener.h"   // Needed so programs have access to the PinEventListener class without having to directly include it also.

#define USE_MULTITASKING_LOOP(mgr) void loop() { mgr.iteration(); }

class MultiTasking
{
   EventContext *m_ContextStack;
   uint16_t m_ContextOffset;
   uint16_t m_ContextDepth;
   uint8_t m_NumEvents;

   public:
      MultiTasking(uint8_t numEvents);
      ~MultiTasking();

      void iteration() const;

      EventContext* pushContext();
      EventContext* popContext();
      EventContext* resetContext() const;
      EventContext* currentContext() const;

      void addListener(const EventListener* lstn);
      void removeListener(const EventListener* lstn);
      void clearListeners();
};
