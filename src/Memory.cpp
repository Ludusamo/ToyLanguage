#include "Memory.h"

#include "Debug.h"

void Memory::createVariable(Variable::VAR_TYPE type, const char *identifier, int depth) {
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

	Debug::print("Created Variable:", identifier);
	variables[depth].push_back(v);
}

void Memory::setValue(const char *id, const char *value) {
	getVariable(id)->assignValue(value);
	Debug::print(id, "Assigned:", value);
}

char *Memory::operation(const char *id1, const char *id2, Token::SUB_OPERATOR type) {
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

				Debug::print("Operation yielded:", Variable::operation(var1->getValue(), var2->getValue(), var1->type, type));
				return Variable::operation(var1->getValue(), var2->getValue(), var1->type, type);	
			}
		}
	}
}

bool Memory::comparator(const char *id1, const char *id2, Token::SUB_OPERATOR type) {
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

Variable *Memory::getVariable(const char *id) {
	for (int i = 0; i < variables.size(); i++) {
		for (int j = 0; j < variables[i].size(); j++) {
			if (variables[i][j].identifier == id) {
				return &(variables[i][j]);
			}
		}
	}		
}
