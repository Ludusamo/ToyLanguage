#ifndef PARSER_H
#define PARSER_H

#include "token.h"
#include "statement.h"
#include "shared_values.h"

int parse(Statement *statements);
int parse_line(Statement *statement);
int is_declaration(Statement *statement);

#endif // PARSER_H
