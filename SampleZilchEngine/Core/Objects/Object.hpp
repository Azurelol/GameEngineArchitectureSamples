#pragma once
#include "Object.h"

namespace SZEngine
{
  /**************************************************************************/
  /*!
  @brief  Serializes the Object by type through Zilch.
  @param  builder A reference to the JSON builder which will contain the
                  deserialized data.
  @param  state A pointer to the singleton Zilch's executable state.
  @param  objectPtr A handle (Pointer/Zilch Handle) to the Object.
  @param  boundType A pointer to the Object's derived type.
  @note
  */
  /**************************************************************************/
  template<typename ObjectPtr>
  void Object::SerializeByType(Zilch::JsonBuilder& builder, Zilch::ExecutableState * state, 
                               Zilch::BoundType * boundType, ObjectPtr objectPtr, Zilch::Handle handle)
  {
    Zilch::PropertyArray& properties = boundType->AllProperties;
    Zilch::ExceptionReport report;

    for (auto& property : properties) {

      // Any propertiess that do not have the 'Property' attribute won't be
      // considered for serialization. We are doing this explicitly because
      // there are times that you wish to have properties bound but do not want them
      // serialized. A clear example of this comes is during scripts. If a script
      // has for example a pointer as a Property.. how do you serialize a pointer?    
      if (!property->HasAttribute("Property"))
        continue;

      // Perhaps also check that you don't try to serialize pointer types?


      // Set up the 'getter' method so that we can serialize the value
      Zilch::Call call(property->Get, state);
      if (handle.Dereference())
        call.SetHandle(Zilch::Call::This, handle);
      else
        call.SetHandleVirtual(Zilch::Call::This, objectPtr);
      call.Invoke(report);

      //----------------------------------------------------------------------/
      // Serialize by type
      //----------------------------------------------------------------------/
      builder.Key(property->Name);
      {
        // Property: Real (float)
        if (Zilch::Type::IsSame(property->PropertyType, ZilchTypeId(Zilch::Real)))
        {
          builder.Value(call.Get<Zilch::Real>(Zilch::Call::Return));
        }
        // Property: Enum (This one is a bit trickier since we have to
        //           associate a given enum (which is an int) with a string
        //           that we can serialize properly..
        else if (Zilch::Type::IsEnumType(property->PropertyType)) {
          Zilch::Call call(property->Get, state);
          if (handle.Dereference())
            call.SetHandle(Zilch::Call::This, handle);
          else
            call.SetHandleVirtual(Zilch::Call::This, objectPtr);

          Zilch::ExceptionReport reportForEnum;
          call.Invoke(reportForEnum);

          // Convert the enum to an integer
          auto enumAsInt = call.Get<Zilch::Integer>(Zilch::Call::Return);
          // Convert the enum to a string
          Zilch::String enumAsStr = property->PropertyType->GenericToString((byte*)&enumAsInt);
          builder.Value(enumAsStr);
        }
        // Property: Integer
        else if (Zilch::Type::IsSame(property->PropertyType, ZilchTypeId(Zilch::Integer)))
        {
          builder.Value(call.Get<Zilch::Integer>(Zilch::Call::Return));
        }
        // Property: String
        else if (Zilch::Type::IsSame(property->PropertyType, ZilchTypeId(Zilch::String)))
        {
          builder.Value(call.Get<Zilch::String>(Zilch::Call::Return));
        }
        // Property: Boolean
        else if (Zilch::Type::IsSame(property->PropertyType, ZilchTypeId(Zilch::Boolean)))
        {
          builder.Value(call.Get<Zilch::Boolean>(Zilch::Call::Return));
        }
        // Property: Real3
        else if (Zilch::Type::IsSame(property->PropertyType, ZilchTypeId(Zilch::Real3)))
        {
          auto value = call.Get<Zilch::Real3>(Zilch::Call::Return);
          // Serialize a Vec3 Object
          builder.Begin(Zilch::JsonType::Object);
          {
            builder.Key("Vec3");
            builder.Begin(Zilch::JsonType::Object);
            {
              builder.Key("x");
              builder.Value(value.x);
              builder.Key("y");
              builder.Value(value.y);
              builder.Key("z");
              builder.Value(value.z);
            }
            builder.End();
          }
          builder.End();
        }
      }



    }
  }

