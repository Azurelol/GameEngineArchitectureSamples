/*****************************************************************************/
/*!
@file   Types.h
@author Christian Sagel
@par    email: c.sagel\@digipen.edu
@date   4/25/2016
@brief  Definitions for the types used in this engine.
*/
/******************************************************************************/
#pragma once

#include <string>

// Functions taking degrees are deprecated
#define GLM_FORCE_RADIANS
#include <GLM\glm.hpp>
#include <GLM\matrix.hpp>
#include <GLM\gtc\type_ptr.hpp>
#include <GLM\gtc\matrix_transform.hpp>

// Common types
using String = std::string;
using Boolean = bool;
using Integer = int;
using Integer2 = glm::i64vec2;
using Integer3 = glm::i64vec3;
using Integer4 = glm::i64vec4;
using Real = float;
using Vec2 = glm::vec2;
using Vec3 = glm::vec3;
using Vec4 = glm::vec4;
using Mat3 = glm::mat3;
using Mat4 = glm::mat4;


