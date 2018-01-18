%{

#include "tool.h"
#include "util.h"
#include "absyn.h"
#include <stdlib.h>

#include "y.tab.h"

%}

%x COMMENTS

string_line	[\]a-zA-Z0-9~`!@#$%^&*()_+=|{}\[,./<>?;': -]|\\\\|\\\"|\\n|\\t|\t|(\\^(@|[A-Z]|\[|\\\\|\]|^|_))|\\(0[0-9]{2}|11[0-9]|12[0-7])

%%

while		{ pos(_NOT_NEW_LINE, yyleng);	 return WHILE; }
for			{ pos(_NOT_NEW_LINE, yyleng);	 return FOR; }
to			{ pos(_NOT_NEW_LINE, yyleng);	 return TO; }
break		{ pos(_NOT_NEW_LINE, yyleng);	 return BREAK; }
let			{ pos(_NOT_NEW_LINE, yyleng);	 return LET; }
in			{ pos(_NOT_NEW_LINE, yyleng);	 return IN; }
end			{ pos(_NOT_NEW_LINE, yyleng);	 return END; }
function	{ pos(_NOT_NEW_LINE, yyleng);  return FUNCTION; }
var			{ pos(_NOT_NEW_LINE, yyleng);  return VAR; }
type		{ pos(_NOT_NEW_LINE, yyleng);  return TYPE; }
array		{ pos(_NOT_NEW_LINE, yyleng);  return ARRAY; }
if			{ pos(_NOT_NEW_LINE, yyleng);  return IF; }
then		{ pos(_NOT_NEW_LINE, yyleng);  return THEN; }
else		{ pos(_NOT_NEW_LINE, yyleng);  return ELSE; }
do			{ pos(_NOT_NEW_LINE, yyleng);  return DO; }
of			{ pos(_NOT_NEW_LINE, yyleng);  return OF; }
nil			{ pos(_NOT_NEW_LINE, yyleng);  return NIL; }

","			{ pos(_NOT_NEW_LINE, yyleng);  return COMMA; }
":"			{ pos(_NOT_NEW_LINE, yyleng);  return COLON; }
";"			{ pos(_NOT_NEW_LINE, yyleng);  return SEMICOLON; }
"("			{ pos(_NOT_NEW_LINE, yyleng);  return LPAREN; }
")"			{ pos(_NOT_NEW_LINE, yyleng);  return RPAREN; }
"["			{ pos(_NOT_NEW_LINE, yyleng);  return LBRACK; }
"]"			{ pos(_NOT_NEW_LINE, yyleng);  return RBRACK; }
"{"			{ pos(_NOT_NEW_LINE, yyleng);  return LBRACE; }
"}"			{ pos(_NOT_NEW_LINE, yyleng);  return RBRACE; }
"."			{ pos(_NOT_NEW_LINE, yyleng);  return DOT; }
"+"			{ pos(_NOT_NEW_LINE, yyleng);  return PLUS; }
"-"			{ pos(_NOT_NEW_LINE, yyleng);  return MINUS; }
"*"			{ pos(_NOT_NEW_LINE, yyleng);  return TIMES; }
"/"			{ pos(_NOT_NEW_LINE, yyleng);  return DIVIDE; }
"="			{ pos(_NOT_NEW_LINE, yyleng);  return EQ; }
"<>"		{ pos(_NOT_NEW_LINE, yyleng);  return NEQ; }
"<"			{ pos(_NOT_NEW_LINE, yyleng);  return LT; }
"<="		{ pos(_NOT_NEW_LINE, yyleng);  return LE; }
">"			{ pos(_NOT_NEW_LINE, yyleng);  return GT; }
">="		{ pos(_NOT_NEW_LINE, yyleng);  return GE; }
"&"			{ pos(_NOT_NEW_LINE, yyleng);  return AND; }
"|"			{ pos(_NOT_NEW_LINE, yyleng);  return OR; }
":="		{ pos(_NOT_NEW_LINE, yyleng);  return ASSIGN; }

[a-zA-Z][a-zA-Z0-9_]*	{ pos(_NOT_NEW_LINE, yyleng); yylval.string_t = String(yytext);  return ID; }
[0-9]+					{ pos(_NOT_NEW_LINE, yyleng); yylval.int_t = atoi(yytext);    return NUM; }

\"({string_line}|\\[\t ]*\n[\t ]*\\)*\"	{ 
	pos(_NOT_NEW_LINE, yyleng); yylval.string_t = String(yytext);  return STR;
}

"/*"                   	{ BEGIN(COMMENTS); }
<COMMENTS>"*/"			{ BEGIN(INITIAL); }
<COMMENTS>\n           { pos(_IS_NEW_LINE, yyleng); } 
<COMMENTS>.            { pos(_NOT_NEW_LINE, yyleng); }

[ \t\f]			{ pos(_NOT_NEW_LINE, yyleng); }
\n	       		{ pos(_IS_NEW_LINE, yyleng); }
.				{ pos(_NOT_NEW_LINE, yyleng); myerror("The lexer encounters an error!\n"); }

%%