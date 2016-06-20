#include "Action.h"

unsigned Action::Created = 0;
unsigned Action::Destroyed = 0;
bool Action::Trace = true;

Action::Action(std::string type) : Type(type), Elapsed(0.0f), Duration(0.0f),
                                   ID(Created++)
{
}

Action::~Action()
{
}
