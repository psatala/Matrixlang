#pragma once

#include "Variable.h"

// variable used only as return value
class VoidVariable : public Variable {
public:
    VoidVariable() { type = VOID; }
};