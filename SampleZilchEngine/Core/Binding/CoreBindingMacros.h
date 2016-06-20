/******************************************************************************/
/*!
@file   CoreBindingMacros.h
@author Christian Sagel
@par    email: c.sagel\@digipen.edu
@date   4/24/2016
@brief  A list of useful macros to be used while binding!
*/
/******************************************************************************/
#pragma once

// In a type definition, specifies that the object will be handled by pointer. The default is by handle.
#define SZE_BINDING_SET_HANDLE_TYPE_POINTER \
type->HandleManager = ZilchManagerId(Zilch::PointerManager)

// In a type definition, specifies that the object will be handled by pointer. The default is by handle.
#define SZE_BINDING_SET_HANDLE_TYPE_HANDLE \
type->HandleManager = ZilchManagerId(Zilch::HandleManager)

// This macro defines a property (getter/setter) to Zilch
#define SZE_BINDING_DEFINE_PROPERTY(className, propertyName)          \
  auto property##propertyName = ZilchBindProperty(builder, type, &className::get##propertyName, &className::set##propertyName, "" #propertyName);  \
  Zilch::Attribute propertyTag##propertyName;   \
  propertyTag##propertyName.Name = "Property";  \
  property##propertyName->Attributes.push_back(propertyTag##propertyName)

// This macro defines a property with no setter to Zilch
#define SZE_BINDING_DEFINE_PROPERTY_NOSETTER(className, propertyName) \
 auto property##propertyName = ZilchBindProperty(builder, type, &className::get##propertyName, ZilchNoSetter, "" #propertyName);  \
  Zilch::Attribute propertyTag##propertyName;   \
  propertyTag##propertyName.Name = "Property";  \
  property##propertyName->Attributes.push_back(propertyTag##propertyName)

/*====================
     COMPONENTS
====================*/
// This macro defines a component's constructor to zilch
#define SZE_BINDING_COMPONENT_DEFINE_CONSTRUCTOR(componentName)          \
  ZilchBindConstructor(builder, type, componentName, "owner", Entity&);  \
  ZilchBindDestructor(builder, type, componentName)
