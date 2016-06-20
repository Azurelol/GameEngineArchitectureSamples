#include "Event.h"

// Initialize static members
unsigned Event::Created = 0;
unsigned Event::Destroyed = 0;

Event::Event(std::string name) : Name(name), ID(Created++)
{
}

Event::~Event(void)
{
  Destroyed++;
}
