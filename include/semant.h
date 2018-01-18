#ifndef SEMANT_H
#define SEMANT_H

#include "absyn.h"
#include "types.h"
#include "env.h"
#include "translate.h"

// typedef void *Tr_exp;

struct expty {Tr_exp exp; Ty_ty ty;};

// void SEM_transProg(A_exp exp);

F_fragList SEM_transProg(A_exp exp);

#endif
