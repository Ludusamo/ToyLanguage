#ifndef DEBUG_H
#define DEBUG_H

#include <stdio.h>

class Debug {
public:
	static const bool debugging = true;

	static void print(const char *msg) {
		if (debugging)
			printf("%s\n", msg);
	};

	static void print(const char *pre, const char *msg) {
		if (debugging)
			printf("%s %s\n", pre, msg);
	};

	static void print(const char *pre, const char *msg, const char *post) {
		if (debugging)
			printf("%s %s %s\n", pre, msg, post);
	};
};

#endif // DEBUG_H
