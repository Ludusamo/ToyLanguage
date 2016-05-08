#include <lex.h>

Statement *lex(FILE *input) {
	int ln = 0;
	char *lines[MAX_LINES];
	while(lines[ln++] = read_line(input));
	ln--; // To account for the one overcount in the while
	Statement *statements = malloc(sizeof(Statement) * ln);
	for (int i = 0; i < ln; i++) {
		Statement *statement = create_statement(lines[i]);
		tokenize_statement(statement);
		statements[i] = *statement;
	}

	return statements;
}
