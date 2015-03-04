#include "FileReader.h"
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
		return NULL;
	} else {
		char *line;
		line = (char*) malloc(200);
		fgets(line, 200, source);
		return line;
	}
	
}
