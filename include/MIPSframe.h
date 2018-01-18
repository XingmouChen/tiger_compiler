#ifndef __MIPSframe__
#define __MIPSframe__

#include "temp.h"
#include "util.h"
#include "tree.h"

typedef struct F_frame_ *F_frame;
typedef struct F_access_ *F_access;
typedef struct F_accessList_ *F_accessList;
typedef struct F_frag_ *F_frag;
typedef struct F_fragList_ *F_fragList;

struct F_access_ {
	enum { inFrame, inReg } kind;
	union {
		int offset;
		Temp_temp reg;
	} u;
};

struct F_accessList_ {
	F_access head;
	F_accessList tail;
};

struct F_frame_ {
	Temp_label name;
	F_accessList formals;
	int local_count;
};

struct F_frag_ {
	enum {F_stringFrag, F_procFrag} kind;
	union {
		struct {
			Temp_label label;
			string str;
		} stringg;
		struct {
			T_stm body;
			F_frame frame;
		} proc;
	} u;
};

struct F_fragList_ {
	F_frag head;
	F_fragList tail;
};

extern const int F_WORD_SIZE;

F_frame F_newFrame(Temp_label name, U_boolList formals);
Temp_label F_name(F_frame frame);
F_accessList F_formals(F_frame frame);
F_access F_allocLocal(F_frame frame, bool escape);
bool F_doesEscape(F_access access);
F_frag F_StringFrag(Temp_label label, string str);
F_frag F_ProcFrag(T_stm body, F_frame frame);
F_fragList F_FragList(F_frag head, F_fragList tail);
int F_offset(F_access access);

Temp_temp F_FP(void);

T_exp F_externalCall(string str, T_expList args);
T_exp F_Exp(F_access access, T_exp framePtr);

#endif
