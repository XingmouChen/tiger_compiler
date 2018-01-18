#include "semant.h"
#include "errormsg.h"

static struct expty expTy(Tr_exp exp, Ty_ty ty);
static struct expty transVar(Tr_level level, S_table venv, S_table tenv, A_var v);
static struct expty transExp(Tr_level level, S_table venv, S_table tenv, A_exp a);
static Tr_exp transDec(Tr_level level, S_table venv, S_table tenv, A_dec d);
static Ty_ty transTy(S_table tenv, A_ty a);
static Ty_ty actual_ty(Ty_ty ty); //Find the actual type of the T_Name type
static Ty_tyList makeFormalTyList(S_table tenv, A_fieldList paraList); 
static U_boolList makeFormalsBoolList(A_fieldList paraList);
static bool isAssignTypeLegal(Ty_ty lhs, Ty_ty rhs);
static bool isLoop(Ty_ty type);

#define MAXSIZE 1024
static Temp_label stack[1024];
static int stackTop = -1;

static bool isLoopLabelsEmpty(void) {
    return stackTop == -1;
}
static void loopLabelsPush(Temp_label x) {
    stack[++stackTop] = x;
}
static void loopLabelsPop(void) {
    --stackTop;
}
static Temp_label loopLabelsTop(void) {
    return stack[stackTop];
}

static bool isAssignTypeLegal(Ty_ty lhs, Ty_ty rhs)
{
  //void type? nil type?
	lhs = actual_ty(lhs);
	rhs = actual_ty(rhs);
  
    int lhsKind = lhs->kind;
	int rhsKind = rhs->kind;
	
  return rhsKind != Ty_void && ( 
		((lhsKind == Ty_record || lhsKind == Ty_array) && lhs == rhs) ||
		(lhsKind == Ty_record && rhsKind == Ty_nil) ||
		(lhsKind != Ty_record && lhsKind != Ty_array && lhsKind == rhsKind));
}

F_fragList SEM_transProg(A_exp exp) {
    S_table venv = E_base_venv();
    S_table tenv = E_base_tenv();
    struct expty mainFunc = transExp(Tr_outermost(), venv, tenv, exp);
    // return Tr_getResult();
    return Tr_mainProcEntryExit(mainFunc.exp);
}

struct expty transVar(Tr_level level, S_table venv, S_table tenv, A_var v) {
    switch(v->kind) {
        case A_simpleVar: {
            E_enventry x = S_look(venv, v->u.simple);
          
            if (x && (x->kind == E_varEntry || x->kind == E_loopVarEntry) ) {
                return expTy(Tr_simpleVar(x->u.var.access, level), actual_ty(x->u.var.ty));
            } else {
                EM_error(v->pos, "Undefined variable %s", S_name(v->u.simple));
                return expTy(Tr_noExp(), Ty_Int());
            }
        }
        case A_fieldVar: {
          struct expty var = transVar(level, venv, tenv, v->u.field.var);

          // Check Record type 
          if(var.ty->kind != Ty_record){
              EM_error(v->pos, "Not a record type");
              return expTy(Tr_noExp(), Ty_Int());
          }

          Ty_fieldList fieldList;
          int fieldOff = 0;
          // Iterate record field
          for (fieldList = var.ty->u.record; 
                  fieldList && fieldList->head->name != v->u.field.sym;
                      fieldList = fieldList->tail, ++fieldOff) {
          }
          if(fieldList) {
              return expTy(Tr_fieldVar(var.exp, fieldOff), actual_ty(fieldList->head->ty));
          } else {
              EM_error(v->pos, "Field %s doesn't exist", S_name(v->u.field.sym));
              return expTy(Tr_noExp(), Ty_Int());
          }
        }
        case A_subscriptVar:{
            struct expty var = transVar(level, venv, tenv, v->u.subscript.var);
            struct expty exp = transExp(level, venv, tenv, v->u.subscript.exp);

            // Subsciprt expression only support Array type
            if (var.ty->kind != Ty_array) {
                EM_error(v->pos, "Subscript expression should be array.");
                return expTy(Tr_noExp(), Ty_Int());
            }

            // subsciprt of an array must be int
            if (exp.ty->kind != Ty_int) {
                EM_error(v->pos, "Subscript should be int.");
                return expTy(Tr_noExp(), Ty_Int());
            }

            return expTy(Tr_subscriptVar(var.exp, exp.exp), actual_ty(var.ty->u.array));
        }
        default:{
            assert(0);
            return expTy(Tr_noExp(), Ty_Int());
        }
    }
}

