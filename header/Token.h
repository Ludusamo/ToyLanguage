#ifndef TOKEN_H
#define TOKEN_H

class Token {
public:
	enum TOKEN_TYPE { WHITESPACE, KEYWORD, IDENTIFIER, NUMBER, ASSIGN_OP, LPAREN, RPAREN };
	char *token;
	
	void setToken(char *token);
	void setType(TOKEN_TYPE type);
	char *getType();

	TOKEN_TYPE type;
};

class TWhiteSpace : Token {
	TWhiteSpace() { setType(WHITESPACE); }
};

class TKeyword : Token {
	TKeyword() { setType(WHITESPACE); }
};

class TIdentifier : Token {
	TIdentifier() { setType(IDENTIFIER); }
};

class TNumber : Token {
	TNumber() { setType(NUMBER); }
};

class TAssignOp : Token {
	TAssignOp() { setType(ASSIGN_OP); }
};

class TLParen : Token {
	TLParen() { setType(LPAREN); }
};

class TRParen : Token {
	TRParen() { setType(RPAREN); }
};

#endif // TOKEN_H
