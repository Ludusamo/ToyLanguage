#include "filepath.h"

FilePath *create_filepath(const char *filepath) {
	FilePath *fp = malloc(sizeof(FilePath));
	fp->num_dir = 0;
	fp->dirs = calloc(sizeof(char*), 256);
	int bp = 0;
	char *buffer = calloc(sizeof(char), 256);
	int extension_mode = 0;
	for (int i = 0; i < strlen(filepath); i++) {
		char c = filepath[i];
		if (c == '\\' || c == '/') {
			buffer[bp] = '\0';
			bp = 0;
			fp->dirs[fp->num_dir++] = str_copy(buffer);
		} else if (c == '.') {
			extension_mode = 1;
			buffer[bp] = '\0';
			bp = 0;
			fp->filename = str_copy(buffer);
		} else if (i == strlen(filepath) - 1) {
			buffer[bp++] = c;
			buffer[bp] = '\0';
			bp = 0;
			if (!extension_mode) {
				fp->filename = str_copy(buffer);
			} else {
				fp->extension = str_copy(buffer);
			}
		} else {
			buffer[bp++] = c;
		}
	}
	return fp;
}

char *filepath_to_string(FilePath *filepath) {
	char *path = str_copy(filepath->dirs[0]);
	path = str_add(path, "/");
	for (int i = 1; i < filepath->num_dir; i++) {
		path = str_add(path, filepath->dirs[i]);
		path = str_add(path, "/");
	}
	path = str_add(path, filepath->filename);
	path = str_add(path, ".");
	path = str_add(path, filepath->extension);
	return path;
}
