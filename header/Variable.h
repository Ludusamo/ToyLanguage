#ifndef VARIABLE_H
#define VARIABLE_H

class Variable {
public:
	enum VAR_TYPE { INT, STRING, BOOL };
	char *identifier;

	void setType(VAR_TYPE type) { this->type = type; };
	void assignValue(char *value) { this->value = value; };

	VAR_TYPE type;
private:
	char *value;
};

#endif // VARIABLE_H