struct expty transExp(Tr_level level, S_table venv, S_table tenv, A_exp a) {
    switch(a->kind){
        /*A_varExp, A_nilExp, A_intExp, A_stringExp, A_callExp,
            A_opExp, A_recordExp, A_seqExp, A_assignExp, A_ifExp,
            A_whileExp, A_forExp, A_breakExp, A_letExp, A_arrayExp*/
        case A_varExp:{
            return transVar(level, venv, tenv, a->u.var);
        }
        case A_nilExp:{
            return expTy(Tr_nilExp(), Ty_Nil());
        }
        case A_intExp:{
            return expTy(Tr_intExp(a->u.intt), Ty_Int());
        }
        case A_stringExp:{
            return expTy(Tr_stringExp(a->u.stringg), Ty_String());
        }
        case A_callExp:{
            E_enventry x = S_look(venv, a->u.call.func);
            Tr_expList argsList = Tr_ExpList();
            // Check func's type
            if(!x || (x->kind != E_funEntry && x->kind != E_stdFuncEntry)) {
                EM_error(a->pos, "Undefined function %s", S_name(a->u.call.func));
                return expTy(Tr_noExp(), Ty_Int());
            }

            // Compare call list and func arglist
            Ty_tyList l;
            A_expList k;
            for (l = x->u.fun.formals, k = a->u.call.args; l && k; l = l->tail, k = k->tail) {
                Ty_ty paraT = l->head;
                struct expty arg = transExp(level, venv, tenv, k->head);
                Ty_ty callT = arg.ty;
                
                if (callT->kind == Ty_void) {
                    EM_error(a->pos, "Assigh rhs type cannot be void");
                }
				
                // check var and exp type consistency
                // 如果 t2 不能强制转换成 t1 则出错
                if (!isAssignTypeLegal(paraT, callT)) {
                    EM_error(a->pos, "Exp's type and para's type should be the same");
                }
                Tr_expListAppend(argsList, arg.exp);                
            }

            if (k) {
                EM_error(k->head->pos, "Parameter number more than expectation");
                return expTy(Tr_noExp(), Ty_Int());
            }
            if (l) {
                EM_error(a->u.call.args->head->pos, "Parameter number less than expectation");
                return expTy(Tr_noExp(), Ty_Int());
            }

            return expTy(Tr_callExp(level, x->u.fun.level, x->u.fun.label, argsList), 
                        actual_ty(x->u.fun.result));
        }
        case A_opExp:{
            A_oper oper = a->u.op.oper;
            struct expty left = transExp(level, venv, tenv, a->u.op.left);
            struct expty right = transExp(level, venv, tenv, a->u.op.right);
            if(oper == A_plusOp || oper == A_minusOp || oper == A_timesOp || oper == A_divideOp){               
                if(left.ty->kind != Ty_int){
                    EM_error(a->u.op.left->pos,"Integer required");
                } 
                if(right.ty->kind != Ty_int){
                    EM_error(a->u.op.right->pos,"Integer required");
                }
                if (left.ty->kind == Ty_int && right.ty->kind == Ty_int) {
                    return expTy(Tr_arithExp(oper, left.exp, right.exp), Ty_Int());
                } else {
                    return expTy(Tr_noExp(), Ty_Int());
                }
            } else if(oper == A_eqOp || oper == A_neqOp) {
                // 左右中任一个不能为 void 类型
                // 左右不能全为 nil
                // 可以一个为 nil 一个为 record 类型
                // 其它情况下必须左右类型完全一致
                bool flag = TRUE;
                if (left.ty->kind == Ty_void || right.ty->kind == Ty_void) {
                    EM_error(a->pos, "Operation types cannot be void");
                    flag = FALSE;
                }
                if (left.ty->kind == Ty_nil && right.ty->kind == Ty_nil) {
                    EM_error(a->pos, "Operation types cannot be nil both");
                    flag = FALSE;
                }
                if (!isAssignTypeLegal(left.ty, right.ty)) {
                    EM_error(a->pos, "Operation types should be the same");
                    flag = FALSE;
                }
                if (flag) {

                    if (left.ty->kind == Ty_string) {
                        return expTy(Tr_stringEqExp(oper, left.exp, right.exp), Ty_Int());
                    } else {
                        return expTy(Tr_otherEqExp(oper, left.exp, right.exp), Ty_Int());
                    }

                } else {
                    return expTy(Tr_noExp(), Ty_Int());                    
                }
            } else if (oper == A_leOp || oper == A_ltOp || oper == A_gtOp || oper == A_geOp) {
                //左右两边必须全为 int 或 string
                bool flag = TRUE;
                if (left.ty->kind != Ty_int && left.ty->kind != Ty_string) {
                    EM_error(a->u.op.left->pos,"Integer or string required");
                    flag = FALSE;
                }
                if (right.ty->kind != Ty_int && right.ty->kind != Ty_string) {
                    EM_error(a->u.op.right->pos,"Integer or string required");
                    flag = FALSE;
                }
                if (left.ty->kind != right.ty->kind) {
                    EM_error(a->pos, "Operation types should be the same");
                    flag = FALSE;
                }

                if (flag) {
                    if (left.ty->kind == Ty_string) {
                        return expTy(Tr_stringRelExp(oper, left.exp, right.exp), Ty_Int());
                    } else {
                        return expTy(Tr_otherRelExp(oper, left.exp, right.exp), Ty_Int());
                    }
                } else {
                    return expTy(Tr_noExp(), Ty_Int());                    
                }
            }
            assert(0);
            return expTy(Tr_noExp(), Ty_Int());
        }
        case A_recordExp:{
            Ty_ty record = S_look(tenv, a->u.record.typ);
            // Check record type
            
            if(!record) {
                EM_error(a->pos, "Undefined record %s", S_name(a->u.record.typ));
                return expTy(Tr_noExp(), Ty_Int());
            }
            record = actual_ty(record);
            if (record->kind != Ty_record) {
                EM_error(a->pos, "Undefined record %s", S_name(a->u.record.typ));
                return expTy(Tr_noExp(), Ty_Int());
            }

            A_efieldList efieldList;
            Ty_fieldList fieldList;
            bool flag = TRUE;
            Tr_expList list = Tr_ExpList();
			int n = 0;
            for (efieldList = a->u.record.fields, fieldList = record->u.record; 
                    efieldList && fieldList; ++n, 
                        efieldList = efieldList->tail, fieldList = fieldList->tail) {
                Ty_field field = fieldList->head;
                A_efield efield = efieldList->head;
                struct expty exp = transExp(level, venv, tenv, efield->exp);
                Ty_ty efieldTy = exp.ty;                
                Ty_ty fieldTy = actual_ty(field->ty); 
                
                if (field->name != efield->name) {
                    EM_error(a->pos, "Field names mismatched");
                    flag = FALSE;
                }
                if (!isAssignTypeLegal(fieldTy, efieldTy)) {
                    EM_error(a->pos, "Field types mismatched");
                    flag =FALSE;
                }
                if (flag) {
                    Tr_expListPrepend(list, exp.exp);
                }
            }

            if (efieldList) {
                EM_error(a->pos, "More record fields than expectaion");
                flag = FALSE;
            }

            if (fieldList) {
                EM_error(a->pos, "Less record fields than expectaion");
                flag = FALSE;
            }

            if (flag) {

                return expTy(Tr_recordExp(n, list), record);

            } else {
                return expTy(Tr_noExp(), Ty_Int());
            }
        }
        case A_seqExp:{
			struct expty exp;
			A_expList seq, prev;
			Tr_expList list = Tr_ExpList();
			for (seq = a->u.seq; seq; seq = seq->tail) {
				exp = transExp(level, venv, tenv, seq->head);
				Tr_expListPrepend(list, exp.exp); // last expr is result of expression
			}
			// At least one exp in the list.
			if (Tr_expListIsEmpty(list)) {
                exp = expTy(Tr_noExp(), Ty_Void());
                Tr_expListPrepend(list, exp.exp);
            }
			return expTy(Tr_seqExp(list, exp.ty->kind == Ty_void), exp.ty);
        }
        case A_assignExp:{
            if (a->u.assign.var->kind == A_SimpleVar) {
                E_enventry x = S_look(venv, a->u.assign.var->u.simple);
                if (x->kind == E_loopVarEntry) {
                    return expTy(Tr_noExp(), Ty_Void());
                }
            }

            struct expty var = transVar(level, venv, tenv, a->u.assign.var);
            struct expty exp = transExp(level, venv, tenv, a->u.assign.exp);
            bool flag = TRUE;
            if (exp.ty->kind == Ty_void) {
                EM_error(a->pos, "Assigh rhs type cannot be void");
                flag = FALSE;
            }

            // Check var and exp type consistency
            // 如果 t2 不能强制转换成 t1 则出错
            if (!isAssignTypeLegal(var.ty, exp.ty)) {
                EM_error(a->pos, "Type mismatch");
                flag = FALSE;
            } 
            
            if (flag) {
                return expTy(Tr_assignExp(var.exp, exp.exp), Ty_Void());
            } else {
                return expTy(Tr_noExp(), Ty_Void());
            }
            
        }
        case A_ifExp:{
            struct expty test = transExp(level, venv, tenv, a->u.iff.test);
            struct expty then = transExp(level, venv, tenv, a->u.iff.then);
            
            if (test.ty->kind != Ty_int) {
				EM_error(a->u.iff.test->pos, "Test condition should be integer.");
                return expTy(Tr_noExp(), Ty_Int());
            }

            if(a->u.iff.elsee) {
                struct expty elsee = transExp(level, venv, tenv, a->u.iff.elsee);
                // @test9
                if ( !(then.ty->kind == Ty_void && elsee.ty->kind == Ty_void) &&
                    (!isAssignTypeLegal(then.ty, elsee.ty) || !isAssignTypeLegal(elsee.ty, then.ty)) 
                    && (then.ty->kind != Ty_nil && elsee.ty->kind != Ty_nil)) 
                {
                    EM_error(a->u.iff.elsee->pos, "Then exp and else exp type mismatch");
                    return expTy(Tr_noExp(), Ty_Int());
                } else {
                    return expTy(Tr_ifExp(test.exp, then.exp, elsee.exp), then.ty);
                }
            } else {
                // @merge.tig
                if(then.ty->kind != Ty_void) {
                    EM_error(a->u.iff.then->pos, "This ifexp must produce no value");
                    return expTy(Tr_noExp(), Ty_Int());
                } else {
                    return expTy(Tr_ifExp(test.exp, then.exp, NULL), Ty_Void());
                }
            }
        }
        case A_whileExp:{
            struct expty test = transExp(level, venv, tenv, a->u.whilee.test);
            
            if (test.ty->kind != Ty_int) {
                EM_error(a->u.whilee.test->pos, "Test condition should be Integer type");
                return expTy(Tr_noExp(), Ty_Void());
            }
			Tr_exp doneExp = Tr_doneExp();	
            loopLabelsPush(Tr_getDoneLabel(doneExp));
            struct expty body = transExp(level, venv, tenv, a->u.whilee.body);
            if  (body.ty->kind != Ty_void) {
                EM_error(a->u.whilee.body->pos, "While body exp must return no value");
                return expTy(Tr_noExp(), Ty_Void());
            }
            loopLabelsPop();

            return expTy(Tr_whileExp(test.exp, doneExp, body.exp), Ty_Void());

        }
        case A_forExp:{
            // Low and high index of a for exp
            struct expty lo = transExp(level, venv, tenv, a->u.forr.lo);
            struct expty hi = transExp(level, venv, tenv, a->u.forr.hi);
            // @test11, index has to be int
            if(lo.ty->kind != Ty_int) {
                EM_error(a->u.forr.lo->pos, "Integer type required");
                return expTy(Tr_noExp(), Ty_Void());
            }
            if(hi.ty->kind != Ty_int) {
                EM_error(a->u.forr.hi->pos, "Integer type required");
                return expTy(Tr_noExp(), Ty_Void());
            }
            Tr_access var = Tr_allocLocal(level, TRUE);
            Tr_access limit = Tr_allocLocal(level, TRUE);
            S_enter(venv, a->u.forr.var, E_LoopVarEntry(var, Ty_Int()));
            S_beginScope(venv);
            struct expty body = transExp(level, venv, tenv, a->u.forr.body);
            S_endScope(venv);
            return expTy(Tr_forExp(var, limit, lo.exp, hi.exp, Tr_doneExp(), body.exp), 
                        Ty_Void());
        }
        case A_breakExp:{

			if (isLoopLabelsEmpty()) {
				EM_error(a->pos, "Illegal break expression: break should be inside a loop");
			    return expTy(Tr_noExp(), Ty_Void());
            } else {
                return expTy(Tr_breakExp(loopLabelsTop()), Ty_Void());
			}

        }
        case A_letExp:{
            S_beginScope(venv);
            S_beginScope(tenv);
            Tr_expList list = Tr_ExpList();
            // Check dec part
            A_decList dec;
            for(dec = a->u.let.decs; dec; dec = dec->tail) {
                Tr_expListAppend(list, 
                    transDec(level, venv, tenv, dec->head));
            }

            // Check body part
            struct expty exp = transExp(level, venv, tenv, a->u.let.body);
            Tr_expListPrepend(list, exp.exp);

            S_endScope(tenv);
            S_endScope(venv);

            return expTy(Tr_seqExp(list, exp.ty->kind == Ty_void), exp.ty);
        }
        case A_arrayExp:{
            // Check exp type
            Ty_ty array = S_look(tenv, a->u.array.typ);
            if(!array) {
                EM_error(a->pos, "Undefined array type %s", S_name(a->u.array.typ));
                return expTy(Tr_noExp(), Ty_Int());
            }
            array = actual_ty(array);
            if(array->kind != Ty_array) {
                EM_error(a->pos, "Undefined array type %s", S_name(a->u.array.typ));
                return expTy(Tr_noExp(), Ty_Int());
            }

            // Check array size type
            struct expty sizeExp = transExp(level, venv, tenv, a->u.array.size);
            if(sizeExp.ty->kind != Ty_int) {
                EM_error(a->pos, "Array size type should be int");
                return expTy(Tr_noExp(), Ty_Int());
            }

            // Check type and init value consistency
            struct expty initExp = transExp(level, venv, tenv, a->u.array.init);
            if (!isAssignTypeLegal(array->u.array, initExp.ty)) {
                EM_error(a->u.array.init->pos, "Init type and array element's type should be the same");
                return expTy(Tr_noExp(), Ty_Int());
            }

            return expTy(Tr_arrayExp(sizeExp.exp, initExp.exp), array);
        }
        default: {
            return expTy(NULL, NULL);
        }
    }
  
