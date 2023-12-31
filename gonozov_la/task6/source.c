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
	double etal = sin(x); //��������� �������� �������
	printf("��������� �������� ���������� %f\n����������� ������ �������� ������� ����� %f\n������� ����� ������� � ��������� ��������� ��������� %f\n ���������� ���������, ������� ���� ���������, ����� %d", etal, sum, fabs(etal - sum), numb_elem);
}
void sin2(double x, int numb_exper) {
	double tabl[25] = { 0 };
	tabl[0] = x;
	int k = 1;
	for (int i = 1; i < numb_exper; i++) {
		k += 2;
		tabl[i] = tabl[i - 1] * (-1) * x / k * x / (k - 1);
	}
	double etal = sin(x); //��������� �������� �������
	printf("|     �����     | ����������� ������ | ������� ����� ������� |\n| ������������  |  �������� �������  | � ��������� ��������� |\n");
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
	double etal = cos(x); //��������� �������� �������
	printf("��������� �������� ���������� %f\n����������� ������ �������� ������� ����� %f\n������� ����� ������� � ��������� ��������� ��������� %f\n ���������� ���������, ������� ���� ���������, ����� %d", etal, sum, fabs(etal - sum), numb_elem);
}
void cos2(double x, int numb_exper) {
	double tabl[25] = { 0 };
	tabl[0] = 1;
	int k = 0;
	for (int i = 1; i < numb_exper; i++) {
		k += 2;
		tabl[i] = tabl[i - 1] * (-1) * x / k * x / (k - 1);
	}
	double etal = cos(x); //��������� �������� �������
	printf("|     �����     | ����������� ������ | ������� ����� ������� |\n| ������������  |  �������� �������  | � ��������� ��������� |\n");
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
	double etal = exp(x); //��������� �������� �������
	printf("��������� �������� ���������� %f\n����������� ������ �������� ������� ����� %f\n������� ����� ������� � ��������� ��������� ��������� %f\n ���������� ���������, ������� ���� ���������, ����� %d", etal, sum, fabs(etal - sum), numb_elem);
}
void expon2(double x, int numb_exper) {
	double tabl[25] = { 0 };
	tabl[0] = 1;
	int k = 0;
	for (int i = 1; i < numb_exper; i++) {
		k ++;
		tabl[i] = tabl[i - 1] * x / k;
	}
	double etal = exp(x); //��������� �������� �������
	printf("|     �����     | ����������� ������ | ������� ����� ������� |\n| ������������  |  �������� �������  | � ��������� ��������� |\n");
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
		double num_comb = 1; // ��������������� ���������� ��� ��������� �������� ����� ���������
		double upper_k = i * 2 + 1; // ��������� � ����� ���������
		int lower_k = 1; // ����������� � ����� ���������
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
	printf("��������� �������� ���������� %f\n����������� ������ �������� ������� ����� %f\n������� ����� ������� � ��������� ��������� ��������� %f\n ���������� ���������, ������� ���� ���������, ����� %d", etal, l, fabs(etal - l), numb_elem);
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
		double num_comb = 1; // ��������������� ���������� ��� ��������� �������� ����� ���������
		double upper_k = i * 2 + 1; // ��������� � ����� ���������
		int lower_k = 1; // ����������� � ����� ���������
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
	double etal = cos(x)/sin(x); //��������� �������� �������
	printf("|     �����     | ����������� ������ | ������� ����� ������� |\n| ������������  |  �������� �������  | � ��������� ��������� |\n");
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

	printf("����� ���������� � ��������� \n");
	while (choice_mode != '0') {
		if (choice_mode == '3') {
			printf("����� ������:\n1. ����������� ������ ������� � �������� �����\n2. �������� �����������\n������� ����� ���� ������, ������� ������ ������������");
			scanf("%c", &choice_mode);
			int �;
			while (choice_mode != '1' && choice_mode != '2') {
				printf("����� ������������ �����, ���������� ��� ��� ");
				scanf("%c", &choice_mode);
				while ((� = getchar()) != '\n' && � != EOF) {}
			}
		}
		else {
			printf("����� ����������� ��������:\n0. ����� �� ���������\n1. ����������� ������ ������� � �������� �����\n2. �������� �����������\n");
			int �;
			scanf("%c", &choice_mode);
			while (choice_mode != '1' && choice_mode != '2' && choice_mode != '0') {
				printf("����� ������������ �����, ���������� ��� ��� ");
				scanf("%c", &choice_mode);
				while ((� = getchar()) != '\n' && � != EOF) {}
			}
		}
		if (choice_mode == '1') {
			int �;
			while ((� = getchar()) != '\n' && � != EOF) {}
			printf("�������� ������� ��� ���������:\n1. sin\n2. cos\n3. exp\n4. ctg\n");
			scanf("%c", &choice_function);
			while (choice_function != '1' && choice_function != '2' && choice_function != '3' && choice_function != '4') {
				printf("������� ������������ �������, ���������� ��� ��� ");
				scanf("%c", &choice_function);
				while ((� = getchar()) != '\n' && � != EOF) {}
			}
			printf("������� ����� x, � ������� ���������� ��������� ��������");
			scanf("%lf", &x);
			while ((� = getchar()) != '\n' && � != EOF) {}
			while (choice_function == '4'&& (x == 0 || x > 3.141592 || x < -3.141592)) {
				printf("���������� ��� ���������� ����� ����������� ������ � ����������� �������� ����������.\n������� x, ��������������� ����������� 0 < |x| <3.141592\n");
				scanf("%lf", &x);
				while ((� = getchar()) != '\n' && � != EOF) {}
			}
			printf("%lf\tx\n", x);
			printf("������� �������� ���������� (>= 0,000001)");
			scanf("%lf", &calculation_accuracy);
			while ((� = getchar()) != '\n' && � != EOF) {}
			while (!(calculation_accuracy >= 0.000001)) {
				printf("�������� ���������� ������� ���� >= 0, 000001, ������� ��� ���");
				scanf("%lf", &calculation_accuracy);
				while ((� = getchar()) != '\n' && � != EOF) {}
			}
			printf("������� ����� ��������� ���� ��� ���������� �������(�� 1 �� 1000)");
			scanf("%d", &numb_elem);
			while ((numb_elem < 1) || (numb_elem > 1000)) {
				printf("����� ��������� ���� ������ ���� �� 1 �� 1000, ������� ��� ���");
				scanf("%d", &numb_elem);
				while ((� = getchar()) != '\n' && � != EOF) {}
			}
			Func1[(int)choice_function - 49](x, numb_elem, calculation_accuracy);
		}
		if (choice_mode == '2') {
			int �;
			while ((� = getchar()) != '\n' && � != EOF) {}
			printf("�������� ������� ��� ���������:\n1. sin\n2. cos\n3. exp\n4. ctg\n");
			scanf("%c", &choice_function);
			while (choice_function != '1' && choice_function != '2' && choice_function != '3' && choice_function != '4') {
				printf("������� ������������ �������, ���������� ��� ��� ");
				scanf("%c", &choice_function);
				while ((� = getchar()) != '\n' && � != EOF) {}
			}
			printf("������� ����� x, � ������� ���������� ��������� ��������");
			scanf("%lf", &x);
			while (choice_function == '4' && (x == 0 || x > 3.141592 || x < -3.141592)) {
				printf("���������� ��� ���������� ����� ����������� ������ � ����������� �������� ����������.\n������� x, ��������������� ����������� 0 < |x| <3.141592\n");
				scanf("%lf", &x);
				while ((� = getchar()) != '\n' && � != EOF) {}
			}
			printf("������� ����� ������������� (�� 1 �� 25)");
			scanf("%d", &numb_exper);
			while (!(numb_exper < 26 && numb_exper > 0)) {
				printf("������� ������������ ����� �������������, ���������� ��� ��� ");
				scanf("%d", &numb_exper);
				while ((� = getchar()) != '\n' && � != EOF) {}
			}
			Func2[(int)choice_function - 49](x, numb_exper);
		}
	}
	printf("������� �� ������������� ����� ���������, �� ��������!");
	system("pause");
}