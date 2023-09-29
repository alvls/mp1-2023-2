/*
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#include <locale.h>

int main(){
	float r1, r2, x1, x2, y1, y2, D;
	setlocale(LC_ALL, "rus");
	printf("������� ������� ����������� 1 � 2\n");
	scanf("%f %f", &r1, &r2);
	printf("������� ���������� ������ ������ ����������\n");
	scanf("%f %f", &x1, &y1);
	printf("������� ���������� ������ ������ ����������\n");
	scanf("%f %f", &x2, &y2);
	D = sqrt((x2 - x1)*(x2 - x1) + (y2 - y1)*(y2 - y1));
	if (D > r2 + r1){
		printf("���������� �� ��������  ");
	}
	else if (D == r1 + r2){
		printf("���������� �������� �������  ");
	}
	else if ((D < r1 + r2) && (D > fabs(r1 - r2))){
		printf("���������� ������������ � ���� ������  ");
	}
	else if (x1 == x2 && y1 == y2 && r1 == r2){
		printf("���������� ���������  ");
	}
	else if ((D == fabs(r1 - r2))){
		printf("���������� �������� �������  ");
	}
	else if ((D < fabs(r1 - r2))){
		printf("���������� �� ��������, ������ ���� ����� ������ ������  ");
	}
	
	system("pause");

}
*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#include <locale.h>

int main() 
{
	setlocale(LC_ALL, "rus");
	float zadst, bok, kr, door, polk;//����� �������
	float h, w, d;//������������������ ����������
	float pldvp, pldsp, pld;//��������� ����������
	float kolpol, hvsp, i;//��������������� ���������� ��� ���������� ���������� �����
	float masshk;//����� ������ �����
	do
	{
		printf("������� ������\n");
		scanf("%f", &h);
		if (h < 180.0 || h > 220.0)
		{
			printf("������� �������� ������ �� 180 �� 220 ��  \n");
		}
	} while (h < 180.0 || h > 220.0);
	do
	{
		printf("������� ������\n");
		scanf("%f", &w);
		if (w < 80 || w>120)
		{
			printf("������� �������� ������ �� 80 �� 120 ��  \n");
		}
	} while (w < 80 || w>120);
	do
	{
		printf("������� �������\n");
		scanf("%f", &d);
		if (d < 50 || d>90)
		{
			printf("������� �������� ������� �� 50 �� 90 ��  \n");
		}
	} while (d < 50 || d>90);
	hvsp = h;
	i = 0;
	do
	{
		i++;
		hvsp = hvsp - 41.5;
	} while (hvsp > 41.5);
	kolpol = i;
	pldvp = 0.82;
	pldsp = 0.55;
	pld = 0.7;
	zadst = h * w * 0.5*pldvp;
	bok = h * d * 1.5 * pldsp;
	kr = w * d * 1.5 * pldsp;
	door = h * w * 1 * pld;
	polk = d * (w - 1.5 * 2) * 1.5 * pldsp;//���� ������� ������� ����� ������ 15 ��, ��� � ����� ��� �� �����
	//����� ���� ���� ������ ��� ������� ������ �� 1.5 �� ������
	masshk = (zadst + 2 * bok + 2 * kr + 2 * door + kolpol * polk)/1000;
	printf("����� ����� = %f", masshk);
	system("pause");
}