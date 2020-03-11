project(myCompiller)

cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 17)

find_package(BISON REQUIRED)
find_package(FLEX REQUIRED)

include_directories(
        scanner
        driver
        expressions
        assignments
        BaseClass
        visitors
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

add_executable(
        myCompiller
        main.cpp
        driver/driver.cpp
        expressions/AddExpression.cpp
        expressions/MulExpression.cpp
        expressions/DivExpression.cpp
        expressions/SubstractExpression.cpp
        expressions/NumExpression.cpp
        expressions/IdentExpression.cpp
        assignments/Assignment.cpp
        ${BISON_MyParser_OUTPUTS}
        ${FLEX_MyScanner_OUTPUTS}
        assignments/AssignmentList.cpp
        assignments/AssignmentList.h
        expressions/Expression.h
        Program.cpp Program.h
        visitors/BaseVisitor.cpp visitors/BaseVisitor.h
        BaseClass/BaseClass.cpp BaseClass/BaseClass.h visitors/Interprenter.cpp visitors/Interprenter.h visitors/PrintTreeVisitor.cpp visitors/PrintTreeVisitor.h)

target_include_directories(myCompiller PRIVATE ${myCompille_SOURCE_DIR})
