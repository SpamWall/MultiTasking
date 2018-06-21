#include "MultiTasking.h"

MultiTasking::MultiTasking(uint8_t numEvents) : m_ContextStack(nullptr), m_ContextOffset(0), m_ContextDepth(0), m_NumEvents(numEvents)
{
   m_ContextStack = new EventContext[numEvents];
   m_ContextStack[m_ContextOffset].setupContext();
}

MultiTasking::~MultiTasking()
{
   delete m_ContextStack;  // Not technically necessary in arduino, but good form...
}

// NOTE:  Must not add more events than allowed by the numEvents parameter passsed to the constructor
void MultiTasking::addListener(const EventListener *listener)
{
   m_ContextStack[m_ContextOffset].addListener(listener);
}

void MultiTasking::removeListener(const EventListener *listener)
{
   m_ContextStack[m_ContextOffset].removeListener(listener);
}

void MultiTasking::clearListeners()
{
   
}

EventContext *MultiTasking::currentContext() const
{
   return &m_ContextStack[m_ContextOffset];
}

EventContext *MultiTasking::pushContext() {
   m_ContextOffset++;
   m_ContextStack[m_ContextOffset].setupContext();
   return &m_ContextStack[m_ContextOffset];
}

EventContext *MultiTasking::resetContext() const
{
   m_ContextStack[m_ContextOffset].setupContext();
   return &m_ContextStack[m_ContextOffset];
}

EventContext *MultiTasking::popContext() {
   m_ContextOffset--;
   return &m_ContextStack[m_ContextOffset];
}

void MultiTasking::iteration() const
{
   m_ContextStack[m_ContextOffset].loopIteration();
}
