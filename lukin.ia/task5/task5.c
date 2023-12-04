#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#include <io.h>
#include <time.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include <omp.h>
struct _finddata_t c_file;
struct _finddata_t* c_file_2;//его будем портить
intptr_t hFile;

void incr(int size)
{
	int count = 0;
	printf("\nСписок файлов\n\n");
	printf("Файл         Дата %24c   Размер\n", ' ');
	printf("----         ---- %24c   ----\n", ' ');
	for (int i = 0; i < size; i++)
	{
		char buffer[30];
		ctime_s(buffer, _countof(buffer), &c_file_2[i].time_write);
		if (count <= 20)
		{
			printf("%-12.12s %.24s  %10ld Байт\n", c_file_2[i].name, buffer, c_file_2[i].size);
		}
		count++;
		_findclose(hFile);
	}
	printf("\nКоличество файлов в каталоге: %d\n", count);
}

void decr(int size)
{
	int count = 0;
	printf("\nСписок файлов:\n\n");
	printf("Файл         Дата %24c   Размер\n", ' ');
	printf("----         ---- %24c   ----\n", ' ');
	for (int i = size - 1; i >= 0; i--)
	{
		char buffer[30];
		ctime_s(buffer, _countof(buffer), &c_file_2[i].time_write);
		if (count <= 20)
		{
			printf("%-12.12s %.24s  %10ld Байт\n", c_file_2[i].name, buffer, c_file_2[i].size);
		}
		count++;
		_findclose(hFile);
	}
	printf("\nКоличество файлов в каталоге: %d\n", count);
}

void bubble(int size)
{
	struct _finddata_t vsp;
	int i, j;
	for (i = 0; i < size; i++)
	{
		for(j = size - 1; j > i; j--)
		{
			if (c_file_2[j].size < c_file_2[j-1].size)
			{
				vsp = c_file_2[j];
				c_file_2[j] = c_file_2[j-1];
				c_file_2[j-1] = vsp;
			}
		}
	}
}

void selection(int size)
{
	struct _finddata_t vsp;
	int i, j, k;
	for (i = 0; i < size; i++)
	{
		k = i;
		vsp = c_file_2[i];
		for (j = i + 1; j < size; j++)
		{
			if (c_file_2[j].size < vsp.size)
			{
				k = j;
				vsp = c_file_2[j];
			}
		}
		c_file_2[k] = c_file_2[i];
		c_file_2[i] = vsp;
	}
}

void insertion(int size)
{
	struct _finddata_t vsp;
	int i, j;
	for (i = 0; i < size; i++)
	{
		vsp = c_file_2[i];
		for (j = i - 1; j >= 0 && c_file_2[j].size > vsp.size; j--)
		{
			c_file_2[j + 1] = c_file_2[j];
		}
		c_file_2[j + 1] = vsp;
	}
}

void merge1(int left, int mid, int right)
{
	struct _finddata_t* vsp = (struct _finddata_t*)malloc((right - left + 1) * sizeof(struct _finddata_t));
	int k = 0, i = left, j = mid + 1;
	while (k < (right - left + 1))
	{
		while ((i <= mid) && (j <= right))
		{
			if (c_file_2[i].size < c_file_2[j].size)
			{
				vsp[k] = c_file_2[i];
				i++;
			}
			else
			{
				vsp[k] = c_file_2[j];
				j++;
			}
			k++;
		}
		if (i > mid)
		{
			while (j <= right)
			{
				vsp[k] = c_file_2[j];
				j++;
				k++;
			}
		}
		else
		{
			while (i <= mid)
			{
				vsp[k] = c_file_2[i];
				i++;
				k++;
			}
		}
	}
	for (i = left; i <= right; i++)
	{
		c_file_2[i] = vsp[i - left];
	}
	free(vsp);
}

void merge(int left, int right)
{
	int mid;
	if (left == right)
	{
		return;
	}
	if ((left + right) % 2 != 0)
	{
		mid = (left + right) / 2;
	}
	else
	{
		mid = (left + right) / 2;
	}
	merge(left, mid);
	merge(mid + 1, right);
	merge1(left, mid, right);
}

void hoara(struct _finddata_t* a,int size)
{
	int i = 0, j = size - 1;
	struct _finddata_t vsp, p;
	p = a[size >> 1];
	do
	{
		while (a[i].size < p.size)
		{
			i++;
		}
		while (a[j].size > p.size)
		{
			j--;
		}
		if (i <= j)
		{
			vsp = a[i];
			a[i] = a[j];
			a[j] = vsp;
			i++;
			j--;
		}
	} while (i <= j);
	if (j > 0)
	{
		hoara(a, j);
	}
	if (size > i)
	{
		hoara(a + i, size - i);
	}
}

void shealla(int size)

