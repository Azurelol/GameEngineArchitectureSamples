/*****************************************************************************/
/*!
@file      Bank.cpp
@author    Christian Sagel
@par       email: c.sagel\@digipen.edu
@date      5/22/2016
*/
/******************************************************************************/

#include "Bank.h"

namespace Resources {

  /**************************************************************************/
  /*!
  @brief  Unpacks and generates the resources contained inside a bank:
          Events, VCAs, Buses, etc... In addition it will generate SoundCues
          from the list of events that can be used.
  */
  /**************************************************************************/
  SoundCue::Container Bank::Generate()
  {
    Trace("");
    return Interface->Generate();
  }

}
