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
        objects
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
        visitors/sources.h
        visitors/BaseVisitor.cpp visitors/BaseVisitor.h
        visitors/Interprenter.cpp visitors/Interprenter.h
        visitors/PrintTreeVisitor.cpp visitors/PrintTreeVisitor.h
        visitors/TemplateBaseVisitor.cpp
        symbol_table/Symbol.cpp
        symbol_table/Table.cpp
        objects/BaseObject.h
        objects/Integer.cpp objects/Integer.h)

add_executable(
        myCompiller
        ${SOURCES}
)

target_include_directories(myCompiller PRIVATE ${myCompille_SOURCE_DIR})
