#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <time.h>

struct Apple_Store { //  структура - магазин
    char barcode[4]; // штрихкод
    char name[50]; // наименование товара
    int unit_cost;   // стоимость за единицу указывается в рублях
    int discount; // скидка в процентах
};

struct Apple_Store iPhone11 = {"2563", "iPhone 11 128GB", 59000, 15}; // 1-ый товар
struct Apple_Store iPhone12 = {"3199", "iPhone 12 64GB", 70000, 10}; // 2-ой товар
struct Apple_Store iPhone13 = {"4796", "iPhone 13 256GB", 102000, 10}; // 3-ий товар
struct Apple_Store iPhone14_1 = {"8571", "iPhone 14 128GB ", 87000, 10};  //4-ый товар
struct Apple_Store iPhone14_2 = {"8574", "iPhone 14 Pro Max 1TB ", 212000, 10}; // 5-ый товар
struct Apple_Store iPhone15_1 = {"9231", "iPhone 15 128GB", 130000, 5}; // 6-ой товар
struct Apple_Store iPhone15_2 = {"9238", "iPhone 15 Pro Max 512GB", 284000, 5}; // 7-ой товар
struct Apple_Store iPad_Air_2022 = {"6656", "iPad Air 2022 64GB", 70000, 20}; // 8-ой товар
struct Apple_Store iPad_Pro_2022 = {"7777", "iPad Pro 2022 128GB", 104000, 20}; // 9-ый товар
struct Apple_Store MacBook_Air_15inch = {"8898", "MacBook Air 15-inch 2023 512GB", 190000, 25}; // 10-ый товар
struct Apple_Store MacBook_Air_13inch = {"7434", "MacBook Air 13-inch 2022 2TB", 336000, 25}; // 11-ый товар
struct Apple_Store MacBook_Pro_16inch = {"9999", "MacBook Pro 16-inch 2023 8TB", 976000, 20}; // 12-ый товар
struct Apple_Store AirPods_Pro = {"6538", "AirPods Pro 2nd generation 2023 USB-C", 33000, 35}; // 13-ый товар
struct Apple_Store AirPods_Max = {"8667", "AirPods Max USB-C", 75000, 30}; // 14-ый товар
struct Apple_Store Watch_Ultra_2 = {"9787", "Watch Ultra 2 GPS", 120000, 25}; // 15-ый товар

// функция, выдающая по штрихкоду описание товара
void description(int b) {
    if (b == 2563)
        printf("Наименование: %s. Стоимость за единицу: %d рублей. Возможная скидка (в процентах): %d. \n", iPhone11.name, iPhone11.unit_cost, iPhone11.discount);
    else if (b == 3199)
        printf("Наименование: %s. Стоимость за единицу: %d рублей. Возможная скидка (в процентах): %d. \n", iPhone12.name, iPhone12.unit_cost, iPhone12.discount);
    else if (b == 4796)
        printf("Наименование: %s. Стоимость за единицу: %d рублей. Возможная скидка (в процентах): %d. \n", iPhone13.name, iPhone13.unit_cost, iPhone13.discount);
    else if (b == 8571)
        printf("Наименование: %s. Стоимость за единицу: %d рублей. Возможная скидка (в процентах): %d. \n", iPhone14_1.name, iPhone14_1.unit_cost, iPhone14_1.discount);
    else if (b == 8574)
        printf("Наименование: %s. Стоимость за единицу: %d рублей. Возможная скидка (в процентах): %d. \n", iPhone14_2.name, iPhone14_2.unit_cost, iPhone14_2.discount);
    else if (b == 9231)
        printf("Наименование: %s. Стоимость за единицу: %d рублей. Возможная скидка (в процентах): %d. \n", iPhone15_1.name, iPhone15_1.unit_cost, iPhone15_1.discount);
    else if (b == 9238)
        printf("Наименование: %s. Стоимость за единицу: %d рублей. Возможная скидка (в процентах): %d. \n", iPhone15_2.name, iPhone15_2.unit_cost, iPhone15_2.discount);
    else if (b == 6656)
        printf("Наименование: %s. Стоимость за единицу: %d рублей. Возможная скидка (в процентах): %d. \n", iPad_Air_2022.name, iPad_Air_2022.unit_cost, iPad_Air_2022.discount);
    else if (b == 7777)
        printf("Наименование: %s. Стоимость за единицу: %d рублей. Возможная скидка (в процентах): %d. \n", iPad_Pro_2022.name, iPad_Pro_2022.unit_cost, iPad_Pro_2022.discount);
    else if (b == 8898)
        printf("Наименование: %s. Стоимость за единицу: %d рублей. Возможная скидка (в процентах): %d. \n", MacBook_Air_15inch.name, MacBook_Air_15inch.unit_cost, MacBook_Air_15inch.discount);
    else if (b == 7434)
        printf("Наименование: %s. Стоимость за единицу: %d рублей. Возможная скидка (в процентах): %d. \n", MacBook_Air_13inch.name, MacBook_Air_13inch.unit_cost, MacBook_Air_13inch.discount);
    else if (b == 9999)
        printf("Наименование: %s. Стоимость за единицу: %d рублей. Возможная скидка (в процентах): %d. \n", MacBook_Pro_16inch.name, MacBook_Pro_16inch.unit_cost, MacBook_Pro_16inch.discount);
    else if (b == 6538)
        printf("Наименование: %s. Стоимость за единицу: %d рублей. Возможная скидка (в процентах): %d. \n", AirPods_Pro.name, AirPods_Pro.unit_cost, AirPods_Pro.discount);
    else if (b == 8667)
        printf("Наименование: %s. Стоимость за единицу: %d рублей. Возможная скидка (в процентах): %d. \n", AirPods_Max.name, AirPods_Max.unit_cost, AirPods_Max.discount);
    else if (b == 9787)
        printf("Наименование: %s. Стоимость за единицу: %d рублей. Возможная скидка (в процентах): %d. \n", Watch_Ultra_2.name, Watch_Ultra_2.unit_cost, Watch_Ultra_2.discount);
    else if (b == 0) // 0 - вывод чека
        printf("-------------------------------------------------------------------------  \n");
    else
        printf("Наименование с таким штрих-кодом не существует в 'Apple Store'. \n");
}

