#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

//Ёмкость чека - количество товаров в чеке

// Структура для хранения информации о товаре
typedef struct 
{
    char barcode[5]; // ШК товара
    char name[50]; // Название товара
    int price; // цена товара (руб)
    int discount; // Скидка (в процентах)
} product;

// Структура для хранения чека
typedef struct
{
    product* items; // Массив товаров в покупке
    int* kolvo; // Массив количества каждого товара в покупке
    int size; // Размер items и kolvo
    int capacity; // Ёмкость items и kolvo
} chek;

// Функция для создания нового товара с заданными параметрами
product* create_product(char* barcode, char* name, int price, int discount) 
{
    product* p = (product*)malloc(sizeof(product)); // Выделяем память под структуру
    strcpy(p->barcode, barcode); // Копируем ШК в структуру
    strcpy(p->name, name); // Копируем название в структуру
    p->price = price; // Записываем цену в структуру
    p->discount = discount; // Записываем скидку в структуру
    return p; // Возвращаем указатель на созданный товар
}

// Функция для создания нового чека с заданной емкостью массивов
chek* create_chek(int capacity) 
{
    chek* p = (chek*)malloc(sizeof(chek)); // Выделяем память под структуру
    p->items = (product*)malloc(capacity * sizeof(product)); // Выделяем память под массив товаров
    p->kolvo = (int*)malloc(capacity * sizeof(int)); // Выделяем память под массив количества товаров
    p->size = 0; // Устанавливаем размер покупки равным нулю
    p->capacity = capacity; // Записываем ёмкость чека в структуру
    return p; // Возвращаем указатель на созданный чек
}

// Функция для добавления нового товара в чек с заданным количеством
void add_product(chek* p, product* item, int quantity) 
{
    if (p->size == p->capacity) // Если чек заполнен до предела, то увеличиваем его ёмкость в два раза
    { 
        p->capacity *= 2; // Увеличиваем ёмкость в два раза
        p->items = (product*)realloc(p->items, p->capacity * sizeof(product)); // Перевыделяем память под массив товаров с новой ёмкостью
        p->kolvo = (int*)realloc(p->kolvo, p->capacity * sizeof(int)); // Перевыделяем память под массив количества товаров с новой ёмкостью
    }
    for (int i = 0; i < p->size; i++) // Проходим по всем товарам в покупке и ищем совпадение по штрих-коду с добавляемым товаром
    { 
        if (strcmp(p->items[i].barcode, item->barcode) == 0) // Если нашли, то увеличиваем количество этого товара
        { 
            p->kolvo[i] += quantity;
            return;
        }
    }
    // Если не нашли совпадение, то добавляем новый товар в конец массива
    p->items[p->size] = *item;
    p->kolvo[p->size] = quantity;
    p->size++; // Увеличиваем размер покупки на единицу
}

// Функция для вывода информации о товаре на экран
void print_product(product* p) 
{
    printf("Штрих-код: %s\n", p->barcode); // Выводим ШК товара
    printf("Наименование: %s\n", p->name); // Выводим название товара
    printf("Цена: %d руб.\n", p->price); // Выводим цену товара
    printf("Скидка: %d%%\n", p->discount); // Выводим скидку на товар
    printf("\n\n");
}

// Функция для вывода информации о покупке на экран в виде чека
void print_chek(chek* p) 
{
    int total_price = 0;
    int total_discount = 0;
    int final_price = 0;
    printf("Чек за покупку:\n");
    printf("-----------------------------------------------------------------\n");
    for (int i = 0; i < p->size; i++) // Проходим по всем товарам в покупке и выводим информацию о каждом из них
    { 
        printf("%s - %d руб. - %d шт. - %d руб.\n", p->items[i].name, p->items[i].price, p->kolvo[i], p->items[i].price * p->kolvo[i]);
        total_price += p->items[i].price * p->kolvo[i]; // Увеличиваем общую стоимость товаров на стоимость текущего товара
        total_discount += p->items[i].price * p->kolvo[i] * p->items[i].discount / 100; // Увеличиваем суммарную скидку на скидку текущего товара
    }
    final_price = total_price - total_discount;
    printf("-----------------------------------------------------------------\n");
    printf("Общая стоимость товаров: %d руб.\n", total_price);
    printf("Суммарная скидка: %d руб.\n", total_discount);
    printf("Итоговая сумма к оплате: %d руб.\n", final_price);
    printf("\n\n");
}

int print_final_price(chek* p) // (просто переписал кусок функции вывода чека)
{
    int total_price = 0;
    int total_discount = 0;
    int final_price = 0;
    for (int i = 0; i < p->size; i++)
    {
        total_price += p->items[i].price * p->kolvo[i];
        total_discount += p->items[i].price * p->kolvo[i] * p->items[i].discount / 100;
        final_price = total_price - total_discount;
    }
    return final_price;
}

