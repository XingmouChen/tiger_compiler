#include <stdlib.h>
#include "translate.h"
#include "tree.h"

typedef struct Tr_node_ *Tr_node;

struct Tr_level_ {
	Tr_level parent;
	Temp_label name;
	F_frame frame;
	Tr_accessList formals;
};

struct Tr_access_ {
	Tr_level level;
	F_access access;
};

struct Cx {
	patchList trues;
	patchList falses;
	T_stm stm;
};

struct Tr_exp_ {
	enum {Tr_ex, Tr_nx, Tr_cx} kind;
	union {
		T_exp ex;
		T_stm nx;
		struct Cx cx;
	} u;
};

struct Tr_expList_ {
	Tr_node head;
	Tr_node tail;
};

struct Tr_node_ {
	Tr_exp expr;
	Tr_node next;
};

struct patchList_ {
	Temp_label *head;
	patchList tail;
};


static F_fragList fragList = NULL;

static Tr_accessList makeFormalAccessList(Tr_level level);
static Tr_access Tr_Access(Tr_level level, F_access access);


static T_expList Tr_expListConvert(Tr_expList list);


static Tr_exp Tr_StaticLink(Tr_level funLevel, Tr_level level); 

static Tr_exp Tr_Ex(T_exp ex);
static Tr_exp Tr_Nx(T_stm nx);
static Tr_exp Tr_Cx(patchList trues, patchList falses, T_stm stm);

static T_exp unEx(Tr_exp e);
static T_stm unNx(Tr_exp e);
static struct Cx unCx(Tr_exp e);

static patchList PatchList(Temp_label *head, patchList tail);
static void doPatch(patchList pList, Temp_label label);
static patchList joinPatch(patchList fList, patchList sList);

static T_exp Tr_externalCall(string str, T_expList args);

Tr_exp Tr_combine2Exp(Tr_exp e1, Tr_exp e2);
Tr_exp Tr_combine2Stm(Tr_exp e1, Tr_exp e2);

static Tr_level outer = NULL;
Tr_level Tr_outermost(void)
{
	if (!outer)
		outer = Tr_newLevel(NULL, Temp_newlabel(), NULL);
	return outer;
}

static Tr_accessList makeFormalAccessList(Tr_level level)
{
	Tr_accessList headList = NULL, tailList = NULL;

	F_accessList accessList = F_formals(level->frame)->tail;
	for (; accessList; accessList = accessList->tail) {
		Tr_access access = Tr_Access(level, accessList->head);
		if (headList) {
			tailList->tail = Tr_AccessList(access, NULL);
			tailList = tailList->tail;
		} else {
			headList = Tr_AccessList(access, NULL);
			tailList = headList;
		}
	}
	return headList;
}

static Tr_exp Tr_Ex(T_exp ex)
{
	Tr_exp trEx = checked_malloc(sizeof(*trEx));
	trEx->kind = Tr_ex;
	trEx->u.ex = ex;
	return trEx;
}

static Tr_exp Tr_Nx(T_stm nx)
{
	Tr_exp trNx = checked_malloc(sizeof(*trNx));
	trNx->kind = Tr_nx;
	trNx->u.nx = nx;
	return trNx;
}

static Tr_exp Tr_Cx(patchList trues, patchList falses, T_stm stm)
{
	Tr_exp trCx = checked_malloc(sizeof(*trCx));
	trCx->kind = Tr_cx;
	trCx->u.cx.trues = trues;
	trCx->u.cx.falses = falses;
	trCx->u.cx.stm = stm;
	return trCx;
}

static void doPatch(patchList pList, Temp_label label)
{
	for (; pList; pList = pList->tail)
		*(pList->head) = label;
}

static patchList joinPatch(patchList fList, patchList sList)
{
	if (!fList) return sList;
	for (; fList->tail; fList = fList->tail)
		;
	fList->tail = sList;
	return fList;
}

static T_exp unEx(Tr_exp e)
{
	switch(e->kind) {
		case Tr_ex:
			return e->u.ex;
		case Tr_nx:
			return T_Eseq(e->u.nx, T_Const(0));
		case Tr_cx:
		{
			Temp_temp r = Temp_newtemp();
			Temp_label t = Temp_newlabel(), f = Temp_newlabel();
			doPatch(e->u.cx.trues, t);
			doPatch(e->u.cx.falses, f);
			return T_Eseq(T_Move(T_Temp(r), T_Const(1)),
				T_Eseq(e->u.cx.stm,
					T_Eseq(T_Label(f), 
						T_Eseq(T_Move(T_Temp(r), T_Const(0)),
							T_Eseq(T_Label(t), T_Temp(r))))));
		}
		default:
		{
			assert(0);
		}
	}
	return NULL;
}