// функция, добавляющая в чек 1 единицу товара с соответствующим штрихкодом b
int adding_to_check(int b) {
    if (b == 2563)
        return 1;
    else if (b == 3199)
        return 2;
    else if (b == 4796)
        return 3;
    else if (b == 8571)
        return 4;
    else if (b == 8574)
        return 5;
    else if (b == 9231)
        return 6;
    else if (b == 9238)
        return 7;
    else if (b == 6656)
        return 8;
    else if (b == 7777)
        return 9;
    else if (b == 8898)
        return 10;
    else if (b == 7434)
        return 11;
    else if (b == 9999)
        return 12;
    else if (b == 6538)
        return 13;
    else if (b == 8667)
        return 14;
    else if (b == 9787)
        return 15;
    else
        return 0;
}

// функция, считающая стоимость всех товаров в чеке без учёта возможных скидок
int creating_a_check(int i, int count) {
    int sum = 0;
    if (i == 0)
        sum = count * iPhone11.unit_cost;
    else if (i == 1)
        sum = count * iPhone12.unit_cost;
    else if (i == 2)
        sum = count * iPhone13.unit_cost;
    else if (i == 3)
        sum = count * iPhone14_1.unit_cost;
    else if (i == 4)
        sum = count * iPhone14_2.unit_cost;
    else if (i == 5)
        sum = count * iPhone15_1.unit_cost;
    else if (i == 6)
        sum = count * iPhone15_2.unit_cost;
    else if (i == 7)
        sum = count * iPad_Air_2022.unit_cost;
    else if (i == 8)
        sum = count *  iPad_Pro_2022.unit_cost;
    else if (i == 9)
        sum = count *  MacBook_Air_15inch.unit_cost;
    else if (i == 10)
        sum = count *  MacBook_Air_13inch.unit_cost;
    else if (i == 11)
        sum = count *  MacBook_Pro_16inch.unit_cost;
    else if (i == 12)
        sum = count *  AirPods_Pro.unit_cost;
    else if (i == 13)
        sum = count *  AirPods_Max.unit_cost;
    else if (i == 14)
        sum = count *  Watch_Ultra_2.unit_cost;
    return sum;
}

