#ifndef STRINGUTIL_H
#define STRINGUTIL_H

#include <sstream>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

class StringUtil {
public:
	static bool equal(const char *str1, const char *str2);
	static char *add(const char *str1, const char *str2);
	static int atoi(const char *str);
	static char *itoa(int x);
	static char *copy(const char *origin);
};

#endif // STRINGUTIL_H