#pragma once

#include "EventListener.h"

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif


class PinEventListener : public EventListener
{
   uint8_t m_Pin;
   uint8_t m_Debounce;
   bool m_TargetValue = HIGH;
   bool mustStartOpposite = true;
   mutable bool m_StartState;
   mutable uint32_t m_FirstNoticed = 0;

   public:
      PinEventListener(uint8_t pin, EventAction action, uint8_t debounce = 40);
      virtual ~PinEventListener() = default;

      void setupListener() override;
      bool isEventTriggered() const override;
};
