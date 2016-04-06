#ifndef FILEIO_H
#define FILEIO_H

#include <stdlib.h>
#include <stdio.h>

char *read_line(FILE *file);

void write_line(FILE *file, const char *line);
void write_char(FILE *file, char c);
void write_int(FILE *file, int i);

#endif // FILEIO_H
