/* A Bison parser, made by GNU Bison 2.7.  */

/* Bison implementation for Yacc-like parsers in C
   
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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.7"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
/* Line 371 of yacc.c  */
#line 1 "src/tiger.y"

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


/* Line 371 of yacc.c  */
#line 90 "src/y.tab.c"

# ifndef YY_NULL
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULL nullptr
#  else
#   define YY_NULL 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* In a future release of Bison, this section will be replaced
   by #include "y.tab.h".  */
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
/* Line 387 of yacc.c  */
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


/* Line 387 of yacc.c  */
#line 251 "src/y.tab.c"
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

/* Copy the second part of user declarations.  */

/* Line 390 of yacc.c  */
#line 279 "src/y.tab.c"

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(N) (N)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int yyi)
#else
static int
YYID (yyi)
    int yyi;
#endif
{
  return yyi;
}
#endif

#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)				\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack_alloc, Stack, yysize);			\
	Stack = &yyptr->Stack_alloc;					\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (YYID (0))
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  35
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   346

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  50
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  18
/* YYNRULES -- Number of rules.  */
#define YYNRULES  68
/* YYNRULES -- Number of states.  */
#define YYNSTATES  149

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   304

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     5,     8,    10,    12,    14,    16,    20,
      24,    28,    32,    36,    40,    44,    48,    52,    56,    60,
      64,    68,    73,    77,    81,    84,    89,    93,   100,   105,
     112,   117,   126,   128,   133,   139,   144,   149,   153,   155,
     157,   161,   163,   167,   169,   173,   177,   179,   182,   184,
     186,   188,   190,   193,   198,   200,   204,   207,   211,   213,
     217,   221,   223,   226,   233,   241,   250,   260,   265
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      51,     0,    -1,    52,    -1,    17,    52,    -1,     3,    -1,
       5,    -1,    42,    -1,    53,    -1,    52,    16,    52,    -1,
      52,    17,    52,    -1,    52,    18,    52,    -1,    52,    19,
      52,    -1,    52,    27,    52,    -1,    52,    26,    52,    -1,
      52,    20,    52,    -1,    52,    22,    52,    -1,    52,    23,
      52,    -1,    52,    24,    52,    -1,    52,    25,    52,    -1,
      52,    21,    52,    -1,    53,    28,    52,    -1,     4,     9,
      54,    10,    -1,     4,     9,    10,    -1,     9,    55,    10,
      -1,     9,    10,    -1,     4,    13,    56,    14,    -1,     4,
      13,    14,    -1,     4,    11,    52,    12,    40,    52,    -1,
      30,    52,    31,    52,    -1,    30,    52,    31,    52,    32,
      52,    -1,    33,    52,    36,    52,    -1,    34,     4,    28,
      52,    35,    52,    36,    52,    -1,    41,    -1,    37,    58,
      38,    39,    -1,    37,    58,    38,    55,    39,    -1,    53,
      11,    52,    12,    -1,     4,    11,    52,    12,    -1,    53,
      15,     4,    -1,     4,    -1,    52,    -1,    52,     6,    54,
      -1,    52,    -1,    52,     8,    55,    -1,    57,    -1,    57,
       6,    56,    -1,     4,    20,    52,    -1,    59,    -1,    59,
      58,    -1,    60,    -1,    65,    -1,    67,    -1,    61,    -1,
      61,    60,    -1,    45,     4,    20,    62,    -1,     4,    -1,
      13,    63,    14,    -1,    13,    14,    -1,    29,    40,     4,
      -1,    64,    -1,    64,     6,    63,    -1,     4,     7,     4,
      -1,    66,    -1,    66,    65,    -1,    43,     4,     9,    10,
      20,    52,    -1,    43,     4,     9,    63,    10,    20,    52,
      -1,    43,     4,     9,    10,     7,     4,    20,    52,    -1,
      43,     4,     9,    63,    10,     7,     4,    20,    52,    -1,
      44,     4,    28,    52,    -1,    44,     4,     7,     4,    28,
      52,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    85,    85,    88,    93,    94,    95,    97,    99,   100,
     101,   102,   104,   105,   107,   108,   109,   110,   111,   112,
     114,   116,   120,   125,   129,   134,   138,   143,   148,   152,
     157,   162,   167,   169,   173,   179,   184,   188,   192,   198,
     202,   208,   212,   218,   222,   228,   234,   238,   244,   248,
     252,   258,   262,   268,   274,   278,   282,   287,   293,   297,
     303,   309,   313,   319,   323,   327,   331,   337,   341
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "NUM", "ID", "STR", "COMMA", "COLON",
  "SEMICOLON", "LPAREN", "RPAREN", "LBRACK", "RBRACK", "LBRACE", "RBRACE",
  "DOT", "PLUS", "MINUS", "TIMES", "DIVIDE", "EQ", "NEQ", "LT", "LE", "GT",
  "GE", "AND", "OR", "ASSIGN", "ARRAY", "IF", "THEN", "ELSE", "WHILE",
  "FOR", "TO", "DO", "LET", "IN", "END", "OF", "BREAK", "NIL", "FUNCTION",
  "VAR", "TYPE", "STRING", "INT", "COMMENT", "UMINUS", "$accept",
  "program", "expr", "lvalue", "exprlist", "exprseqlist", "fieldlist",
  "exprfield", "declarationlist", "declaration", "typedeclist",
  "typedeclaration", "type", "typefields", "typefield", "functiondeclist",
  "functiondeclaration", "variabledeclaration", YY_NULL
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    50,    51,    52,    52,    52,    52,    52,    52,    52,
      52,    52,    52,    52,    52,    52,    52,    52,    52,    52,
      52,    52,    52,    52,    52,    52,    52,    52,    52,    52,
      52,    52,    52,    52,    52,    53,    53,    53,    53,    54,
      54,    55,    55,    56,    56,    57,    58,    58,    59,    59,
      59,    60,    60,    61,    62,    62,    62,    62,    63,    63,
      64,    65,    65,    66,    66,    66,    66,    67,    67
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     2,     1,     1,     1,     1,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     4,     3,     3,     2,     4,     3,     6,     4,     6,
       4,     8,     1,     4,     5,     4,     4,     3,     1,     1,
       3,     1,     3,     1,     3,     3,     1,     2,     1,     1,
       1,     1,     2,     4,     1,     3,     2,     3,     1,     3,
       3,     1,     2,     6,     7,     8,     9,     4,     6
};

