#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <locale.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

void main()
{	
	int k; //выбор режима игры
	setlocale(LC_ALL, "rus");
	printf("В какой режим игры вы хотите сыграть?\nВведите 1, если в первый, или 2, если во второй ");
	scanf("%d", &k);
	switch (k) {
	case 1:
		game1();
		break;
	case 2:
		game2();
		break;
	default:
		k = 0;
		do {
			printf("Пожалуйста, введите 1 или 2 ");
			scanf("%d", &k);
		} while ((k != 1) || (k != 2));
		switch (k) {
		case 1:
			game1();
			break;
		case 2:
			game2();
			break;
		}
	}
	system("pause");
}
int game1() {
	printf("1");
}
int game2() {
	printf("2");
}