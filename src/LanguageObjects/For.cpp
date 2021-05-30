#include "../../headers/LanguageObjects/For.h"
#include "../../headers/LanguageObjects/Statement.h"

For::For(std::unique_ptr<Declaration> declaration,
    std::unique_ptr<Expression> conditionalExpression,
    std::unique_ptr<Expression> incrementalExpression,
    std::unique_ptr<Statement> statement) : 
        declaration(std::move(declaration)),
        conditionalExpression(std::move(conditionalExpression)),
        incrementalExpression(std::move(incrementalExpression)),
        statement(std::move(statement)) {}

std::string For::getStatementInfo(int identLevel) { 
    if(statement)
        return statement->print(identLevel + 1);
    return std::string("\n");
}

std::string For::print(int identLevel) { 
    return std::string("For") + "\n" + 
        ident(identLevel) + "Declaration: " + 
            declaration->print(identLevel + 1) + 
        ident(identLevel) + "Conditional expression: " + 
            conditionalExpression->print(identLevel + 1) + 
        ident(identLevel) + "Incremental expression: " + 
            incrementalExpression->print(identLevel + 1) + 
        ident(identLevel) + "Statement: " + 
            getStatementInfo(identLevel);
}

std::unique_ptr<Variable> For::execute(ScopeManager* scopeManager) {
    scopeManager->addBlock();
    if(declaration)
        declaration->execute(scopeManager);
    if(!conditionalExpression)
        throw std::string("Infinite loop detected");
    while(conditionalExpression->value(scopeManager)->getLogicalValue()) {
        statement->execute(scopeManager);
        if(incrementalExpression)
            incrementalExpression->value(scopeManager);
    }
    scopeManager->endBlock();
    return std::unique_ptr<Variable>(nullptr);
}