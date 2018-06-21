#pragma once

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif

#include "EventListener.h"

class TimerEventListener : public EventListener
{
   uint32_t m_Millis;
   uint32_t m_StartMillis;
   uint16_t numFires = 0;
   bool m_MultiFire = false;

   public:
      TimerEventListener(uint32_t time, bool multiFire, EventAction trigger);
      virtual ~TimerEventListener() = default;

      void setupListener() override;
      bool isEventTriggered() const override;

      bool performTriggerAction(EventContext *) override;
};
