#include "Script.h"

#include "FileReader.h"
#include "stdio.h"

void Script::readScript(const char *path) {
	FileReader file;
	file.openFile(path);
	char *line;
	line = file.getLine();
	Statement statement;
	while (line != NULL) {
		statement.setStatement(line);
		statement.tokenizeStatement();
		scriptStatements.push_back(statement);
		line = file.getLine();
	}
	puts("Completed Reading Script.");
	file.closeFile();
}

Node Script::compile() {
	if (scriptStatements.size() == 0) {
		perror("No script was loaded for compilation");
		return Memory();
	}
	for (int i = 0; i < scriptStatements.size(); i++) {
		return Parser::parse(
	}		
}
