#ifndef TOKEN_H 
#define TOKEN_H

#include <stdio.h>
#include <string_util.h>
#include <stdlib.h>

#define NUM_DATATYPE 4
#define NUM_OP 13
#define NUM_PAREN 2
#define NUM_QUOTE 2
#define NUM_BOOLVAL 2

typedef enum {
	WHITESPACE,
	ASSIGNMENT,
	DATATYPE,
	OPERATOR,
	PAREN,
	QUOTE,
	COMMA,
	NUM,
	BOOLVAL,
	RETURN,
	IDENTIFIER
} TYPE;

enum DATASUB { VOID, INT, BOOL, CHAR };
enum OPSUB { AND, OR, EQ, NEQ, LTE, GTE, LT, GT, PLUS, MINUS, MULTIPLY, DIVIDE, MODULO };
enum PARENSUB { LPAREN, RPAREN };
enum QUOTESUB { SINGLE_QUOTE, DOUBLE_QUOTE };
enum BOOLVAL { FALSE, TRUE };

typedef struct {
	const char *token_str;	
	TYPE type;
	int subtype;
} Token;

const char* const data_sub[NUM_DATATYPE];
const char* const op_sub[NUM_OP];
const char* const paren_sub[NUM_PAREN];
const char* const quote_sub[NUM_QUOTE];
const char* const boolval_sub[NUM_BOOLVAL];

Token *create_token(const char *str);
void destroy_token(Token *token);

int is_in_list(const char* const *strings, int num_in_list, const char *s);
void identify_token_type(Token *token);

int is_type(Token token, int type);
int is_subtype(Token token, int subtype);

void *create_data_packet(Token token);

#endif // TOKEN_H
