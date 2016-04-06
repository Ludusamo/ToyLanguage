#include "file_io.h"

char *read_line(FILE *file) {
	if (!file) perror("No file is opened");
	else {
		char *line = NULL;
		line = (char*) malloc(200);
		if (fgets(line, 200, file) != NULL) return line;
	}
	return NULL;
}

void write_line(FILE *file, const char *line) {
	if (file == NULL) perror("File is not opened");
	else fprintf(file, "%s\n", line);
}
