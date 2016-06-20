/*****************************************************************************/
/*!
\file   Object.h
\author Christian Sagel
\par    email: c.sagel\@digipen.edu
\date   4/17/2016
\brief  The base object class, from which everything else is derived.
*/
/******************************************************************************/
#pragma once

// Binding
#include "..\Binding\CoreBinding.h"

namespace SZEngine
{
  class Object : public Zilch::IZilchObject
  {
    std::string Name;
    unsigned ObjectID; // Unique identifier for the object
    static unsigned Created; // An incremented amount of how many objects have been created

  public:
    ZilchDeclareBaseType(Object, Zilch::TypeCopyMode::ReferenceType);
    Object(std::string name);
    virtual ~Object();
    SZE_DEFINE_PROPERTY(std::string, Name);
    using Ptr = Object*;

    // Main serialization methods
    template <typename ObjectPtr>
    void SerializeByType(Zilch::JsonBuilder& builder, Zilch::ExecutableState* state,
                         Zilch::BoundType* boundType, ObjectPtr objectPtr,
                         Zilch::Handle = Zilch::Handle());
    template <typename ObjectPtr>
    void DeserializeByType(Zilch::JsonValue* properties, Zilch::ExecutableState* state,
                           Zilch::BoundType* boundType, ObjectPtr objectPtr,
                           Zilch::Handle = Zilch::Handle());

    // For serializing the base object (Name property)
    void Serialize(Zilch::JsonBuilder& builder);
    void Deserialize(Zilch::JsonValue* properties);

  };
}

// Template definitions
#include "Object.hpp"