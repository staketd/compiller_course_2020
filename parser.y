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
    #include <AddExpression.h>
    #include <MulExpression.h>
    #include <DivExpression.h>
    #include <NumExpression.h>
    #include <SubstractExpression.h>
    #include <IdentExpression.h>
    #include <Assignment.h>
    #include <AssignmentList.h>
    #include <Program.h>
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
    ASSIGN ":="
    PLUS "+"
    MINUS "-"
    STAR "*"
    SLASH "/"
    LPAREN "("
    RPAREN ")"
;

%token <std::string> IDENTIFIER "identifier"
%token <int> NUMBER "number"
%nterm <Expression*> expr
%nterm <AssignmentList*> assignments
%nterm <Assignment*> assignment
%nterm <Program*> unit;

%printer {yyo << $$;} <*>;

%%
%start unit;
unit: assignments expr { $$ = new Program($1, $2); driver.program = $$;};

assignments:
    %empty {$$ = new AssignmentList();}
    | assignments assignment {
    	$1->AddAssignment($2);
    	$$ = $1;
    }

assignment:
    "identifier" ":=" expr {
    	$$ = new Assignment($1, $3);
    };

%left "+" "-";
%left "*" "/";

expr:
    "number" 		{$$ = new NumExpression($1);}
    | "identifier" 	{$$ = new IdentExpression($1); }
    | expr "+" expr 	{$$ = new AddExpression($1, $3); }
    | expr "-" expr 	{$$ = new SubstractExpression($1, $3); }
    | expr "*" expr 	{$$ = new MulExpression($1, $3); }
    | expr "/" expr 	{$$ = new DivExpression($1, $3); }
    | "(" expr ")" 	{$$ = $2; };

%%

void
yy::parser::error(const location_type& l, const std::string& m) {
    std::cerr << l << ": " << m << '\n';
}
