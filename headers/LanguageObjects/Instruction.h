#pragma once

#include <memory>
#include <variant>

#include "../LanguageObjects.h"
#include "Expression.h"
#include "If.h"
#include "For.h"
#include "Return.h"
#include "Declaration.h"

class Instruction {
public:
    std::variant<
        std::unique_ptr<Expression>, 
        std::unique_ptr<If>, 
        std::unique_ptr<For>,
        std::unique_ptr<Return>,
        std::unique_ptr<Declaration>>
            instructionVariant;
    
    Instruction(std::variant<
        std::unique_ptr<Expression>, 
        std::unique_ptr<If>, 
        std::unique_ptr<For>,
        std::unique_ptr<Return>,
        std::unique_ptr<Declaration>>
            instructionVariant) : 
            instructionVariant(std::move(instructionVariant)) {}

    std::string print(int identLevel) {
        std::string toPrintString = std::string("Instruction") + "\n";
        switch (instructionVariant.index()) {
            
        case 0:
            toPrintString += ident(identLevel) + "Expression: ";
            // warning - expression can be null
            if(!std::get<std::unique_ptr<Expression>>(instructionVariant))
                break;
            toPrintString +=std::get<std::unique_ptr<Expression>>
                (instructionVariant)->print(identLevel + 1);
            break;
            
        case 1:
            toPrintString += ident(identLevel) + "If: " + 
                std::get<std::unique_ptr<If>>(instructionVariant)->
                print(identLevel + 1);
            break;
            
        case 2:
            toPrintString += ident(identLevel) + "For: " + 
                std::get<std::unique_ptr<For>>(instructionVariant)->
                print(identLevel + 1);
            break;
            
        case 3:
            toPrintString += ident(identLevel) + "Return: " + 
                std::get<std::unique_ptr<Return>>(instructionVariant)->
                print(identLevel + 1);
            break;
            
        case 4:
            toPrintString += ident(identLevel) + "Declaration: " + 
                std::get<std::unique_ptr<Declaration>>(instructionVariant)->
                print(identLevel + 1);
            break;
            
        default:
            toPrintString += ident(identLevel) + "Unknown content";
            break;
        }

        return toPrintString;
    }
};