static T_stm unNx(Tr_exp e)
{
	switch(e->kind) {
		case Tr_ex:
			return T_Exp(e->u.ex);
		case Tr_nx:
			return e->u.nx;
		case Tr_cx:
		{
			Temp_temp r = Temp_newtemp();
			Temp_label t = Temp_newlabel(), f = Temp_newlabel();
			doPatch(e->u.cx.trues, t);
			doPatch(e->u.cx.falses, f);
			return T_Exp(T_Eseq(T_Move(T_Temp(r), T_Const(1)),
				T_Eseq(e->u.cx.stm,
					T_Eseq(T_Label(f), 
						T_Eseq(T_Move(T_Temp(r), T_Const(0)),
							T_Eseq(T_Label(t), T_Temp(r)))))));
		}
		default:
		{
			assert(0);
		}
	}
	return NULL;
}

static struct Cx unCx(Tr_exp e)
{
	switch(e->kind) {
		case Tr_ex:
		{
            //若表达式非 0 转到 t,否则转到 f
            //if (exp!=0) goto T else goto F
			struct Cx cx;
			cx.stm = T_Cjump(T_ne, e->u.ex, T_Const(0), NULL, NULL);
			cx.trues = PatchList(&(cx.stm->u.CJUMP.true), NULL);
			cx.falses = PatchList(&(cx.stm->u.CJUMP.false), NULL);
			return cx;
		}
		case Tr_nx:
		{
			assert(0); // Should never occur
		}
		case Tr_cx:
		{
			return e->u.cx;
		}
		default:
		{
			assert(0);
		}
	}

}

static patchList PatchList(Temp_label *head, patchList tail)
{
	patchList pList = checked_malloc(sizeof(*pList));
	pList->head = head;
	pList->tail = tail;
	return pList;
}

static Tr_access Tr_Access(Tr_level level, F_access access)
{
	Tr_access trAccess = checked_malloc(sizeof(*trAccess));
	trAccess->level = level;
	trAccess->access = access;
	return trAccess;
}


static Tr_exp Tr_StaticLink(Tr_level funLevel, Tr_level level)
{
	T_exp addr = T_Temp(F_FP());

	while (level != funLevel->parent) {

		F_access staticLink = F_formals(level->frame)->head;
		addr = T_Mem(T_Binop(T_plus, addr, T_Const(F_offset(staticLink))));
		level = level->parent;
	}
	return Tr_Ex(addr);
}

Tr_level Tr_newLevel(Tr_level parent, Temp_label name, U_boolList formals)
{
	Tr_level level = checked_malloc(sizeof(*level));
	level->parent = parent;
	level->name = name;
	level->frame = F_newFrame(name, U_BoolList(TRUE, formals));
	level->formals = makeFormalAccessList(level);
	return level;
}

Tr_access Tr_allocLocal(Tr_level level, bool escape)
{
	Tr_access local = checked_malloc(sizeof(*local));
	local->level = level;
	local->access = F_allocLocal(level->frame, escape);
	return local;
}

Tr_accessList Tr_formals(Tr_level level)
{
	return level->formals;
}

Tr_accessList Tr_AccessList(Tr_access head, Tr_accessList tail)
{
	Tr_accessList list = checked_malloc(sizeof(*list));
	list->head = head;
	list->tail = tail;
	return list;
}

Tr_expList Tr_ExpList(void)
{
	Tr_expList list = checked_malloc(sizeof(*list));
	list->head = NULL;
	list->tail = NULL;
	return list;
}

void Tr_expListPrepend(Tr_expList list, Tr_exp expr)
{
	if (list->head) {
		Tr_node node = checked_malloc(sizeof(*node));
		node->expr = expr;
		node->next = list->head;
		list->head = node;
	} else {
		list->head = checked_malloc(sizeof(*(list->head)));
		list->head->expr = expr;
		list->head->next = NULL;
		list->tail = list->head;
	}
}

void Tr_expListAppend(Tr_expList list, Tr_exp expr)
{
	if (list->head) {
		Tr_node node = checked_malloc(sizeof(*node));
		node->expr = expr;
		node->next = NULL;
		list->tail->next = node;
		list->tail = node;
	} else {
		Tr_expListPrepend(list, expr);
	}
}