/* YYDEFACT[STATE-NAME] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     4,    38,     5,     0,     0,     0,     0,     0,     0,
      32,     6,     0,     2,     7,     0,     0,     0,    24,    41,
       0,     3,     0,     0,     0,     0,     0,     0,     0,    46,
      48,    51,    49,    61,    50,     1,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    22,    39,     0,     0,     0,    26,     0,    43,     0,
      23,     0,     0,     0,     0,     0,     0,     0,    47,    52,
      62,     8,     9,    10,    11,    14,    19,    15,    16,    17,
      18,    13,    12,     0,    37,    20,     0,    21,    36,     0,
      25,     0,    42,    28,    30,     0,     0,     0,     0,     0,
      33,     0,    35,    40,     0,    45,    44,     0,     0,     0,
       0,     0,    58,     0,    67,    54,     0,     0,    53,    34,
      27,    29,     0,     0,     0,     0,     0,     0,     0,    56,
       0,     0,     0,    60,     0,    63,     0,     0,    59,    68,
      55,    57,    31,     0,     0,    64,    65,     0,    66
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,    12,    19,    14,    53,    20,    57,    58,    28,    29,
      30,    31,   118,   111,   112,    32,    33,    34
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -114
static const yytype_int16 yypact[] =
{
     147,  -114,    20,  -114,    50,   147,   147,   147,    26,    21,
    -114,  -114,    25,   288,    -7,   112,   147,    13,  -114,   195,
      22,  -114,   244,   149,    23,    45,    48,    53,    18,    21,
    -114,    36,  -114,    39,  -114,  -114,   147,   147,   147,   147,
     147,   147,   147,   147,   147,   147,   147,   147,   147,    81,
     147,  -114,    52,    78,   260,    70,  -114,    79,    88,   147,
    -114,   147,   147,   147,    86,    -5,    76,    97,  -114,  -114,
    -114,    16,    16,  -114,  -114,   311,   311,   311,   311,   311,
     311,   321,   300,   276,  -114,   288,   147,  -114,    57,   147,
    -114,    95,  -114,   227,   288,   207,     9,    99,   147,    -3,
    -114,    66,  -114,  -114,   147,   288,  -114,   147,   147,   102,
       2,   100,   105,    84,   288,  -114,    14,    73,  -114,  -114,
     288,   288,   174,   114,   115,   147,     4,   116,   147,  -114,
     109,   120,   147,  -114,   106,   288,   129,   147,  -114,   288,
    -114,  -114,   288,   147,   121,   288,   288,   147,   288
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
    -114,  -114,     0,  -114,    49,   -47,    64,  -114,   111,  -114,
     113,  -114,  -114,  -113,  -114,   124,  -114,  -114
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const yytype_int16 yytable[] =
{
      13,   115,    97,   130,    48,    21,    22,    23,    49,   124,
     116,   136,    92,   109,   138,    52,    54,    55,   109,   110,
     101,    50,   125,    98,   137,    35,   117,    56,   129,    15,
      24,    16,    60,    17,    38,    39,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    64,
      85,    63,    65,     1,     2,     3,    67,    66,    86,     4,
      18,    93,    94,    95,    25,    26,    27,     5,    36,    37,
      38,    39,    40,    41,    42,    43,    44,    45,    46,    47,
       6,    27,    25,     7,     8,    84,    52,     9,    87,   105,
      89,    10,    11,    90,    91,    96,    99,   104,   114,    55,
       1,     2,     3,   113,   120,   119,     4,   121,   122,   123,
     126,   127,   128,   131,     5,     1,     2,     3,   133,   134,
     109,     4,    51,   140,   141,   135,   143,     6,   139,     5,
       7,     8,   142,   144,     9,   103,   100,   145,    10,    11,
      68,   147,     6,   146,    69,     7,     8,   148,     0,     9,
       1,     2,     3,    10,    11,   106,     4,    70,     0,     0,
       0,     0,     0,     0,     5,    36,    37,    38,    39,    40,
      41,    42,    43,    44,    45,    46,    47,     6,     0,     0,
       7,     8,     0,     0,     9,    62,     0,     0,    10,    11,
      36,    37,    38,    39,    40,    41,    42,    43,    44,    45,
      46,    47,     0,    59,     0,     0,     0,     0,     0,     0,
     132,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    36,    37,    38,    39,    40,    41,    42,
      43,    44,    45,    46,    47,     0,     0,     0,     0,     0,
       0,     0,   108,    36,    37,    38,    39,    40,    41,    42,
      43,    44,    45,    46,    47,     0,     0,     0,     0,   107,
      36,    37,    38,    39,    40,    41,    42,    43,    44,    45,
      46,    47,    88,     0,     0,    61,    36,    37,    38,    39,
      40,    41,    42,    43,    44,    45,    46,    47,   102,     0,
       0,     0,    36,    37,    38,    39,    40,    41,    42,    43,
      44,    45,    46,    47,    36,    37,    38,    39,    40,    41,
      42,    43,    44,    45,    46,    47,    36,    37,    38,    39,
      40,    41,    42,    43,    44,    45,    46,    36,    37,    38,
      39,    -1,    -1,    -1,    -1,    -1,    -1,    36,    37,    38,
      39,    40,    41,    42,    43,    44,    45
};

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-114)))

#define yytable_value_is_error(Yytable_value) \
  (!!((Yytable_value) == (-1)))

static const yytype_int16 yycheck[] =
{
       0,     4,     7,   116,    11,     5,     6,     7,    15,     7,
      13,     7,    59,     4,   127,    15,    16,     4,     4,    10,
      67,    28,    20,    28,    20,     0,    29,    14,    14,     9,
       4,    11,    10,    13,    18,    19,    36,    37,    38,    39,
      40,    41,    42,    43,    44,    45,    46,    47,    48,     4,
      50,    28,     4,     3,     4,     5,    38,     4,     6,     9,
      10,    61,    62,    63,    43,    44,    45,    17,    16,    17,
      18,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      30,    45,    43,    33,    34,     4,    86,    37,    10,    89,
      20,    41,    42,    14,     6,     9,    20,    40,    98,     4,
       3,     4,     5,     4,   104,    39,     9,   107,   108,     7,
      10,     6,    28,    40,    17,     3,     4,     5,     4,     4,
       4,     9,    10,    14,     4,   125,    20,    30,   128,    17,
      33,    34,   132,     4,    37,    86,    39,   137,    41,    42,
      29,    20,    30,   143,    31,    33,    34,   147,    -1,    37,
       3,     4,     5,    41,    42,    91,     9,    33,    -1,    -1,
      -1,    -1,    -1,    -1,    17,    16,    17,    18,    19,    20,
      21,    22,    23,    24,    25,    26,    27,    30,    -1,    -1,
      33,    34,    -1,    -1,    37,    36,    -1,    -1,    41,    42,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    -1,     8,    -1,    -1,    -1,    -1,    -1,    -1,
      36,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    35,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    -1,    -1,    -1,    -1,    32,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    12,    -1,    -1,    31,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    12,    -1,
      -1,    -1,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    16,    17,    18,
      19,    20,    21,    22,    23,    24,    25,    16,    17,    18,
      19,    20,    21,    22,    23,    24,    25
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,     4,     5,     9,    17,    30,    33,    34,    37,
      41,    42,    51,    52,    53,     9,    11,    13,    10,    52,
      55,    52,    52,    52,     4,    43,    44,    45,    58,    59,
      60,    61,    65,    66,    67,     0,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    11,    15,
      28,    10,    52,    54,    52,     4,    14,    56,    57,     8,
      10,    31,    36,    28,     4,     4,     4,    38,    58,    60,
      65,    52,    52,    52,    52,    52,    52,    52,    52,    52,
      52,    52,    52,    52,     4,    52,     6,    10,    12,    20,
      14,     6,    55,    52,    52,    52,     9,     7,    28,    20,
      39,    55,    12,    54,    40,    52,    56,    32,    35,     4,
      10,    63,    64,     4,    52,     4,    13,    29,    62,    39,
      52,    52,    52,     7,     7,    20,    10,     6,    28,    14,
      63,    40,    36,     4,     4,    52,     7,    20,    63,    52,
      14,     4,    52,    20,     4,    52,    52,    20,    52
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  However,
   YYFAIL appears to be in use.  Nevertheless, it is formally deprecated
   in Bison 2.4.2's NEWS entry, where a plan to phase it out is
   discussed.  */

