#ifndef PARSER_H
#define PARSER_H

#include <vector>

#include "Node.h"
#include "Statement.h"
#include "Token.h"

class Parser {
public:
	static Node parse(Statement statement);
private:	
	bool isDeclaration(Statement statement);
};

#endif // PARSER_H
