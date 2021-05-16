#include "../../headers/LanguageObjects/If.h"
#include "../../headers/LanguageObjects/Statement.h"


std::string If::getTrueStatementInfo(int identLevel) { 
    if(trueStatement)
        return trueStatement->print(identLevel + 1);
    return std::string("\n");
}

std::string If::getFalseStatementInfo(int identLevel) { 
    if(falseStatement)
        return falseStatement->print(identLevel + 1);
    return std::string("\n");
}


std::string If::print(int identLevel) { 
    return std::string("If") + "\n" + 
        ident(identLevel) + "Conditional expression: " + 
            conditionalExpression->print(identLevel + 1) + 
        ident(identLevel) + "True statement: " + 
            getTrueStatementInfo(identLevel) + 
        ident(identLevel) + "False statement: " + 
            getFalseStatementInfo(identLevel);
}