    assert(0);
    return expTy(NULL, NULL);
}

static Tr_exp transDec(Tr_level level, S_table venv, S_table tenv, A_dec d) {
    switch(d->kind) {
        case A_varDec: {
            struct expty e;
            Ty_ty ty;
            Tr_access access = Tr_allocLocal(level, TRUE);
            //With init expression
            e = transExp(level, venv, tenv, d->u.var.init);
            //With type-id
            if (d->u.var.typ) {
                ty = S_look(tenv, d->u.var.typ);

                if (!ty) {
                    EM_error(d->pos, "Undefined type %s", S_name(d->u.var.typ));
                    //Continue semant check??!!
                    ty = Ty_Void();
                }
                if (e.ty == Ty_Void()) {
                    EM_error(d->pos, "Assign expression type cannot be void");
                }

                if (!isAssignTypeLegal(ty, e.ty)) {
                      EM_error(d->u.var.init->pos, "Exp's type:%s and dec's type:%s mismatch",
                          "", "");
                          //S_name(e.ty), S_name(ty));
                }
                
                S_enter(venv, d->u.var.var, E_VarEntry(access, ty));
            } else if (e.ty->kind == Ty_nil) { // && d->u.var.typ == NULL
                EM_error(d->pos, "Cannot assign nil expression to no record var.");
                S_enter(venv, d->u.var.var, E_VarEntry(access, e.ty));
            } else {
                S_enter(venv, d->u.var.var, E_VarEntry(access, e.ty));
            }
            return Tr_assignExp(Tr_simpleVar(access, level), e.exp);
            // break;
        }

        case A_typeDec: {
            A_nametyList nameList;
            //Check if each type has an identical name
            for (nameList = d->u.type; nameList; nameList = nameList->tail) {
                for (A_nametyList l = nameList->tail; l; l = l->tail) {
                    //We only need to check the function symbol
                    if(nameList != l && nameList->head->name == l->head->name) {
                        // @test38
                        EM_error(d->pos, "Types have the same name in block");  
                          //S_name(l->head->name), d->pos, S_name(nameList->head->name));
                    }
                }
            }
            
            bool isCyclic = TRUE; 

            //Deal with recursive type definition
       		for (nameList = d->u.type; nameList; nameList = nameList->tail) {
                S_enter(tenv, nameList->head->name, Ty_Name(nameList->head->name, NULL));
            }
            
            //To detect cycle, we should build servel graphs, and dect cycle
            isCyclic = FALSE;

            //Deal with cyclic type define
            for (nameList = d->u.type; nameList; nameList = nameList->tail) {
                Ty_ty ty = transTy(tenv, nameList->head->ty); 
                /* Complete type declare*/
                
                Ty_ty t = S_look(tenv, nameList->head->name);
                t->u.name.ty = ty;
            }

            for (nameList = d->u.type; nameList; nameList = nameList->tail) {
                Ty_ty t = S_look(tenv, nameList->head->name);
                if (isLoop(t)) {
                    EM_error(d->pos, "Cyclic type define exist");
                }
            }
            return Tr_noExp();

        }
        case A_functionDec: {
            A_fundecList funList;
            A_fundec funDec = NULL;
            Ty_ty resultTy = NULL;
            Ty_tyList formalTys = NULL;
            //Deal with recursive function def 

            //check if each function has an identical name
            for (funList = d->u.function; funList; funList = funList->tail) {
                for (A_fundecList l = funList->tail; l; l = l->tail) {
                    //We only need to check the function symbol
                    if(funList != l && funList->head->name == l->head->name) {
                        // @test39
                        EM_error(l->head->pos, "Two functions has same name");
                    }
                }
                //check if function has the same name with std function

                for (nameList l = stdFunList; l; l = l->next) {
                    //We only need to check the function symbol
                    if(funList->head->name == S_Symbol(l->name)) {
                        // @test39
                        EM_error(funList->head->pos, "Functions has same name with std function");
                    }
                }                
            }
            bool isCyclic = FALSE;
            if (isCyclic) {
                EM_error(d->pos, "Cyclic type define exist");
            } 

            for (funList = d->u.function; funList; funList = funList->tail) {
                funDec = funList->head;
                // check if return type void

                if (!funDec->result) {                   
                    resultTy = Ty_Void();
                } else {
                    resultTy = S_look(tenv, funDec->result);
                    if (!resultTy) {
                        EM_error(funDec->pos, "Undefined type for return type");
                    }
                }

                formalTys = makeFormalTyList(tenv, funDec->params);
                Temp_label funLabel = Temp_newlabel();
				Tr_level funLevel = Tr_newLevel(level, funLabel, makeFormalsBoolList(funDec->params));
                S_enter(venv, funDec->name, E_FunEntry(funLevel, funLabel, formalTys, resultTy));
            }

            E_enventry funEntry = NULL;
            for (funList = d->u.function; funList; funList = funList->tail) {
                funDec = funList->head;
                funEntry = S_look(venv, funDec->name);
                S_beginScope(venv);
                Ty_tyList ty;
                A_fieldList l;
                Tr_accessList accessList = Tr_formals(funEntry->u.fun.level);
                for (l = funDec->params,  
                     ty = makeFormalTyList(tenv, funDec->params);
                      l; l = l->tail, ty = ty->tail, accessList = accessList->tail) {
                    S_enter(venv, l->head->name, E_VarEntry(accessList->head, ty->head));
                }

                if (!(funDec->result)) {                   
                    resultTy = Ty_Void();
                } else { //Undefined type error has been detect above
                    resultTy = S_look(tenv, funDec->result);
                }
                struct expty funExpty = transExp(level, venv, tenv, funList->head->body);                
                

                // Detect if the return type is the same as expression type
                if ( !(resultTy->kind == Ty_void && funExpty.ty->kind == Ty_void) &&
                        !isAssignTypeLegal(resultTy, funExpty.ty))
					          EM_error(funDec->body->pos, "Incorrect return type %s: expected %s",
                        "", "");
                        //S_name(funExpty.ty), S_name(resultTy));
                Tr_procEntryExit(funEntry->u.fun.level, funExpty.exp, Tr_formals(funEntry->u.fun.level));
                S_endScope(venv);
            }
            return Tr_noExp();
        }
    }    
}