#define YYFAIL		goto yyerrlab
#if defined YYFAIL
  /* This is here to suppress warnings from the GCC cpp's
     -Wunused-macros.  Normally we don't worry about that warning, but
     some users do, and we want to make it easy for users to remove
     YYFAIL uses, which will produce warnings from Bison 2.5.  */
#endif

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
do                                                              \
  if (yychar == YYEMPTY)                                        \
    {                                                           \
      yychar = (Token);                                         \
      yylval = (Value);                                         \
      YYPOPSTACK (yylen);                                       \
      yystate = *yyssp;                                         \
      goto yybackup;                                            \
    }                                                           \
  else                                                          \
    {                                                           \
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))

/* Error token number */
#define YYTERROR	1
#define YYERRCODE	256


/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */
#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
        break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
#else
static void
yy_stack_print (yybottom, yytop)
    yytype_int16 *yybottom;
    yytype_int16 *yytop;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
} while (YYID (0))

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
	switch (*++yyp)
	  {
	  case '\'':
	  case ',':
	    goto do_not_strip_quotes;

	  case '\\':
	    if (*++yyp != '\\')
	      goto do_not_strip_quotes;
	    /* Fall through.  */
	  default:
	    if (yyres)
	      yyres[yyn] = *yyp;
	    yyn++;
	    break;

	  case '"':
	    if (yyres)
	      yyres[yyn] = '\0';
	    return yyn;
	  }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULL, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULL;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - Assume YYFAIL is not used.  It's too flawed to consider.  See
       <http://lists.gnu.org/archive/html/bison-patches/2009-12/msg00024.html>
       for details.  YYERROR is fine as it does not invoke this
       function.
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULL, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
        break;
    }
}




