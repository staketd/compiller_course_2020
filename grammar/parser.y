
%skeleton "lalr1.cc"
%require "3.5"

%defines
%define api.token.constructor
%define api.value.type variant
%define parse.assert

%code requires {
    #include <string>
    class Scanner;
    class Driver;
    #include <sources.h>
    #include <SetLocation.h>
}

%define parse.trace
%define parse.error verbose

%code {
    #include <driver.h>
    #include <location.hh>

    static yy::parser::symbol_type yylex(Scanner& scanner, Driver& driver) {
        return scanner.ScanToken();
    }
}

%lex-param { Scanner& scanner }
%lex-param { Driver& driver }
%parse-param { Scanner& scanner }
%parse-param { Driver& driver }

%locations

%define api.token.prefix {TOK_}

%token
    END 0 "end of file"
    ASSIGN "="
    PLUS "+"
    MINUS "-"
    STAR "*"
    SLASH "/"
    LPAREN "("
    RPAREN ")"
    SLPAREN "["
    SRPAREN "]"
    PRINT "print"
    READ "read"
    LESS "<"
    GREATER ">"
    LE "<="
    GE ">="
    EQUAL "=="
    IF "if"
    LEFTSCOPE "{"
    RIGHTSCOPE "}"
    ELSE "else"
    VAR "var"
    SEMICOLON ";"
    MODULO "%"
    WHILE "while"
    COMMA ","
    RETURN "return"
    CLASS "class"
    THIS "this"
    DOT "."
    PUBLIC "public"
    STATIC "static"
    VOID "void"
    MAIN "main"
    NEW "new"
;

%token <std::string> IDENTIFIER "identifier"
%token <int> NUMBER "number"
%nterm <Expression*> expr
%nterm <StatementList*> statements
%nterm <Assignment*> assignment
%nterm <Statement*> statement
%nterm <Program*> unit;
%nterm <PrintStatement*> printStatement
%nterm <ReadStatement*> readStatement
%nterm <IfStatement*> IfStatement
%nterm <Scope*> Scope
%nterm <VariableDeclaration*> VariableDeclaration
%nterm <WhileStatement*> While
%nterm <std::string> type
%nterm <MethodArgumentList*> Arguments
%nterm <MethodArgumentList*> empty_arguments
%nterm <MethodArgumentList*> complex_arguments
%nterm <CallArgumentList*> call_arguments
%nterm <CallArgumentList*> empty_call_arguments
%nterm <CallArgumentList*> complex_call_arguments
%nterm <Class*> class
%nterm <ClassBody*> class_body
%nterm <ClassField*> class_field
%nterm <ClassMethod*> class_method;
%nterm <MethodCallExpression*> call_method;
%nterm <ClassMain*> main_class
%nterm <ClassList*> classes
%nterm <ReturnStatement*> returnStatement
%nterm <ArrayAssignment*> array_assignment
%nterm <ArrayDeclaration*> ArrayDeclaration

%printer {yyo << $$;} <*>;

%%
%start unit;
unit:  main_class classes { $$ = new Program($1, $2); driver.program = $$;};

main_class:
	"class" "identifier" "{" "public" "static" "void" "main" "(" ")" "{" statements "}" "}" {
		$$ = new ClassMain($2, new ClassMethod("main", new MethodArgumentList(), $11, "void"));
		SetLocation($$, @1);
	}
	;

classes:
	%empty {$$ = new ClassList();}
	| classes class {$1->AddClass($2); $$ = $1;}
	;

class:
	"class" "identifier" "{" class_body "}" {$$ = new Class($2, $4); SetLocation($$, @1);}
	;

class_body:
	%empty {$$ = new ClassBody();}
	| class_body class_field {$1->AddField($2); $$ = $1;}
	| class_body class_method {$1->AddMethod($2); $$ = $1;}
	;

class_field:
	type "identifier" ";" {$$ = new ClassField($1, $2); SetLocation($$, @1);}
	;

class_method:
	type "identifier" "(" Arguments ")" "{" statements "}" {$$ = new ClassMethod($2, $4, $7, $1); SetLocation($$, @1);}
	| "void" "identifier" "(" Arguments ")" "{" statements "}" {$$ = new ClassMethod($2, $4, $7, "void");}
	;

type:
	"identifier" {$$ = $1;}

Arguments:
	empty_arguments {$$ = $1;}
	| complex_arguments {$$ = $1;}
	;

empty_arguments:
	%empty {$$ = new MethodArgumentList();}
	;

complex_arguments:
	type "identifier" {
		$$ = new MethodArgumentList();
		$$->AddArgument($1, $2);
		SetLocation($$, @1);
	}
	| complex_arguments "," type "identifier" {
		$1->AddArgument($3, $4), $$ = $1;
		SetLocation($$, @1);
	}
	;

