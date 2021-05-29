#pragma once

#include <string>
#include <memory>

#include "../../ExecutionObjects/ScopeManager.h"
#include "../../ExecutionObjects/Execution.h"
#include "../../ExecutionObjects/OperatorExecution.h"


class Expression {
public:
    virtual std::string print(int identLevel) = 0;
    virtual bool isLValue() const {
        return false;
    }
    virtual ~Expression() {}

    std::unique_ptr<Variable> logicalValue(ScopeManager* scopeManager) {
        return VariableManagement::createLogicalVariable(
            value(scopeManager)->getLogicalValue());
    }

    virtual std::unique_ptr<Variable> value(ScopeManager* scopeManager) {
        throw std::string("Not implemented exception");
    }
    
    virtual Variable* rawValue(ScopeManager* scopeManager) {
        throw std::string("Not implemented exception");
    }

};
