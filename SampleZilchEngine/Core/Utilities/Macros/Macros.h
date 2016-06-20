/*****************************************************************************/
/*!
@file   Macros.h
@author Christian Sagel
@par    email: c.sagel\@digipen.edu
@date   4/24/2016
@brief  A collection of macros to alleviate rote code writing!
*/
/******************************************************************************/
#pragma once

/*===================*
*     Properties     *
*===================*/
// This macro creates the definitions of getter and setter method for a Property.
#define SZE_DEFINE_PROPERTY(propertyType, propertyName)                           \
  const propertyType& get##propertyName() const {                                 \
    return propertyName;                                                          \
  }                                                                               \
  void set##propertyName(propertyType const& value) {                             \
    propertyName = value;                                                         \
  }
// This macro creates the definitions of a getter method for a Property.
#define SZE_DEFINE_GETTER(propertyType, propertyName)                             \
  const propertyType& get##propertyName() const {                                 \
    return propertyName;                                                          \
  }
// This macro creates the definitions of a setter method for a Property.
#define SZE_DEFINE_SETTER(propertyType, propertyName)                             \
  void set##propertyName(propertyType const& value) {                             \
    propertyName = value;                                                         \
  }