statements:
    %empty {$$ = new StatementList();}
    | statements statement {
    	$1->AddStatement($2);
    	$$ = $1;
	}
	;

statement:
	assignment ";" {$$ = $1; SetLocation($$, @1);}
	| printStatement ";" {$$ = $1; SetLocation($$, @1);}
	| readStatement ";" {$$ = $1; SetLocation($$, @1);}
	| IfStatement {$$ = $1; SetLocation($$, @1);}
	| Scope {$$ = $1; SetLocation($$, @1);}
	| VariableDeclaration ";" {$$ = $1; SetLocation($$, @1);}
	| While {$$ = $1; SetLocation($$, @1);}
	| returnStatement ";" {$$ = $1; SetLocation($$, @1);}
	| call_method ";" {$$ = new MethodCallStmt($1); SetLocation($$, @1);}
	| array_assignment ";" {$$ = $1; SetLocation($$, @1);}
	| ArrayDeclaration ";" {$$ = $1; SetLocation($$, @1);}
	;

returnStatement:
	"return" expr {$$ = new ReturnStatement($2);}
	| "return" {$$ = new ReturnStatement(nullptr);}
	;

While:
	"while" "(" expr ")" Scope {$$ = new WhileStatement($3, $5);}
	;

VariableDeclaration:
	type "identifier" "=" expr {$$ = new VariableDeclaration($2, $1, $4);}
	;

ArrayDeclaration:
	type "identifier" "[" "number" "]" {$$ = new ArrayDeclaration($1, $2, $4);}
	;

Scope:
	"{" statements "}" {$$ = new Scope($2);}
	;

IfStatement:
	"if" "(" expr ")" Scope {$$ = new IfStatement($3, $5, nullptr);}
	| "if" "(" expr ")" Scope "else" Scope {$$ = new IfStatement($3, $5, $7);}
	;

printStatement:
	"print" "(" expr ")" {$$ = new PrintStatement($3);}
	;

readStatement:
	"read" "(" "identifier" ")" {$$ = new ReadStatement($3);}
	;

assignment:
    "identifier" "=" expr {
    	$$ = new Assignment($1, $3);
    }
    ;

array_assignment:
    "identifier" "[" expr "]" "=" expr {
    	$$ = new ArrayAssignment($1, $3, $6);
    }
    ;

%left "<" ">" "==" "<=" ">=";
%left "+" "-";
%left "*" "/" "%";

call_method:
	expr "." "identifier" "(" call_arguments ")" {$$ = new MethodCallExpression($1, $3, $5);}

expr:
    "number" 			{$$ = new NumExpression($1);  SetLocation($$, @1);}
    | "identifier" 		{$$ = new IdentExpression($1); SetLocation($$, @1);}
    | expr "+" expr 	{$$ = new AddExpression($1, $3); SetLocation($$, @1);}
    | expr "-" expr 	{$$ = new SubstractExpression($1, $3); SetLocation($$, @1);}
    | expr "*" expr 	{$$ = new MulExpression($1, $3); SetLocation($$, @1);}
    | expr "/" expr 	{$$ = new DivExpression($1, $3); SetLocation($$, @1);}
    | expr "<" expr		{$$ = new LessExpression($1, $3); SetLocation($$, @1);}
    | expr ">" expr		{$$ = new GreaterExpression($1, $3); SetLocation($$, @1);}
    | expr "==" expr	{$$ = new EqualExpression($1, $3); SetLocation($$, @1);}
    | expr ">=" expr	{$$ = new GreaterOrEqualExpression($1, $3); SetLocation($$, @1);}
    | expr "<=" expr	{$$ = new LessOrEqualExpression($1, $3); SetLocation($$, @1);}
    | expr "%" expr 	{$$ = new ModuloExpression($1, $3); SetLocation($$, @1);}
    | "(" expr ")" 	{$$ = $2;  SetLocation($$, @2);}
    | call_method {$$ = $1; SetLocation($$, @1);}
    | "this" {$$ = new ThisExpression(); SetLocation($$, @1);}
    | "new" "identifier" "(" ")" {$$ = new NewExpression($2); SetLocation($$, @1);}
    | "identifier" "[" expr "]" {$$ = new ArrayExpression($1, $3); SetLocation($$, @1);}
    ;

call_arguments:
	empty_call_arguments {$$ = $1;}
	| complex_call_arguments {$$ = $1;}
	;

empty_call_arguments:
	%empty {$$ = new CallArgumentList();}
	;

complex_call_arguments:
	expr {
		$$ = new CallArgumentList();
		$$->AddArgument($1);
	}
	| complex_call_arguments "," expr {
		$1->AddArgument($3);
		$$ = $1;
	}
%%

void
yy::parser::error(const location_type& l, const std::string& m) {
    std::cerr << l << ": " << m << '\n';
}
