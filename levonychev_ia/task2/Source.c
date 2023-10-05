#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#include <locale.h>
#include <time.h>


int main()
{
	srand(time(0));

	int num = rand() % 1000;
	int robot_num;
	int flag;
	int user_num = -1;
	int attempts = 0;
	char user_char, b;
	int min = 1, max = 999;

	setlocale(LC_ALL, "rus");

	do
	{
		printf("�������� ����� ���� (1 - ��������� ���������� �����, 2 - �� ����������� �����): ");
		scanf("%d", &flag);
	} while (!(flag == 1 || flag == 2));
	
	// ������ �����
	if (flag == 1)
	{
		printf("�� ������� ������ �����! ��������� �������� ����� �� 1 �� 999. ����������� ������� ���!\n\n");

		while (num != user_num)
		{
			scanf("%d", &user_num);
			attempts += 1;

			if (user_num == num)
			{
				printf("���������� �����: %d. �����������!\n", num);
				break;
			}

			if (user_num < num)
				printf("���������� ����� ������.\n\n");

			if (user_num > num)
				printf("���������� ����� ������.\n\n");
		}
	
	}

	// ������ �����
	else
	{
		printf("�� ������� ������ �����! ������� ����� �� 1 �� 999, � ��������� ������� ���!\n");

		do
		{	
			printf("���� �����: ");
			scanf("%d", &user_num);
		} while ((user_num < 1) || (user_num > 999));

		printf("����� ������������� ���������, ������� ������ \'<\', \'>\' ��� \'=\'\n");
		
		do
		{
			robot_num = (min + max) / 2;

			if (min == 998)
				robot_num = 999;

			printf("\n%d?\n", robot_num);
			attempts += 1;

			scanf("%c", &b);
			scanf("%c", &user_char);

			if (user_char == '<' && user_num > robot_num)
				printf("��� �������, �� ���� �����������...\n");
			else if (user_char == '<')
				max = robot_num;

			if (user_char == '>' && user_num < robot_num)
				printf("��� �������, �� ���� �����������...\n");
			else if (user_char == '>')
				min = robot_num;

			if (user_char == '=' && user_num != robot_num)
				printf("��� �������, �� ���� �����������...\n");

			if ((user_char == '<' || user_char == '>') && (user_num == robot_num))
				do
				{
					printf("��� �������, �� ���� �����������...\n");
					scanf("%c", &b);
					scanf("%c", &user_char);
				} while (user_char != '=');

		} while (robot_num != user_num);
		
		printf("\n� ������ ���� �����! ��� %d!\n", robot_num);
	}

	printf("���������� �������: %d\n\n", attempts);

	system("pause");
	return 0;
}