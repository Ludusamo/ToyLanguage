#ifndef COMMAND_H
#define COMMAND_H

#include "Program.h"
#include "Variable.h"
#include "Token.h"

class Command {
public:
	Command() {};
	virtual ~Command() {};
	virtual void execute(Program &program) = 0;		
};

class CreateVariableCommand : public Command {
public:
	Variable::VAR_TYPE type;
	char *id, *value;
	int depth;
	CreateVariableCommand(Variable::VAR_TYPE type, const char *id, const char *value, int depth) {
		this->type = type;
		this->id = (char *) id;
		this->value = (char *) value;
		this->depth = depth;
	};

	void execute(Program &program) {
		program.createVariable(type, id, value, depth);
	};
};

class OperationCommand : public Command {
public:
	char *var1, *var2;
	Token::SUB_OPERATOR op_type;

	OperationCommand(const char *var1, const char *var2, Token::SUB_OPERATOR op_type) {
		this->var1 = (char *) var1;
		this->var2 = (char *) var2;
		this->op_type = op_type;		
	};

	void execute(Program &program) {
		program.operation(var1, var2, op_type);	
	};
};

class ComparatorCommand : public Command {
public:
	char *var1, *var2;
	Token::SUB_OPERATOR op_type;

	ComparatorCommand(const char *var1, const char *var2, Token::SUB_OPERATOR op_type) {
		this->var1 = (char *) var1;
		this->var2 = (char *) var2;
		this->op_type = op_type;		
	};

	void execute(Program &program) {
		program.comparator(var1, var2, op_type);	
	};
};

#endif // COMMAND_H
