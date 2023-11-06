#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<locale.h>
#include<memory.h>
#include<windows.h>

typedef struct  {
	char code[4];
	char* name;
	unsigned int qty;
	unsigned int cost;
	unsigned int skid;
}tovar;

void printtovar(tovar t, int mode) {
	if (mode == 0)
	{
		printf("%.*s %s %u руб. скидка %u%% = %u руб./шт.\n", 4, t.code, t.name, t.cost, t.skid, t.cost * (100 - t.skid) / 100);
	}
	else if (mode == 1)
		printf("%s %u руб./шт. %uшт всего %u руб.\n", t.name,t.cost * (100 - t.skid) / 100, t.qty, t.cost* (100 - t.skid) / 100*t.qty);
}

void append(tovar** check, unsigned* size, tovar t) {
	tovar* newcheck;
	if (*size > 0) {
		newcheck = (tovar*)realloc(*check, (*size + 1) * sizeof(tovar));
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

void clear(tovar** check, unsigned* size) {
	free(*check);
	(*size)=0;
}

long int codefind(char code[4], tovar arr[], unsigned size) {
	//char* tcode = terminated(code);
	for (int i = 0; i < size; i++) {
		if (memcmp(code, arr[i].code, 4*sizeof(char)) == 0) { //strcmp(terminated(arr[i].code), tcode)
			return i;
			break;
		}
	}
	//free(tcode);
	return -1;
}

int isvalidcode(char code[5]) {
	for (int i = 0;i<4;i++) {
		if (code[i] < '0' || code[i]>'9')
			return 0;
	}
	return 1;
}

void printcheck(tovar** check, unsigned* csize) {
	unsigned sum = 0, sskid = 0;
	printf("\nЧек: %i позиций\n", *csize);
	for (unsigned i = 0;i < *csize;i++) {
		tovar t = (*check)[i];
		sum += t.cost * t.qty;
		sskid += t.cost * t.skid / 100 * t.qty;
		printtovar(t, 1);
		Beep(150, 250);
	}
	printf("------------------------------------\n");
	printf("Сумма без скидок %u руб.\nСуммарная скидка %u руб.\nИТОГО %u руб.\n", sum, sskid, sum-sskid);
	Beep(250, 500);
}

int main() {
	setlocale(LC_ALL, "");
	srand(time(NULL));
	

	tovar assort[] = { 
		{"0000", "пакет", 1, 32, 0},
		{"0001", "пакет с пакетом", 1, 64, 5},
		{"0002", "пакет с пакетом с двумя пакетами", 1, 128, 10},
		{"1000","круглый корень",1, 314, 5},
		{"1001","треугольный корень",1, 173, 10},
		{"1002","ГМО логарифм",1, 271, 0},
		{"1003","дедукция математическая",1, 1, 0},
		{"2000","малок",1, 5000, 50},
		{"2001","пеленг",1, 3000, 45},
		{"3000", "слон", 1, 1140000, 35},
		{"3001", "медведь огнеупорный", 1, 35999, 10},
		{"3002", "нарды", 1, 1200, 25},
		{"3003", "бипки", 1, 105, 10},
		{"3004", "дилижанс", 1, 500, 5 },
		{"3005", "шушунчик", 1, 17000, 15},
		{"3006", "нюанс", 1, 750, 20},
		{"9999", "нуль-терминатор", 1, 9999, 30},
		
	};
	unsigned asssize = 17;

	printf("Добро пожаловать в магазин -5+3iёрочка!\nУ нас целочисленные цены и комплексные товары!\nПросканируйте (напишите) код, тогда будет выведено описание и товар будет добавлен в чек\nНапишите команду end для завершения покупки, тогда будет сформирован чек и посчитана итоговая сумма\n\nАссортимент:\n");
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
			printf("Символы начиная с символа %c проигнорированы\n", endc);
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
				clear(&check, &csize);
			}
			else {
				printf("Вы ничего не купили и уже уходите? Покажите карманы! Ага! Два атома азота у нас своровали!!!!\n");
				int t1 = 1200, t2 = 1100;
				for (int i = 0; i < 10; i++) {
					Beep(t1, 400);
					Beep(t2, 400);
				}
				
			}
			
			
		}
		else {
			printf("Не распознано\n");
		}

	}
	
	
	system("pause");
}