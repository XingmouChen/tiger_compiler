#include "absyn.h"
#include "tool.h"
#include <time.h>
#include <stdio.h>
#include <string.h>

extern FILE* yyin;
extern int yyparse();
extern int yydebug;

static int _remain = 0;
static int* remain = &_remain;

static int nodeIdx = 0;
static int idIdx = 0;
static int termIdx = 0;

static FILE* dotFile = NULL;
static char* opTable[] = {
	"PLUS", "MINUS", "TIMES", "DIVIDE", "EQ", "NEQ", "LT", "lE", "GT", "GE"
};

typedef struct myId {
    S_symbol id;
    int idx;
} *myId;

myId getMyId(S_symbol s) {
    myId i = checked_malloc(sizeof(*i));
    i->id = s;
    i->idx = idIdx++;

    return  i;
}

void print_edge(void* p_father, void* p_child, const char* labelStr) {
    if ((int*)p_child == remain) {
        _remain++;
        fprintf(dotFile, "\"%p\" -> \"%d%s\"\n", p_father, _remain, labelStr);
        fprintf(dotFile, "\"%d%s\"[label=\"%s\"]\n", _remain, labelStr, labelStr);
    }
	else if (p_child != NULL) {
		fprintf(dotFile, "\"%p\" -> \"%p\"\n", p_father, p_child);
		fprintf(dotFile, "\"%p\"[label=\"%s\"]\n", p_child, labelStr);
	}
        // p_child is a terminal
	else {
        nodeIdx++;
		fprintf(dotFile, "\"%p\" -> \"terminal%d\"\n", p_father, nodeIdx);
		fprintf(dotFile, "\"terminal%d\"[label=\"%s\"]\n", nodeIdx, labelStr);

        termIdx++;
		fprintf(dotFile, "\"terminal%d\" -> \"%d%s\"\n", nodeIdx, termIdx, hardTerm2Str(labelStr));
        fprintf(dotFile, "\"%d%s\"[label=\"%s\"]\n", termIdx, hardTerm2Str(labelStr), hardTerm2Str(labelStr));
	}
}

int parse_ast(const char* fileName) {
    if ((yyin = fopen(fileName, "r")) == NULL) {
		printf("####! Can not open file: %s\n", fileName);
        return 0;
    }
	    
    if (yyparse() != 0) {
		fclose(yyin);
		printf("####! yyparse() error!\n");
		return 0;
	}
    
    fclose(yyin);
    return 1;
}

void vis_NUM(int* node) {
    char s[100];
    sprintf(s, "%d", *node);
    print_edge(node, remain, s);
}

void vis_STR(const char* node) {
    //print_edge(node, remain, node);
}

void vis_ID(myId node) {
	print_edge(node, remain, S_name(node->id));
}

void vis_lvalue(A_var node) {
	switch (node->kind) {
		case A_simpleVar:
        {
            myId id1 = getMyId(node->u.simple);
            print_edge(node, id1, "ID");

            vis_ID(id1);
            break;
        }
		case A_fieldVar:
        {
            print_edge(node, node->u.field.var, "lvalue");
            print_edge(node, NULL, "DOT");
            myId id1 = getMyId(node->u.field.sym);
            print_edge(node, id1, "ID");

            vis_lvalue(node->u.field.var);
            vis_ID(id1);
            break;
        }
		case A_subscriptVar:
            print_edge(node, node->u.subscript.var, "lvalue");
            print_edge(node, NULL, "LBRACK");
            print_edge(node, node->u.subscript.exp, "exp");
            print_edge(node, NULL, "RBRACK");

            vis_lvalue(node->u.subscript.var);
            vis_expr(node->u.subscript.exp);
			break;
		default:	printf("####! vis_lvalue error!\n");
	}
}

void vis_exprlist(A_expList node) {
    if (node == NULL) {
        printf("####! vis_exprlist error!\n");
    }

    for (A_expList e = node; e; e = e->tail) {
        print_edge(node, e->head, "expr");
    }

    for (A_expList e = node; e; e = e->tail) {
        vis_expr(e->head);
    }
}

