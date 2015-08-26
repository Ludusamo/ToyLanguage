#ifndef COMPILABLE_H
#define COMPILABLE_H

#include <vector>
#include "Token.h"
#include "Memory.h"

class Compilable {
public:
	virtual void compile(std::vector<int> &bytecode, Memory &mem);	

	void setTokens(std::vector<Token> tokens);
private:
	std::vector<Token> tokens;
};

#endif // COMPILABLE_H
