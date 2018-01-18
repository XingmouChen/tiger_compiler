%{
#define YYDEBUG 1
#include "tool.h"
#include "util.h"
#include "absyn.h"
#include <stdio.h>
#include <stdlib.h>

#include "y.tab.h"

/* Defined in lex */
extern FILE* yyin;
extern char* yytext;
extern int yylex();

/* Defined in tool.c */
extern int global_line_num;
extern int global_column_num;
extern int global_pos;

%}

/* Self-defined types */
%union	{
	int 			int_t;
	string 			string_t;
	A_exp 			exp_t;
	A_var 			var_t;
	A_expList 		expList_t;
	A_efieldList 	efieldList_t;
	A_efield 		efield_t;
	A_decList 		decList_t;
	A_dec 			dec_t;
	A_nametyList 	nametyList_t;
	A_namety 		namety_t;
	A_ty 			ty_t;
	A_fieldList 	fieldList_t;
	A_field 		field_t;
	A_fundecList 	fundecList_t;
	A_fundec 		fundec_t;
}


/* Token Type */
%token	<int_t>		NUM
%token	<string_t>		ID STR
%token 	COMMA COLON SEMICOLON LPAREN RPAREN LBRACK RBRACK LBRACE RBRACE
%token  DOT PLUS MINUS TIMES DIVIDE EQ NEQ LT LE GT GE AND OR ASSIGN
%token 	ARRAY IF THEN ELSE WHILE FOR TO DO LET IN END OF BREAK NIL
%token 	FUNCTION VAR TYPE STRING INT COMMENT UMINUS

/* Precedence */
%right FUNCTION TYPE
%right OF
%right DO ELSE THEN
%nonassoc ASSIGN
%left OR
%left AND
%nonassoc EQ NEQ LT LE GT GE
%left PLUS MINUS
%left TIMES DIVIDE
%left UMINUS
%left LPAREN

/* Non-terminals' types */
%type 	<exp_t> expr program
%type 	<var_t> lvalue
%type 	<expList_t> exprlist exprseqlist
%type 	<efieldList_t> fieldlist
%type 	<efield_t> exprfield
%type 	<decList_t> declarationlist
%type 	<dec_t> declaration variabledeclaration
%type 	<nametyList_t> typedeclist
%type 	<namety_t>	typedeclaration
%type 	<ty_t> type
%type 	<fieldList_t> typefields
%type 	<field_t> typefield
%type 	<fundecList_t> functiondeclist
%type 	<fundec_t> functiondeclaration

%start	program

%%

program	:	expr { absyn_root = $1;  }
		;

expr 	:	MINUS expr %prec UMINUS
			{ 
				$$ = A_OpExp(global_pos, A_minusOp, A_IntExp(global_pos, 0), $2);
			}

		|	NUM { $$ = A_IntExp(global_pos, $1); }
		|	STR { $$ = A_StringExp(global_pos, $1); }
		|	NIL { $$ = A_NilExp(global_pos); }

		|	lvalue { $$ = A_VarExp(global_pos, $1); }

		|	expr PLUS expr { $$ = A_OpExp(global_pos, A_plusOp, $1, $3); }
		|	expr MINUS expr { $$ = A_OpExp(global_pos, A_minusOp, $1, $3); }
		|	expr TIMES expr { $$ = A_OpExp(global_pos, A_timesOp, $1, $3); }
		|	expr DIVIDE expr { $$ = A_OpExp(global_pos, A_divideOp, $1, $3); }

		|	expr OR expr { $$ = A_IfExp(global_pos, $1, A_IntExp(global_pos, 1), $3); }
		|	expr AND expr { $$ = A_IfExp(global_pos, $1, $3, A_IntExp(global_pos, 0)); }

		|	expr EQ expr { $$ = A_OpExp(global_pos, A_eqOp, $1, $3); }
		|	expr LT expr { $$ = A_OpExp(global_pos, A_ltOp, $1, $3); }
		|	expr LE expr { $$ = A_OpExp(global_pos, A_leOp, $1, $3); }
		|	expr GT expr { $$ = A_OpExp(global_pos, A_gtOp, $1, $3); }
		|	expr GE expr { $$ = A_OpExp(global_pos, A_geOp, $1, $3); }
		|	expr NEQ expr { $$ = A_OpExp(global_pos, A_neqOp, $1, $3); }

		|	lvalue ASSIGN expr { $$ = A_AssignExp(global_pos, $1, $3); }

		|	ID LPAREN exprlist RPAREN 
			{ 
				$$ = A_CallExp(global_pos, S_Symbol($1), $3);
			}
		|	ID LPAREN RPAREN
			{
				$$ = A_CallExp(global_pos, S_Symbol($1), NULL);
			}

		|	LPAREN exprseqlist RPAREN
			{
				$$ = A_SeqExp(global_pos, $2);
			}
		|	LPAREN RPAREN
			{
				$$ = A_SeqExp(global_pos, NULL);
			}

		|	ID LBRACE fieldlist RBRACE
			{
				$$ = A_RecordExp(global_pos, S_Symbol($1), $3);
			}
		|	ID LBRACE RBRACE
			{
				$$ = A_RecordExp(global_pos, S_Symbol($1), NULL);
			}

		|	ID LBRACK expr RBRACK OF expr
			{
				$$ = A_ArrayExp(global_pos, S_Symbol($1), $3, $6);
			}

		|	IF expr THEN expr
			{
				$$ = A_IfExp(global_pos, $2, $4, NULL);
			}
		|	IF expr THEN expr ELSE expr
			{
				$$ = A_IfExp(global_pos, $2, $4, $6);
			}

		|	WHILE expr DO expr
			{
				$$ = A_WhileExp(global_pos, $2, $4);
			}

		|	FOR ID ASSIGN expr TO expr DO expr
			{
				$$ = A_ForExp(global_pos, S_Symbol($2), $4, $6, $8);
			}

		|	BREAK { $$ = A_BreakExp(global_pos); }

		|	LET declarationlist IN END
			{
				$$ = A_LetExp(global_pos, $2, NULL);
			}
		|	LET declarationlist IN exprseqlist END
			{
				$$ = A_LetExp(global_pos, $2, A_SeqExp(global_pos, $4));
			}
		;

