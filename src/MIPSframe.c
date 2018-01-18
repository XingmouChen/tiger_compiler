#include "MIPSframe.h"

const int F_WORD_SIZE = 4;
static const int F_K = 6;

static F_access InFrame(int offset);
static F_access InReg(Temp_temp reg);
static F_accessList F_AccessList(F_access head, F_accessList tail);
static F_accessList makeFormalAccessList(U_boolList formals);

int F_offset(F_access access) {
	return access->u.offset;
}

static F_accessList F_AccessList(F_access head, F_accessList tail)
{
	F_accessList list = checked_malloc(sizeof(*list));
	list->head = head;
	list->tail = tail;
	return list;
}

static F_access InFrame(int offset)
{
	F_access fa = checked_malloc(sizeof(*fa));
	fa->kind = inFrame;
	fa->u.offset = offset;
	return fa;
}

static F_access InReg(Temp_temp reg)
{
	F_access fa = checked_malloc(sizeof(*fa));
	fa->kind = inReg;
	fa->u.reg = reg;
	return fa;
}

F_frag F_StringFrag(Temp_label label, string str)
{
	F_frag strfrag = checked_malloc(sizeof(*strfrag));
	strfrag->kind = F_stringFrag;
	strfrag->u.stringg.label = label;
	strfrag->u.stringg.str = str;
	return strfrag;
}

F_frag F_ProcFrag(T_stm body, F_frame frame)
{
	F_frag pfrag = checked_malloc(sizeof(*pfrag));
	pfrag->kind = F_procFrag;
	pfrag->u.proc.body = body;
	pfrag->u.proc.frame = frame;
	return pfrag;
}

F_fragList F_FragList(F_frag head, F_fragList tail) {
	F_fragList flist= checked_malloc(sizeof(*flist));
	flist->head = head;
	flist->tail = tail;
	return flist;
}


static F_accessList makeFormalAccessList(U_boolList formals) 
{
	F_accessList headList = NULL, tailList = NULL;
	U_boolList fmls;
	int i = 0;
	int localIdx = 0;
	for (fmls = formals; fmls; fmls = fmls->tail, i++) {
		F_access access = NULL;
		if (i < F_K && !fmls->head)//
		{
			access = InReg(Temp_newtemp());
		}
		else {	// stack access
			/*2 slots reserved, the 1st word for static link*/
			access = InFrame(F_WORD_SIZE * (1 + localIdx++));
		}
		if (headList) {
			tailList->tail = F_AccessList(access, NULL);
			tailList = tailList->tail;
		} else {
			headList = F_AccessList(access, NULL);
			tailList = headList;
		}
	}
	return headList;
}

T_exp F_Exp(F_access access, T_exp framePtr)
{
	if (access->kind == inFrame) {
		return T_Mem(T_Binop(T_plus, framePtr, T_Const(access->u.offset)));
	} else {
		return T_Temp(access->u.reg);
	}
}

T_exp F_externalCall(string str, T_expList args)
{
	return T_Call(T_Name(Temp_namedlabel(str)), args);
}

Temp_temp F_FP(void)
{
	static Temp_temp fp = NULL;
	if (!fp) {
		fp = Temp_newtemp();
	}
	return fp;
}

bool F_doesEscape(F_access access)
{
	return (access != NULL && access->kind == inFrame);
}

F_access F_allocLocal(F_frame f, bool escape)
{
	f->local_count++;
	if (escape)
		return InFrame(F_WORD_SIZE * (- f->local_count));
	else
		return InReg(Temp_newtemp());
}

F_frame F_newFrame(Temp_label name, U_boolList formals)
{
	F_frame f = checked_malloc(sizeof(*f));
	f->name = name;
	f->formals = makeFormalAccessList(formals);
	f->local_count = 0;
	return f;
}

Temp_label F_name(F_frame f)
{
	return f->name;
}

F_accessList F_formals(F_frame f)
{
	return f->formals;
}
