#include "FileReader.h" 

int main() {
	FileReader file;
	file.openFile("res/test.ls");
	char *line = file.getLine();
	printf("%c %c\n", line[0], line[1]);
	if (line[0] == 9) printf("The first character is a tab.\n");
	printf("%i\n", sizeof(line));
	file.closeFile();
	return 0;
}
