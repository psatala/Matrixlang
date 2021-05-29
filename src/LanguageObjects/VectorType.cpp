#include "../../headers/LanguageObjects/VectorType.h"
#include "../../headers/LanguageObjects/Expressions/Expression.h"

VectorType::VectorType(std::unique_ptr<Type> type, 
    std::unique_ptr<Expression> expression) : type(std::move(type)), 
    expression(std::move(expression)) {}

std::string VectorType::print(int identLevel) {
    return std::string("Vector type") + "\n" + 
        ident(identLevel) + "Contained type: " + 
            type->print(identLevel + 1) + 
        ident(identLevel) + "Expression: " + 
            expression->print(identLevel + 1);
}