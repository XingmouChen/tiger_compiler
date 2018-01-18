#ifndef ENV_H
#define ENV_H

#include <stdio.h>
#include "util.h"
#include "symbol.h"
#include "absyn.h"
#include "types.h"
#include "translate.h"

typedef struct E_enventry_ *E_enventry;

struct E_enventry_ {
	enum { E_varEntry, E_funEntry, E_loopVarEntry, E_stdFuncEntry } kind;
	union {
		struct {
			Tr_access access;
			Ty_ty ty;
		} var;
		struct {
			Tr_level level;
			Temp_label label;
			Ty_tyList formals;
			Ty_ty result;
		} fun;
	} u;
};

E_enventry E_VarEntry(Tr_access access, Ty_ty ty);
E_enventry E_FunEntry(Tr_level level, Temp_label label, Ty_tyList formals, Ty_ty result);
E_enventry E_LoopVarEntry(Tr_access access, Ty_ty ty);
E_enventry E_StdfunEntry(Tr_level level, Temp_label label, Ty_tyList formals, Ty_ty result);


S_table E_base_tenv(void);  /*Ty_ty environment */
S_table E_base_venv(void);  /*E_enventry environment */

typedef struct nameList_ *nameList;
struct nameList_ {
	string name;
	nameList next;
};
nameList stdFunList;

#endif

// #ifndef ENV_H
// #define ENV_H

// #include <stdio.h>
// #include "util.h"
// #include "symbol.h"
// #include "absyn.h"
// #include "types.h"

// typedef struct E_enventry_ *E_enventry;

// struct E_enventry_ {
// 	enum {E_varEntry, E_funEntry} kind;
// 	union {
// 		struct {Ty_ty ty;} var;
// 		struct {
// 			Ty_tyList formals; Ty_ty result;
// 		} fun;
// 	} u;
// };

// E_enventry E_VarEntry(Ty_ty ty);
// E_enventry E_FunEntry(Ty_tyList formals, Ty_ty result);

// S_table E_base_tenv(void);  /*Ty_ty environment */
// S_table E_base_venv(void);  /*E_enventry environment */

// #endif
