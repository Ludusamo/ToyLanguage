#ifndef MEMORY_H
#define MEMORY_H

#include <vector>
#include <stdio.h>
#include "Statement.h"

class Memory {
public:
	typedef struct {
		char *id;
		int type;
	} Variable;

	Memory() {};
	~Memory() {};
	std::vector<Variable> variables;
	
	int createVariable(const char *id, int type) {
		Variable var = {(char*)id, type};
		variables.push_back(var);
		return variables.size() - 1;
	}

	int getVariable(const char *id) {
		for (int i = 0; i < variables.size(); i++) {
			if (variables[i].id == (char*)id) return i;
		}
		return -1;
	}
};

#endif // MEMORY_H