  /**************************************************************************/
  /*!
  @brief  Deserializes the Object through Zilch, filling in the values
          for all known bound properties.
  @param  properties The list of properties in the Object.
  @param  state A pointer to the singleton Zilch's executable state.
  @param  objectPtr A handle (Pointer/Zilch Handle) to the Object.
  @param  boundType A pointer to the Object's derived type.
  @note   This function is called by derived classes.
  @todo   Factor out the code to convert from Values!
  */
  /**************************************************************************/
  template<typename ObjectPtr>
  void Object::DeserializeByType(Zilch::JsonValue * properties, Zilch::ExecutableState * state, 
                                 Zilch::BoundType * boundType, ObjectPtr objectPtr, Zilch::Handle handle)
  {
    // If there's no properties, there's nothing to do!
    if (properties == nullptr || boundType == nullptr)
      return;

    for (auto property : properties->OrderedMembers.all()) {

      Zilch::JsonValue* value = property->Value;
      // Attemot to either get it as a 'Property' with Getter/Setter methods
      Zilch::Property* namedProperty = boundType->GetInstanceProperty(property->Key);
      //----------------------------------------------------------------------/
      // If we could not get it as a property, try as a field
      if (namedProperty == nullptr) {
        namedProperty = boundType->GetInstanceField(property->Key);
      }
      // If the property on file could not be found on the object...
      if (namedProperty == nullptr)
        continue;
      // If there is no set method
      if (namedProperty->Set == nullptr)
        continue;

      if (!namedProperty->HasAttribute("Property"))
        continue;

      // Construct a Zilch::Call object for invoking the set method!
      Zilch::ExceptionReport report;
      Zilch::Call call(namedProperty->Set, state);
      // If it's a handle
      if (handle.Dereference())
        call.SetHandle(Zilch::Call::This, handle);
      // Else if its a pointer
      else
        call.SetHandleVirtual(Zilch::Call::This, objectPtr);

      bool isValidProperty = true;

      //----------------------------------------------------------------------/
      // Deserialize by type
      //----------------------------------------------------------------------/
      // Type is a float
      if (Zilch::Type::IsSame(namedProperty->PropertyType, ZilchTypeId(Zilch::Real)))
      {
        call.Set(0, value->AsFloat());
      }
      // Type is an enum
      else if (Zilch::Type::IsEnumType(namedProperty->PropertyType)) {
        Zilch::BoundType* enumType = Zilch::Type::GetBoundType(namedProperty->PropertyType);
        auto enumValue = enumType->GetStaticProperty(value->AsString());

        // If the value cannot be found (could have been removed), do nothing
        if (!enumValue)
          continue;

        // Convert the enum to its integer value
        Zilch::Call getCall(enumValue->Get, state);
        getCall.Invoke(report);
        int enumAsInt = getCall.Get<Zilch::Integer>(Zilch::Call::Return);
        call.Set(0, enumAsInt);
      }
      // Type is an int.
      else if (Zilch::Type::IsSame(namedProperty->PropertyType, ZilchTypeId(Zilch::Integer)))
      {
        call.Set(0, value->AsInteger());
      }
      // Type is a string.
      else if (Zilch::Type::IsSame(namedProperty->PropertyType, ZilchTypeId(Zilch::String)))
      {
        // If there is no value, create an empty string
        if (!value)
          call.Set(0, Zilch::String());
        else
          call.Set(0, value->AsString());
      }
      // Type is a Boolean.
      else if (Zilch::Type::IsSame(namedProperty->PropertyType, ZilchTypeId(Zilch::Boolean)))
      {
        call.Set(0, value->AsBool());
      }
      // Type is a Real3.
      else if (Zilch::Type::IsSame(namedProperty->PropertyType, ZilchTypeId(Zilch::Real3)))
      {
        auto real3 = value->GetMember("Vec3");
        auto x = real3->GetMember("x")->AsFloat();
        auto y = real3->GetMember("y")->AsFloat();
        auto z = real3->GetMember("z")->AsFloat();
        call.Set(0, Zilch::Real3(x, y, z));
      }
      // Type is invalid 
      else {
        isValidProperty = false;
      }
      // If the property was valid
      if (isValidProperty)
        call.Invoke(report);

    }

  }
}