void vis_exprseqlist(A_expList node) {
    if (node == NULL) {
        printf("####! vis_exprseqlist error!\n");
    }

    for (A_expList e = node; e; e = e->tail) {
        print_edge(node, e->head, "expr");
    }

    for (A_expList e = node; e; e = e->tail) {
        vis_expr(e->head);
    }
}

void vis_typefield(A_field node) {
    myId id1 = getMyId(node->name);
    print_edge(node, id1, "ID");
    print_edge(node, NULL, "COLON");
    myId id2 = getMyId(node->typ);
    print_edge(node, id2, "ID");

    vis_ID(id1);
    vis_ID(id2);
}

void vis_typefields(A_fieldList node) {
    if (node == NULL) {
        printf("####! vis_typefields error!\n");
    }

    for (A_fieldList f = node; f; f = f->tail) {
        print_edge(node, f->head, "typefield");
    }

    for (A_fieldList f = node; f; f = f->tail) {
        vis_typefield(f->head);
    }
}

void vis_functiondeclaration(A_fundec node) {
    print_edge(node, NULL, "FUNCTION");
    myId id1 = getMyId(node->name);
    myId id2 = NULL;
    print_edge(node, id1, "ID");
    print_edge(node, NULL, "LPAREN");
    if (node->params != NULL) {
        print_edge(node, node->params, "typefields");
    }
    print_edge(node, NULL, "RPAREN");
    if (node->result != NULL) {
        print_edge(node, NULL, "COLON");

        id2 = getMyId(node->result);
        print_edge(node, id2, "ID");
    }
    print_edge(node, NULL, "EQ");
    print_edge(node, node->body, "expr");

    vis_ID(id1);
    if (node->params != NULL) {
        vis_typefields(node->params);
    }
    if (node->result != NULL) {
        vis_ID(id2);
    }
    vis_expr(node->body);
}


void vis_functiondeclist(A_fundecList node) {
    if (node == NULL) {
        printf("####! vis_functiondeclist error!\n");
    }

    for (A_fundecList f = node; f; f = f->tail) {
        print_edge(node, f->head, "functiondeclaration");
    }

    for (A_fundecList f = node; f; f = f->tail) {
        vis_functiondeclaration(f->head);
    }
}

void vis_type(A_ty node) {
    switch (node->kind) {
        case A_nameTy:{
            myId id1 = getMyId(node->u.name);
            print_edge(node, id1, "ID");
            vis_ID(id1);

            break;
        }
        case A_recordTy:
            print_edge(node, NULL, "LBRACE");
            if (node->u.record != NULL) {
                print_edge(node, node->u.record, "typefields");
            }
            print_edge(node, NULL, "RBRACE");

            vis_typefields(node->u.record);
            break;
        case A_arrayTy:{
            print_edge(node, NULL, "ARRAY");
            print_edge(node, NULL, "OF");
            myId id1 = getMyId(node->u.array);
            print_edge(node, id1, "ID");

            vis_ID(id1);
            break;
        }
        default:	printf("####! vis_type error!\n");
    }
}

void vis_typedeclaration(A_namety node){
    print_edge(node, NULL, "TYPE");
    myId id1 = getMyId(node->name);
    print_edge(node, id1, "ID");
    print_edge(node, node->ty, "type");

    vis_ID(id1);
    vis_type(node->ty);
}

void vis_typedeclist(A_nametyList node) {
    if (node == NULL) {
        printf("####! vis_functiondeclist error!\n");
    }

    for (A_nametyList t = node; t; t = t->tail) {
        print_edge(node, t->head, "typedeclaration");
    }

    for (A_nametyList t = node; t; t = t->tail) {
        vis_typedeclaration(t->head);
    }
}

