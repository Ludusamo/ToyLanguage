#include <stdio.h>
#include <vector>

#include "FileReader.h"
#include "Statement.h"
#include "Parser.h"
#include "Compiler.h"
#include "LexicalAnalyzer/LexicalAnalyzer.h"

#include "ErrorHandler.h"

#include "Script.h"

int main() {
	Script script;
	script.readScript("res/test.ls");

	script.parse();

	printf("===================\n");

	std::vector<int> bytecode = script.compile();

	printf("\nBytecode: \n");
	for (int i = 0; i < bytecode.size(); i++) {
		printf("%i\n", bytecode[i]);	
	}

	return 0;
}
