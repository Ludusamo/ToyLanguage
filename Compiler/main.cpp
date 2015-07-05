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
	/*FileReader reader;
	reader.openFile("res/test.ls");
	Statement statement;
	statement.setStatement(reader.getLine());
	statement.tokenizeStatement();
	Parser parser;
	parser.parse(statement);*/
	
	Memory mem;
	std::vector<Command*> commands;

	CreateVariableCommand vc1(Variable::INT, "x", 0);
	commands.push_back(&vc1);

	SetVariableValueCommand sv1("x", "10");
	commands.push_back(&sv1);

	CreateVariableCommand vc2(Variable::INT, "y", 0);
	commands.push_back(&vc2);

	SetVariableValueCommand sv2("y", "20");
	commands.push_back(&sv2);

	OperationCommand op1("x", "y", Token::ADD);	
	commands.push_back(&op1);

	for (int i = 0; i < commands.size(); i++) {
		commands[i]->execute(mem);
	}
	return 0;
}
