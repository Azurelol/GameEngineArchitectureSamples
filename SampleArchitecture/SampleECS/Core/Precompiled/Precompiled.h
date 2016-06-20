/******************************************************************************/
/*!
@file   Precompiled.h
@author Christian Sagel
@par    email: c.sagel\@digipen.edu
@date   4/17/2016
@brief  The Precompiled header for Sample Zilch Engine.
@note   The use of this file requires that it be included in every translational
unit (.cpp) in the project.
*/
/******************************************************************************/
#pragma once

/**************************************************************************/
/*! Standard Library / Standard Template Library */
/**************************************************************************/
#include <vector>
#include <string>
#include <memory>
#include <unordered_map>
#include <iostream>
#include <fstream>
#include <sstream>
#include <chrono>
#include <typeindex>

/**************************************************************************/
/*! Math */
/**************************************************************************/
 #include <GLM\glm.hpp>
 #include <GLM\matrix.hpp>
 #include <GLM\gtc\type_ptr.hpp>
 #include <GLM\gtc\matrix_transform.hpp>

/**************************************************************************/
/*! Custom Utilities */
/**************************************************************************/
#include "..\Debug\Trace.h"
#include "..\Types\Types.h"
#include "..\Types\Macros.h"