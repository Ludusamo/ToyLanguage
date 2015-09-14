#ifndef FILEREADER_H
#define FILEREADER_H

#include <stdio.h>

class FileReader {
public:
	FILE *source = NULL;

	void openFile(const char *path);
	void closeFile();
	char *getLine();
};


#endif // FILEREADER_H