int Tr_expListIsEmpty(Tr_expList list)
{
	if (list && list->head) 
		return FALSE;
	else 
		return TRUE;
}

static T_expList Tr_expListConvert(Tr_expList list)
{
	T_expList eList = NULL;
	T_expList tailList = NULL;
	Tr_node iter = list->head;
	for (; iter ; iter = iter->next) {
		if (eList) {
			tailList->tail = T_ExpList(unEx(iter->expr), NULL);
			tailList = tailList->tail;
		} else {
			eList = T_ExpList(unEx(iter->expr), NULL);
			tailList = eList;
		}
	}
	return eList;
}

Tr_exp Tr_seqExp(Tr_expList list, bool isVoid)
{
	Tr_exp result = NULL;

	if (isVoid) {
		result = Tr_Nx(unNx(list->head->expr));
	} else {
		result = Tr_Ex(unEx(list->head->expr));
	}

	Tr_node p = NULL;
	for (p = list->head->next; p; p = p->next) {
		if (isVoid) {
			result = Tr_combine2Stm(p->expr, result);
		} else {
			result = Tr_combine2Exp(p->expr, result);
		}
	}
	return result;
}

Tr_exp Tr_simpleVar(Tr_access access, Tr_level level)
{
	T_exp addr = T_Temp(F_FP());

	Tr_level l = level;
	F_access staticLink;
	while (l && l != access->level) {

		staticLink = F_formals(l->frame)->head;
		addr = T_Mem(T_Binop(T_plus, addr, T_Const(F_offset(staticLink))));
		l = l->parent;
	}
	return Tr_Ex(T_Mem(T_Binop(T_plus, addr, T_Const(F_offset(access->access)))));
}

Tr_exp Tr_fieldVar(Tr_exp recordBase, int fieldOffset)
{
	T_exp recAddr = unEx(recordBase); //记录首地址
	//偏移量 (每个记录项目占一个 wordsize)
	T_exp recOff = T_Const(fieldOffset * F_WORD_SIZE);
	return Tr_Ex(T_Mem(T_Binop(T_plus, recAddr, recOff)));
}

Tr_exp Tr_subscriptVar(Tr_exp arrayBase, Tr_exp index)
{
	T_exp arrAddr = unEx(arrayBase); //arr_addr 数组首地址
	T_exp arrOff = T_Binop(T_mul, unEx(index), T_Const(F_WORD_SIZE)); //arr_off 偏移量, 等于下标乘以字长
	return Tr_Ex(T_Mem(T_Binop(T_plus, arrAddr, arrOff)));
}

Tr_exp Tr_arrayExp(Tr_exp size, Tr_exp init)
{
	return Tr_Ex(Tr_externalCall(String("initArray"),
		   	T_ExpList(unEx(size), T_ExpList(unEx(init), NULL))));
}

Tr_exp Tr_recordExp(int n, Tr_expList list)
{
	int i = n - 1;
	Temp_temp r = Temp_newtemp();
	// 调用外部函数 _allocRecord 为记录在 frame 上分配空间,
	// 并得存储空间首地址

	T_stm alloc = T_Move(T_Temp(r),
		Tr_externalCall(String("initRecord"), T_ExpList(T_Const( (n == 0 ? 1 : n) * F_WORD_SIZE), NULL)));

	// 注意如果记录为空,也要用 1 个 word,否则每个域为一个 word,按顺序存放	
	T_stm init = unNx(Tr_noExp());
	for (Tr_node p = list->head; p; p = p->next, i--) {
		//为记录中每个域生成 MOVE 指令,将值复制到帧中的相应区域
		init = T_Seq(T_Move(T_Mem(T_Binop(T_plus, T_Temp(r), T_Const(i * F_WORD_SIZE))),
				unEx(p->expr)), init);
	}
	// 返回记录的首地址
	return Tr_Ex(T_Eseq(T_Seq(alloc, init), T_Temp(r)));
}

Tr_exp Tr_letExp(Tr_expList list)
{
	T_exp result = unEx(list->head->expr); // Result of executing let body
	Tr_node p;
	for (p = list->head->next; p; p = p->next)
		result = T_Eseq(T_Exp(unEx(p->expr)), result);
	return Tr_Ex(result);
}

Tr_exp Tr_doneExp(void)
{
	return Tr_Ex(T_Name(Temp_newlabel()));
}

