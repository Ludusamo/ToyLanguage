#include "Program.h"

#include <stdio.h>

void Program::createVariable(Variable::VAR_TYPE type, const char *identifier, const char *value, int depth) {
	/* TODO:
	 * Currently variables cannot be created with the same identifier no matter the scope.
	 */
	for (int i = 0; i < variables.size(); i++) {
		for (int j = 0; j < variables[i].size(); j++) {
			if (variables[i][j].identifier == identifier) {
				printf("Variable: %s already exists\n", identifier);
				return;	
			}
		}
	}
	Variable v;
	v.setIdentifier(identifier);
	v.setType(type);
	v.assignValue(value);

	printf("Created Variable: %s with value %s.\n", identifier, value);
	variables[depth].push_back(v);
}

char *Program::operation(const char *id1, const char *id2, Token::SUB_OPERATOR type) {
	Variable *var1 = NULL, *var2 = NULL;
	for (int i = 0; i < variables.size(); i++) {
		for (int j = 0; j < variables[i].size(); j++) {
			if (variables[i][j].identifier == id1) {
				var1 = &variables[i][j];
			}
			if (variables[i][j].identifier == id2) {
				var2 = &variables[i][j];
			}
			if (var1 != NULL && var2 != NULL) {
				if (var1->type != var2->type) {
					printf("Invalid Operation: Type Mismatch.\n");
					return NULL;
				}

				printf("Operation on %s and %s yielded: %s", var1->identifier, var2->identifier, Variable::operation(var1->getValue(), var2->getValue(), var1->type, type));
				return Variable::operation(var1->getValue(), var2->getValue(), var1->type, type);	
			}
		}
	}
}

bool Program::comparator(const char *id1, const char *id2, Token::SUB_OPERATOR type) {
	Variable *var1 = NULL, *var2 = NULL;
	for (int i = 0; i < variables.size(); i++) {
		for (int j = 0; j < variables[i].size(); j++) {
			if (variables[i][j].identifier == id1) {
				var1 = &variables[i][j];
			}
			if (variables[i][j].identifier == id2) {
				var2 = &variables[i][j];
			}
			if (var1 != NULL && var2 != NULL) {
				if (var1->type != var2->type) {
					printf("Invalid Operation: Type Mismatch.\n");
					return NULL;
				}
				return Variable::comparator(var1->getValue(), var2->getValue(), var1->type, type);	
			}
		}
	}
}
