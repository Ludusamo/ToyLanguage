#include "FileIO/FileReader.h"
#include <stdlib.h>

void FileReader::openFile(const char *path) {
	source = fopen(path, "r");
	if (source == NULL) perror("File could not be opened");		
}

void FileReader::closeFile() {
	if (source != NULL) fclose(source);
	else perror("No file is opened");
}

char *FileReader::getLine() {
	if (source == NULL) {
		perror("No file is opened");
	} else {
		char *line = NULL;
		line = (char*) malloc(200);
		if (fgets(line, 200, source) != NULL) return line;
	}
	return NULL;
}
