#include "peripherals.h"

struct JoY JoYAct;


 int gRawKeys[6] = { 0, 0, 0, 0, 0, 0 };

int checkKey(int code) {
	int a = 0;
	while (a < 6)
		if (gRawKeys[a++] == code)
			return 1;
	return 0;
}
int getKey() {
	int a = 0;
	while (a < 6)
		if (gRawKeys[a++] != 0)
			return gRawKeys[--a];
	return 0;
}

