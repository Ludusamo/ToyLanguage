#include <token.h>

const char * const data_sub[] = { "void", "int", "bool", "char" };
const char * const arithop_sub[] = { "+", "-", "*", "/" };
const char * const boolop_sub[] = { "==", "<=", ">=", "<", ">", "!=" };
const char * const paren_sub[] = { "(", ")" };
const char * const quote_sub[] = { "\'", "\"" };

Token *create_token(const char *str) {
	Token *t = malloc(sizeof(Token));
	t->token_str = str_copy(str);
	return t;
}

void identify_token_type(Token *token) {
	const char *s = token->token_str;
	if (s[0] <= 32) {
		token->type = WHITESPACE;
		return;
	}
	if (s[0] == '=') {
		token->type = ASSIGNMENT;
		return;
	}	
	for (int i = 0; i < NUM_DATATYPE; i++) {
		if (str_equal(data_sub[i], s)) {
			token->type = DATATYPE;
			token->subtype = i;
			return;
		}
	}	
	for (int i = 0; i < NUM_ARITHOP; i++) {
		if (str_equal(arithop_sub[i], s)) {
			token->type = ARITHOP;
			token->subtype = i;
			return;
		}
	}
	for (int i = 0; i < NUM_BOOLOP; i++) {
		if (str_equal(boolop_sub[i], s)) {
			token->type = BOOLOP;
			token->subtype = i;
			return;
		}
	}
	for (int i = 0; i < NUM_PAREN; i++) {
		if (str_equal(paren_sub[i], s)) {
			token->type = PAREN;
			token->subtype = i;
			return;
		}
	}
	for (int i = 0; i < NUM_QUOTE; i++) {
		if (str_equal(quote_sub[i], s)) {
			token->type = QUOTE;
			token->subtype = i;
			return;
		}
	}
	for (int i = 0; i < strlen(s); i++) {
		if (s[i] > 57 || s[i] < 48) break;
		if (i == strlen(s) - 1) token->type = NUM;
		return;
	}

	token->type = IDENTIFIER;
}

int is_type(Token token, int type) {
	return token.type == type;
}

int is_subtype(Token token, int subtype) {
	return token.subtype == subtype;
}
