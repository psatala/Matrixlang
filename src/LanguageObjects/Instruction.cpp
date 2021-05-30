#include "../../headers/LanguageObjects/Statement.h"
#include "../../headers/LanguageObjects/Instruction.h"
#include "../../headers/LanguageObjects/Block.h"


Instruction::Instruction(std::variant<
    std::unique_ptr<Expression>, 
    std::unique_ptr<If>, 
    std::unique_ptr<Switch>, 
    std::unique_ptr<For>,
    std::unique_ptr<Return>,
    std::unique_ptr<Declaration>, 
    std::unique_ptr<Block>
    >
        instructionVariant) : 
        instructionVariant(std::move(instructionVariant)) {}



std::string Instruction::print(int identLevel) {
    std::string toPrintString = std::string("Instruction") + "\n";

    // expression
    if(std::unique_ptr<Expression>* expressionInstruction = 
        std::get_if<std::unique_ptr<Expression>>(&instructionVariant)) {
        
        toPrintString += ident(identLevel) + "Expression: ";
        // warning - expression can be null
        if(!*expressionInstruction)
            return toPrintString + "\n";
            
        return toPrintString + 
            (*expressionInstruction)->print(identLevel + 1);
    }

    // if
    if(std::unique_ptr<If>* ifInstruction = 
        std::get_if<std::unique_ptr<If>>(&instructionVariant)) {
        
        return toPrintString + ident(identLevel) + "If: " + 
            (*ifInstruction)->print(identLevel + 1);
    }

    // switch
    if(std::unique_ptr<Switch>* switchInstruction = 
        std::get_if<std::unique_ptr<Switch>>(&instructionVariant)) {
        
        return toPrintString + ident(identLevel) + "Switch: " + 
            (*switchInstruction)->print(identLevel + 1);
    }

    // for
    if(std::unique_ptr<For>* forInstruction = 
        std::get_if<std::unique_ptr<For>>(&instructionVariant)) {
        
        return toPrintString + ident(identLevel) + "For: " + 
            (*forInstruction)->print(identLevel + 1);
    }

    // return
    if(std::unique_ptr<Return>* returnInstruction = 
        std::get_if<std::unique_ptr<Return>>(&instructionVariant)) {
        
        return toPrintString + ident(identLevel) + "Return: " + 
            (*returnInstruction)->print(identLevel + 1);
    }

    // declaration
    if(std::unique_ptr<Declaration>* declarationInstruction = 
        std::get_if<std::unique_ptr<Declaration>>(&instructionVariant)) {
        
        return toPrintString + ident(identLevel) + "Declaration: " + 
            (*declarationInstruction)->print(identLevel + 1);
    }

    // block
    if(std::unique_ptr<Block>* blockInstruction = 
        std::get_if<std::unique_ptr<Block>>(&instructionVariant)) {
        
        return toPrintString + ident(identLevel) + "Block: " + 
            (*blockInstruction)->print(identLevel + 1);
    }

    // unknown
    return toPrintString + ident(identLevel) + "Unknown content";
}




std::unique_ptr<Variable> Instruction::execute(ScopeManager* scopeManager) {
    // expression
    if(std::unique_ptr<Expression>* expressionInstruction = 
        std::get_if<std::unique_ptr<Expression>>(&instructionVariant)) {
        
        (*expressionInstruction)->value(scopeManager);
        return std::unique_ptr<Variable>(nullptr);
    }

    // if
    if(std::unique_ptr<If>* ifInstruction = 
        std::get_if<std::unique_ptr<If>>(&instructionVariant)) {
        
        return (*ifInstruction)->execute(scopeManager);
    }

    // switch
    if(std::unique_ptr<Switch>* switchInstruction = 
        std::get_if<std::unique_ptr<Switch>>(&instructionVariant)) {
        
    }

    // for
    if(std::unique_ptr<For>* forInstruction = 
        std::get_if<std::unique_ptr<For>>(&instructionVariant)) {
        
    }

    // return
    if(std::unique_ptr<Return>* returnInstruction = 
        std::get_if<std::unique_ptr<Return>>(&instructionVariant)) {
        
    }

    // declaration
    if(std::unique_ptr<Declaration>* declarationInstruction = 
        std::get_if<std::unique_ptr<Declaration>>(&instructionVariant)) {
        
        return (*declarationInstruction)->execute(scopeManager);
    }

    // block
    if(std::unique_ptr<Block>* blockInstruction = 
        std::get_if<std::unique_ptr<Block>>(&instructionVariant)) {
        
        return (*blockInstruction)->execute(scopeManager);
    }

    // unknown
    return std::unique_ptr<Variable>(nullptr);
}