lvalue	:	lvalue LBRACK expr RBRACK
			{
				$$ = A_SubscriptVar(global_pos, $1, $3);
			}
			/* ??? why ??? */
		|	ID LBRACK expr RBRACK
			{
				$$ = A_SubscriptVar(global_pos, A_SimpleVar(global_pos, S_Symbol($1)), $3);
			}
		|	lvalue DOT ID
			{
				$$ = A_FieldVar(global_pos, $1, S_Symbol($3));
			}
		|	ID
			{
				$$ = A_SimpleVar(global_pos, S_Symbol($1));
			}
		;

exprlist:	expr
			{
				$$ = A_ExpList($1, NULL);
			}
		|	expr COMMA exprlist
			{
				$$ = A_ExpList($1, $3);
			}
		;

exprseqlist	:	expr
				{
					$$ = A_ExpList($1, NULL);
				}
			|	expr SEMICOLON exprseqlist
				{
					$$ = A_ExpList($1, $3);
				}
			;

fieldlist:	exprfield
			{
				$$ = A_EfieldList($1, NULL);
			}
		|	exprfield COMMA fieldlist
			{
				$$ = A_EfieldList($1, $3);
			}
		;

exprfield:	ID EQ expr
			{
				$$ = A_Efield(S_Symbol($1), $3);
			}
		;

declarationlist	:	declaration
					{
						$$ = A_DecList($1, NULL);
					}
				|	declaration declarationlist
					{
						$$ = A_DecList($1, $2);
					}
				;

declaration	:	typedeclist
				{
					$$ = A_TypeDec(global_pos, $1);
				}
			|	functiondeclist
				{
					$$ = A_FunctionDec(global_pos, $1);
				}
			|	variabledeclaration
				{
					$$ = $1;
				}
			;

typedeclist	:	typedeclaration
				{
					$$ = A_NametyList($1, NULL);
				}
			|	typedeclaration typedeclist
				{
					$$ = A_NametyList($1, $2);
				}
			;

typedeclaration	:	TYPE ID EQ type
					{
						$$ = A_Namety(S_Symbol($2), $4);
					}
				;

type 	:	ID
			{
				$$ = A_NameTy(global_pos, S_Symbol($1));
			}
		|	LBRACE typefields RBRACE
			{
				$$ = A_RecordTy(global_pos, $2);
			}
		|	LBRACE RBRACE
			{
				$$ = A_RecordTy(global_pos, NULL);
			}
		|
			ARRAY OF ID
			{
				$$ = A_ArrayTy(global_pos, S_Symbol($3));
			}
		;

typefields 	:	typefield
				{
					$$ = A_FieldList($1, NULL);
				}
			|	typefield COMMA typefields
				{
					$$ = A_FieldList($1, $3);
				}
			;

typefield 	:	ID COLON ID
				{
					$$ = A_Field(global_pos, S_Symbol($1), S_Symbol($3));
				}
			;

functiondeclist	:	functiondeclaration
					{
						$$ = A_FundecList($1, NULL);
					}
				|	functiondeclaration functiondeclist
					{
						$$ = A_FundecList($1, $2);
					}
				;

functiondeclaration :	FUNCTION ID LPAREN RPAREN EQ expr
						{
							$$ = A_Fundec(global_pos, S_Symbol($2), NULL, NULL, $6);
						}
					|	FUNCTION ID LPAREN typefields RPAREN EQ expr
						{
							$$ = A_Fundec(global_pos, S_Symbol($2), $4, NULL, $7);
						}
					|	FUNCTION ID LPAREN RPAREN COLON ID EQ expr
						{
							$$ = A_Fundec(global_pos, S_Symbol($2), NULL, S_Symbol($6), $8);
						}
					|	FUNCTION ID LPAREN typefields RPAREN COLON ID EQ expr
						{
							$$ = A_Fundec(global_pos, S_Symbol($2), $4, S_Symbol($7), $9);
						}
					;

variabledeclaration	:	VAR ID ASSIGN expr
						{
							$$ = A_VarDec(global_pos, S_Symbol($2), NULL, $4);
						}
					|	VAR ID COLON ID ASSIGN expr
						{
							$$ = A_VarDec(global_pos, S_Symbol($2), S_Symbol($4), $6);
						}

%%

void yyerror() {
	printf("####! yyerror()!\n");
}

int yywrap() {
	return 1;
}
