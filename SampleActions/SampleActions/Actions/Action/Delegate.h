#pragma once

/**************************************************************************/
/*!
@class Delegate Base class for delegates.
*/
/**************************************************************************/
class Delegate {
public:
  Delegate() {}
  virtual ~Delegate() {}
  virtual bool Call() = 0;
};

/**************************************************************************/
/*!
@class MemberFunctionDelegate An instantiation for a specific member function
       of a specific class.
*/
/**************************************************************************/
template <typename Class>
class MemberFunctionDelegate : public Delegate {
public:
  typedef void(Class::*MemFunc)();
  MemFunc FuncPtr;
  Class* ClassInstance;

  MemberFunctionDelegate(Class* instance, MemFunc funcPtr)
    : ClassInstance(instance), FuncPtr(funcPtr) {}

  virtual bool Call() {
    (ClassInstance->*FuncPtr)();
    return true;
  }
};