// функция, считающая стоимость всех товаров в чеке с учётом скидок, случайно выбранных на разные наименования товаров
int creating_a_check_with_discount(int i, int count) {
    int sum = 0;
    srand(time(0));
    int c = rand() % 2; // 1 - скидка есть, 0 - скидки нет
    if (i == 0) {
        sum = count * iPhone11.unit_cost;
        if (c == 1)
            sum -= count * (iPhone11.unit_cost / 100) * iPhone11.discount;
        printf("%s - %d рублей/шт. - %d шт. - %d рублей. \n", iPhone11.name, iPhone11.unit_cost, count, sum); }
    else if (i == 1) {
        sum = count * iPhone12.unit_cost;
        if (c == 1)
            sum -= count * (iPhone12.unit_cost / 100) * iPhone12.discount;
        printf("%s - %d рублей/шт. - %d шт. - %d рублей. \n", iPhone12.name, iPhone12.unit_cost, count, sum); }
    else if (i == 2) {
        sum = count * iPhone13.unit_cost;
        if (c == 1)
            sum -= count * (iPhone13.unit_cost / 100) * iPhone13.discount;
        printf("%s - %d рублей/шт. - %d шт. - %d рублей. \n", iPhone13.name, iPhone13.unit_cost, count, sum); }
    else if (i == 3) {
        sum = count * iPhone14_1.unit_cost;
        if (c == 1)
            sum -= count * (iPhone14_1.unit_cost / 100) * iPhone14_1.discount;
        printf("%s - %d рублей/шт. - %d шт. - %d рублей. \n", iPhone14_1.name, iPhone14_1.unit_cost, count, sum); }
    else if (i == 4) {
        sum = count * iPhone14_2.unit_cost;
        if (c == 1)
            sum -= count * (iPhone14_2.unit_cost / 100) * iPhone14_2.discount;
        printf("%s - %d рублей/шт. - %d шт. - %d рублей. \n", iPhone14_2.name, iPhone14_2.unit_cost, count, sum); }
    else if (i == 5) {
        sum = count * iPhone15_1.unit_cost;
        if (c == 1)
            sum -= count * (iPhone15_1.unit_cost / 100) * iPhone15_1.discount;
        printf("%s - %d рублей/шт. - %d шт. - %d рублей. \n", iPhone15_1.name, iPhone15_1.unit_cost, count, sum); }
    else if (i == 6) {
        sum = count * iPhone15_2.unit_cost;
        if (c == 1)
            sum -= count * (iPhone15_2.unit_cost / 100) * iPhone15_2.discount;
        printf("%s - %d рублей/шт. - %d шт. - %d рублей. \n", iPhone15_2.name, iPhone15_2.unit_cost, count, sum); }
    else if (i == 7) {
        sum = count * iPad_Air_2022.unit_cost;
        if (c == 1)
            sum -= count * (iPad_Air_2022.unit_cost / 100) * iPad_Air_2022.discount;
        printf("%s - %d рублей/шт. - %d шт. - %d рублей. \n", iPad_Air_2022.name, iPad_Air_2022.unit_cost, count, sum); }
    else if (i == 8) {
        sum = count *  iPad_Pro_2022.unit_cost;
        if (c == 1)
            sum -= count * (iPad_Pro_2022.unit_cost / 100) * iPad_Pro_2022.discount;
        printf("%s - %d рублей/шт. - %d шт. - %d рублей. \n", iPad_Pro_2022.name, iPad_Pro_2022.unit_cost, count, sum); }
    else if (i == 9) {
        sum = count *  MacBook_Air_15inch.unit_cost;
        if (c == 1)
            sum -= count * (MacBook_Air_15inch.unit_cost / 100) * MacBook_Air_15inch.discount;
        printf("%s - %d рублей/шт. - %d шт. - %d рублей. \n", MacBook_Air_15inch.name, MacBook_Air_15inch.unit_cost, count, sum); }
    else if (i == 10) {
        sum = count *  MacBook_Air_13inch.unit_cost;
        if (c == 1)
            sum -= count * (MacBook_Air_13inch.unit_cost / 100) * MacBook_Air_13inch.discount;
        printf("%s - %d рублей/шт. - %d шт. - %d рублей. \n", MacBook_Air_13inch.name, MacBook_Air_13inch.unit_cost, count, sum); }
    else if (i == 11) {
        sum = count *  MacBook_Pro_16inch.unit_cost;
        if (c == 1)
            sum -= count * (MacBook_Pro_16inch.unit_cost / 100) * MacBook_Pro_16inch.discount;
        printf("%s - %d рублей/шт. - %d шт. - %d рублей. \n", MacBook_Pro_16inch.name, MacBook_Pro_16inch.unit_cost, count, sum); }
    else if (i == 12) {
        sum = count *  AirPods_Pro.unit_cost;
        if (c == 1)
            sum -= count * (AirPods_Pro.unit_cost / 100) * AirPods_Pro.discount;
        printf("%s - %d рублей/шт. - %d шт. - %d рублей. \n", AirPods_Pro.name, AirPods_Pro.unit_cost, count, sum); }
    else if (i == 13) {
        sum = count *  AirPods_Max.unit_cost;
        if (c == 1)
            sum -= count * (AirPods_Max.unit_cost / 100) * AirPods_Max.discount;
        printf("%s - %d рублей/шт. - %d шт. - %d рублей. \n", AirPods_Max.name, AirPods_Max.unit_cost, count, sum); }
    else if (i == 14) {
        sum = count *  Watch_Ultra_2.unit_cost;
        if (c == 1)
            sum -= count * (Watch_Ultra_2.unit_cost / 100) * Watch_Ultra_2.discount;
        printf("%s - %d рублей/шт. - %d шт. - %d рублей. \n", Watch_Ultra_2.name, Watch_Ultra_2.unit_cost, count, sum); }
    return sum;
}

