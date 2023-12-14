#define _CRT_SECURE_NO_WARNINGS

#include "header.h"
#include <stdio.h>
int main() {
	int mode; getmode(&mode);
	func_ptr_t funcPtr = getfunc();
	if (mode == 1)
		mode1(funcPtr);
	else
		mode2(funcPtr);

	system("pause");
	return 0;
}