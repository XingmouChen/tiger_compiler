/* A Bison parser, made by GNU Bison 2.7.  */

/* Bison interface for Yacc-like parsers in C
   
      Copyright (C) 1984, 1989-1990, 2000-2012 Free Software Foundation, Inc.
   
   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.
   
   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

#ifndef YY_YY_SRC_Y_TAB_H_INCLUDED
# define YY_YY_SRC_Y_TAB_H_INCLUDED
/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     NUM = 258,
     ID = 259,
     STR = 260,
     COMMA = 261,
     COLON = 262,
     SEMICOLON = 263,
     LPAREN = 264,
     RPAREN = 265,
     LBRACK = 266,
     RBRACK = 267,
     LBRACE = 268,
     RBRACE = 269,
     DOT = 270,
     PLUS = 271,
     MINUS = 272,
     TIMES = 273,
     DIVIDE = 274,
     EQ = 275,
     NEQ = 276,
     LT = 277,
     LE = 278,
     GT = 279,
     GE = 280,
     AND = 281,
     OR = 282,
     ASSIGN = 283,
     ARRAY = 284,
     IF = 285,
     THEN = 286,
     ELSE = 287,
     WHILE = 288,
     FOR = 289,
     TO = 290,
     DO = 291,
     LET = 292,
     IN = 293,
     END = 294,
     OF = 295,
     BREAK = 296,
     NIL = 297,
     FUNCTION = 298,
     VAR = 299,
     TYPE = 300,
     STRING = 301,
     INT = 302,
     COMMENT = 303,
     UMINUS = 304
   };
#endif
/* Tokens.  */
#define NUM 258
#define ID 259
#define STR 260
#define COMMA 261
#define COLON 262
#define SEMICOLON 263
#define LPAREN 264
#define RPAREN 265
#define LBRACK 266
#define RBRACK 267
#define LBRACE 268
#define RBRACE 269
#define DOT 270
#define PLUS 271
#define MINUS 272
#define TIMES 273
#define DIVIDE 274
#define EQ 275
#define NEQ 276
#define LT 277
#define LE 278
#define GT 279
#define GE 280
#define AND 281
#define OR 282
#define ASSIGN 283
#define ARRAY 284
#define IF 285
#define THEN 286
#define ELSE 287
#define WHILE 288
#define FOR 289
#define TO 290
#define DO 291
#define LET 292
#define IN 293
#define END 294
#define OF 295
#define BREAK 296
#define NIL 297
#define FUNCTION 298
#define VAR 299
#define TYPE 300
#define STRING 301
#define INT 302
#define COMMENT 303
#define UMINUS 304



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{
/* Line 2058 of yacc.c  */
#line 24 "src/tiger.y"

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


/* Line 2058 of yacc.c  */
#line 175 "src/y.tab.h"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;

#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */

#endif /* !YY_YY_SRC_Y_TAB_H_INCLUDED  */
