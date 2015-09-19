#ifndef SCRIPT_H
#define SCRIPT_H

#include "Parser/Parser.h"
#include "Compiler/Compiler.h"
#include "LexicalAnalyzer/LexicalAnalyzer.h"
#include "FileIO/FileReader.h"

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