{
	int vsp1 = 4, j;
	struct _finddata_t vsp;
	while (vsp1 > 0)
	{
		for (int i = 0; i < size; i++)
		{
			j = i;
			vsp = c_file_2[i];
			while ((j >= vsp1) && (c_file_2[j - vsp1].size > vsp.size))
			{
				c_file_2[j] = c_file_2[j - vsp1];
				j = j - vsp1;
			}
			c_file_2[j] = vsp;
		}
		if (vsp1 > 1)
		{
			vsp1 /= 2;
		}
		else
		{
			vsp1 = 0;
		}
	}
}
void counting(int size)
{
	struct _finddata_t vsp;
	int* array;
	int  i, vsp1 = 0, k = 0, j;
	for (i = 0; i < size; i++)
	{
		if (c_file_2[i].size > c_file_2[vsp1].size)
		{
			vsp1 = i;
		}
	}
	vsp1 = c_file_2[vsp1].size + 1;
	array = (int*)malloc(vsp1 * sizeof(int));
	memset(array, 0, (vsp1 * sizeof(int)));
	for (i = 0; i < size; i++)
	{
		array[c_file_2[i].size]++;
	}
	for (i = 0; i < vsp1; i++)
	{
		while (array[i] > 0)
		{
			j = k;
			while (i != c_file_2[j].size)
			{
				j++;
			}
			vsp = c_file_2[k];
			c_file_2[k] = c_file_2[j];
			c_file_2[j] = vsp;
			k++;
			array[i]--;
		}
	}
	free(array);
}

void copy(struct _finddata_t arr[], int size)
{
	for (int i = 0; i < size; i++)
	{
		c_file_2[i] = arr[i];
	}
}

int incr_or_decr()
{
	int choice, itog = 0;
	do
	{
		printf("\nБудем сортировать по возрастанию(1) или убыванию(0)?\n");
		printf("Ввод: ");
		scanf("%i", &choice);
		while (getchar() != '\n');
			if (choice != 1 && choice != 0)
			{
				printf("\nЯ вас не понимаю");
			}
			else if (choice == 1)
			{
				itog = 1;
				return 1;
			}
			else if (choice == 0)
			{
				itog = 1;
				return 0;
			}
	} while (itog == 0);
}

int exit_()
{
	int choice;
	int itog;
	do
	{
		printf("\nХотите ли вы сканировать дальше?(Да - 1/Нет - 0)\n");
		printf("Ввод: ");
		scanf("%i", &choice);
		while (getchar() != '\n');
			if (choice != 0 && choice != 1)
			{
				printf("Не понимаю вас!\n");
				itog = 0;
			}
			else
			{
				itog = 1;
			}
	} while (itog != 1);
	if (choice == 1)
		return;
	else if (choice == 0)
	{
		return 5;
	}
}

