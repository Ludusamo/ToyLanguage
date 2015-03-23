#ifndef PROGRAM_H
#define PROGRAM_H

#include <vector>
#include <stdio.h>
#include "Statement.h"
#include "Variable.h"

#define MAX_DEPTH 20

class Program {
public:
	Program() { variables.resize(MAX_DEPTH); };
	~Program() {};
	std::vector< std::vector<Variable> > variables;
	
	void createVariable(Variable::VAR_TYPE type, const char *id, const char *value, int depth);
	char *operation(const char *id1, const char *id2, Token::SUB_OPERATOR type);
	bool comparator(const char *id1, const char *id2, Token::SUB_OPERATOR type);

	void execute();
};

#endif // PROGRAM_H