Ty_ty transTy(S_table tenv, A_ty a) {
    switch(a->kind) {
        case A_nameTy:{
            Ty_ty ty = S_look(tenv, a->u.name);
            if (!ty) {
                EM_error(a->pos, "Undefined type %s",
                    S_name(a->u.name));
            }
            return Ty_Name(a->u.name, ty);
        }
        case A_recordTy: {
            Ty_fieldList fieldList = NULL;
 
            for (A_fieldList l = a->u.record; l; l = l->tail) {
                Ty_ty ty = S_look(tenv, l->head->typ);
                if (!ty) {
                    EM_error(l->head->pos, "Undefined type %s",
                        S_name(l->head->typ));
                }
                fieldList = Ty_FieldList(
                    Ty_Field(l->head->name, ty), fieldList);
            }

            //Reverse
            Ty_fieldList rList = NULL;
            while (fieldList){
                rList = Ty_FieldList(fieldList->head, rList);
                fieldList = fieldList->tail;
            }
            return Ty_Record(rList);
        }
        case A_arrayTy:{
            // char *s = S_name(a->u.array);
            Ty_ty ty = S_look(tenv, a->u.array);
            if (!ty) {
                EM_error(a->pos, "Undefined type %s",
                    S_name(a->u.array));
            }
            return Ty_Array(ty);
        }
    }
    assert(0);
    return NULL;
}

