#include <token.h>

const char * const data_sub[] = { "void", "int", "bool", "char" };
const char * const arithop_sub[] = { "+", "-", "*", "/", "%" };
const char * const boolop_sub[] = { "==", "<=", ">=", "<", ">", "!=" };
const char * const paren_sub[] = { "(", ")" };
const char * const quote_sub[] = { "\'", "\"" };
const char * const boolval_sub[] = { "false", "true" };

Token *create_token(const char *str) {
	Token *t = malloc(sizeof(Token));
	t->token_str = str_copy(str);
	return t;
}

int is_in_list(const char* const *strings, int num_in_list, const char *s) {
	for (int i = 0; i < num_in_list; i++) {
		if (str_equal(strings[i], s)) {
			return i;
		}
	}
	return -1;
}

void identify_token_type(Token *token) {
	int list_index = -1;
	const char *s = token->token_str;
	if (s[0] <= 32) {
		token->type = WHITESPACE;
		return;
	} else if (s[0] == '=') {
		token->type = ASSIGNMENT;
		return;
	} else if ((list_index = is_in_list(data_sub, NUM_DATATYPE, s)) != -1) {
		token->type = DATATYPE;
		token->subtype = list_index;
		return;
	} else if ((list_index = is_in_list(arithop_sub, NUM_ARITHOP, s)) != -1) {
		token->type = ARITHOP;
		token->subtype = list_index;
		return;
	} else if ((list_index = is_in_list(boolop_sub, NUM_BOOLOP, s)) != -1) {
		token->type = BOOLOP;
		token->subtype = list_index;
		return;
	} else if ((list_index = is_in_list(paren_sub, NUM_PAREN, s)) != -1) {
		token->type = PAREN;
		token->subtype = list_index;
		return;
	} else if ((list_index = is_in_list(quote_sub, NUM_QUOTE, s)) != -1) {
		token->type = QUOTE;
		token->subtype = list_index;
	} else if (str_equal(",", s)) {
		token->type = COMMA;
		return;
	} else if ((list_index = is_in_list(boolval_sub, NUM_BOOLVAL, s)) != -1) {
		token->type = BOOLVAL;
		token->subtype = list_index;
		return;
	} else if (str_equal("return", s)) {
		token->type = RETURN;
		return;
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
