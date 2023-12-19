#include "header.h"
#include <stdio.h>

int main() {
	int mode; getmode(&mode);
	func_ptr_t funcPtr;
	standart_func_ptr_t standartFuncPtr;
	getfunc(&funcPtr, &standartFuncPtr);
	if (mode == 1)
		mode1(funcPtr, standartFuncPtr);
	else
		mode2(funcPtr, standartFuncPtr);
	system("pause");
	return 0;
}