#include <stdio.h>
#include <vector>

#include "FileIO/FileReader.h"
#include "FileIO/FileWriter.h"
#include "Parser/Parser.h"
#include "Compiler/Compiler.h"
#include "LexicalAnalyzer/LexicalAnalyzer.h"

#include "Util/ErrorHandler.h"

#include "Script/Script.h"

int main() {
	Script script;
	script.readScript("res/test.ls");
	printf("===================\n");
	script.parse();
	printf("===================\n");

	std::vector<int> bytecode = script.compile();

	printf("\nBytecode: \n");
	FileWriter writer;
	writer.openFile("res/bytecode.bytels");
	for (int i = 0; i < bytecode.size(); i++) {
		writer.writeInt(bytecode[i]);
		printf("%i\n", bytecode[i]);	
	}

	return 0;
}
