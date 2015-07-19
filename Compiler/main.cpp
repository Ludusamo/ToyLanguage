#include "Script.h" 
#include "BitUtil.h"
#include "Parser.h"
#include "Statement.h"
#include "StringUtil.h"
#include <stdio.h>
#include "Variable.h"
#include "Token.h"
#include <vector>
#include "Command.h"
#include "Debug.h"
#include "Memory.h"
#include "FileReader.h"

int main() {
	FileReader reader;
	reader.openFile("res/test.ls");
	Statement statement;
	statement.setStatement(reader.getLine());
	statement.tokenizeStatement();
	Parser parser;
	parser.parse(statement);
	
	return 0;
}
