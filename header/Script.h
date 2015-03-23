#ifndef SCRIPT_H
#define SCRIPT_H

#include <vector>

#include "Statement.h"
#include "Program.h"
#include "Parser.h"

class Script {
public:		
	void readScript(const char *path);
	Program compile();
private:
	std::vector<Statement> scriptStatements;
	Parser parser;
};

#endif // SCRIPT_H
