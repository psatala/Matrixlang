#pragma once

#include <memory>
#include <vector>

#include "../LanguageObjects.h"
#include "Expressions/Expression.h"
#include "Switch.h"
#include "CaseC.h"
#include "Default.h"

class SwitchC : public Switch {
public:
    std::unique_ptr<Expression> postExpression;
    std::vector<std::unique_ptr<CaseC>> caseCInstructions;
    std::unique_ptr<Default> defaultInstruction;
    SwitchC();

    std::string print(int identLevel) override;

    // ~SwitchC();
};