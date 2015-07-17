#include "Parser.h"

#include <stdio.h>

Node Parser::parse(Statement statement) {
	std::vector<Token> tokens;
	tokens = statement.tokens;
	for (int i = statement.depth; i < tokens.size(); i++) {
		if (tokens[i].type == Token::KEYWORD) {
			if (tokens[i].subtype == Token::IF) {
				if (tokens[i+1].type != Token::PAREN && tokens[i+1].subtype != Token::LPAREN) perror("Unexpected token.");

			} else if (tokens[i].subtype == Token::ELSE) {
			
			} else if (tokens[i].subtype == Token::INT) {
				
			} else {
				perror("Invalid token");
			}
		} else if (tokens[i].type == Token::IDENTIFIER) {
			if ((tokens.size() - i) <= 1) // Further commands beyond end stmnt
				continue;
			if (tokens[i + 1].type == Token::OPERATOR) {
				
			}
		} else if (tokens[i].type == Token::NUMBER) {

		} else if (tokens[i].type == Token::OPERATOR) {

		} else if (tokens[i].type == Token::PAREN) {
			
		}
	}	
}
