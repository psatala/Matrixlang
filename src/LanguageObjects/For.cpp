#include "../../headers/LanguageObjects/For.h"
#include "../../headers/LanguageObjects/Statement.h"

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