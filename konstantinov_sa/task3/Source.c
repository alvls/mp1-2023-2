#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<locale.h>
#include<time.h>
#include<math.h>

// | test mode with debug hints
// V
//#define Test

//random in range
int rir(int l, int r) {
	return round(rand() * ((double)(r - l) / RAND_MAX) + l);
}

int checkuniq(int n) {
	int digits[10] = { 0 };
	while (n > 0) {
		int c = n % 10;
		if (digits[c]){
			return 0;
		}	
		digits[c] = 1;
		n /= 10;
	}
	return 1;
}

void printnum(int n, int places[5]) {
	for (int i = 0; i < n; i++) {
		printf("%d", places[i]);
	}
	printf("\n");
}

void gennum(int n, int places[5], int digits[10]) {
	places[0] = rir(1, 9);
	digits[places[0]] = 1;
	for (int i = 1; i < n; i++) {

		while (1) {
			int e = rir(0, 9);
			if (!digits[e])
			{
				places[i] = e;
				digits[e] = 1;
				break;
			}
		}
	}

#ifdef Test
	printnum(n, places);
	
	for (int i = 0; i < 10; i++) {
		printf("%d", i);
	}
	printf("\n");
	for (int i = 0; i < 10; i++) {
		printf("%d", digits[i]);
	}
#endif
}

int main() {
	setlocale(LC_ALL, "");

	srand(time(NULL)* time(NULL));

	int n = 0;
	printf("Игра \"Быки и коровы\". Вам предстоит угадать загаданное компьютером число с различными цифрами.\nКомпьютер сообщает, сколько цифр угадано без совпадения с их позициями в загаданном числе (то есть количество коров)\nи сколько угадано вплоть до позиции в загаданном числе (то есть количество быков). Чтобы сдаться введите 0.\nВведите количество цифр числа, которое будет загадано:\n");
	while (!((n>=2)&&(n<=5))) {
		if (!scanf("%d", &n))
			while (getchar() != '\n');
	}

	int mg = 1;
	for (int i = 0; i < n;i++)
		mg *= 10;

	int num[5] = { -1,-1,-1,-1,-1 };
	int digits[10] = { 0 };
	gennum(n, num, digits);
	printf("\n"); 

	int vp = 0, tries = 0;
	while(vp != n) {
		vp = 0;
		int g = -1, vd = 0;

		while ((!((mg/10 <= g) && (g< mg))) || (!checkuniq(g))) {
			printf("      Введите %d-значное число с различными цифрами:\n", n);
			if(!scanf("%d", &g))
				while (getchar() != '\n');
			if (g == 0) {
				printf("Вы сдались, затратив %d попыток...\nЧисло было ", tries);
				printnum(n, num);
				system("pause");
				return 0;
			}
		}
		
		tries += 1;
		for (int i = n-1; i >= 0; i--) {
			int c = g % 10;
			g /= 10;
			//printf("c%d d%d n%d \n", c, digits[c], num[i]);
			if (digits[c])
				vd++;
			if (num[i] == c)
				vp++;
		}
		printf("      Коров: %d  Быков: %d\n", vd-vp, vp);

	}

	printf("Угадано за %d попыток\n", tries);
	system("pause");
	return 0;
}