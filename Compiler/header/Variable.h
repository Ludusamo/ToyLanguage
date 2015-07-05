#ifndef VARIABLE_H
#define VARIABLE_H

#include "Token.h"

class Variable {
public:
	~Variable() {};
	enum VAR_TYPE { INT, STRING, BOOL };
	char *identifier;

	void setIdentifier(const char *id) { this->identifier = (char *) id; };
	void setType(VAR_TYPE type) { this->type = type; };
	void assignValue(const char *value) { this->value = (char *) value; };
	char* getValue() { return value; };

	static char *operation(const char *val1, const char *val2, VAR_TYPE varType, Token::SUB_OPERATOR type);
	static bool comparator(const char *val1, const char *val2, VAR_TYPE varType, Token::SUB_OPERATOR type);

	VAR_TYPE type;
private:
	char *value;
};

#endif // VARIABLE_H
