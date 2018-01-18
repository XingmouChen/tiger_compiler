#ifndef __TOOL__
#define __TOOL__

#define _NOT_NEW_LINE 0
#define _IS_NEW_LINE 1

#define PRT printf("%s\n", yytext)

#include "absyn.h"

extern int global_line_num;
extern int global_column_num;
extern int global_pos;

void pos(int isNewline, int length);
void myerror(const char* msg);
const char* hardTerm2Str(const char* termName);

extern A_exp absyn_root;

#endif