Tr_exp Tr_breakExp(Temp_label dsc)
{
	return Tr_Nx(T_Jump(T_Name(dsc), Temp_LabelList(dsc, NULL)));
}

Tr_exp Tr_forExp(Tr_access var, Tr_access limit,
	Tr_exp low, Tr_exp high, Tr_exp done, Tr_exp body) 
{
	/*
	循环变量和循环上限被分配在帧空间中
	MOVE VAR, LOW
	MOVE LIMIT, HIGH
	if (VAR<=LIMIT) goto BEGIN else goto DONE
	LABEL BEGIN:
	body
	if (VAR<LIMIT) goto GOON else goto DONE
	LABEL GOON:
	VAR=VAR+1
	GOTO BEGIN:
	LABEL DONE:
	*/
	Temp_label begin = Temp_newlabel(), goon = Temp_newlabel(); 
	return Tr_Nx(T_Seq(
					T_Move(
						T_Mem(T_Binop(T_plus, T_Temp(F_FP()), T_Const(F_offset(var->access)))), 
						unEx(low)),
					T_Seq(
						T_Move(
							T_Mem(T_Binop(T_plus, T_Temp(F_FP()), T_Const(F_offset(limit->access)))), 
							unEx(high)),
					T_Seq(
						T_Cjump(T_le, T_Mem(T_Binop(T_plus, T_Temp(F_FP()), T_Const(F_offset(var->access)))),
							T_Mem(T_Binop(T_plus, T_Temp(F_FP()), T_Const(F_offset(limit->access)))), 
							begin, unEx(done)->u.NAME),
					T_Seq(T_Label(begin),
					T_Seq(unNx(body),
					T_Seq(
						T_Cjump(T_lt, T_Mem(T_Binop(T_plus, T_Temp(F_FP()), T_Const(F_offset(var->access)))),
							T_Mem(T_Binop(T_plus, T_Temp(F_FP()), T_Const(F_offset(limit->access)))), 
							goon, unEx(done)->u.NAME),
					T_Seq(
						T_Label(goon),
					T_Seq(
						T_Move(
							T_Mem(T_Binop(T_plus, T_Temp(F_FP()), T_Const(F_offset(var->access)))), 
							T_Binop(T_plus, T_Mem(T_Binop(T_plus, T_Temp(F_FP()), T_Const(F_offset(var->access)))), 
								T_Const(1))),
					T_Seq(
						T_Jump(T_Name(begin), Temp_LabelList(begin, NULL)),
						T_Label(unEx(done)->u.NAME)))))))))));
}

Tr_exp Tr_whileExp(Tr_exp test, Tr_exp done, Tr_exp body)
{
	//LABEL BEGIN:
	//if (test) goto T else goto DONE
	//LABEL T:
	//body
	//goto BEGIN
	//LABEL DONE:
	Temp_label begin = Temp_newlabel(), t = Temp_newlabel();
	return Tr_Nx(T_Seq(T_Label(begin), 
					T_Seq(T_Cjump(T_ne, unEx(test), T_Const(0), t, unEx(done)->u.NAME),
					T_Seq(T_Label(t), 
					T_Seq(unNx(body),
					T_Seq(T_Jump(T_Name(begin), Temp_LabelList(begin, NULL)),
					T_Label(unEx(done)->u.NAME)))))));
}

