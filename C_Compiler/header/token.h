#ifndef TOKEN_H 
#define TOKEN_H

#include <stdio.h>
#include <string_util.h>
#include <stdlib.h>
#include <ctype.h>

#define NUM_DATATYPE 4
#define NUM_OP 16
#define NUM_PAREN 2
#define NUM_BOOLVAL 2
#define NUM_CONTROL 4
#define NUM_EOS 2

typedef enum {
	WHITESPACE,
	ASSIGNMENT,
	DATATYPE,
	OPERATOR,
	PAREN,
	COMMA,
	NUM,
	BOOLVAL,
	CHAR_LITERAL,
	STRING_LITERAL,
	CONTROL,
	RETURN,
	EOS,
	IDENTIFIER,
	PRINT // TODO: REMOVE
} TYPE;

enum DATASUB { VOID, INT, BOOL, CHAR };
enum OPSUB { AND, OR, EQ, NEQ, LTE, GTE, LT, GT, PLUS, MINUS, MULTIPLY, DIVIDE, MODULO, BITAND, BITXOR, BITOR };
enum PARENSUB { LPAREN, RPAREN };
enum BOOLVAL { FALSE, TRUE };
enum CONTROL { IF, ELSE, WHILE, FOR };
enum EOS { SEMICOLON, NEWLINE };

typedef struct {
	const char *token_str;	
	TYPE type;
	int subtype;
} Token;

const char* const data_sub[NUM_DATATYPE];
const char* const op_sub[NUM_OP];
const char* const paren_sub[NUM_PAREN];
const char* const boolval_sub[NUM_BOOLVAL];
const char* const control_sub[NUM_CONTROL];
const char* const eos_sub[NUM_EOS];

Token *create_token(const char *str);
void destroy_token(Token *token);

int is_in_list(const char* const *strings, int num_in_list, const char *s);
void identify_token_type(Token *token);

int is_type(Token token, int type);
int is_subtype(Token token, int subtype);

void *create_data_packet(Token token);

char identify_char_literal(Token char_token);

#endif // TOKEN_H
