#pragma once

#include <vector>
#include <variant>
#include <string>
#include <memory>

#include "Expression.h"
#include "../LanguageObjects.h"

class StringExpression : public Expression {
public:
    std::vector<std::variant<std::string, std::unique_ptr<Expression>>>
        stringLiteralsAndExpressions;
    StringExpression() {}

    std::string print(int identLevel) override {
        std::string toPrintString = std::string("String Expression: ") + "\n";
        for(int i = 0; i < stringLiteralsAndExpressions.size(); ++i) {
            
            //string
            if(0 == stringLiteralsAndExpressions[i].index()) {
                toPrintString += ident(identLevel) + "Raw String: " + 
                    std::get<std::string>(stringLiteralsAndExpressions[i]) + 
                    "\n";
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
};
