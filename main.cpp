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
#include "Program.h"

int main() {
	/*Statement statement;
	//statement.setStatement((char *) "int test");
	statement.tokenizeStatement();
	Parser parser;
	parser.parse(statement);*/
	
	/*Program program;
	program.execute();*/

	Program program;
	std::vector<Command*> commands;

	CreateVariableCommand vc1(Variable::INT, "x", "10", 0);
	commands.push_back(&vc1);

	CreateVariableCommand vc2(Variable::INT, "y", "20", 0);
	commands.push_back(&vc2);

	OperationCommand op1("x", "y", Token::ADD);	
	commands.push_back(&op1);

	for (int i = 0; i < commands.size(); i++) {
		commands[i]->execute(program);
	}
	return 0;
}