/* The lookahead symbol.  */
int yychar;


#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval YY_INITIAL_VALUE(yyval_default);

/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack.  Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	yytype_int16 *yyss1 = yyss;

	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),
		    &yystacksize);

	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	yytype_int16 *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyexhaustedlab;
	YYSTACK_RELOCATE (yyss_alloc, yyss);
	YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
/* Line 1792 of yacc.c  */
#line 85 "src/tiger.y"
    { absyn_root = (yyvsp[(1) - (1)].exp_t);  }
    break;

  case 3:
/* Line 1792 of yacc.c  */
#line 89 "src/tiger.y"
    { 
				(yyval.exp_t) = A_OpExp(global_pos, A_minusOp, A_IntExp(global_pos, 0), (yyvsp[(2) - (2)].exp_t));
			}
    break;

  case 4:
/* Line 1792 of yacc.c  */
#line 93 "src/tiger.y"
    { (yyval.exp_t) = A_IntExp(global_pos, (yyvsp[(1) - (1)].int_t)); }
    break;

  case 5:
/* Line 1792 of yacc.c  */
#line 94 "src/tiger.y"
    { (yyval.exp_t) = A_StringExp(global_pos, (yyvsp[(1) - (1)].string_t)); }
    break;

  case 6:
/* Line 1792 of yacc.c  */
#line 95 "src/tiger.y"
    { (yyval.exp_t) = A_NilExp(global_pos); }
    break;

  case 7:
/* Line 1792 of yacc.c  */
#line 97 "src/tiger.y"
    { (yyval.exp_t) = A_VarExp(global_pos, (yyvsp[(1) - (1)].var_t)); }
    break;

  case 8:
/* Line 1792 of yacc.c  */
#line 99 "src/tiger.y"
    { (yyval.exp_t) = A_OpExp(global_pos, A_plusOp, (yyvsp[(1) - (3)].exp_t), (yyvsp[(3) - (3)].exp_t)); }
    break;

  case 9:
/* Line 1792 of yacc.c  */
#line 100 "src/tiger.y"
    { (yyval.exp_t) = A_OpExp(global_pos, A_minusOp, (yyvsp[(1) - (3)].exp_t), (yyvsp[(3) - (3)].exp_t)); }
    break;

  case 10:
/* Line 1792 of yacc.c  */
#line 101 "src/tiger.y"
    { (yyval.exp_t) = A_OpExp(global_pos, A_timesOp, (yyvsp[(1) - (3)].exp_t), (yyvsp[(3) - (3)].exp_t)); }
    break;

  case 11:
/* Line 1792 of yacc.c  */
#line 102 "src/tiger.y"
    { (yyval.exp_t) = A_OpExp(global_pos, A_divideOp, (yyvsp[(1) - (3)].exp_t), (yyvsp[(3) - (3)].exp_t)); }
    break;

  case 12:
/* Line 1792 of yacc.c  */
#line 104 "src/tiger.y"
    { (yyval.exp_t) = A_IfExp(global_pos, (yyvsp[(1) - (3)].exp_t), A_IntExp(global_pos, 1), (yyvsp[(3) - (3)].exp_t)); }
    break;

  case 13:
/* Line 1792 of yacc.c  */
#line 105 "src/tiger.y"
    { (yyval.exp_t) = A_IfExp(global_pos, (yyvsp[(1) - (3)].exp_t), (yyvsp[(3) - (3)].exp_t), A_IntExp(global_pos, 0)); }
    break;

  case 14:
/* Line 1792 of yacc.c  */
#line 107 "src/tiger.y"
    { (yyval.exp_t) = A_OpExp(global_pos, A_eqOp, (yyvsp[(1) - (3)].exp_t), (yyvsp[(3) - (3)].exp_t)); }
    break;

  case 15:
/* Line 1792 of yacc.c  */
#line 108 "src/tiger.y"
    { (yyval.exp_t) = A_OpExp(global_pos, A_ltOp, (yyvsp[(1) - (3)].exp_t), (yyvsp[(3) - (3)].exp_t)); }
    break;

  case 16:
/* Line 1792 of yacc.c  */
#line 109 "src/tiger.y"
    { (yyval.exp_t) = A_OpExp(global_pos, A_leOp, (yyvsp[(1) - (3)].exp_t), (yyvsp[(3) - (3)].exp_t)); }
    break;

  case 17:
/* Line 1792 of yacc.c  */
#line 110 "src/tiger.y"
    { (yyval.exp_t) = A_OpExp(global_pos, A_gtOp, (yyvsp[(1) - (3)].exp_t), (yyvsp[(3) - (3)].exp_t)); }
    break;

  case 18:
/* Line 1792 of yacc.c  */
#line 111 "src/tiger.y"
    { (yyval.exp_t) = A_OpExp(global_pos, A_geOp, (yyvsp[(1) - (3)].exp_t), (yyvsp[(3) - (3)].exp_t)); }
    break;

  case 19:
/* Line 1792 of yacc.c  */
#line 112 "src/tiger.y"
    { (yyval.exp_t) = A_OpExp(global_pos, A_neqOp, (yyvsp[(1) - (3)].exp_t), (yyvsp[(3) - (3)].exp_t)); }
    break;

  case 20:
/* Line 1792 of yacc.c  */
#line 114 "src/tiger.y"
    { (yyval.exp_t) = A_AssignExp(global_pos, (yyvsp[(1) - (3)].var_t), (yyvsp[(3) - (3)].exp_t)); }
    break;

  case 21:
/* Line 1792 of yacc.c  */
#line 117 "src/tiger.y"
    { 
				(yyval.exp_t) = A_CallExp(global_pos, S_Symbol((yyvsp[(1) - (4)].string_t)), (yyvsp[(3) - (4)].expList_t));
			}
    break;

  case 22:
/* Line 1792 of yacc.c  */
#line 121 "src/tiger.y"
    {
				(yyval.exp_t) = A_CallExp(global_pos, S_Symbol((yyvsp[(1) - (3)].string_t)), NULL);
			}
    break;

  case 23:
/* Line 1792 of yacc.c  */
#line 126 "src/tiger.y"
    {
				(yyval.exp_t) = A_SeqExp(global_pos, (yyvsp[(2) - (3)].expList_t));
			}
    break;

  case 24:
/* Line 1792 of yacc.c  */
#line 130 "src/tiger.y"
    {
				(yyval.exp_t) = A_SeqExp(global_pos, NULL);
			}
    break;

  case 25:
/* Line 1792 of yacc.c  */
#line 135 "src/tiger.y"
    {
				(yyval.exp_t) = A_RecordExp(global_pos, S_Symbol((yyvsp[(1) - (4)].string_t)), (yyvsp[(3) - (4)].efieldList_t));
			}
    break;

  case 26:
/* Line 1792 of yacc.c  */
#line 139 "src/tiger.y"
    {
				(yyval.exp_t) = A_RecordExp(global_pos, S_Symbol((yyvsp[(1) - (3)].string_t)), NULL);
			}
    break;

  case 27:
/* Line 1792 of yacc.c  */
#line 144 "src/tiger.y"
    {
				(yyval.exp_t) = A_ArrayExp(global_pos, S_Symbol((yyvsp[(1) - (6)].string_t)), (yyvsp[(3) - (6)].exp_t), (yyvsp[(6) - (6)].exp_t));
			}
    break;

  case 28:
/* Line 1792 of yacc.c  */
#line 149 "src/tiger.y"
    {
				(yyval.exp_t) = A_IfExp(global_pos, (yyvsp[(2) - (4)].exp_t), (yyvsp[(4) - (4)].exp_t), NULL);
			}
    break;

  case 29:
/* Line 1792 of yacc.c  */
#line 153 "src/tiger.y"
    {
				(yyval.exp_t) = A_IfExp(global_pos, (yyvsp[(2) - (6)].exp_t), (yyvsp[(4) - (6)].exp_t), (yyvsp[(6) - (6)].exp_t));
			}
    break;

  case 30:
/* Line 1792 of yacc.c  */
#line 158 "src/tiger.y"
    {
				(yyval.exp_t) = A_WhileExp(global_pos, (yyvsp[(2) - (4)].exp_t), (yyvsp[(4) - (4)].exp_t));
			}
    break;

  case 31:
/* Line 1792 of yacc.c  */
#line 163 "src/tiger.y"
    {
				(yyval.exp_t) = A_ForExp(global_pos, S_Symbol((yyvsp[(2) - (8)].string_t)), (yyvsp[(4) - (8)].exp_t), (yyvsp[(6) - (8)].exp_t), (yyvsp[(8) - (8)].exp_t));
			}
    break;

  case 32:
/* Line 1792 of yacc.c  */
#line 167 "src/tiger.y"
    { (yyval.exp_t) = A_BreakExp(global_pos); }
    break;

  case 33:
/* Line 1792 of yacc.c  */
#line 170 "src/tiger.y"
    {
				(yyval.exp_t) = A_LetExp(global_pos, (yyvsp[(2) - (4)].decList_t), NULL);
			}
    break;

  case 34:
/* Line 1792 of yacc.c  */
#line 174 "src/tiger.y"
    {
				(yyval.exp_t) = A_LetExp(global_pos, (yyvsp[(2) - (5)].decList_t), A_SeqExp(global_pos, (yyvsp[(4) - (5)].expList_t)));
			}
    break;

  case 35:
/* Line 1792 of yacc.c  */
#line 180 "src/tiger.y"
    {
				(yyval.var_t) = A_SubscriptVar(global_pos, (yyvsp[(1) - (4)].var_t), (yyvsp[(3) - (4)].exp_t));
			}
    break;

  case 36:
/* Line 1792 of yacc.c  */
#line 185 "src/tiger.y"
    {
				(yyval.var_t) = A_SubscriptVar(global_pos, A_SimpleVar(global_pos, S_Symbol((yyvsp[(1) - (4)].string_t))), (yyvsp[(3) - (4)].exp_t));
			}
    break;

  case 37:
/* Line 1792 of yacc.c  */
#line 189 "src/tiger.y"
    {
				(yyval.var_t) = A_FieldVar(global_pos, (yyvsp[(1) - (3)].var_t), S_Symbol((yyvsp[(3) - (3)].string_t)));
			}
    break;

  case 38:
/* Line 1792 of yacc.c  */
#line 193 "src/tiger.y"
    {
				(yyval.var_t) = A_SimpleVar(global_pos, S_Symbol((yyvsp[(1) - (1)].string_t)));
			}
    break;

  case 39:
/* Line 1792 of yacc.c  */
#line 199 "src/tiger.y"
    {
				(yyval.expList_t) = A_ExpList((yyvsp[(1) - (1)].exp_t), NULL);
			}
    break;

  case 40:
/* Line 1792 of yacc.c  */
#line 203 "src/tiger.y"
    {
				(yyval.expList_t) = A_ExpList((yyvsp[(1) - (3)].exp_t), (yyvsp[(3) - (3)].expList_t));
			}
    break;

  case 41:
/* Line 1792 of yacc.c  */
#line 209 "src/tiger.y"
    {
					(yyval.expList_t) = A_ExpList((yyvsp[(1) - (1)].exp_t), NULL);
				}
    break;

  case 42:
/* Line 1792 of yacc.c  */
#line 213 "src/tiger.y"
    {
					(yyval.expList_t) = A_ExpList((yyvsp[(1) - (3)].exp_t), (yyvsp[(3) - (3)].expList_t));
				}
    break;

  case 43:
/* Line 1792 of yacc.c  */
#line 219 "src/tiger.y"
    {
				(yyval.efieldList_t) = A_EfieldList((yyvsp[(1) - (1)].efield_t), NULL);
			}
    break;

  case 44:
/* Line 1792 of yacc.c  */
#line 223 "src/tiger.y"
    {
				(yyval.efieldList_t) = A_EfieldList((yyvsp[(1) - (3)].efield_t), (yyvsp[(3) - (3)].efieldList_t));
			}
    break;

  case 45:
/* Line 1792 of yacc.c  */
#line 229 "src/tiger.y"
    {
				(yyval.efield_t) = A_Efield(S_Symbol((yyvsp[(1) - (3)].string_t)), (yyvsp[(3) - (3)].exp_t));
			}
    break;

  case 46:
/* Line 1792 of yacc.c  */
#line 235 "src/tiger.y"
    {
						(yyval.decList_t) = A_DecList((yyvsp[(1) - (1)].dec_t), NULL);
					}
    break;

  case 47:
/* Line 1792 of yacc.c  */
#line 239 "src/tiger.y"
    {
						(yyval.decList_t) = A_DecList((yyvsp[(1) - (2)].dec_t), (yyvsp[(2) - (2)].decList_t));
					}
    break;

  case 48:
/* Line 1792 of yacc.c  */
#line 245 "src/tiger.y"
    {
					(yyval.dec_t) = A_TypeDec(global_pos, (yyvsp[(1) - (1)].nametyList_t));
				}
    break;

  case 49:
/* Line 1792 of yacc.c  */
#line 249 "src/tiger.y"
    {
					(yyval.dec_t) = A_FunctionDec(global_pos, (yyvsp[(1) - (1)].fundecList_t));
				}
    break;

  case 50:
/* Line 1792 of yacc.c  */
#line 253 "src/tiger.y"
    {
					(yyval.dec_t) = (yyvsp[(1) - (1)].dec_t);
				}
    break;

  case 51:
/* Line 1792 of yacc.c  */
#line 259 "src/tiger.y"
    {
					(yyval.nametyList_t) = A_NametyList((yyvsp[(1) - (1)].namety_t), NULL);
				}
    break;

  case 52:
/* Line 1792 of yacc.c  */
#line 263 "src/tiger.y"
    {
					(yyval.nametyList_t) = A_NametyList((yyvsp[(1) - (2)].namety_t), (yyvsp[(2) - (2)].nametyList_t));
				}
    break;

  case 53:
/* Line 1792 of yacc.c  */
#line 269 "src/tiger.y"
    {
						(yyval.namety_t) = A_Namety(S_Symbol((yyvsp[(2) - (4)].string_t)), (yyvsp[(4) - (4)].ty_t));
					}
    break;

  case 54:
/* Line 1792 of yacc.c  */
#line 275 "src/tiger.y"
    {
				(yyval.ty_t) = A_NameTy(global_pos, S_Symbol((yyvsp[(1) - (1)].string_t)));
			}
    break;

  case 55:
/* Line 1792 of yacc.c  */
#line 279 "src/tiger.y"
    {
				(yyval.ty_t) = A_RecordTy(global_pos, (yyvsp[(2) - (3)].fieldList_t));
			}
    break;

  case 56:
/* Line 1792 of yacc.c  */
#line 283 "src/tiger.y"
    {
				(yyval.ty_t) = A_RecordTy(global_pos, NULL);
			}
    break;

  case 57:
/* Line 1792 of yacc.c  */
#line 288 "src/tiger.y"
    {
				(yyval.ty_t) = A_ArrayTy(global_pos, S_Symbol((yyvsp[(3) - (3)].string_t)));
			}
    break;

  case 58:
/* Line 1792 of yacc.c  */
#line 294 "src/tiger.y"
    {
					(yyval.fieldList_t) = A_FieldList((yyvsp[(1) - (1)].field_t), NULL);
				}
    break;

  case 59:
/* Line 1792 of yacc.c  */
#line 298 "src/tiger.y"
    {
					(yyval.fieldList_t) = A_FieldList((yyvsp[(1) - (3)].field_t), (yyvsp[(3) - (3)].fieldList_t));
				}
    break;

  case 60:
/* Line 1792 of yacc.c  */
#line 304 "src/tiger.y"
    {
					(yyval.field_t) = A_Field(global_pos, S_Symbol((yyvsp[(1) - (3)].string_t)), S_Symbol((yyvsp[(3) - (3)].string_t)));
				}
    break;

  case 61:
/* Line 1792 of yacc.c  */
#line 310 "src/tiger.y"
    {
						(yyval.fundecList_t) = A_FundecList((yyvsp[(1) - (1)].fundec_t), NULL);
					}
    break;

  case 62:
/* Line 1792 of yacc.c  */
#line 314 "src/tiger.y"
    {
						(yyval.fundecList_t) = A_FundecList((yyvsp[(1) - (2)].fundec_t), (yyvsp[(2) - (2)].fundecList_t));
					}
    break;

  case 63:
/* Line 1792 of yacc.c  */
#line 320 "src/tiger.y"
    {
							(yyval.fundec_t) = A_Fundec(global_pos, S_Symbol((yyvsp[(2) - (6)].string_t)), NULL, NULL, (yyvsp[(6) - (6)].exp_t));
						}
    break;

  case 64:
/* Line 1792 of yacc.c  */
#line 324 "src/tiger.y"
    {
							(yyval.fundec_t) = A_Fundec(global_pos, S_Symbol((yyvsp[(2) - (7)].string_t)), (yyvsp[(4) - (7)].fieldList_t), NULL, (yyvsp[(7) - (7)].exp_t));
						}
    break;

  case 65:
/* Line 1792 of yacc.c  */
#line 328 "src/tiger.y"
    {
							(yyval.fundec_t) = A_Fundec(global_pos, S_Symbol((yyvsp[(2) - (8)].string_t)), NULL, S_Symbol((yyvsp[(6) - (8)].string_t)), (yyvsp[(8) - (8)].exp_t));
						}
    break;

  case 66:
/* Line 1792 of yacc.c  */
#line 332 "src/tiger.y"
    {
							(yyval.fundec_t) = A_Fundec(global_pos, S_Symbol((yyvsp[(2) - (9)].string_t)), (yyvsp[(4) - (9)].fieldList_t), S_Symbol((yyvsp[(7) - (9)].string_t)), (yyvsp[(9) - (9)].exp_t));
						}
    break;

  case 67:
/* Line 1792 of yacc.c  */
#line 338 "src/tiger.y"
    {
							(yyval.dec_t) = A_VarDec(global_pos, S_Symbol((yyvsp[(2) - (4)].string_t)), NULL, (yyvsp[(4) - (4)].exp_t));
						}
    break;

  case 68:
/* Line 1792 of yacc.c  */
#line 342 "src/tiger.y"
    {
							(yyval.dec_t) = A_VarDec(global_pos, S_Symbol((yyvsp[(2) - (6)].string_t)), S_Symbol((yyvsp[(4) - (6)].string_t)), (yyvsp[(6) - (6)].exp_t));
						}
    break;


/* Line 1792 of yacc.c  */
#line 2132 "src/y.tab.c"
      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
	 error, discard it.  */

      if (yychar <= YYEOF)
	{
	  /* Return failure if at end of input.  */
	  if (yychar == YYEOF)
	    YYABORT;
	}
      else
	{
	  yydestruct ("Error: discarding",
		      yytoken, &yylval);
	  yychar = YYEMPTY;
	}
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule which action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
	{
	  yyn += YYTERROR;
	  if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
	    {
	      yyn = yytable[yyn];
	      if (0 < yyn)
		break;
	    }
	}

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
	YYABORT;


      yydestruct ("Error: popping",
		  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}


/* Line 2055 of yacc.c  */
#line 346 "src/tiger.y"


void yyerror() {
	printf("####! yyerror()!\n");
}

int yywrap() {
	return 1;
}
