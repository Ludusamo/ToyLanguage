#include "Variable.h"

#include <stdio.h>

#include "StringUtil.h"

char *Variable::operation(const char *val1, const char *val2, VAR_TYPE varType, Token::SUB_OPERATOR type) {
	if (varType == INT) {
		switch (type) {
		case Token::ADD:
			return StringUtil::itoa(StringUtil::atoi(val1) + StringUtil::atoi(val2));
		case Token::SUB:
			return StringUtil::itoa(StringUtil::atoi(val1) - StringUtil::atoi(val2));
		case Token::MUL:
			return StringUtil::itoa(StringUtil::atoi(val1) * StringUtil::atoi(val2));
		case Token::DIV:
			return StringUtil::itoa(StringUtil::atoi(val1) / StringUtil::atoi(val2));
		}
	} else if (varType == STRING) {
		if (type != Token::ADD) {
			printf("Invalid Operation: Type STRING\n");
			return NULL;
		}
		return StringUtil::add(val1, val2);
	} else if (varType == BOOL) {
		printf("Invalid Operation: Type BOOL\n");
		return NULL;
	} else {
		printf("Invalid Operation: UNKNOWN ERROR\n");
		return NULL;
	}
}

bool Variable::comparator(const char *val1, const char *val2, VAR_TYPE varType, Token::SUB_OPERATOR type) {
	if (varType == INT) {
		switch (type) {
		case Token::EQ:
			return StringUtil::equal(val1, val2);
		case Token::NEQ:
			return !StringUtil::equal(val1, val2);
		case Token::LT:
			return (StringUtil::atoi(val1) < StringUtil::atoi(val2)); 
		case Token::GT:
			return (StringUtil::atoi(val1) > StringUtil::atoi(val2)); 
		case Token::LTEQ:
			return (StringUtil::atoi(val1) <= StringUtil::atoi(val2)); 
		case Token::GTEQ:
			return (StringUtil::atoi(val1) >= StringUtil::atoi(val2)); 
		}
	} else if (varType == STRING) {
		if (type != Token::EQ && type != Token::NEQ) {
			printf("Invalid Comparator: Type STRING\n");
			return NULL;
		}
		if (type == Token::EQ) return StringUtil::equal(val1, val2);
		if (type == Token::NEQ) return !StringUtil::equal(val1, val2);
	} else if (varType == BOOL) {
 		if (type != Token::EQ && type != Token::NEQ) {
			printf("Invalid Comparator: Type BOOL\n");
			return NULL;
		}
		if (type == Token::EQ) return StringUtil::equal(val1, val2);
		if (type == Token::NEQ) return !StringUtil::equal(val1, val2);
	} else {
		printf("Invalid Comparator: UNKNOWN ERROR\n");
		return NULL;
	}
}
