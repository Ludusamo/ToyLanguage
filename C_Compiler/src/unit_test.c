#include "unit_test.h"

int run_test(Unit_Test test) {
	int run_code = test.run();	
	switch (run_code) {
	case SUCCESS:
		printf("Successfully Ran Test: %s\nSuccess Code %i\n", test.name, run_code);
		break;
	case FAILURE:
		printf("Test %s failed: Error Code %i\n", test.name, run_code);
		break;
	}
}
