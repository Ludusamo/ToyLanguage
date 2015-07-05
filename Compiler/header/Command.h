#ifndef COMMAND_H
#define COMMAND_H

#include "Memory.h"
#include "Variable.h"
#include "Token.h"

class Command {
public:
	Command() {};
	virtual ~Command() {};
	virtual void execute(Memory &mem) = 0;		
};

class CreateVariableCommand : public Command {
public:
	Variable::VAR_TYPE type;
	char *id, *value;
	int depth;
	CreateVariableCommand(Variable::VAR_TYPE type, const char *id, int depth) {
		this->type = type;
		this->id = (char *) id;
		this->depth = depth;
	};

	void execute(Memory &mem) {
		mem.createVariable(type, id, depth);
	};
};

class SetVariableValueCommand : public Command {
public:
	char *id, *value;

	SetVariableValueCommand(const char *id, const char *value) {
		this->id = (char *) id;
		this->value = (char *) value;
	};

	int execute(Memory &mem) {
		mem.setValue(id, value);
		return 0;
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

	int execute(Memory &mem) {
		mem.operation(var1, var2, op_type);	
		return 0;
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

	int execute(Memory &mem) {
		if (mem.comparator(var1, var2, op_type)) return 0;
		return 1;
	};
};

#endif // COMMAND_H
