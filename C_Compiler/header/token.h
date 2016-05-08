#ifndef TOKEN_H 
#define TOKEN_H

#include <stdio.h>
#include <string_util.h>
#include <stdlib.h>

#define NUM_DATATYPE 4
#define NUM_ARITHOP 4
#define NUM_BOOLOP 6
#define NUM_PAREN 2
#define NUM_QUOTE 2

typedef enum {
	WHITESPACE,
	ASSIGNMENT,
	DATATYPE,
	ARITHOP,
	BOOLOP,
	PAREN,
	QUOTE,
	NUM,
	IDENTIFIER
} TYPE;

enum DATASUB { VOID, INT, BOOL, CHAR };
enum ARITHOPSUB { PLUS, MINUS, MULTIPLY, DIVIDE };
enum BOOLOPSUB { EQ, LTE, GTE, LT, GT, NEQ };
enum PARENSUB { LPAREN, RPAREN };
enum QUOTESUB { SINGLE_QUOTE, DOUBLE_QUOTE };

typedef struct {
	const char *token_str;	
	TYPE type;
	int subtype;
} Token;

const char* const data_sub[NUM_DATATYPE];
const char* const arithop_sub[NUM_ARITHOP];
const char* const boolop_sub[NUM_BOOLOP];
const char* const paren_sub[NUM_BOOLOP];
const char* const quote_sub[NUM_BOOLOP];

Token *create_token(const char *str);
void destroy_token(Token *token);

void identify_token_type(Token *token);

#endif // TOKEN_H