void main() {
    setlocale(LC_ALL, "rus");
    int b; // штрихкод, вводимый пользователем в виде целого числа
    char strihcode[4] = {'0000'}; // штрихкод, вводимый пользователем в виде массива символов
    int count[15] = {0}; // количество единиц каждого наименования товара в чеке
    int final_sum = 0; // общая стоимость
    int total_discount = 0; // суммарная скидка
    int final_sum_with_discount = 0; // итоговая стоимость с учетом скидок
    int check_size = 0; // размер чека (в единицах товара)
    int flag_stop;
    
    printf("Добро пожаловать в магазин Apple-техники 'Apple Store'! У нас есть на выбор 15 наименований товаров, для которых мы укажем штрих-коды: \n");
    printf("2563 3199 4796 6538 6656 7434 7777 8571 8574 8667 8898 9231 9238 9787 9999 \n");
    printf("Начинайте шоппинг! Вводите заинтересовавшие вас штрихкоды, а мы будем добавлять эти товары вам в чек! \n");
    printf("Наличие скидки на каждое наименование определяется случайным образом. \n");
    printf("Или введите stop, если хотите посмотреть чек и перейти к оплате: \n");
    if ((strihcode[0] == 's') && (strihcode[1] == 't') && (strihcode[2] == 'o') && (strihcode[3] == 'p'))
        flag_stop = 1;
    while (flag_stop != 1) { // stop - вывод чека
        for (int i = 0; i < 4; i++)
              scanf("%c", &strihcode[i]);
        if ((strihcode[0] == 's') && (strihcode[1] == 't') && (strihcode[2] == 'o') && (strihcode[3] == 'p'))
            flag_stop = 1;
        if (flag_stop != 1) {
            b = atoi(strihcode);
            description(b); // выводим описание наименования товара с введённым штрихкодом
            int number = adding_to_check(b); // присваиваем порядковый номер наименования товара в ассортименте
            if (number > 0) // если number = 0, значит пользователь ввел неправильный штрихкод
                count[number - 1]++; // считаем количество единиц данного товара в чеке (сдвиг в индексе элементов массива на 1)
        }
        while (getchar() != '\n')
            ;
        for (int i = 0; i < 4; i++)
            strihcode[i] = '0';
    }
    
    // подсчет общей суммы и итоговой суммы(со скидками)
    for (int i = 0; i < 15; i++) { // индексация на 1 меньше, чем в ассортименте
        if (count[i] > 0) { // проверяем наличие каждого наименования товара в чеке
            final_sum_with_discount += creating_a_check_with_discount(i, count[i]);
            final_sum += creating_a_check(i, count[i]);
        }
    }
    
    // подсчет размера чека
    for (int i = 0; i < 15; i++)
        if (count[i] != 0)
            check_size += count[i];
    
    if (check_size == 0)
        // вывод предупреждения
        printf("Чек должен содержать как минимум 1 позицию! \n");
    else {
        // вывод чека
        printf("Чек: \n"); 
        printf("-------------------------------------------------------------------------  \n");
        total_discount = final_sum - final_sum_with_discount;
        printf("Общая стоимость: %d рублей. \n", final_sum);
        if (final_sum > final_sum_with_discount)
            printf("Поздравляем! У вас действует скидка! \n");
        printf("Суммарная скидка: %d рублей. \n", total_discount);
        printf("Итоговая стоимость (с учётом скидок): %d рублей. \n", final_sum_with_discount);
        printf("-------------------------------------------------------------------------  \n");
    }
}
