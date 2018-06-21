#pragma once

#include "EventContext.h"

typedef bool(*EventAction)(EventListener*, EventContext*);

class EventListener
{
   void *m_UserData; // Anything you want to store here
   EventAction m_TriggerAction;

   public:
      EventListener(EventAction triggerAction, void *userData = nullptr) : m_UserData(userData), m_TriggerAction(triggerAction) {};
      virtual ~EventListener() = default;

      virtual void setupListener() = 0;
      virtual bool isEventTriggered() const = 0;

      virtual bool performTriggerAction(EventContext *);  // return false if I should stop the current chain

      void *setUserData(void *userData);
      void *getUserData() const;

   protected:
      EventAction getTriggerAction() const { return m_TriggerAction;  }

   friend bool operator== (const EventListener &left, const EventListener &right);
   friend bool operator!= (const EventListener &left, const EventListener &right);

};

bool operator== (const EventListener &left, const EventListener &right);
bool operator!= (const EventListener &left, const EventListener &right);
