#ifndef SCRIPT_H
#define SCRIPT_H

#include <vector>

#include "Statement.h"
#include "Parser.h"
#include "Compiler.h"
#include "Parser.h"
#include "LexicalAnalyzer/LexicalAnalyzer.h"
#include "FileIO/FileReader.h"
#include "stdio.h"

class Script {
public:		
	void readScript(const char *path);
	void tokenize();
	void parse();
	std::vector<int> compile();
private:
	std::vector<Statement> scriptStatements;
	LexicalAnalyzer lex;
	Parser parser;
	Compiler compiler;
};

#endif // SCRIPT_H
