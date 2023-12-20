#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <locale.h>
#include <math.h>

void sin1(double x, int numb_elem, double calc_acc) {
	double l = x;
	int k = 0;
	double sum = x;
	for (int i = 3; i < numb_elem; i++) {
		if (i % 2 == 1) {
			int s1 = 1;
			double pred_chl = l;
			k++;
			if (k % 2 == 1) {
				s1 = -1;
			}
			l = pred_chl * (s1 * x / i * x / (i-1));
			sum += l;
			if (fabs(l - pred_chl) <= calc_acc) {
				numb_elem = i-1;
				sum -= l;
				break;
			}
		}
	}
	double etal = sin(x); //эталонное значение функции
	printf("Эталонное значение составляет %f\nВычисленная оценка значения функции равна %f\nРазница между оценкой и эталонным значением достигает %f\n Количество слагаемых, которое было вычислено, равно %d", etal, sum, fabs(etal - sum), numb_elem);
}
void sin2(double x, int numb_exper) {
	double tabl[25] = { 0 };
	tabl[0] = x;
	int k = 1;
	for (int i = 1; i < numb_exper; i++) {
		k += 2;
		tabl[i] = tabl[i - 1] * (-1) * x / k * x / (k - 1);
	}
	double etal = sin(x); //эталонное значение функции
	printf("|     Номер     | Вычисленная оценка | Разница между оценкой |\n| эксперимента  |  значения функции  | и эталонным значением |\n");
	for (int i = 0; i < numb_exper; i++) {
		printf("|%15d|%20lf|%23lf|\n", i + 1, tabl[i], fabs(tabl[i]-etal));
		tabl[i + 1] += tabl[i];
	}
}
void cos1(double x, int numb_elem, double calc_acc) {
	double l = 1;
	int k = 0;
	double sum = 1;
	for (int i = 2; i < numb_elem; i++) {
		if (i % 2 == 0) {
			int s1 = 1;
			double pred_chl = l;
			k++;
			if (k % 2 == 1) {
				s1 = -1;
			}
			l = pred_chl * (s1 * x / i * x / (i-1));
			sum += l;
			if (fabs(l - pred_chl) <= calc_acc) {
				numb_elem = i-1;
				sum -= l;
				break;
			}
		}
	}
	double etal = cos(x); //эталонное значение функции
	printf("Эталонное значение составляет %f\nВычисленная оценка значения функции равна %f\nРазница между оценкой и эталонным значением достигает %f\n Количество слагаемых, которое было вычислено, равно %d", etal, sum, fabs(etal - sum), numb_elem);
}
void cos2(double x, int numb_exper) {
	double tabl[25] = { 0 };
	tabl[0] = 1;
	int k = 0;
	for (int i = 1; i < numb_exper; i++) {
		k += 2;
		tabl[i] = tabl[i - 1] * (-1) * x / k * x / (k - 1);
	}
	double etal = cos(x); //эталонное значение функции
	printf("|     Номер     | Вычисленная оценка | Разница между оценкой |\n| эксперимента  |  значения функции  | и эталонным значением |\n");
	for (int i = 0; i < numb_exper; i++) {
		printf("|%15d|%20lf|%23lf|\n", i + 1, tabl[i], fabs(tabl[i] - etal));
		tabl[i + 1] += tabl[i];
	}
}
void exp1(double x, int numb_elem, double calc_acc) {
	double l = x;
	double sum = 1 + x;
	for (int i = 2; i < numb_elem; i++) {
		double pred_chl = l;
		l = pred_chl * x / i;
		sum += l;
		if (fabs(l) <= calc_acc) {
			numb_elem = i-1;
			sum -= l;
			break;
		}
		printf("%lf", sum);
	}
	double etal = exp(x); //эталонное значение функции
	printf("Эталонное значение составляет %f\nВычисленная оценка значения функции равна %f\nРазница между оценкой и эталонным значением достигает %f\n Количество слагаемых, которое было вычислено, равно %d", etal, sum, fabs(etal - sum), numb_elem);
}
void expon2(double x, int numb_exper) {
	double tabl[25] = { 0 };
	tabl[0] = 1;
	int k = 0;
	for (int i = 1; i < numb_exper; i++) {
		k ++;
		tabl[i] = tabl[i - 1] * x / k;
	}
	double etal = exp(x); //эталонное значение функции
	printf("|     Номер     | Вычисленная оценка | Разница между оценкой |\n| эксперимента  |  значения функции  | и эталонным значением |\n");
	for (int i = 0; i < numb_exper; i++) {
		printf("|%15d|%20lf|%23lf|\n", i + 1, tabl[i], fabs(tabl[i] - etal));
		tabl[i + 1] += tabl[i];
	}
}
void ctg1(double x, int numb_elem, double calc_acc) {
	double B[1000] = { 0 };
	B[0] = 1; B[1] = -0.5;
	double l = 1 / x;
	int k2 = 1;
	int sk3 = 0;
	int k3 = 1;
	double k4 = x;
	for (int i = 1; i < numb_elem; i++) {
		double pr = l;
		double num_comb = 1; // вспомогательная переменная для занесения подсчёта числа сочетаний
		double upper_k = i * 2 + 1; // числитель у числа сочетаний
		int lower_k = 1; // знаменатель у числа сочетаний
		double s1 = 1;
		for (int j = 0; j < i * 2 - 1; j++) {
			num_comb *= upper_k;
			num_comb /= lower_k;
			s1 += (num_comb * B[lower_k]);
			upper_k -= 1; 
			lower_k += 1;
		}
		B[i * 2] = ( s1 / -(i * 2 + 1) ) ;
		int k1 = 1;
		if (i % 2 == 1) {
			k1 = -1;
		}
		k2 *= 4;
		sk3 += 2;
		k3 *= sk3 * (sk3 - 1);
		l += k1 * k2 * B[i * 2] / k3 * k4;
		printf("\n1||%d 2||%d 3||%d 4||%lf 5||%lf 6||%lf", k1, k2, k3, k4, B[i *2], l);
		k4 *= (x * x);
		if (fabs(l - pr) <= calc_acc) {
			numb_elem = i;
			l = pr;
			break;
		}
	}
	double etal = cos(x)/sin(x);
	printf("Эталонное значение составляет %f\nВычисленная оценка значения функции равна %f\nРазница между оценкой и эталонным значением достигает %f\n Количество слагаемых, которое было вычислено, равно %d", etal, l, fabs(etal - l), numb_elem);
}
void ctg2(double x, int numb_exper) {
	double B[1000] = { 0 };
	B[0] = 1; B[1] = -0.5;
	double tabl[25] = { 0 };
	tabl[0] = 1/x;
	int k = 0;
	int k2 = 1;
	int sk3 = 0;
	double k3 = 1;
	double k4 = x;
	for (int i = 1; i < numb_exper; i++) {
		double num_comb = 1; // вспомогательная переменная для занесения подсчёта числа сочетаний
		double upper_k = i * 2 + 1; // числитель у числа сочетаний
		int lower_k = 1; // знаменатель у числа сочетаний
		double s1 = 1;
		for (int j = 0; j < i * 2 - 1; j++) {
			num_comb *= upper_k;
			num_comb /= lower_k;
			s1 += (num_comb * B[lower_k]);
			upper_k -= 1;
			lower_k += 1;
		}
		B[i * 2] = (s1 / -(i * 2 + 1));
		int k1 = 1;
		if (i % 2 == 1) {
			k1 = -1;
		}
		k2 *= 4;
		sk3 += 2;
		k3 *= sk3 * (sk3 - 1);
		tabl[i] = k1 * k2 * B[i * 2] / k3 * k4;
		k4 *= (x * x);
	}
	double etal = cos(x)/sin(x); //эталонное значение функции
	printf("|     Номер     | Вычисленная оценка | Разница между оценкой |\n| эксперимента  |  значения функции  | и эталонным значением |\n");
	for (int i = 0; i < numb_exper; i++) {
		printf("|%15d|%20lf|%23lf|\n", i + 1, tabl[i], fabs(tabl[i] - etal));
		tabl[i + 1] += tabl[i];
	}
}
void main() {
	setlocale(LC_ALL, "rus");
	char choice_function;
	char choice_mode = '3';
	double x = 0.0;
	int numb_elem = 0;
	double calculation_accuracy = 0.0;
	int numb_exper;
	void (*Func1[4])(double, int, double) = { sin1, cos1, exp1, ctg1 };
	void (*Func2[4])(double, int) = { sin2, cos2, expon2, ctg2 };

	printf("Добро пожаловать в программу \n");
	while (choice_mode != '0') {
		if (choice_mode == '3') {
			printf("Выбор режима:\n1. Однократный расчет функции в заданной точке\n2. Серийный эксперимент\nВведите цифру того режима, который хотите использовать");
			scanf("%c", &choice_mode);
			int а;
			while (choice_mode != '1' && choice_mode != '2') {
				printf("Введён недопустимый режим, попробуйте ещё раз ");
				scanf("%c", &choice_mode);
				while ((а = getchar()) != '\n' && а != EOF) {}
			}
		}
		else {
			printf("Выбор дальнейшего действия:\n0. Выход из программы\n1. Однократный расчет функции в заданной точке\n2. Серийный эксперимент\n");
			int а;
			scanf("%c", &choice_mode);
			while (choice_mode != '1' && choice_mode != '2' && choice_mode != '0') {
				printf("Введён недопустимый режим, попробуйте ещё раз ");
				scanf("%c", &choice_mode);
				while ((а = getchar()) != '\n' && а != EOF) {}
			}
		}
		if (choice_mode == '1') {
			int а;
			while ((а = getchar()) != '\n' && а != EOF) {}
			printf("Выберите функцию для подсчётов:\n1. sin\n2. cos\n3. exp\n4. ctg\n");
			scanf("%c", &choice_function);
			while (choice_function != '1' && choice_function != '2' && choice_function != '3' && choice_function != '4') {
				printf("Введена недопустимая функция, попробуйте ещё раз ");
				scanf("%c", &choice_function);
				while ((а = getchar()) != '\n' && а != EOF) {}
			}
			printf("Задайте точку x, в которой необходимо вычислить значение");
			scanf("%lf", &x);
			while ((а = getchar()) != '\n' && а != EOF) {}
			while (choice_function == '4'&& (x == 0 || x > 3.141592 || x < -3.141592)) {
				printf("Разложение для котангенса будет справедливо только в определённом числовом промежутке.\nВведите x, удовлетворяющий неравенству 0 < |x| <3.141592\n");
				scanf("%lf", &x);
				while ((а = getchar()) != '\n' && а != EOF) {}
			}
			printf("%lf\tx\n", x);
			printf("Задайте точность вычисления (>= 0,000001)");
			scanf("%lf", &calculation_accuracy);
			while ((а = getchar()) != '\n' && а != EOF) {}
			while (!(calculation_accuracy >= 0.000001)) {
				printf("Точность вычисления должнва быть >= 0, 000001, введите ещё раз");
				scanf("%lf", &calculation_accuracy);
				while ((а = getchar()) != '\n' && а != EOF) {}
			}
			printf("Задайте число элементов ряда для выполнения расчета(от 1 до 1000)");
			scanf("%d", &numb_elem);
			while ((numb_elem < 1) || (numb_elem > 1000)) {
				printf("Число элементов ряда должно быть от 1 до 1000, введите ещё раз");
				scanf("%d", &numb_elem);
				while ((а = getchar()) != '\n' && а != EOF) {}
			}
			Func1[(int)choice_function - 49](x, numb_elem, calculation_accuracy);
		}
		if (choice_mode == '2') {
			int а;
			while ((а = getchar()) != '\n' && а != EOF) {}
			printf("Выберите функцию для подсчётов:\n1. sin\n2. cos\n3. exp\n4. ctg\n");
			scanf("%c", &choice_function);
			while (choice_function != '1' && choice_function != '2' && choice_function != '3' && choice_function != '4') {
				printf("Введена недопустимая функция, попробуйте ещё раз ");
				scanf("%c", &choice_function);
				while ((а = getchar()) != '\n' && а != EOF) {}
			}
			printf("Задайте точку x, в которой необходимо вычислить значение");
			scanf("%lf", &x);
			while (choice_function == '4' && (x == 0 || x > 3.141592 || x < -3.141592)) {
				printf("Разложение для котангенса будет справедливо только в определённом числовом промежутке.\nВведите x, удовлетворяющий неравенству 0 < |x| <3.141592\n");
				scanf("%lf", &x);
				while ((а = getchar()) != '\n' && а != EOF) {}
			}
			printf("Задайте число экспериментов (от 1 до 25)");
			scanf("%d", &numb_exper);
			while (!(numb_exper < 26 && numb_exper > 0)) {
				printf("Введено недопустимое число экспериментов, попробуйте ещё раз ");
				scanf("%d", &numb_exper);
				while ((а = getchar()) != '\n' && а != EOF) {}
			}
			Func2[(int)choice_function - 49](x, numb_exper);
		}
	}
	printf("Спасибо за использование нашей программы, до свидания!");
	system("pause");
}