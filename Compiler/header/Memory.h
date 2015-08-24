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
		std::vector< std::vector<Variable> > bufferVariables;
		int argTypes[MAX_ARGS];
	} Function;

	Memory() {
		numLocalVars = 0;
		for (int i = 0; i < MAX_DEPTH; i++) {
			std::vector<Variable> v;
			variables.push_back(v);
		}	
	};
	~Memory() {};
	std::vector< std::vector<Variable> > variables;
	std::vector<Function> globalFunctions;

	int numLocalVars;

	int popVariableLayers(int currentDepth, int previousDepth) {
		int initialNumLocalVars = numLocalVars;
		for (int i = currentDepth; i < previousDepth; i++) {
			numLocalVars -= variables[i + 1].size();
			variables[i + 1].clear();
		}
		return initialNumLocalVars - numLocalVars;
	}

	void returnVariables(const char *id) {
		variables = globalFunctions[getFunction(id)].bufferVariables;
	}
	
	void clearVariablesForFunction() {
		popVariableLayers(1, MAX_DEPTH);
	}

	int addGlobalFunction(Function f) {
		f.bufferVariables = variables;
		globalFunctions.push_back(f);
		clearVariablesForFunction();
		return globalFunctions.size() - 1;
	}

	int createFunction(const char *id, int numArgs, int returnType) {
		Function func = {id, numArgs, returnType};
		func.bufferVariables = variables;
		globalFunctions.push_back(func);
		return globalFunctions.size() - 1;
	}

	int getFunction(const char *id) {
		for (int i = 0; i < globalFunctions.size(); i++) {
			if (StringUtil::equal(globalFunctions[i].id, id)) return i;
		}	
		return -1;
	}

	int addArgument(Function &f, const char *id, int type) {
		f.argTypes[f.numArgs] = type;
		f.numArgs++;
		Variable var = {id, type, -f.numArgs - 2};
		variables[1].push_back(var);
		return var.memAddr;
	}
	
	int createVariable(const char *id, int type, int depth) {
		int memAddr;
		if (depth > 0) {
			numLocalVars++;
			memAddr = numLocalVars;
		} else memAddr = variables[0].size();
		Variable var = {id, type, memAddr};
		variables[depth].push_back(var);
		return var.memAddr;
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

	bool isLocalVariable(const char *id, int depth) {
		for (int i = 0; i < variables[0].size(); i++) {
			if (StringUtil::equal(variables[0][i].id, id)) return false;
		}
		return true;
	}
};

#endif // MEMORY_H
