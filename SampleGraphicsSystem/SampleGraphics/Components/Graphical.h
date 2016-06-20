/******************************************************************************/
/*!
@file   Graphical.h
@author William Mao, Christian Sagel
@par    email: c.sagel\@digipen.edu
@date   1/22/2016
@brief  The Graphical component is the base class from which all graphical
        components derive from.
*/
/******************************************************************************/
#pragma once
#include "ComponentReference.h"

// Every graphical component needs to interact with a camera
#include "Camera.h"
#include "../Resources/Shader.h"

namespace Components {

  class Graphical : public Component {

  protected:

    bool Visible;

  public:

    Graphical(const std::string& name, Entity& owner) : Component(name, &owner),
                                                        Visible(true) {}
    virtual void Initialize() = 0;
    virtual void Terminate() = 0;
    virtual void SetUniforms(const Camera* camera) = 0;
    virtual void Draw() = 0;
    void Register();
    DEFINE_GETTER(bool, Visible);

    using Ptr = Graphical*;
    using Container = std::vector<Ptr>;

  protected:

    // I have decided to leave the time to register decoupled in case we need
    // to shift it around (rather than automatically happening on the constructor)

  };

}
