#pragma once

#include <vector>
#include <variant>
#include <string>
#include <memory>

#include "Expression.h"
#include "../../LanguageObjects.h"

class StringExpression : public Expression {
public:
    std::vector<std::variant<std::string, std::unique_ptr<Expression>>>
        stringLiteralsAndExpressions;
    StringExpression() {}

    std::string print(int identLevel) override {
        std::string toPrintString = std::string("String Expression: ") + "\n";
        for(int i = 0; i < stringLiteralsAndExpressions.size(); ++i) {
            
            //string
            if(std::string* stringLiteral = std::get_if<std::string> 
                (&stringLiteralsAndExpressions[i])) {

                toPrintString += ident(identLevel) + "Raw String: " + 
                    *stringLiteral + "\n";
                continue;
            }

            //expression
            toPrintString += ident(identLevel) + "Expression within string: " + 
                std::get<std::unique_ptr<Expression>>
                (stringLiteralsAndExpressions[i])->print(identLevel + 1);
            
        }
        return toPrintString;
    }

    bool isLValue() const override {
        return false;
    }

    std::unique_ptr<Variable> value(ScopeManager* scopeManager) override {
        
        std::string stringExpressionValue;
        
        for(int i = 0; i < stringLiteralsAndExpressions.size(); ++i) {
            
            //string
            if(std::string* stringLiteral = std::get_if<std::string> 
                (&stringLiteralsAndExpressions[i])) {

                stringExpressionValue += *stringLiteral;
                continue;
            }

            //expression
            std::unique_ptr<Variable> innerVariable = 
                std::get<std::unique_ptr<Expression>>
                (stringLiteralsAndExpressions[i])->value(scopeManager);
            stringExpressionValue += 
                VariableManagement::getStringFromVariable(innerVariable.get());
            
        }
        return std::make_unique<SimpleVariable>
            (SimpleVariable(stringExpressionValue));
    }

};
