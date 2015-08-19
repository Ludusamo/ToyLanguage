#ifndef MEMORY_H
#define MEMORY_H

#include <vector>
#include <stdio.h>
#include "Statement.h"
#include "StringUtil.h"

#define MAX_LOCAL_VARS 255
#define MAX_ARGS 255

class Memory {
public:
	typedef struct {
		const char *id;
		int type;
	} Variable;

	typedef struct {
		const char *id;
		int returnType;
		int numArgs;
		int addr;
		Variable variables[MAX_LOCAL_VARS];
		Variable args[MAX_ARGS];
	} Function;

	Memory() {};
	~Memory() {};
	std::vector< std::vector<Variable> > variables;
	std::vector<Function> globalFunctions;

	int addGlobalFunction(Function f) {
		globalFunctions.push_back(f);
		return globalFunctions.size() - 1;
	}

	int createFunction(const char *id, int numArgs, int returnType) {
		Function func = {id, numArgs, returnType};
		globalFunctions.push_back(func);
		return globalFunctions.size() - 1;
	}

	int getFunction(const char *id) {
		for (int i = 0; i < globalFunctions.size(); i++) {
			if (StringUtil::equal(globalFunctions[i].id, id)) return i;
		}	
		return -1;
	}
	
	int createVariable(const char *id, int type, int depth) {
		Variable var = {id, type};
		variables[depth].push_back(var);
		return variables.size() - 1;
	}

	int getVariable(const char *id, int depth) {
		for (int i = 0; i < variables.size(); i++) {
			if (StringUtil::equal(variables[depth][i].id, id)) return i;
		}
		return -1;
	}
};

#endif // MEMORY_H
