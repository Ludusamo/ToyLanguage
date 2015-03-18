#include "StringUtil.h"

#include "string.h"

bool StringUtil::equal(const char *str1, const char *str2) {
	for (int i = 0; i < strlen(str1); i++) {
		if (str1[i] != str2[i]) break;
		if (i == strlen(str1) - 1) return true;
	}
	return false;
}
