#ifndef LEX_H
#define LEX_H

#include <stdio.h>
#include "file_io.h"
#include "statement.h"
#include "shared_values.h"

#define MAX_LINES 10000

Statement *lex(FILE *input);

#endif // LEX_H
