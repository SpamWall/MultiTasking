#pragma once

class EventListener;

class EventContext
{
   void* data;

   public:
      EventContext();
      ~EventContext() = default;

      void setupContext();
      void loopIteration();
      void addListener(EventListener* lstn);
      void removeListener(const EventListener* lstn);
      EventListener* *m_Listeners{};
      int m_ListenerCount{};
};
