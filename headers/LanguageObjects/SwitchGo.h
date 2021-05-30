#pragma once

#include <memory>
#include <vector>

#include "../LanguageObjects.h"
#include "Switch.h"
#include "CaseGo.h"
#include "Default.h"

class SwitchGo : public Switch {
public:
    std::vector<std::unique_ptr<CaseGo>> caseGoInstructions;
    std::unique_ptr<Default> defaultInstruction;
    SwitchGo();

    std::string print(int identLevel) override;

    // ~SwitchGo();
};