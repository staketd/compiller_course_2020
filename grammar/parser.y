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
    INTEGER "Integer"
    BOOL "Bool"
    RETURN "return"
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
%nterm <FunctionList*> Functions
%nterm <std::string> type
%nterm <FuncArgumentList*> Arguments
%nterm <FuncArgumentList*> empty_arguments
%nterm <FuncArgumentList*> complex_arguments
%nterm <CallArgumentList*> call_arguments
%nterm <FuncCallExpression*> func_call
%nterm <CallArgumentList*> empty_call_arguments
%nterm <CallArgumentList*> complex_call_arguments
%nterm <Function*> function
%nterm <FuncCallStatement*> st_func_call

%printer {yyo << $$;} <*>;

%%
%start unit;
unit: Functions { $$ = new Program($1); driver.program = $$;};

Functions:
	%empty {$$ = new FunctionList();}
	| Functions function {
		$1->AddFunction($2);
		$$ = $1;
	}
	;

function:
	type "identifier" "(" Arguments ")" "{" statements "}" {$$ = new Function($2, $4, $7, $1);}
	;

type:
	"Integer" {$$ = "Integer";}
	| "Bool" {$$ = "Bool";}
	;

Arguments:
	empty_arguments {$$ = $1;}
	| complex_arguments {$$ = $1;}
	;

empty_arguments:
	%empty {$$ = new FuncArgumentList();}
	;

complex_arguments:
	"identifier" {
		$$ = new FuncArgumentList();
		$$->AddArgument($1);
	}
	| complex_arguments "," "identifier" {$1->AddArgument($3), $$ = $1;}
	;

statements:
    %empty {$$ = new StatementList();}
    | statements statement {
    	$1->AddStatement($2);
    	$$ = $1;
    };

statement:
	assignment ";" {$$ = $1;}
	| printStatement ";" {$$ = $1;}
	| readStatement ";" {$$ = $1;}
	| IfStatement {$$ = $1;}
	| Scope {$$ = $1;}
	| VariableDeclaration ";" {$$ = $1;}
	| While {$$ = $1;}
	| st_func_call ";" {$$ = $1;}
	| "return" expr ";" {$$ = new ReturnStatement($2);}
	;

st_func_call:
	func_call {$$ = new FuncCallStatement($1);}
	;

While:
	"while" "(" expr ")" Scope {$$ = new WhileStatement($3, $5);}
	;

VariableDeclaration:
	type "identifier" {$$ = new VariableDeclaration($2, $1);}
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
    };

%left "<" ">" "==" "<=" ">=";
%left "+" "-";
%left "*" "/" "%";

expr:
    "number" 			{$$ = new NumExpression($1);}
    | "identifier" 		{$$ = new IdentExpression($1); }
    | expr "+" expr 	{$$ = new AddExpression($1, $3); }
    | expr "-" expr 	{$$ = new SubstractExpression($1, $3); }
    | expr "*" expr 	{$$ = new MulExpression($1, $3); }
    | expr "/" expr 	{$$ = new DivExpression($1, $3); }
    | expr "<" expr		{$$ = new LessExpression($1, $3);}
    | expr ">" expr		{$$ = new GreaterExpression($1, $3);}
    | expr "==" expr	{$$ = new EqualExpression($1, $3);}
    | expr ">=" expr	{$$ = new GreaterOrEqualExpression($1, $3);}
    | expr "<=" expr	{$$ = new LessOrEqualExpression($1, $3);}
    | expr "%" expr 	{$$ = new ModuloExpression($1, $3);}
    | "(" expr ")" 	{$$ = $2; }
    | func_call {$$ = $1;}
    ;

func_call:
	"identifier" "(" call_arguments ")" {$$ = new FuncCallExpression($1, $3);}

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
