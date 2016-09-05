#ifndef FILEPATH_H
#define FILEPATH_H

#include "string_util.h"

typedef struct {
	int num_dir;
	char **dirs;
	char *filename;
	char *extension;
} FilePath;

FilePath *create_filepath(const char *filepath);
char *filepath_to_string(FilePath *filepath);

#endif // FILEPATH_H
