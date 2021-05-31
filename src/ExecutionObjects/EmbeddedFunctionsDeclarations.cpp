#include "../../headers/ExecutionObjects/EmbeddedFunctionsDeclarations.h"
#include "../../headers/LanguageObjects/EmbeddedFunction.h"


namespace EmbeddedFunctionsDeclarations {
    void addAllEmbeddedFunctions(ScopeManager* scopeManager) {

        // print function
        ArgumentList printArgumentList;
        printArgumentList.typeVector.push_back(
            std::make_unique<SimpleType>(SimpleType(STRING))
        );
        printArgumentList.identifierVector.push_back("textToPrint");
        scopeManager->addFunction(std::make_unique<EmbeddedFunction>(
            EmbeddedFunction(
                std::make_unique<SimpleType>(SimpleType(VOID)), 
                "print", 
                std::make_unique<ArgumentList>(std::move(printArgumentList)),
                std::unique_ptr<Statement>(nullptr)
            )));
    }
}