Tr_exp Tr_ifExp(Tr_exp test, Tr_exp then, Tr_exp elsee)
{
	// if (elsee) return Tr_ifExpWithElse(test, then, elsee);
	// else return Tr_ifExpNoElse(test, then);
 	Temp_label t = Temp_newlabel(), f = Temp_newlabel(), join = Temp_newlabel();
	struct Cx cond = unCx(test);
    T_stm joinJump = T_Jump(T_Name(join), Temp_LabelList(join, NULL));
	doPatch(cond.trues, t);
	doPatch(cond.falses, f);
    
    switch (then->kind) { 
        //if-else 这样翻译成有返回值的表达式:
        //if (test) goto T else goto F
        //LABEL T: r=e1
        //goto JOIN
        //LABEL F: r=e2
        //LABEL JOIN: return r
        case Tr_ex: { // Then "else" expression must exist
			Temp_temp r = Temp_newtemp();
            return Tr_Ex(T_Eseq(cond.stm, T_Eseq(T_Label(t), 
                        T_Eseq(T_Move(T_Temp(r), unEx(then)),
                        T_Eseq(joinJump, 
                        T_Eseq(T_Label(f),
                        T_Eseq(T_Move(T_Temp(r), unEx(elsee)), 
                        T_Eseq(joinJump, 
                        T_Eseq(T_Label(join), 
                        T_Temp(r))))))))));        
        }
        // 这样翻译成无返回值的 if-then
        // 如果没有 else 子句
        // if (test) goto T else goto JOIN
        // LABEL T: e1
        // LABEL JOIN:
        // 如果有 else 子句
        // if (test) goto T else goto F
        // LABEL T: e1
        // goto JOIN
        // LABEL F: e2
        // LABEL JOIN:
        case Tr_nx: {
            if (!elsee) {
                return Tr_Nx(T_Seq(cond.stm, 
                        T_Seq(T_Label(t),
                        T_Seq(unNx(then), T_Label(f)))));
            } else {
                return Tr_Nx(T_Seq(cond.stm, 
                            T_Seq(T_Label(t), 
                            T_Seq(unNx(then),
                            T_Seq(joinJump, 
                            T_Seq(T_Label(f),
                            T_Seq(unNx(elsee),  
                            T_Label(join))))))));
            }
        }        
        case Tr_cx: {
            // if (!elsee) {
            //     return Tr_Cx(T_Seq(cond.stm, 
            //             T_Seq(T_Label(t),
            //             T_Seq(then->u.cx.stm, T_Label(f)))));
            // } else {
            //     return Tr_Cx(T_Seq(cond.stm, 
            //                 T_Seq(T_Label(t), 
            //                 T_Seq(then->u.cx.stm,
            //                 T_Seq(joinJump, 
            //                 T_Seq(T_Label(f),
            //                 T_Seq(elsee->u.cx.stm,  
            //                 T_Label(join))))))));
            // }
			Temp_temp r = Temp_newtemp();
			T_stm c = T_Cjump(T_ne, T_Eseq(cond.stm, T_Eseq(T_Label(t), 
                        T_Eseq(T_Move(T_Temp(r), unEx(then)),
                        T_Eseq(joinJump, 
                        T_Eseq(T_Label(f),
                        T_Eseq(T_Move(T_Temp(r), unEx(elsee)), 
                        T_Eseq(joinJump, 
                        T_Eseq(T_Label(join), 
                        T_Temp(r))))))))), T_Const(0), t, f);	
			patchList trues = PatchList(&c->u.CJUMP.true, NULL);
			patchList falses = PatchList(&c->u.CJUMP.false, NULL);
			return Tr_Cx(trues, falses, c);
        }
        default: {
            assert(0);
            return NULL;
        }
    }
}

Tr_exp Tr_assignExp(Tr_exp var, Tr_exp exp)
{
	return Tr_Nx(T_Move(unEx(var), unEx(exp)));
}

Tr_exp Tr_arithExp(A_oper op, Tr_exp left, Tr_exp right)
{
	T_binOp oper = T_plus;
	switch(op) {
		case A_plusOp: oper = T_plus; break;
		case A_minusOp: oper = T_minus; break;
		case A_timesOp: oper = T_mul; break;
		case A_divideOp: oper = T_div; break;
		default: assert(0); break; // Should never happen
	}
	return Tr_Ex(T_Binop(oper, unEx(left), unEx(right)));
}

Tr_exp Tr_stringRelExp(A_oper op, Tr_exp left, Tr_exp right)
{
	T_relOp oper;
	switch(op) {
		case A_ltOp: oper = T_lt; break;
		case A_leOp: oper = T_le; break;
		case A_gtOp: oper = T_gt; break;
		case A_geOp: oper = T_ge; break;
		default: assert(0); break; // should never happen
	}
	
	// 其中 COMP 是调用外部函数 stringCompare 得出的比较结果
	// 代码: Exp transStringRelExp
	// Expr comp = home.frame.externalCall("_stringCompare", new ExpList(left.unEx(),
	// new ExpList(right.unEx(), null)));
	// return new RelCx(oper, new Ex(comp), new Ex(CONST._zero));
	T_stm cond = T_Cjump(oper, unEx(left), unEx(right), NULL, NULL);
	patchList trues = PatchList(&(cond->u.CJUMP.true), NULL);
	patchList falses = PatchList(&(cond->u.CJUMP.false), NULL);
    //先把左右都翻译成Ex
    //再用 CJUMP 处理跳转
	return Tr_Cx(trues, falses, cond);
}

