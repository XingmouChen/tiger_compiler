#include "env.h"

string stdFunc[] = {
		"print", "flush", "getchar", "ord", "chr", "size", "substring",
		"concat", "not", "exit"
};
static void makeStdFuncList(void) {
	nameList s, prev;
	for (int i = 0; i < sizeof(stdFunc)/sizeof(stdFunc[0]); ++i) {
		s = checked_malloc(sizeof(*s));
		s->name = stdFunc[i];
		s->next = NULL;
		if (!stdFunList) {
			stdFunList = s;
			prev = stdFunList;
		} else {
			prev->next = s;
			prev = s;
		}
	} 
}

E_enventry E_VarEntry(Tr_access access, Ty_ty ty)
{
	E_enventry varEntry = checked_malloc(sizeof(*varEntry));
	varEntry->kind = E_varEntry;
	varEntry->u.var.access = access;
	varEntry->u.var.ty = ty;
	return varEntry;
}

E_enventry E_FunEntry(Tr_level level, Temp_label label, Ty_tyList formals, Ty_ty result)
{
	E_enventry funEntry = checked_malloc(sizeof(*funEntry));
	funEntry->kind = E_funEntry;
	funEntry->u.fun.level = level;
	funEntry->u.fun.label = label;
	funEntry->u.fun.formals = formals;
	funEntry->u.fun.result = result;
	return funEntry;
}

E_enventry E_LoopVarEntry(Tr_access access, Ty_ty ty)
{
	E_enventry loopVarEntry = checked_malloc(sizeof(*loopVarEntry));
	loopVarEntry->kind = E_loopVarEntry;
	loopVarEntry->u.var.access = access;
	loopVarEntry->u.var.ty = ty;
	return loopVarEntry;
}

E_enventry E_StdFunEntry(Tr_level level, Temp_label label, Ty_tyList formals, Ty_ty result)
{
	E_enventry stdFunEntry = checked_malloc(sizeof(*stdFunEntry));
	stdFunEntry->kind = E_stdFuncEntry;
	stdFunEntry->u.fun.level = level;
	stdFunEntry->u.fun.label = label;
	stdFunEntry->u.fun.formals = formals;
	stdFunEntry->u.fun.result = result;
	return stdFunEntry;
}

S_table E_base_tenv(void){
    S_table table = S_empty();
    S_enter(table, S_Symbol("int"), Ty_Int());
    S_enter(table, S_Symbol("string"), Ty_String());
    S_enter(table, S_Symbol("void"), Ty_Void());
    S_enter(table, S_Symbol("nil"), Ty_Nil());
    return table;
}

S_table E_base_venv(void) { 
    S_table table = S_empty();
	S_enter(table, S_Symbol("print"), E_StdFunEntry(Tr_outermost(), Temp_newlabel(),
		Ty_TyList(Ty_String(), NULL), Ty_Void()));
	S_enter(table, S_Symbol("flush"), E_StdFunEntry(Tr_outermost(), Temp_newlabel(),
		NULL, Ty_Void()));
	S_enter(table, S_Symbol("getchar"), E_StdFunEntry(Tr_outermost(), Temp_newlabel(),
		NULL, Ty_String()));
	S_enter(table, S_Symbol("ord"), E_StdFunEntry(Tr_outermost(), Temp_newlabel(),
		Ty_TyList(Ty_String(), NULL), Ty_Int()));
	S_enter(table, S_Symbol("chr"), E_StdFunEntry(Tr_outermost(), Temp_newlabel(),
		Ty_TyList(Ty_Int(), NULL), Ty_String()));
	S_enter(table, S_Symbol("size"), E_StdFunEntry(Tr_outermost(), Temp_newlabel(),
		Ty_TyList(Ty_String(), NULL), Ty_Int()));
	S_enter(table, S_Symbol("substring"), E_StdFunEntry(Tr_outermost(), Temp_newlabel(),
		Ty_TyList(Ty_String(), Ty_TyList(Ty_Int(),
					Ty_TyList(Ty_Int(), NULL))), Ty_String()));
	S_enter(table, S_Symbol("concat"),  E_StdFunEntry(Tr_outermost(), Temp_newlabel(),
		Ty_TyList(Ty_String(), Ty_TyList(Ty_String(), NULL)), Ty_String()));
	S_enter(table, S_Symbol("not"), E_StdFunEntry(Tr_outermost(), Temp_newlabel(),
		Ty_TyList(Ty_Int(), NULL), Ty_Int()));
	S_enter(table, S_Symbol("exit"), E_StdFunEntry(Tr_outermost(), Temp_newlabel(),
		Ty_TyList(Ty_Int(), NULL), Ty_Void()));
    makeStdFuncList();
	return table;
}