#include "../../headers/LanguageObjects/MatrixType.h"
#include "../../headers/LanguageObjects/Expressions/Expression.h"

MatrixType::MatrixType(std::unique_ptr<Type> type, 
    std::unique_ptr<Expression> firstExpression, 
    std::unique_ptr<Expression> secondExpression) : type(std::move(type)), 
    firstExpression(std::move(firstExpression)), 
    secondExpression(std::move(secondExpression)) {}

std::string MatrixType::print(int identLevel) {
    return std::string("Matrix type") + "\n" + 
        ident(identLevel) + "Contained type: " + 
            type->print(identLevel + 1) + 
        ident(identLevel) + "First expression: " + 
            firstExpression->print(identLevel + 1) + 
        ident(identLevel) + "Second expression" + 
            secondExpression->print(identLevel + 1);
}

unsigned int MatrixType::getFirstExpressionPosition(ScopeManager* 
    scopeManager) {

    return VariableManagement::getUnsignedIntValueFromVariable(
        firstExpression->value(scopeManager).get());
}

unsigned int MatrixType::getSecondExpressionPosition(ScopeManager* 
    scopeManager) {

    return VariableManagement::getUnsignedIntValueFromVariable(
        secondExpression->value(scopeManager).get());
}