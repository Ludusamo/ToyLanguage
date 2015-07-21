#include "StringUtil.h"

#include <sstream>
#include <stdlib.h>
#include <string.h>

bool StringUtil::equal(const char *str1, const char *str2) {
	for (int i = 0; i < strlen(str1); i++) {
		if (str1[i] != str2[i]) break;
		if (i == strlen(str1) - 1) return true;
	}
	return false;
}

char *StringUtil::add(const char *str1, const char *str2) {
	char *output = (char*) malloc(sizeof(str1) + sizeof(str2));

	for (int i = 0; i < strlen(str1); i++) {
		output[i] = str1[i];
	}
	for (int i = strlen(str1); i < strlen(str1) + strlen(str2); i++) {
		output[i] = str2[i - strlen(str1)];
	}
	
	return output;
}

int StringUtil::atoi(const char *str) {
	int output;
	std::stringstream ss;
	ss << str;
	ss >> output;

	return output;
}

char *StringUtil::itoa(int x) {
	std::stringstream ss;
	ss << x;

	return (char *) ss.str().c_str();
}

char *StringUtil::copy(char *origin) {
	char *destination = (char*) malloc(sizeof(origin));
	for (int i = 0; i < strlen(origin) + 1; i++) {
		destination[i] = origin[i];
	}
	return destination;
}
