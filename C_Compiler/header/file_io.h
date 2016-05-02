#ifndef FILEIO_H
#define FILEIO_H

#include <stdlib.h>
#include <stdio.h>

char *read_line(FILE *file);

void write_line(FILE *file, const char *line);

#endif // FILEIO_H
