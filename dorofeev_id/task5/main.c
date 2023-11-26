#include <string.h>
#include <stdlib.h>
#include <string.h>
#include "sorts.h"
#include "files.h"
#include <locale.h>



int main()
{
	setlocale(LC_ALL, "rus");
	char path[] = "D:\\Desktop\\ONB2\\*.*";
	int file_count;
	file* lol = get_files(path, &file_count);
	print_files(lol, file_count);
	printf("\n%d", file_count);
	printf("\n\n\ncomplete");
	return 0;
}

//дальше - больше