struct expty expTy(Tr_exp exp, Ty_ty ty){
    struct expty e;
    e.exp = exp;
    e.ty = ty;
    return e;
}

Ty_ty actual_ty(Ty_ty ty){
    while(ty && ty->kind == Ty_name) {
        ty = ty->u.name.ty;
    }
    return ty;
}

Ty_tyList makeFormalTyList(S_table tenv, A_fieldList paraList){
    //Iterate parameter's list and return list of types
    Ty_tyList head = NULL;
    Ty_tyList p = NULL;
    A_field field = NULL;
    Ty_ty ty = NULL;
    
    while (paraList) {
      field = paraList->head;
      ty = actual_ty(S_look(tenv, field->typ));
      if (p) {
          p->tail = Ty_TyList(ty, NULL);
          p = p->tail;
      } else { //p == NULL
          p = Ty_TyList(ty, NULL);
          head = p;
      }
      paraList = paraList->tail;
    }
    return head;
}

U_boolList makeFormalsBoolList(A_fieldList paraList) {
    U_boolList formalsList = NULL;
	for (; paraList; paraList = paraList->tail) {
        formalsList = U_BoolList(TRUE, formalsList);
	}
    // Because we assume all the parameter is escaped, so it is no need to reverse
    // //Reverse
    // p = formalsList;
    // formalsList = NULL;
    // while (p) {
    //     formalsList = U_BoolList(p->head, formalsList);
    //     p = p->tail;
    // }
	return formalsList;
}

bool isLoop(Ty_ty type)
{
    bool any = FALSE;
    Ty_ty b = type->u.name.ty;
    type->u.name.ty = NULL;
    if (b == NULL) {
        any = TRUE;
    } else if (b->kind == Ty_name) {
        any = isLoop(b);
    } else if (b->kind == Ty_array && 
        b->u.array->kind == Ty_name) {
        any = isLoop(b->u.array);
    } else {
        any = FALSE;
    }
    type->u.name.ty = b;
    return any;
}