%{
    #include <cerrno>
    #include <climits>
    #include <cstdlib>
    #include <cstring> // strerror
    #include <string>
    #include <iostream>
    #include <driver.h>
    #include "parser.hh"
%}

%option noyywrap nounput noinput batch debug

%option c++
%option yyclass="Scanner"

%{
  // A number symbol corresponding to the value in S.
  yy::parser::symbol_type make_NUMBER(
    const std::string &s,
    const yy::parser::location_type& loc
  );
%}

id    [a-zA-Z][a-zA-Z_0-9]*
int   [0-9]+
blank [ \t\r]

%{
  # define YY_USER_ACTION  loc.columns (yyleng);
%}
%%

%{
  yy::location& loc = driver.location;
  loc.step();
%}

{blank}+    loc.step ();
\n+         loc.lines (yyleng); loc.step ();

"-"         return yy::parser::make_MINUS   (loc);
"+"         return yy::parser::make_PLUS    (loc);
"*"         return yy::parser::make_STAR    (loc);
"/"         return yy::parser::make_SLASH   (loc);
"("         return yy::parser::make_LPAREN  (loc);
")"         return yy::parser::make_RPAREN  (loc);
"="        return yy::parser::make_ASSIGN  (loc);
"print"     return yy::parser::make_PRINT   (loc);
"read"      return yy::parser::make_READ    (loc);
"<"         return yy::parser::make_LESS    (loc);
">"         return yy::parser::make_GREATER (loc);
"=="        return yy::parser::make_EQUAL   (loc);
"<="        return yy::parser::make_LE      (loc);
">="        return yy::parser::make_GE      (loc);
"if"        return yy::parser::make_IF      (loc);
"{"         return yy::parser::make_LEFTSCOPE(loc);
"}"         return yy::parser::make_RIGHTSCOPE(loc);
"else"      return yy::parser::make_ELSE    (loc);
"var"       return yy::parser::make_VAR     (loc);
";"         return yy::parser::make_SEMICOLON(loc);
"%"         return yy::parser::make_MODULO  (loc);
"while"     return yy::parser::make_WHILE   (loc);
","         return yy::parser::make_COMMA(loc);
"Integer"   return yy::parser::make_INTEGER(loc);
"Bool"      return yy::parser::make_BOOL(loc);
"return"    return yy::parser::make_RETURN(loc);

{int}       return make_NUMBER(yytext, loc);
{id}        return yy::parser::make_IDENTIFIER(yytext, loc);
.           {
                throw yy::parser::syntax_error(loc, "invalid character: " + std::string(yytext));
            }
<<EOF>>     return yy::parser::make_END (loc);
%%

yy::parser::symbol_type make_NUMBER(
  const std::string &s,
  const yy::parser::location_type& loc
) {
  errno = 0;
  long n = strtol(s.c_str(), NULL, 10);
  if (! (INT_MIN <= n && n <= INT_MAX && errno != ERANGE))
    throw yy::parser::syntax_error(loc, "integer is out of range: " + s);
  return yy::parser::make_NUMBER((int) n, loc);
}