#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <locale.h>
#include <math.h>

/*
int main()
{	
	float x1, y1; // ���������� ������ ������ ����������
	float r1; // ������ ������ ����������
	float x2, y2; // ���������� ������ ������ ����������
	float r2; // ������ ������ ����������
	float d; // ��������� ����� �������� ���� �����������
	int flag1 = 0, flag2 = 0; // �������� ��������������� ��������

	setlocale(LC_ALL, "rus");

	printf("������� ����������(� � �) ������ ����������: ");
	scanf("%f %f", &x1, &y1);
	
	while (flag1 == 0)
	{
		printf("\n������� ������ ������ ����������: ");
		scanf("%f", &r1);
		if (r1 > 0)
			flag1 = 1;
		else
			printf("\n������ ������������ ������!\n");
	}

	printf("\n������� ����������(� � �) ������ ����������: ");
	scanf("%f %f", &x2, &y2);

	while (flag2 == 0)
	{
		printf("\n������� ������ ������ ����������: ");
		scanf("%f", &r2);
		if (r2 > 0)
			flag2 = 1;
		else
			printf("\n������ ������������ ������!\n");
	}

	d = sqrt(pow((x2 - x1), 2) + pow((y2 - y1), 2));

	if (x1 == x2 && y1 == y2 && r1 == r2)
		printf("\n���������� ���������.\n");
	
	if ((r1 + r2) == d)
		printf("\n���������� �������� ������� �������.\n");

	if ((fabs(r2 - r1) == d) && (!(x1 == x2 && y1 == y2 && r1 == r2)))
		printf("\n���������� �������� ���������� �������.\n");

	if ((r1 + r2) < d)
		printf("\n���������� �� ������������.\n");

	if (fabs(r2 - r1) > d)
		printf("\n���������� �� ������������(���� ������ ������).\n");

	if ((fabs(r2 - r1) < d) && (d < (r1 + r2)))
		printf("\n���������� ������������ � ���� ������.\n");

	system("pause");
	return 0;
}
*/


int main()
{
    setlocale(LC_ALL, "rus");

    float h; // ������ ������ ��������� ������ �� ��� (180-220��)
    float w; // ������ ������ ��������� ������ �� ��� (80-120��)
    float d; // ������� ������� �� ��� (50-90��)
    const float S1 = 0.5; // ������� ������ ��������� ������ �� ��� (5��)
    const float S2 = 1.5; // ������� ������� �� ��� (15��)
    const float S3 = 1; // ������� ������ �� ������ (10��)
    const float P1 = 0.75; // ��������� ��� (0.75 �/��^3)
    const float P2 = 1.1; // ��������� ��� (1.1 �/��^3)
    const float P3 = 0.6; // ��������� ������ (0.6 �/��^3)
    int count_shelf; // ���������� �����
    float m1, m2, m3, m4, m5, m; /* m1 - ����� ������ ������,
    m2 - ����� �������, m3 - ����� ������, m4 - ����� ������,
    m5 - ����� �����, m - ����� ����� */

    do
    {
        printf("������� ������ ����� (�� 180�� �� 220��): ");
        scanf("%f", &h);

    } while ((h < 180) || (h > 220));
    printf("\n");
    do
    {
        printf("������� ������ ����� (�� 80�� �� 120��): ");
        scanf("%f", &w);

    } while ((w < 80) || (w > 120));
    printf("\n");
    do
    {
        printf("������� ������� ����� (�� 50�� �� 90��): ");
        scanf("%f", &d);

    } while ((d < 50) || (d > 90));
    printf("\n");

    m1 = (P2 * h * w * S1) / 1000;
    m2 = (2 * P1 * h * d * S2) / 1000;
    m3 = (2 * P1 * w * d * S2) / 1000;
    m4 = (P3 * h * w * S3) / 1000;
    count_shelf = floor(h / 41.5);
    m5 = (count_shelf * P1 * (w - 3) * d * S2) / 1000;
    m = m1 + m2 + m3 + m4 + m5;
    printf("����� ������ ������: %g ��\n", m1);
    printf("����� ���� �������: %g ��\n", m2);
    printf("����� ������� � ������ ������: %g ��\n", m3);
    printf("����� ������: %g ��\n", m4);
    printf("����� �����: %g ��\n", m5);
    printf("����� �����: %g ��\n", m);

	system("pause");
    return 0;
}