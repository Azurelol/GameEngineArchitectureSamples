#pragma once

#include <string>

class Event {

  static unsigned Created;
  static unsigned Destroyed;
  unsigned ID;

public:
  std::string Name;
  Event(std::string name);
  virtual ~Event(void);

};
