#include <token.h>

const char * const data_sub[] = { "void", "int", "bool", "char" };
const char * const op_sub[] = { "&&", "||", "==", "!=", "<=", ">=", "<", ">", "|", "^", "&", "<<", ">>", "+", "-", "*", "/", "%" };
const char * const paren_sub[] = { "(", ")" };
const char * const boolval_sub[] = { "false", "true" };
const char * const control_sub[] = { "if", "else", "while", "for" };
const char * const eos_sub[] = { ";", "\n" };

Token *create_token(const char *str) {
	Token *t = malloc(sizeof(Token));
	t->token_str = str_copy(str);
	return t;
}

void destroy_token(Token *token) {
	token->token_str = 0;
	free((char*)token->token_str);
	token = 0;
	free(token);
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
	if ((list_index = is_in_list(data_sub, NUM_DATATYPE, s)) != -1) {
		token->type = DATATYPE;
		token->subtype = list_index;
		return;
	} else if ((list_index = is_in_list(op_sub, NUM_OP, s)) != -1) {
		token->type = OPERATOR;
		token->subtype = list_index;
		return;
	} else if (s[0] == '=') {
		token->type = ASSIGNMENT;
		return;
	} else if ((list_index = is_in_list(paren_sub, NUM_PAREN, s)) != -1) {
		token->type = PAREN;
		token->subtype = list_index;
		return;
	} else if (s[0] == '\'') {
		token->type = CHAR_LITERAL;
		return;
	} else if (s[0] == '\"') {
		token->type = STRING_LITERAL;
		return;
	} else if (str_equal(",", s)) {
		token->type = COMMA;
		return;
	} else if ((list_index = is_in_list(boolval_sub, NUM_BOOLVAL, s)) != -1) {
		token->type = BOOLVAL;
		token->subtype = list_index;
		return;
	} else if ((list_index = is_in_list(control_sub, NUM_CONTROL, s)) != -1) {
		token->type = CONTROL;
		token->subtype = list_index;	
		return;
	} else if ((list_index = is_in_list(eos_sub, NUM_EOS, s)) != - 1) {
		token->type = EOS;
		token->subtype = list_index;
		return;
	} else if (str_equal("return", s)) {
		token->type = RETURN;
		return;
	} else if (str_equal("print", s)) { // TODO: REMOVE
		token->type = PRINT;
		return;
	}
	for (int i = 0; i < strlen(s); i++) {
		if (s[i] > 57 || s[i] < 48) break;
		if (i == strlen(s) - 1) {
			token->type = NUM;
			return;
		}
	}

	token->type = IDENTIFIER;
}

int is_type(Token token, int type) {
	return token.type == type;
}

int is_subtype(Token token, int subtype) {
	return token.subtype == subtype;
}

void *create_data_packet(Token token) {
	if (is_type(token, NUM)) {
		int *num = malloc(sizeof(int));
		*num = atoi(token.token_str);
		return (void*) num;
	} else if (is_type(token, BOOLVAL)) {
		int *bool_val = malloc(sizeof(int));
		*bool_val = token.subtype;
		return (void*) bool_val;
	} else if (is_type(token, CHAR_LITERAL)) {
		int *char_val = malloc(sizeof(int));
		*char_val = (int) identify_char_literal(token);
		return (void*) char_val;
	}
	return 0;
}

char identify_char_literal(Token char_token) {
	const char *char_str = char_token.token_str;
	char character = 0;
	if (char_str[1] == '\\') {
		switch (char_str[2]) {
		case '\'':
			character = '\'';
			break;
		case '\"':
			character = '\"';
			break;
		case '\\':
			character = '\\';
			break;
		case 'n':
			character = '\n';
			break;
		case 'r':
			character = '\r';
			break;
		case 't':
			character = '\t';
			break;
		case 'b':
			character = '\b';
			break;
		case 'f':
			character = '\f';
			break;
		case '0':
			character = '\0';
			break;
		}
	} else {
		character = char_str[1];
	}
	return character;
}