Tr_exp Tr_otherRelExp(A_oper op, Tr_exp left, Tr_exp right)
{
	T_relOp oper;
	switch(op) {
		case A_ltOp: oper = T_lt; break;
		case A_leOp: oper = T_le; break;
		case A_gtOp: oper = T_gt; break;
		case A_geOp: oper = T_ge; break;
		default: assert(0); break; // should never happen
	}
	T_stm cond = T_Cjump(oper, unEx(left), unEx(right), NULL, NULL);
	patchList trues = PatchList(&(cond->u.CJUMP.true), NULL);
	patchList falses = PatchList(&(cond->u.CJUMP.false), NULL);
    //先把左右都翻译成Ex
    //再用 CJUMP 处理跳转
	return Tr_Cx(trues, falses, cond);
}

Tr_exp Tr_otherEqExp(A_oper op, Tr_exp left, Tr_exp right)
{
	T_relOp oper;
	if (op == A_eqOp) 
		oper = T_eq;
	else 
		oper = T_ne;
	T_stm cond = T_Cjump(oper, unEx(left), unEx(right), NULL, NULL);	
	patchList trues = PatchList(&cond->u.CJUMP.true, NULL);
	patchList falses = PatchList(&cond->u.CJUMP.false, NULL);
	return Tr_Cx(trues, falses, cond);
}

Tr_exp Tr_stringEqExp(A_oper op, Tr_exp left, Tr_exp right)
{
	T_exp result = Tr_externalCall(String("stringEqual"),
		T_ExpList(unEx(left), T_ExpList(unEx(right), NULL)));
	if (op == A_eqOp) return Tr_Ex(result);
	else {
		T_exp e = (result->kind == T_CONST 
			&& result->u.CONST == 1) ? T_Const(0) : T_Const(1);
		return Tr_Ex(e);
	}
}

Tr_exp Tr_callExp(Tr_level level, Tr_level funLevel, Temp_label funLabel, Tr_expList argsList)
{
	Tr_exp slink = Tr_StaticLink(funLevel, level);
	//Add static link as the first parameter
	Tr_expListPrepend(argsList, slink);
	return Tr_Ex(T_Call(T_Name(funLabel), Tr_expListConvert(argsList)));
}

static F_fragList stringList = NULL;
Tr_exp Tr_stringExp(string str)
{
	Temp_label l = Temp_newlabel(); //新建一个标号
	stringList = F_FragList(F_StringFrag(l, str), stringList); //将字符串添加到段 (DataFrag) 中去
	return Tr_Ex(T_Name(l)); //返回 NAME, 以标号作为标示
}

Tr_exp Tr_intExp(int n)
{
	return Tr_Ex(T_Const(n));
}

Tr_exp Tr_nilExp(void)
{
	return Tr_Ex(T_Const(0)); 
}

Tr_exp Tr_noExp(void)
{
	return Tr_Ex(T_Const(0));
}

F_frame Tr_getLevelFrame(Tr_level level) {
	return level->frame;
}

Temp_label Tr_getDoneLabel(Tr_exp done) {
	return unEx(done)->u.NAME;
}

void Tr_procEntryExit(Tr_level level, Tr_exp body, Tr_accessList formals) {
	F_frag pfrag = F_ProcFrag(unNx(body), level->frame);
	fragList = F_FragList(pfrag, fragList);
}

F_fragList Tr_mainProcEntryExit(Tr_exp body) {
	F_frag pfrag = F_ProcFrag(T_Exp(unEx(body)), (Tr_outermost())->frame);
	return F_FragList(pfrag, Tr_getResult());
}

F_fragList Tr_getResult(void)
{
	F_fragList cursor = NULL, prev = NULL;
	for (cursor = stringList; cursor; cursor = cursor->tail)
		prev = cursor;
	if (prev) prev->tail = fragList;
	return stringList ? stringList : fragList;
}

Tr_exp Tr_combine2Stm(Tr_exp e1, Tr_exp e2) {
	if (e1 == NULL)
		return Tr_Nx(unNx(e2));
	else if (e2 == NULL)
		return Tr_Nx(unNx(e1));
	else
		return Tr_Nx(T_Seq(unNx(e1), unNx(e2)));
}

Tr_exp Tr_combine2Exp(Tr_exp e1, Tr_exp e2) {
	if (e1 == NULL)
		return Tr_Ex(unEx(e2));
	else
		return Tr_Ex(T_Eseq(unNx(e1), unEx(e2)));
}

static T_exp Tr_externalCall(string str, T_expList args)
{
	return T_Call(T_Name(Temp_namedlabel(str)), args);
}