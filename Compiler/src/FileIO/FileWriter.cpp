#include "FileIO/FileWriter.h"

void FileWriter::openFile(const char *path) {
	source = fopen(path, "w");
	if (source == NULL) perror("File could not be opened");
}

void FileWriter::closeFile() {
	if (source != NULL) fclose(source);
	else perror("No file is opened");
}

void FileWriter::writeLine(const char *line) {
	if (source == NULL) perror("File is not opened");
	else fprintf(source, "%s\n", line);	
}

void FileWriter::writeChar(char c) {
	if (source == NULL) perror("File is not opened");
	else fprintf(source, "%c\n", c);	
}

void FileWriter::writeInt(int i) {
	if (source == NULL) perror("File is not opened");
	else fprintf(source, "%i\n", i);	
}
