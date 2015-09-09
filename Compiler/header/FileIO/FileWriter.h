#ifndef FILEWRITER_H
#define FILEWRITER_H

#include <stdio.h>

class FileWriter {
public:
	FILE *source = NULL;

	void openFile(const char *path);
	void closeFile();
	void writeLine(const char *line);
	void writeChar(char c);
	void writeInt(int i);
};

#endif // FILEWRITER_H
