#ifndef STRINGUTIL_H
#define STRINGUTIL_H

class StringUtil {
public:
	static bool equal(const char *str1, const char *str2);
	static char *add(const char *str1, const char *str2);
	static int atoi(const char *str);
	static char *itoa(int x);
};

#endif // STRINGUTIL_H
