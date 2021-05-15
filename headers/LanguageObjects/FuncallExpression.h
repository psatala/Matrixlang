#pragma once

#include <memory>

#include "Expression.h"
#include "../LanguageObjects.h"

using ExpressionList = std::vector<std::unique_ptr<Expression>>;

class FuncallExpression : public Expression {
public:
    std::string identifier;
    std::unique_ptr<ExpressionList> expressionList;

    FuncallExpression(std::string identifier): identifier(identifier) {}

    FuncallExpression(std::string identifier, std::unique_ptr<ExpressionList> 
        expressionList) : identifier(identifier), 
        expressionList(std::move(expressionList)) {}

    std::string print(int identLevel) override {
        std::string toPrintString = std::string("Funcall expression") + "\n";
        toPrintString += ident(identLevel) + "Identifier: " + identifier + "\n";
        if(!expressionList)
            return toPrintString;
            
        for(int i = 0; i < expressionList->size(); ++i) {
            toPrintString += ident(identLevel) + "Expression no. " + 
                std::to_string(i) + ": " + 
                expressionList->at(i)->print(identLevel + 1);
        }
        return toPrintString;
    }

    bool isLValue() const override {
        return true;
    }

};