#include "FileReader.h" 
#include "BitUtil.h"
#include "Statement.h"

int main() {
	FileReader file;
	file.openFile("res/test.ls");
	char *line = file.getLine();
	Statement statement;
	statement.setStatement(line);
	statement.tokenizeStatement();
	printf("%d\n", statement.depth);
	
	file.closeFile();
	return 0;
}
