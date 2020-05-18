project(myCompiller)

cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 17)

find_package(BISON REQUIRED)
find_package(FLEX REQUIRED)

include_directories(
        scanner
        driver
        expressions
        statements
        BaseClass
        visitors
        symbol_table
        types
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
        parser.y
        ${myCompiller_SOURCE_DIR}/parser.cpp
        DEFINES_FILE ${myCompiller_SOURCE_DIR}/parser.hh
)

FLEX_TARGET(
        MyScanner
        scanner.l
        ${myCompiller_SOURCE_DIR}/scanner/scanner.cpp
)

set(
        SOURCES
        BaseClass/BaseClass.cpp
        Program.cpp Program.h
        main.cpp
        driver/driver.cpp
        expressions/AddExpression.cpp
        expressions/MulExpression.cpp
        expressions/DivExpression.cpp
        expressions/SubstractExpression.cpp
        expressions/NumExpression.cpp
        expressions/IdentExpression.cpp
        expressions/Expression.h
        expressions/BinaryExpression.cpp
        expressions/EqualExpression.cpp
        expressions/LessExpression.cpp
        expressions/GreaterExpression.cpp
        expressions/LessOrEqualExpression.cpp
        expressions/GreaterOrEqualExpression.cpp
        statements/Assignment.cpp
        statements/Statement.cpp
        statements/PrintStatement.cpp
        statements/ReadStatement.cpp
        statements/IfStatement.cpp
        statements/StatementList.cpp
        ${BISON_MyParser_OUTPUTS}
        ${FLEX_MyScanner_OUTPUTS}
        include/sources.h
        visitors/BaseVisitor.cpp visitors/BaseVisitor.h
        visitors/Interprenter.cpp visitors/Interprenter.h
        visitors/PrintTreeVisitor.cpp visitors/PrintTreeVisitor.h
        visitors/TemplateBaseVisitor.cpp
        symbol_table/Symbol.cpp
        types/BaseType.h
        types/Integer.cpp types/Integer.h types/UninitObject.cpp types/UninitObject.h statements/Scope.cpp statements/Scope.h statements/VariableDeclaration.cpp statements/VariableDeclaration.h symbol_table/ScopeLayer.cpp symbol_table/ScopeLayer.h symbol_table/ScopeLayerTree.cpp symbol_table/ScopeLayerTree.h types/PrimitiveType.cpp types/PrimitiveType.h types/FunctionType.cpp types/FunctionType.h types/UserClassType.cpp types/UserClassType.h expressions/ModuloExpression.cpp expressions/ModuloExpression.h statements/WhileStatement.cpp statements/WhileStatement.h visitors/BuildSymbolLayerTree.cpp visitors/BuildSymbolLayerTree.h types/BoolType.cpp types/BoolType.h visitors/TypeChecker.cpp visitors/TypeChecker.h include/error_macro.h)

add_executable(
        myCompiller
        ${SOURCES}
)

target_include_directories(myCompiller PRIVATE ${myCompille_SOURCE_DIR})
