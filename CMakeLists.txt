project(myCompiller)

cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 17)

find_package(BISON REQUIRED)
find_package(FLEX REQUIRED)

include_directories(
        driver
        visitors
        symbol_table
        objects
        include
        grammar/expressions
        grammar/statements
        grammar/BaseASTClass
        grammar/scanner
        grammar/
        grammar/classes
        function-calls
        function-calls/address
        class-map
        types
        irtree/generators
        irtree/types
        irtree/visitors
        irtree/tree_wrapper
        irtree/tree_wrapper/conditional_wrappers
        irtree/nodes
        irtree/nodes/expressions
        irtree/nodes/statements
        irtree/
        .
        asm/instructions
        asm/
        support/
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
        grammar/expressions/ThisExpression.cpp
        grammar/expressions/LessExpression.cpp
        grammar/expressions/GreaterExpression.cpp
        grammar/expressions/LessOrEqualExpression.cpp
        grammar/expressions/GreaterOrEqualExpression.cpp
        grammar/expressions/ModuloExpression.cpp
        grammar/expressions/MethodCallExpression.cpp
        grammar/expressions/ArrayExpression.cpp
        grammar/expressions/LogicAndExpression.cpp
        grammar/expressions/LogicOrExpression.cpp

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
        grammar/statements/MethodCallStmt.cpp
        grammar/statements/ArrayDeclaration.cpp
        grammar/statements/ArrayAssignment.cpp

        grammar/classes/Class.cpp
        grammar/classes/ClassField.cpp
        grammar/classes/ClassList.cpp
        grammar/classes/ClassMethod.cpp
        grammar/classes/ClassBody.cpp
        grammar/classes/ClassMain.cpp

        ${BISON_MyParser_OUTPUTS}
        ${FLEX_MyScanner_OUTPUTS}

        include/sources.h
        visitors/BaseVisitors.cpp visitors/BaseVisitors.h
        visitors/TemplateBaseVisitor.cpp
        visitors/BuildSymbolLayerTree.cpp
        visitors/TypeChecker.cpp
        visitors/FunctionCallVisitor.cpp
        visitors/IRTreeBuildVisitor.cpp

        symbol_table/Symbol.cpp

        objects/BaseObject.h
        objects/Integer.cpp objects/Integer.h
        objects/UninitObject.cpp objects/UninitObject.h
        objects/ArrayObject.cpp

        symbol_table/ScopeLayer.cpp
        symbol_table/ScopeLayerTree.cpp
        objects/PrimitiveObject.cpp
        objects/FunctionObject.cpp
        objects/ClassObject.cpp
        objects/BoolObject.cpp objects/BoolObject.h

        include/macros.h
        include/Print.h
        SetLocation.h
        grammar/classes/CallArgumentList.cpp
        grammar/classes/MethodArgumentList.cpp

        function-calls/CallTable.cpp
        function-calls/Frame.cpp
        function-calls/FunctionMap.cpp
        function-calls/address/Address.h
        function-calls/address/FrameAddress.cpp
        function-calls/address/RegAddress.cpp
        function-calls/IRFrameTranslator.cpp

        types/BaseType.cpp
        types/IntegerType.cpp
        types/BoolType.cpp
        types/ClassType.cpp
        types/FunctionType.cpp
        types/VoidType.cpp
        types/TypesSupport.cpp
        types/ArrayType.cpp

        objects/ObjectsSupport.cpp
        grammar/expressions/NewExpression.cpp
        class-map/ClassMap.cpp

        irtree/generators/Label.cpp
        irtree/generators/Temp.cpp
        irtree/nodes/expressions/BinOpExpression.cpp
        irtree/nodes/BaseIRNode.cpp
        irtree/nodes/ExpressionList.cpp
        irtree/types/BinOperatorType.cpp
        irtree/types/LogicOperatorType.cpp
        irtree/nodes/expressions/IRExpression.cpp
        irtree/nodes/expressions/CallExpression.cpp
        irtree/nodes/expressions/ConstExpression.cpp
        irtree/nodes/expressions/EseqExpression.cpp
        irtree/nodes/expressions/MemExpression.cpp
        irtree/nodes/expressions/NameExpression.cpp
        irtree/nodes/expressions/TempExpression.cpp

        irtree/nodes/statements/IRStatement.cpp
        irtree/nodes/statements/ExpStatement.cpp
        irtree/nodes/statements/JumpConditionalStatement.cpp
        irtree/nodes/statements/JumpStatement.cpp
        irtree/nodes/statements/LabelStatement.cpp
        irtree/nodes/statements/MoveStatement.cpp
        irtree/nodes/statements/SeqStatement.cpp
        irtree/nodes/statements/IRPrintStatement.cpp

        irtree/tree_wrapper/SubtreeWrapper.h
        irtree/tree_wrapper/ExpressionWrapper.cpp
        irtree/tree_wrapper/StatementWrapper.cpp
        irtree/tree_wrapper/conditional_wrappers/AndConditionalWrapper.cpp
        irtree/tree_wrapper/conditional_wrappers/ConditionalWrapper.cpp
        irtree/tree_wrapper/conditional_wrappers/NegateConditionalWrapper.cpp
        irtree/tree_wrapper/conditional_wrappers/OrConditionalWrapper.cpp
        irtree/tree_wrapper/conditional_wrappers/CompareConditionalWrapper.cpp

        irtree/visitors/IRPrintVisitor.cpp
        irtree/visitors/IRUnion.h
        irtree/visitors/EliminateDoubleCalls.cpp
        irtree/visitors/EliminateEseq.cpp
        irtree/visitors/LinearizeIRTree.cpp
        irtree/visitors/AsmGenerator.cpp

        asm/instructions/AsmInstruction.cpp
        asm/instructions/MovInstruction.cpp
        asm/instructions/AddInstruction.cpp
        asm/instructions/SubInstruction.cpp
        asm/instructions/CallInstruction.cpp
        asm/instructions/IDivInstruction.cpp
        asm/instructions/JumpInstruction.cpp
        asm/instructions/PopInstruction.cpp
        asm/instructions/PushInstruction.cpp
        asm/instructions/IMulInstruction.cpp
        asm/instructions/LabelInstruction.cpp
        asm/instructions/OrInstruction.cpp
        asm/instructions/AndInstruction.cpp
        asm/instructions/CmpInstruction.cpp
        asm/instructions/RetInstruction.cpp
        asm/Instructions.h
        irtree/Block.cpp
        irtree/Trace.cpp
        support/ElementSet.cpp
)

add_executable(
        myCompiller
        ${SOURCES}
)

target_include_directories(myCompiller PRIVATE ${myCompille_SOURCE_DIR})
