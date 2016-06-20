#pragma once

#include "Types.h"

enum class Ease {
  Linear,
  QuadIn,
  QuadInOut,
  QuadOut,
  SinIn,
  SinInOut,
  SinOut,
};

class Easing {
public:

  static Real Linear(Real t) {
    return t;
  }

  static Real QuadIn(Real t) {
    return t * t;
  }

  static Real QuadOut(Real t) {
    return t * (2 - t);
  }

  static Real Calculate(Real t, Ease ease) {
    Real easeVal;
    switch (ease) {
    case Ease::Linear:
      easeVal = Easing::Linear(t);
      break;
    case Ease::QuadIn:
      easeVal = Easing::QuadIn(t);
      break;
    case Ease::QuadOut:
      easeVal = Easing::QuadOut(t);
      break;
    }
    return easeVal;
  }

};