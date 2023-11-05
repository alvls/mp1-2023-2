#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<locale.h>
#include<memory.h>
#include<windows.h>

typedef struct  {
	char code[5]; //без терминатора неудобно выводить и сравнивать
	char* name;
	unsigned int qty;
	unsigned int cost;
	unsigned int skid;
}tovar;

void printtovar(tovar t, int mode) {
	if (mode == 0)
		printf("%s %s %u руб. скидка %u%% = %u руб./шт.\n", t.code, t.name, t.cost, t.skid, t.cost*(100-t.skid)/100);
	else if (mode == 1)
		printf("%s %uшт %u руб./шт. всего %u руб.\n", t.name,t.qty, t.cost * (100 - t.skid) / 100, t.cost* (100 - t.skid) / 100*t.qty);
}

void append(tovar** check, unsigned* size, tovar t) {
	tovar* newcheck;
	if (*size > 0) {
		newcheck = (tovar*)realloc(*check, (*size + 1) * sizeof(tovar));
		//memcpy(newcheck, *check, (*size) * sizeof(tovar));
		//free(*check);
		if (newcheck != NULL)
			*check = newcheck;
		//printf("realloc\n");
	}
	else {
		newcheck = (tovar*)malloc(sizeof(tovar));
	}
	//printf("appended ");
	//printtovar(t);
	//printf(" to %d\n", *size);
	newcheck[*size] = t;
	
	*check = newcheck;
	(*size)++;
}

long int codefind(char code[5], tovar arr[], unsigned size) {
	for (int i = 0; i < size; i++) {
		if (strcmp(arr[i].code, code) == 0) {
			return i;
			break;
		}
	}
	return -1;
}

//tovar tovarfind(char code[5], tovar assort[], unsigned asssize) {
//	long findex = codefind(code, assort, asssize);
//	/*for (int i = 0; i < asssize; i++) {
//		if (strcmp(assort[i].code, code) == 0) {
//			return assort[i];
//			break;
//		}
//	}*/
//	tovar notfound = { "0000","notfound", 0, 0, 0 };
//	return notfound;
//}

int isvalidcode(char code[5]) {
	for (int i = 0;i<4;i++) {
		if (code[i] < '0' || code[i]>'9')
			return 0;
	}
	return 1;
}

void printcheck(tovar** check, unsigned* csize) {
	printf("Чек: %i\n", *csize);
	for (unsigned i = 0;i < *csize;i++) {
		//Sleep(50);
		printtovar((*check)[i], 1);
		Beep(100, 200);
	}
}

int main() {
	setlocale(LC_ALL, "");
	srand(time(NULL));
	//tovar bipki = {"0003", "bipki",1, 105, 10};
	//tovar dilijans = { "0004", "dilijans",1, 500, 5 };

	tovar assort[] = { 
		{"0000", "пакет", 1, 32, 0},
		{"0001", "пакет с пакетом", 1, 64, 5},
		{"0000", "пакет с пакетом с пакетом", 1, 128, 10},
		{"0003", "бипки", 1, 105, 10},
		{"0004", "дилижанс", 1, 500, 5 },
		{"0005", "шушунчик", 1, 17000, 15},
		{"0006", "нюанс", 1, 750, 20},
		{"1000","круглый корень",1, 314, 5},
		{"1001","треугольный корень",1, 173, 10},
		{"1002","ГМО логарифм",1, 271, 0},
		{"1003","дедукция математическая",1, 1, 0},
		{"2000","малок",1, 5000, 50},
		{"2001","пеленг",1, 3000, 45},
		{"9999", "нуль-терминатор", 1, 9999, 30},
		
	};
	unsigned asssize = 14;

	printf("Добро пожаловать в магазин -5+3iёрочка!\nУ нас целочисленные цены и комплексные товары!\nПросканируёте код или напишите команду end\n\nАссортимент:\n");
	for (unsigned i = 0;i < asssize;i++) {
		printtovar(assort[i], 0);
	}

	tovar* check = &(assort[0]);
	unsigned csize = 0;
	/*append(&check, &csize, assort[0]);
	append(&check, &csize, assort[1]);
	printtovar(check[1]);*/

	while (1) {
		char input[4];
		char endc = '\n';
		scanf("%4s%c", input, &endc);
		//printf(">%s\n", input);
		//printf(" %i<", (int)input[3]);
		if (endc != '\n')
			printf("Символы начиная с %c проигнорированы\n", endc);
		//printf("Присутствие кода %i\n", isvalidcode(input));
		if (isvalidcode(input)) {
			Beep(1900, 150);
			tovar foundt;

			long inchecki = codefind(input, check, csize);
			if (inchecki != -1) { //сначала проверим на повтор товара в чеке
				check[inchecki].qty++;
				foundt = check[inchecki];
				printtovar(foundt, 0);
			}
			else {
				long findex = codefind(input, assort, asssize); //потом поищем в ассортименте
				if (findex != -1) {
					foundt = assort[findex];
					append(&check, &csize, foundt);
					printtovar(foundt, 0);
				}
				else {
					printf("Товар с кодом %s не найден\n", input);
				}
			}

		}
		else if (strcmp(input, "end")==0) {
			if (csize) {
				printcheck(&check, &csize);
			}
			else {
				printf("Вы ничего не купили!\n");
			}
			
			
		}
		else {
			printf("Не распознано\n");
		}

	}
	
	
	system("pause");
}