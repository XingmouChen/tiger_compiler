#include <string.h>
#include "absyn.h"

int global_line_num = 1;
int global_column_num = 1;
int global_pos = 0;

extern char* yytext;

void pos(int isNewline, int length) {
	global_pos += length;
	if (isNewline) {
		global_line_num += 1;
		global_column_num = 0;
	}
	else {
		global_column_num += length;
	}
}

void myerror(const char* msg) {

}

const char* hardTerm2Str(const char* termName) {
	if (strcmp(termName, "NIL") == 0) {
		return "nil";
	}
	else if (strcmp(termName, "DOT") == 0) {
		return ".";
	}
	else if (strcmp(termName, "ASSIGN") == 0) {
		return ":=";
	}
	else if (strcmp(termName, "IF") == 0) {
		return "if";
	}
	else if (strcmp(termName, "THEN") == 0) {
		return "then";
	}
	else if (strcmp(termName, "ELSE") == 0) {
		return "else";
	}
	else if (strcmp(termName, "WHILE") == 0) {
		return "while";
	}
	else if (strcmp(termName, "DO") == 0) {
		return "do";
	}
	else if (strcmp(termName, "FOR") == 0) {
		return "for";
	}
	else if (strcmp(termName, "TO") == 0) {
		return "to";
	}
	else if (strcmp(termName, "BREAK") == 0) {
		return "break";
	}
	else if (strcmp(termName, "LET") == 0) {
		return "let";
	}
	else if (strcmp(termName, "IN") == 0) {
		return "in";
	}
	else if (strcmp(termName, "END") == 0) {
		return "end";
	}
    else if (strcmp(termName, "FUNCTION") == 0) {
        return "function";
    }
    else if (strcmp(termName, "COLON") == 0) {
        return ":";
    }
    else if (strcmp(termName, "TYPE") == 0) {
        return "type";
    }
    else if (strcmp(termName, "ARRAY") == 0) {
        return "array";
    }
    else if (strcmp(termName, "OF") == 0) {
        return "of";
    }
    else if (strcmp(termName, "VAR") == 0) {
        return "var";
    }
	else if (strcmp(termName, "LPAREN") == 0) {
		return "(";
	}
	else if (strcmp(termName, "RPAREN") == 0) {
		return ")";
	}
	else if (strcmp(termName, "LBRACE") == 0) {
		return "{";
	}
	else if (strcmp(termName, "RBRACE") == 0) {
		return "}";
	}
	else if (strcmp(termName, "LBRACK") == 0) {
		return "[";
	}
	else if (strcmp(termName, "RBRACK") == 0) {
		return "]";
	}
	else if (strcmp(termName, "PLUS") == 0) {
		return "+";
	}
	else if (strcmp(termName, "MINUS") == 0) {
		return "-";
	}
	else if (strcmp(termName, "TIMES") == 0) {
		return "*";
	}
	else if (strcmp(termName, "DIVIDE") == 0) {
		return "/";
	}
	else if (strcmp(termName, "EQ") == 0) {
		return "=";
	}
	else if (strcmp(termName, "LT") == 0) {
		return "<";
	}
	else if (strcmp(termName, "LE") == 0) {
		return "<=";
	}
	else if (strcmp(termName, "GT") == 0) {
		return ">";
	}
	else if (strcmp(termName, "GE") == 0) {
		return ">=";
	}
	else if (strcmp(termName, "NEQ") == 0) {
		return "<>";
	}
}