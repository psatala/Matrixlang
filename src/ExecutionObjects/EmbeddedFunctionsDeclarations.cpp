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
                std::make_unique<ArgumentList>(std::move(printArgumentList))
            )
        ));


        // input function
        scopeManager->addFunction(std::make_unique<EmbeddedFunction>(
            EmbeddedFunction(
                std::make_unique<SimpleType>(SimpleType(STRING)),
                "input",
                std::unique_ptr<ArgumentList>(nullptr)
            )
        ));


        // intToFloat function
        ArgumentList intToFloatArgumentList;
        intToFloatArgumentList.typeVector.push_back(
            std::make_unique<SimpleType>(SimpleType(INT))
        );
        intToFloatArgumentList.identifierVector.push_back("value");
        scopeManager->addFunction(std::make_unique<EmbeddedFunction>(
            EmbeddedFunction(
                std::make_unique<SimpleType>(SimpleType(FLOAT)), 
                "intToFloat", 
                std::make_unique<ArgumentList>(std::move(
                    intToFloatArgumentList))
            )
        ));



        // floatToInt function
        ArgumentList floatToIntArgumentList;
        floatToIntArgumentList.typeVector.push_back(
            std::make_unique<SimpleType>(SimpleType(FLOAT))
        );
        floatToIntArgumentList.identifierVector.push_back("value");
        scopeManager->addFunction(std::make_unique<EmbeddedFunction>(
            EmbeddedFunction(
                std::make_unique<SimpleType>(SimpleType(INT)), 
                "floatToInt", 
                std::make_unique<ArgumentList>(std::move(
                    floatToIntArgumentList))
            )
        ));




        // intToString function
        ArgumentList intToStringArgumentList;
        intToStringArgumentList.typeVector.push_back(
            std::make_unique<SimpleType>(SimpleType(INT))
        );
        intToStringArgumentList.identifierVector.push_back("value");
        scopeManager->addFunction(std::make_unique<EmbeddedFunction>(
            EmbeddedFunction(
                std::make_unique<SimpleType>(SimpleType(STRING)), 
                "intToString", 
                std::make_unique<ArgumentList>(std::move(
                    intToStringArgumentList))
            )
        ));



        // stringToInt function
        ArgumentList stringToIntArgumentList;
        stringToIntArgumentList.typeVector.push_back(
            std::make_unique<SimpleType>(SimpleType(STRING))
        );
        stringToIntArgumentList.identifierVector.push_back("value");
        scopeManager->addFunction(std::make_unique<EmbeddedFunction>(
            EmbeddedFunction(
                std::make_unique<SimpleType>(SimpleType(INT)), 
                "stringToInt", 
                std::make_unique<ArgumentList>(std::move(
                    stringToIntArgumentList))
            )
        ));



        // floatToString function
        ArgumentList floatToStringArgumentList;
        floatToStringArgumentList.typeVector.push_back(
            std::make_unique<SimpleType>(SimpleType(FLOAT))
        );
        floatToStringArgumentList.identifierVector.push_back("value");
        scopeManager->addFunction(std::make_unique<EmbeddedFunction>(
            EmbeddedFunction(
                std::make_unique<SimpleType>(SimpleType(STRING)), 
                "floatToString", 
                std::make_unique<ArgumentList>(std::move(
                    floatToStringArgumentList))
            )
        ));


        // stringToFloat function
        ArgumentList stringToFloatArgumentList;
        stringToFloatArgumentList.typeVector.push_back(
            std::make_unique<SimpleType>(SimpleType(STRING))
        );
        stringToFloatArgumentList.identifierVector.push_back("value");
        scopeManager->addFunction(std::make_unique<EmbeddedFunction>(
            EmbeddedFunction(
                std::make_unique<SimpleType>(SimpleType(FLOAT)), 
                "stringToFloat", 
                std::make_unique<ArgumentList>(std::move(
                    stringToFloatArgumentList))
            )
        ));

    }
}