void vis_variabledeclaration(A_variableDec *node) {
    print_edge(node, NULL, "VAR");
    myId id1 = getMyId(node->var);
    myId id2 = NULL;
    print_edge(node, id1, "ID");
    if (node->typ != NULL) {
        print_edge(node, NULL, "COLON");
        id2 = getMyId(node->typ);
        print_edge(node, id2, "ID");
    }
    print_edge(node, NULL, "ASSIGN");
    print_edge(node, node->init, "expr");

    vis_ID(id1);
    if (node->typ != NULL) {
        vis_ID(id2);
    }
    vis_expr(node->init);
}

void vis_declaration(A_dec node) {
    switch (node->kind) {
        case A_functionDec:
            print_edge(node, node->u.function, "functiondeclist");

            vis_functiondeclist(node->u.function);
            break;
        case A_typeDec:
            print_edge(node, node->u.type, "typedeclist");

            vis_typedeclist(node->u.type);
            break;
        case A_varDec:
            print_edge(node, &node->u.var, "variabledeclaration");

            vis_variabledeclaration(&node->u.var);
            break;
        default:	printf("####! vis_declaration error!\n");
    }
}

void vis_declarationlist(A_decList node) {
    if (node == NULL) {
        printf("####! vis_declarationlist error!\n");
    }

    for (A_decList d = node; d; d = d->tail) {
        print_edge(node, d->head, "declaration");
    }

    for (A_decList d = node; d; d = d->tail) {
        vis_declaration(d->head);
    }
}

void vis_efield(A_efield node) {
    myId id1 = getMyId(node->name);
    print_edge(node, id1, "ID");
    print_edge(node, NULL, "EQ");
    print_edge(node, node->exp, "expr");

    vis_ID(id1);
    vis_expr(node->exp);
}

void vis_fieldlist(A_efieldList node) {
    if (node == NULL) {
        printf("####! vis_fieldlist error!\n");
    }

    for (A_efieldList ef = node; ef; ef = ef->tail) {
        print_edge(node, ef->head, "efield");
    }

    for (A_efieldList ef = node; ef; ef = ef->tail) {
        vis_efield(ef->head);
    }
}