// Функция для поиска товаров в базе данных
product* find_product(char* barcode, product* moloko, product* tvorog, product* cir, product* hleb, product* sloyka, product* baranki, product* kartofel, product* arbuz, product* dinya, product* bag_b, product* bag_s)
{
    product* p = NULL;
    while(1 == 1)
    {
        if (strcmp(barcode, moloko->barcode) == 0)
        {
            p = moloko;
            break;
        }
        else if (strcmp(barcode, tvorog->barcode) == 0)
        {
            p = tvorog;
            break;
        }
        else if (strcmp(barcode, cir->barcode) == 0)
        {
            p = cir;
            break;
        }
        else if (strcmp(barcode, hleb->barcode) == 0)
        {
            p = hleb;
            break;
        }
        else if (strcmp(barcode, sloyka->barcode) == 0)
        {
            p = sloyka;
            break;
        }
        else if (strcmp(barcode, baranki->barcode) == 0)
        {
            p = baranki;
            break;
        }
        else if (strcmp(barcode, kartofel->barcode) == 0)
        {
            p = kartofel;
            break;
        }
        else if (strcmp(barcode, arbuz->barcode) == 0)
        {
            p = arbuz;
            break;
        }
        else if (strcmp(barcode, dinya->barcode) == 0)
        {
            p = dinya;
            break;
        }
        else if (strcmp(barcode, bag_b->barcode) == 0)
        {
            p = bag_b;
            break;
        }
        else if (strcmp(barcode, bag_s->barcode) == 0)
        {
            p = bag_s;
            break;
        }
        else
        {
            printf("Товар не найден\n");
            printf("Введите Штрих-код товара\n");
            p = NULL;
            scanf("%s", &barcode);
        }
    }
    return p;
}

// Функция для освобождения памяти, выделенной под покупку
void free_chek(chek* p) 
{
    free(p->items);
    free(p->kolvo);
    free(p);
}


int main()
{
    setlocale(LC_ALL, "rus");
    
    // начало БД продуктов

    // молочные продукты
    product* moloko = create_product("0001", "Молоко Отборное", 80, 10);
    product* tvorog = create_product("0003", "Творог Обезжиренный", 49, 10);
    product* cir = create_product("0004", "Сыр Российский", 71, 10);

    // ХБ изделия   
    product* hleb = create_product("1001", "Хлеб Бородинский", 30, 5);
    product* sloyka = create_product("1002", "Слойка с малиной", 15, 5);
    product* baranki = create_product("1003", "Баранки с маком", 70, 5);

    // фрукты/овощи
    product* kartofel = create_product("2001", "Картофель Отечественный", 30, 5);
    product* arbuz = create_product("2002", "Арбуз Отечественный", 25, 5);
    product* dinya = create_product("2003", "Дыня Торпеда", 40, 5);

    //прочие товары
    product* bag_b = create_product("3001", "Пакет 65*40см", 10, 0);
    product* bag_s = create_product("3002", "Пакет 57*30см", 7, 0);

    // конец БД продуктов

    chek* p = create_chek(10);
    int action;
    int kol;
    char barcode[5];
    product* pr = NULL;

    while (1 == 1)
    {
        printf("Что вы хотите сделать? (введите цифру, соответствующую нужной функции)\n");
        printf("1 - сканировать новый товар\n");
        printf("2 - вывести описание товара\n");
        printf("3 - добавить товар в чек\n");
        printf("4 - сформировать чек за покупку\n");
        printf("5 - Вывести итоговую сумму к оплате\n");
        printf("6 - завершить работу с программой\n");

        
        scanf("%d", &action);
        switch (action)
        {
        case 1:
            printf("Введите штрих-код товара.\n");
            scanf("%s", &barcode);
            pr = find_product(barcode, moloko, tvorog, cir, hleb, sloyka, baranki, kartofel, arbuz, dinya, bag_b, bag_s);
            break;

        case 2:
            if (pr == NULL)
            {
                printf("Введите штрих-код товара.\n");
                scanf("%s", &barcode);
                pr = find_product(barcode, moloko, tvorog, cir, hleb, sloyka, baranki, kartofel, arbuz, dinya, bag_b, bag_s);
            }
            system("cls");
            print_product(pr);
            break;

        case 3:
            if (pr == NULL)
            {
                printf("Введите штрих-код товара.\n");
                scanf("%s", &barcode);
                pr = find_product(barcode, moloko, tvorog, cir, hleb, sloyka, baranki, kartofel, arbuz, dinya, bag_b, bag_s);
            }
            printf("Введите количество товара\n");
            scanf("%d", &kol);
            add_product(p, pr, kol);
            break;

        case 4:
            system("cls");
            print_chek(p);
            break;

        case 5:
            printf("Итого к оплате: %d\n", print_final_price(p));
            break;

        case 6:
            free_chek(p);
            return 0;

        default:
            printf("Такого действия нет. Попробуйте ещё раз.\n");
            break;
        }
    }
}
