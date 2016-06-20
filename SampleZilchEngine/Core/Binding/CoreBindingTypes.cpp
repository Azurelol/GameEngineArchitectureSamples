/******************************************************************************/
/*!
@file   CoreBindingTypes.cpp
@author Christian Sagel
@par    email: c.sagel\@digipen.edu
@date   4/24/2016
@brief  Binds types used in the engine so that Zilch can convert to them and
        back.
*/
/******************************************************************************/
#include "CoreBindingTypes.h"

/*******************************************************************************
  Type A: std::string, Type B: Zilch::String
*******************************************************************************/
inline Zilch::String stdstringToZilchString(const std::string& string)
{
  return Zilch::String(string.c_str());
}
inline std::string ZilchStringTostdstring(const Zilch::String& string)
{
  return std::string(string.c_str());
}
ZilchDefineRedirectType(std::string, stdstringToZilchString, ZilchStringTostdstring);

/*******************************************************************************
  Type A: glm::vec2, Type B: Zilch::Real2
*******************************************************************************/
inline Zilch::Real2 Vec2ToReal2(const SZEngine::Vec2& vec)
{
  return Zilch::Real2(vec.x, vec.y);
}
inline SZEngine::Vec2 Real2ToVec2(const Zilch::Real2& vec)
{
  return SZEngine::Vec2(vec.x, vec.y);
}
ZilchDefineRedirectType(SZEngine::Vec2, Vec2ToReal2, Real2ToVec2);

/*******************************************************************************
  Type A: glm::vec3, Type B: Zilch::Real3
*******************************************************************************/
inline Zilch::Real3 Vec3ToReal3(const SZEngine::Vec3& vec)
{
  return Zilch::Real3(vec.x, vec.y, vec.z);
}
inline SZEngine::Vec3 Real3ToVec3(const Zilch::Real3& vec)
{
  return SZEngine::Vec3(vec.x, vec.y, vec.z);
}
ZilchDefineRedirectType(SZEngine::Vec3, Vec3ToReal3, Real3ToVec3);

/*******************************************************************************
  Type A: glm::vec2, Type B: Zilch::Real2
*******************************************************************************/
inline Zilch::Real4 Vec4ToReal4(const SZEngine::Vec4& vec)
{
  return Zilch::Real4(vec.x, vec.y, vec.z, vec.w);
}
inline SZEngine::Vec4 Real4ToVec4(const Zilch::Real4& vec)
{
  return SZEngine::Vec4(vec.x, vec.y, vec.z, vec.w);
}
ZilchDefineRedirectType(SZEngine::Vec4, Vec4ToReal4, Real4ToVec4);