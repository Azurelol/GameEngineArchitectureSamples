/******************************************************************************/
/*!
@file   CoreBinding.h
@author Christian Sagel
@par    email: c.sagel\@digipen.edu
@date   4/23/2016
@brief  This file includes the Zilch binding header. This header is included
        by all the classes that want to be added to the library.
*/
/******************************************************************************/
#pragma once

// Bindings
#include "CoreBindingTypes.h"
// Macros
#include "CoreBindingMacros.h"


namespace SZEngine {
  ZilchDeclareStaticLibrary(SZEngineCore);
}