int main()
{
	struct _finddata_t c_file;
	setlocale(LC_ALL, "rus");
	int i = 0, itog = 0, pre_itog = 0,ex = 0, vsp = 0, count = 0;
	int final_ch;
	int choice;
	int size;
	int sort;
	double time1, time2;
	struct _finddata_t* c_file_1;
	//ex = exit_();
	//if (ex == 5)
	//return 0;
	char wtf[300];//way to file
	c_file_1 = (struct _finddata_t*)malloc(1 * sizeof(struct _finddata_t));
	do
	{
		printf("Пожалуйста, введите путь до каталога...");
		printf("\nПример: C:\\Users\\dizbv\\Videos\\TheWitcher3\n");
		printf("\nПредупреждение!!!\nФайловый менеджер работает лишь с буквами английского языка!\nУбедитесь, что в вашем пути к каталогу нет посторонних символов(к ним относится и пробел)!!!\n");
		printf("Примечания:\n1.Работа программы не предусматривает анализ размеров папок в каталоге\nВ отчете программы будут фигурировать только лишь файлы\nЧтобы работать с конкретной папкой, нужно указать именно на нее\n2.Программа рассчитана для работы с каталогами, в коих не более 21 файла\nИначе показаны будут только первые 21 сверху или снизу\n");
		printf("Введите каталог: ");
		scanf("%s", &wtf);
		strcat(wtf, "\\*.*");
		while (getchar() != '\n');
			if ((hFile = _findfirst(wtf, &c_file)) != -1L)
			{
				i = 0;
				do
				{
					if (c_file.size > 0)
					{
						i++;//надо понять, сколько файлов в каталоге, чтобы правильно выделить память
					}
				} while (_findnext(hFile, &c_file) == 0);
				_findclose(hFile);
				size = i;//запомнили кол-во файлов в отдельную переменную 
				c_file_1 = (struct _finddata_t*)malloc(size * sizeof(struct _finddata_t));
				if ((hFile = _findfirst(wtf, &c_file)) != -1L)
				{
					i = 0;
					do
					{
						if (c_file.size > 0)
						{
							c_file_1[i] = c_file;
							i++;
						}
					} while (_findnext(hFile, &c_file) == 0);//теперь в памяти последовательно стоят size копий структур c_file под названием c_file_1[i] про каждый из файлов в каталоге
				}
				_findclose(hFile);
				c_file_2 = (struct _finddata_t*)malloc(size * sizeof(struct _finddata_t));
				do
				{
					do
					{
						printf("\nВыберите метод сортировки:");
						printf("\n1.Пузырьком");
						printf("\n2.Выбором");
						printf("\n3.Вставками");
						printf("\n4.Слиянием");
						printf("\n5.Хоара");
						printf("\n6.Шеалла");
						printf("\n7.Подсчетом\n");
						printf("\nВвод: ");
						scanf("%i", &choice);
						while (getchar() != '\n');
							if (choice != 1 && choice != 2 && choice != 3 && choice != 4 && choice != 5 && choice != 6 && choice != 7)
							{
								printf("\nНе понимаю вас!");
							}
							else
							{
								vsp = 1;
							}
					} while (vsp == 0);
					vsp = 0;
					if (choice == 1)
					{
						sort = incr_or_decr();
						time1 = omp_get_wtime();
						copy(c_file_1, size);// c_file_1 не меняется и имеет первоначальную информацию (несортированную) о файлах в каталоге: чтобы можно было менять вариант сортировки, не повторяя алгоритм выше
						bubble(size);
						time2 = omp_get_wtime();
						if (sort == 1)
						{
							incr(size);
						}
						else if (sort == 0)
						{
							decr(size);
						}
						printf("\nВремя сортировки *Пузырьком* составило: %0.8f сек\n", time2 - time1 );
					}
					else if (choice == 2)
					{
						sort = incr_or_decr();
						time1 = omp_get_wtime();
						copy(c_file_1, size);
						selection(size);
						time2 = omp_get_wtime();
						if (sort == 1)
						{
							incr(size);
						}
						else if (sort == 0)
						{
							decr(size);
						}
						printf("\nВремя сортировки *Выбором* составило: %0.8f сек\n", time2 - time1);
					}
					else if (choice == 3)
					{
						sort = incr_or_decr();
						time1 = omp_get_wtime();
						copy(c_file_1, size);
						insertion(size);
						time2 = omp_get_wtime();
						if (sort == 1)
						{
							incr(size);
						}
						else if (sort == 0)
						{
							decr(size);
						}
						printf("\nВремя сортировки *Вставками* составило: %0.8f сек\n", time2 - time1);
					}
					else if (choice == 4)
					{
						sort = incr_or_decr();
						time1 = omp_get_wtime();
						copy(c_file_1, size);
						merge(0, size - 1);
						time2 = omp_get_wtime();
						if (sort == 1)
						{
							incr(size);
						}
						else if (sort == 0)
						{
							decr(size);
						}
						printf("\nВремя сортировки *Слиянием* составило: %0.8f сек\n", time2 - time1);
					}
					else if (choice == 5)
					{
						sort = incr_or_decr();
						time1 = omp_get_wtime();
						copy(c_file_1, size);
						hoara(c_file_2, size);
						time2 = omp_get_wtime();
						if (sort == 1)
						{
							incr(size);
						}
						else if (sort == 0)
						{
							decr(size);
						}
						printf("\nВремя сортировки *Хоара* составило: %0.8f сек\n", time2 - time1);
					}
					else if (choice == 6)
					{
						sort = incr_or_decr();
						time1 = omp_get_wtime();
						copy(c_file_1, size);
						shealla(size);
						time2 = omp_get_wtime();
						if (sort == 1)
						{
							incr(size);
						}
						else if (sort == 0)
						{
							decr(size);
						}
						printf("\nВремя сортировки *Шеалла* составило: %0.8f сек\n", time2 - time1);
					}
					else if (choice == 7)
					{
						sort = incr_or_decr();
						time1 = omp_get_wtime();
						copy(c_file_1, size);
						counting(size);
						time2 = omp_get_wtime();
						if (sort == 1)
						{
							incr(size);
						}
						else if (sort == 0)
						{
							decr(size);
						}
						printf("\nВремя сортировки *Подсчетом* составило: %0.8f сек\n", time2 - time1);
					}
					do
					{
						printf("Доступные действия:\n1.Сменить каталог\n2.Остаться в текущем каталоге\n3.Выйти\n");
						printf("Ввод: ");
						scanf("%i", &final_ch);
						while (getchar() != '\n');
							if (final_ch != 1 && final_ch != 2 && final_ch != 3)
							{
								printf("\nНе понимаю вас!!!\n");
							}
							else
							{
								vsp = 1;
								if (final_ch == 1)
								{
									pre_itog = 1;
								}
								else if (final_ch == 2)
								{
									pre_itog = 0;
								}
								else if (final_ch == 3)
								{
									return;
								}
							}
					} while (vsp == 0);
				} while (pre_itog == 0);
			}
			else
			{
				printf("\nНеверный путь, либо пустой каталог!!!\n");
				ex = exit_();
				if (ex == 5)
					return 0;
				itog = 0;
			}
	} while (itog != 1);
	system("pause");
}