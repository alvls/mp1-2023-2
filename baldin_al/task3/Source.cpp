#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <windows.h>
#include <conio.h>
using namespace std;

HANDLE Console = GetStdHandle(STD_OUTPUT_HANDLE);

void Create_Random_Number(int n, int r[])
{
	int i = 0, f = 0;
	srand(time(0));
	while (i < n)
	{
		r[i] = rand() % 10;
		for (int j = 0; j < i; j++)
		{
			if (r[i] == r[j] || r[0] == 0)
			{
				f = 1;
				break;
			}
		}
		if (f == 0)
			i++;
		f = 0;
	}
}

void GoToXY(short x, short y)
{
	SetConsoleCursorPosition(Console, { x,y });
}

void Name_of_Game()
{
	GoToXY(13, 0);
	printf("88''Yb 88   88 88     88     .dP'Y8        db    88b 88 8888b.       dP''b8  dP'Yb  Yb        dP .dP'Y8 \n");
	GoToXY(13, 1);
	printf("88__dP 88   88 88     88     `Ybo.'       dPYb   88Yb88  8I  Yb     dP   `' dP   Yb  Yb  db  dP  `Ybo.' \n");
	GoToXY(13, 2);
	printf("88''Yb Y8   8P 88  .o 88  .o o.`Y8b      dP__Yb  88 Y88  8I  dY     Yb      Yb   dP   YbdPYbdP   o.`Y8b \n");
	GoToXY(13, 3);
	printf("88oodP `YbodP' 88ood8 88ood8 8bodP'     dP''''Yb 88  Y8 8888Y'       YboodP  YbodP     YP  YP    8bodP' \n");
}

int main()
{
	setlocale(LC_ALL, "rus");

	system("color 2F");

	int n, r[5];
	int bull, cow, a;

	Name_of_Game();

	printf("\n Выберите длину загадываемого числа: \n - 2 \n - 3 \n - 4 \n - 5 \n");
	scanf_s("%d", &n);
	while (!(2 <= n && n <= 5))
	{
		MessageBoxW(NULL, L"Некорректное значение. Попробуйте ещё раз", L"Ошибка", MB_OK | MB_ICONEXCLAMATION);
		scanf_s("%d", &n);
	}
	Create_Random_Number(n, r);

	printf("\n Попробуйте отгадать: \n ");
	printf("--------------------- \n");
	do
	{
		bull = 0;
		cow = 0;
		int c[5], i = 0;
		scanf_s("%d", &a);

		while (a > 0)
		{
			c[n - i - 1] = a % 10;
			a = a / 10;
			i++;
		}

		if (i != n)
		{
			MessageBoxW(NULL, L"Число неверной длины. Введите ещё раз", L"Ошибка", MB_OK | MB_ICONEXCLAMATION);
			continue;
		}

		for (int i = 0; i < n; i++)
		{
			if (c[i] == r[i])
				bull++;
		}
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
			{
				if (c[i] == r[j])
					cow++;
			}
		}

		printf("Кол-во коров: %d Кол-во быков: %d \n", cow - bull, bull);
		printf("--------------------- \n");
	} while (bull != n);

	MessageBoxW(NULL, L"Вы угадали!!!", L"", MB_OK | MB_ICONASTERISK);

}

