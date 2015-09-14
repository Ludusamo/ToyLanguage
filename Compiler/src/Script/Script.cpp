#include "Script/Script.h"

void Script::readScript(const char *path) {
	FileReader file;
	file.openFile(path);
	char *line = file.getLine();
	while (line != NULL) {
		scriptStatements.push_back(Statement());
		scriptStatements[scriptStatements.size() - 1].calculateDepth(line);
		scriptStatements[scriptStatements.size() - 1].tokens = lex.tokenize(line);
		line = file.getLine();
	}
	printf("Completed Reading Script.\n");
	file.closeFile();
}

void Script::parse() {
	for (int i = 0; i < scriptStatements.size(); i++) {
		printf("%i\n", scriptStatements[i].depth);
	}
	parser.parse(scriptStatements);
}

std::vector<int> Script::compile() {
	return compiler.compile(scriptStatements);
}
