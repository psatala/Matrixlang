#pragma once

#include <memory>

#include "../LanguageObjects.h"
#include "Type.h"
#include "ArgumentList.h"
#include "Statement.h"

class Function {
public:
    std::unique_ptr<Type> type;
    std::string identifier;
    std::unique_ptr<ArgumentList> argumentList;
    std::unique_ptr<Statement> statement;

    Function(std::unique_ptr<Type> type, std::string identifier, 
        std::unique_ptr<ArgumentList> argumentList, 
        std::unique_ptr<Statement> statement) : type(std::move(type)), 
        identifier(identifier), argumentList(std::move(argumentList)), 
        statement(std::move(statement)) {}

    std::string print(int identLevel) { 
        std::string toPrintString = std::string("Function") + "\n" + 
            ident(identLevel) + "Type: " + type->print(identLevel + 1) + 
            ident(identLevel) + "Identifier: " + identifier + "\n" + 
            ident(identLevel) + "Argument list: " + "\n";

        if(argumentList)
            toPrintString += argumentList->print(identLevel + 1);
            
        toPrintString += ident(identLevel) + "Statement: " + 
                statement->print(identLevel + 1);

        return toPrintString;
    }

};