void vis_expr(A_exp node) {

	switch(node->kind) {
		case A_varExp:
			print_edge(node, node->u.var, "lvalue");
			vis_lvalue(node->u.var);
			break;
		case A_nilExp:
			print_edge(node, NULL, "NIL");
			break;
		case A_intExp:
			print_edge(node, &node->u.intt, "NUM");

			vis_NUM(&node->u.intt);
			break;
		case A_stringExp:
			print_edge(node, node->u.stringg, "STR");
			vis_STR(node->u.stringg);
			break;
		case A_callExp:
			if (node->u.call.args != NULL) {
                myId id1 = getMyId(node->u.call.func);
                print_edge(node, id1, "ID");
				print_edge(node, NULL, "LPAREN");
				print_edge(node, node->u.call.args, "exprlist");
				print_edge(node, NULL, "RPAREN");

				vis_ID(id1);
				vis_exprlist(node->u.call.args);
			}
			else {
                myId id1 = getMyId(node->u.call.func);
                print_edge(node, id1, "ID");
				print_edge(node, NULL, "LPAREN");
				print_edge(node, NULL, "RPAREN");

				vis_ID(id1);
			}
			break;
		case A_recordExp:
			if (node->u.record.fields != NULL) {
                myId id1 = getMyId(node->u.record.typ);
                print_edge(node, id1, "ID");
				print_edge(node, NULL, "LBRACE");
				print_edge(node, node->u.record.fields, "fieldlist");
				print_edge(node, NULL, "RBRACE");

				vis_ID(id1);
				vis_fieldlist(node->u.record.fields);
			}
			else {
                myId id1 = getMyId(node->u.record.typ);
                print_edge(node, id1, "ID");
				print_edge(node, NULL, "LBRACE");
				print_edge(node, NULL, "RBRACE");

				vis_ID(id1);
			}
			break;
		case A_seqExp:
			if (node->u.seq != NULL) {
				print_edge(node, NULL, "LPAREN");
				print_edge(node, node->u.seq, "exprseqlist");
				print_edge(node, NULL, "RPAREN");

				vis_exprseqlist(node->u.seq);
			}
			else {
				print_edge(node, NULL, "LPAREN");
				print_edge(node, NULL, "RPAREN");
			}
			break;
		case A_opExp:
			print_edge(node, node->u.op.left, "expr");
			print_edge(node, NULL, opTable[node->u.op.oper]);
			print_edge(node, node->u.op.right, "expr");

			vis_expr(node->u.op.left);
			vis_expr(node->u.op.right);
			break;
		case A_assignExp:
			print_edge(node, node->u.assign.var, "lvalue");
			print_edge(node, NULL, "ASSIGN");
			print_edge(node, node->u.assign.exp, "expr");
			break;
		case A_ifExp:
			print_edge(node, NULL, "IF");
			print_edge(node, node->u.iff.test, "expr");
			print_edge(node, NULL, "THEN");
			print_edge(node, node->u.iff.then, "expr");

			if (node->u.iff.elsee != NULL) {
				print_edge(node, NULL, "ELSE");
				print_edge(node, node->u.iff.elsee, "expr");
			}

			vis_expr(node->u.iff.test);
			vis_expr(node->u.iff.then);
			if (node->u.iff.elsee != NULL) {
				vis_expr(node->u.iff.elsee);
			}
			break;
		case A_whileExp:
			print_edge(node, NULL, "WHILE");
			print_edge(node, node->u.whilee.test, "expr");
			print_edge(node, NULL, "DO");
			print_edge(node, node->u.whilee.body, "expr");

			vis_expr(node->u.whilee.test);
			vis_expr(node->u.whilee.body);
			break;
		case A_forExp:
			print_edge(node, NULL, "FOR");
            myId id1 = getMyId(node->u.forr.var);
            print_edge(node, id1, "ID");
			print_edge(node, NULL, "ASSIGN");
			print_edge(node, node->u.forr.lo, "expr");
			print_edge(node, NULL, "TO");
			print_edge(node, node->u.forr.hi, "expr");
			print_edge(node, NULL, "DO");
			print_edge(node, node->u.forr.body, "expr");

			vis_ID(id1);
			vis_expr(node->u.forr.lo);
			vis_expr(node->u.forr.hi);
			vis_expr(node->u.forr.body);
			break;
		case A_breakExp:
			print_edge(node, NULL, "BREAK");
			break;
		case A_letExp:
			print_edge(node, NULL, "LET");
			print_edge(node, node->u.let.decs, "declarationlist");
			print_edge(node, NULL, "IN");
			if (node->u.let.body != NULL) {
				print_edge(node, node->u.let.body, "exprseqlist");
			}
			print_edge(node, NULL, "END");

			vis_declarationlist(node->u.let.decs);
			if (node->u.let.body != NULL) {
				vis_expr(node->u.let.body);
			}
			break;
		case A_arrayExp:
        {
            myId id1 = getMyId(node->u.array.typ);
            print_edge(node, id1, "ID");
            print_edge(node, NULL, "LBRACK");
            print_edge(node, node->u.array.size, "expr");
            print_edge(node, NULL, "RBRACK");
            print_edge(node, NULL, "OF");
            print_edge(node, node->u.array.init, "expr");

            vis_ID(id1);
            vis_expr(node->u.array.size);
            vis_expr(node->u.array.init);
            break;
        }
		default:	printf("####! vis_exp error!\n");
	}
}

int main(int argc, char* argv[]) {
	yydebug = 0;

	if (argc < 2) {
		printf("####! Too little arguments!\n");
		return -1;
	}

	if (parse_ast(argv[1])) {
		//printf("Parsing Succeed !!!\n");
		dotFile = fopen("ast.dot", "w");
        //dotFile = stdout;
		fprintf(dotFile, "digraph ast {\n");
		fprintf(dotFile, "\"%p\" [label=\"root\"]\n", absyn_root);
		vis_expr(absyn_root);
		fprintf(dotFile, "}\n");
		fclose(dotFile);
	}
}