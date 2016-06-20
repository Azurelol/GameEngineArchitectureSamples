#pragma once
#include "Object.h"

class Resource : public Object {

  std::string AssetPath;

public:
  Resource(const std::string& name) : Object(name) {}
  DEFINE_PROPERTY(std::string, AssetPath);

};
