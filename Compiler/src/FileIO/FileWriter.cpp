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

}

void FileWriter::writeChar(char c) {

}

void FileWriter::writeInt(int i) {

}
