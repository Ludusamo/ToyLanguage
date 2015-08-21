#ifndef MEMORY_H
#define MEMORY_H

#include <vector>
#include <stdio.h>
#include "Statement.h"
#include "StringUtil.h"

#define MAX_DEPTH 255
#define MAX_LOCAL_VARS 255
#define MAX_ARGS 255

class Memory {
public:
	typedef struct {
		const char *id;
		int type;
		int memAddr;
	} Variable;

	typedef struct {
		const char *id;
		int returnType;
		int numArgs;
		int addr;
		std::vector< std::vector<Variable> > variables;
		Variable args[MAX_ARGS];
	} Function;

	Memory() {
		numVariables = 0;
		for (int i = 0; i < MAX_DEPTH; i++) {
			std::vector<Variable> v;
			variables.push_back(v);
		}	
	};
	~Memory() {};
	std::vector< std::vector<Variable> > variables;
	std::vector<Function> globalFunctions;

	int numVariables;

	void popVariableLayers(int currentDepth, int previousDepth) {
		for (int i = currentDepth; i < previousDepth; i++) {
			variables[i + 1].clear();
		}
	}

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
		Variable var = {id, type, numVariables};
		variables[depth].push_back(var);
		numVariables++;
		return numVariables - 1;
	}

	int getVariable(const char *id, int depth) {
		for (int i = depth; i >= 0; i--) {
			for (int j = 0; j < variables[i].size(); j++) {
				if (StringUtil::equal(variables[i][j].id, id)) 
					return variables[i][j].memAddr;
			}
		}
		return -1;
	}

	int getVariableType(const char *id, int depth) {
		for (int i = depth; i >= 0; i--) {
			for (int j = 0; j < variables[i].size(); j++) {
				if (StringUtil::equal(variables[i][j].id, id)) {
					return variables[i][j].type;
				}
			}
		}
		return -1;
	}
};

#endif // MEMORY_H
