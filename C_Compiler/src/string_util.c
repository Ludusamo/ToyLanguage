#include "string_util.h"

int str_equal(const char *str1, const char *str2) {
	if (strlen(str1) != strlen(str2)) return 0;
	for (int i = 0 ; i < strlen(str1); i++) {
		if (str1[i] != str2[i]) break;
		if (i == strlen(str1) - 1) return 1;
	}
	return 0;
}

char *str_add(const char *str1, const char *str2) {
	int str1len = strlen(str1);
	int str2len = strlen(str2);
	int len = str1len + str2len;
	char *concat = malloc(len * sizeof(char) + 1);
	for (int i = 0; i < str1len; i++) concat[i] = str1[i];
	for (int i = 0; i < str2len; i++) concat[i + str1len] = str2[i];
	concat[len] = '\0';
	return concat;
}

int atoi(const char *str) {
	int i;
	sscanf(str, "%d\n", &i);
	return i;
}

char *itoa(int x) {
	char *str = malloc(15 * sizeof(char));
	sprintf(str, "%d", x);
	return str;
}

char *str_copy(const char *origin) {
	char *str = malloc(strlen(origin) * sizeof(char));
	sprintf(str, "%s", origin);
	return str;
}

int str_lt(const char *str1, const char *str2) {
	for (int i = 0; i < strlen(str1); i++) {
		if (str1[i] < str2[i]) return 1;
	}
	return 0;
}
