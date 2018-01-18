#ifndef __AST__
#define __AST__

#include "absyn.h"

extern A_exp ast_root;
A_exp parse_ast(const char* fileName);

#endif