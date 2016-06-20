/******************************************************************************/
/*!
@file   CoreBindingTypes.h
@author Christian Sagel
@par    email: c.sagel\@digipen.edu
@date   4/24/2016
@brief  Binds types used in the engine so that Zilch can convert to them and
        back.
*/
/******************************************************************************/
#pragma once

// You would include any headers with custom types here...
// #include "CustomType.h"

ZilchDeclareRedirectType(std::string, Zilch::String);
ZilchDeclareRedirectType(SZEngine::Vec2, Zilch::Real2);
ZilchDeclareRedirectType(SZEngine::Vec3, Zilch::Real3);
ZilchDeclareRedirectType(SZEngine::Vec4, Zilch::Real4);