#ifndef NODE_H
#define NODE_H

#include <vector>
#include "Command.h"

class Node {
public:
	virtual void execute(Memory &mem) {};
protected:
	std::vector<Command*> commands;

	void executeCommands(Memory &mem, int offset) {
		for (int i = offset; i < commands.size(); i++) {
			commands[i]->execute(mem);
		}	
	}
};

class IFNode : public Node {
public:
	void execute(Memory &mem) {
		if (commands[0]->execute(mem) == 0) {
			executeCommands(mem, 1);
		}
	};
};

class WHILENode : public Node {
public:
	void execute(Memory &mem) {
		while (commands[0]->execute(mem) == 0) {
				executeCommands(mem, 1);	
		}
	};
};

#endif // NODE_H
