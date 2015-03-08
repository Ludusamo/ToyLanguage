#ifndef PROGRAM_H
#define PROGRAM_H

#include "Node.h"
#include <vector>
#include "Statement.h"

class Program() : public Node {
public:
	vector<Node> nodes;
	void execute(){};	
};

#endif // PROGRAM_H
