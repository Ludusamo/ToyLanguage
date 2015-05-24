#ifndef NODE_H
#define NODE_H

#include <vector>
#include "Command.h"

class Node {
public:
	virtual void execute(){};
protected:
	std::vector<Command*> commands;
};

class MainNode {
public:
		
};

#endif // NODE_H
