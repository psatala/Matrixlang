#pragma once

#include <istream>
#include <ostream>

#include "ExecutionObjects/ScopeManager.h"
#include "LanguageObjects/Program.h"
#include "LanguageObjects/EmbeddedFunction.h"

class Executor {
public:
    std::istream& userInputStream;
    std::ostream& errStream;
    std::ostream& outputStream;

    std::unique_ptr<Program> program;
    ScopeManager scopeManager;

    Executor(std::istream& userInputStream, std::ostream& errStream, 
        std::ostream& outputStream, std::unique_ptr<Program> program);
};