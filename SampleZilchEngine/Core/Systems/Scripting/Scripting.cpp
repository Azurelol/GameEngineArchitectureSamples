#include "Scripting.h"

namespace SZEngine {

  namespace Systems
  {
    Scripting::Scripting() : System("Scripting")
    {
      Interface.reset(new ZilchInterface());
    }

    void Scripting::Initialize()
    {
      TraceFunction("");
      Interface->Initialize();
    }

    void Scripting::Update(float dt)
    {
    }

    void Scripting::Terminate()
    {
      TraceFunction("");
      Interface->Terminate();
    }
  }

}