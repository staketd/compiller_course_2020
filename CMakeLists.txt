project(myCompiller)

cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 17)

find_package(BISON REQUIRED)
find_package(FLEX REQUIRED)

include_directories(
        driver
        visitors
        symbol_table
        types
        include
        grammar/expressions
        grammar/statements
        grammar/BaseASTClass
        grammar/scanner
        grammar/
        grammar/functions
        function-calls
        .
)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${myCompiller_SOURCE_DIR}/bin)

set(
        HEADERS
        ${myCompiller_SOURCE_DIR}/driver/driver.h
        ${myCompiller_SOURCE_DIR}/parser.hh
)

BISON_TARGET(
        MyParser
        grammar/parser.y
        ${myCompiller_SOURCE_DIR}/grammar/parser.cpp
        DEFINES_FILE ${myCompiller_SOURCE_DIR}/grammar/parser.hh
)

FLEX_TARGET(
        MyScanner
        grammar/scanner.l
        ${myCompiller_SOURCE_DIR}/grammar/scanner/scanner.cpp
)

set(
        SOURCES
        grammar/BaseASTClass/BaseASTClass.cpp
        grammar/Program.cpp grammar/Program.h
        main.cpp
        driver/driver.cpp
        grammar/expressions/AddExpression.cpp
        grammar/expressions/MulExpression.cpp
        grammar/expressions/DivExpression.cpp
        grammar/expressions/SubstractExpression.cpp
        grammar/expressions/NumExpression.cpp
        grammar/expressions/IdentExpression.cpp
        grammar/expressions/Expression.h
        grammar/expressions/BinaryExpression.cpp
        grammar/expressions/EqualExpression.cpp
        grammar/expressions/LessExpression.cpp
        grammar/expressions/GreaterExpression.cpp
        grammar/expressions/LessOrEqualExpression.cpp
        grammar/expressions/GreaterOrEqualExpression.cpp
        grammar/expressions/ModuloExpression.cpp
        grammar/expressions/FuncCallExpression.cpp
        grammar/statements/Assignment.cpp
        grammar/statements/Statement.cpp
        grammar/statements/PrintStatement.cpp
        grammar/statements/ReadStatement.cpp
        grammar/statements/IfStatement.cpp
        grammar/statements/StatementList.cpp
        grammar/statements/Scope.cpp
        grammar/statements/VariableDeclaration.cpp
        grammar/statements/WhileStatement.cpp
        grammar/statements/ReturnStatement.cpp
        grammar/statements/FuncCallStatement.cpp
        grammar/functions/Function.cpp
        grammar/functions/FunctionList.cpp
        ${BISON_MyParser_OUTPUTS}
        ${FLEX_MyScanner_OUTPUTS}
        include/sources.h
        visitors/BaseVisitor.cpp visitors/BaseVisitor.h
        visitors/Interprenter.cpp visitors/Interprenter.h
        visitors/TemplateBaseVisitor.cpp
        symbol_table/Symbol.cpp
        types/BaseType.h
        types/Integer.cpp types/Integer.h
        types/UninitObject.cpp types/UninitObject.h
        symbol_table/ScopeLayer.cpp
        symbol_table/ScopeLayerTree.cpp
        types/PrimitiveType.cpp
        types/FunctionType.cpp
        types/UserClassType.cpp
        visitors/BuildSymbolLayerTree.cpp
        types/BoolType.cpp types/BoolType.h
        visitors/TypeChecker.cpp
        visitors/FunctionCallVisitor.cpp
        include/error_macro.h
        grammar/functions/CallArgumentList.cpp
        grammar/functions/FuncArgumentList.cpp
        function-calls/FunctionTable.cpp
        function-calls/Frame.cpp
        function-calls/FunctionMap.cpp

)

add_executable(
        myCompiller
        ${SOURCES}
)

target_include_directories(myCompiller PRIVATE ${myCompille_SOURCE_DIR})
