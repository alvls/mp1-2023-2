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
    if (p->size == p->capacity) { // Если чек заполнен до предела, то увеличиваем его ёмкость в два раза
        p->capacity *= 2; // Увеличиваем ёмкость в два раза
        p->items = (product*)realloc(p->items, p->capacity * sizeof(product)); // Перевыделяем память под массив товаров с новой ёмкостью
        p->kolvo = (int*)realloc(p->kolvo, p->capacity * sizeof(int)); // Перевыделяем память под массив количества товаров с новой ёмкостью
    }
    for (int i = 0; i < p->size; i++) { // Проходим по всем товарам в покупке и ищем совпадение по штрих-коду с добавляемым товаром
        if (strcmp(p->items[i].barcode, item->barcode) == 0) { // Если нашли, то увеличиваем количество этого товара
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
    printf("Стоимость за единицу: %d руб.\n", p->price); // Выводим цену товара
    printf("Скидка: %d%%\n", p->discount); // Выводим скидку на товар
}

// Функция для вывода информации о покупке на экран в виде чека
void print_chek(chek* p) 
{
    int total_price = 0;
    int total_discount = 0;
    int final_price = 0;
    printf("Чек за покупку:\n");
    printf("-----------------------------------------------------------------\n");
    for (int i = 0; i < p->size; i++) { // Проходим по всем товарам в покупке и выводим информацию о каждом из них
        printf("%s - %d руб. - %d шт. - %d руб.\n", p->items[i].name, p->items[i].price, p->kolvo[i], p->items[i].price * p->kolvo[i]);
        total_price += p->items[i].price * p->kolvo[i]; // Увеличиваем общую стоимость товаров на стоимость текущего товара
        total_discount += p->items[i].price * p->kolvo[i] * p->items[i].discount / 100; // Увеличиваем суммарную скидку на скидку текущего товара
    }
    final_price = total_price - total_discount;
    printf("-----------------------------------------------------------------\n");
    printf("Общая стоимость товаров: %d руб.\n", total_price);
    printf("Суммарная скидка: %d руб.\n", total_discount);
    printf("Итоговая сумма к оплате: %d руб.\n", final_price);
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
    product* moloko = create_product("0001", "Молоко", 80, 10); // Создаем новый товар "Молоко" со штрих-кодом "1234", стоимостью 60 руб. и скидкой 10%
    product* tvorog = create_product("0003", "Творог", 49, 10);
    product* cir = create_product("0004", "Сыр", 71, 10);

    // ХБ изделия   
    product* hleb = create_product("1001", "Хлеб", 30, 5);
    product* sloyka = create_product("1002", "Слойка с малиной", 15, 5);
    product* baranki = create_product("1003", "Слойка с малиной", 70, 5);

    // фрукты/овощи
    product* kartofel = create_product("2001", "Картофель", 30, 3);
    product* arbuz = create_product("2001", "Арбуз", 25, 3);
    product* dinya = create_product("2001", "Дыня", 40, 3);

    // конец БД продуктов

    chek* p = create_chek(10); // Создаем новую покупку с емкостью 10 товаров

    while (1 == 1)
    {
        printf("Что вы хотите сделать? (введите цифру, соответствующую нужной функции)\n");
        printf("1 - сканировать новый товар\n");
        printf("2 - вывести описание товара\n");
        printf("3 - добавить товар в чек\n");
        printf("4 - сформировать чек за покупку\n");

        break;
    }

    print_product(moloko);

    free_chek(p);
    return 0;
}


/*
// Функция для поиска товара по штрих-коду среди тех, которые создаются в функции main
product *find_product_main(char *barcode, product *hleb, product *sloyka, product *baranki) 
{
    product *p = NULL;
    if (strcmp(barcode, hleb->barcode) == 0) 
    {
        p = hleb;
    } 

    else if (strcmp(barcode, sloyka->barcode) == 0) 
    {
        p = sloyka;
    } 

    else if (strcmp(barcode, baranki->barcode) == 0) 
    {
        p = baranki;
    }
    return p;
}
*/