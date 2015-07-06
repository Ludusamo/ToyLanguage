#ifndef PROGRAM_H
#define PROGRAM_H

#include <vector>
#include <stdio.h>
#include "Statement.h"
#include "Variable.h"

#define MAX_DEPTH 20

class Memory {
public:
	Memory() { variables.resize(MAX_DEPTH); };
	~Memory() {};
	std::vector< std::vector<Variable> > variables;
	
	void createVariable(Variable::VAR_TYPE type, const char *id, int depth);
	void setValue(const char *id, const char *value);
	char *operation(const char *id1, const char *id2, Token::SUB_OPERATOR type);
	bool comparator(const char *id1, const char *id2, Token::SUB_OPERATOR type);
	Variable *getVariable(const char *id);
};

#endif // PROGRAM_H