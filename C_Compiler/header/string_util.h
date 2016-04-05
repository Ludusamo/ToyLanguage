#ifndef STRINGUTIL_H
#define STRINGUTIL_H

#include <string.h>

int str_equal(const char *str1, const char *str2);
char *str_add(const char *str1, const char *str2);
int atoi(const char *str);
char *itoa(int x);
char *str_copy(const char *origin);

#endif // STRINGUTIL_H
