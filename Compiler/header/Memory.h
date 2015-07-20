#ifndef MEMORY_H
#define MEMORY_H

#include <vector>
#include <stdio.h>
#include "Statement.h"

class Memory {
public:
	Memory() {};
	~Memory() {};
	std::vector<char*> variables;
	
	int createVariable(const char *id) {
		variables.push_back((char*)id);
		return variables.size() - 1;
	}
	int getVariable(const char *id) {
		for (int i = 0; i < variables.size(); i++) {
			if (variables[i] == (char*)id) return i;
		}
	}
};

#endif // MEMORY_H
