#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>

int main() {
    setlocale(LC_ALL, "rus");
    int mode = 0, kolv = 0;
    srand(time(NULL));
    while (mode != 1 && mode != 2) {
        printf("Выберите режим [1/2]: ");
        scanf_s("%d", &mode);
    }
    if (mode == 1) {
        int rez = rand() % 1000;
        int guess = 0;
        printf("Число было загадано! Введите свое предположение: ");
        while (guess != rez) {
            kolv++;
            scanf_s("%d", &guess);
            if (guess < rez) {
                printf("Загаданное число больше. Введите свое предположение:\n");
            }
            else if (guess > rez) {
                printf("Загаданное число меньше. Введите свое предположение:\n");
            }
        }
        printf("Вы угадали! Количество попыток: %d\n", kolv);
    }
    else {
        int rez, l = 1, r = 1000;
        printf("Введите загаданное Вами число: ");
        scanf_s("%d", &rez);
        while (!(0 < rez && rez < 1000)) {
            printf("Так нечестно! Введите число в диапазоне от 1 до 999 включительно: ");
            scanf_s("%d", &rez);
        }
        int guess = (l + r) / 2;
        int first = 1;
        while (1) {
            kolv++;
            guess = (l + r) / 2;
            printf("Вы загадали число %d? ", guess);
            if (first) {
                printf("Введите \"<\", если загаданное число меньше, \">\", если загаданное число больше, или \"=\", если загаданное число равно предполагаемому. (Сейчас, например, нужно ввести ");
                if (guess == rez) {
                    printf("\"=\"");
                }
                else if (guess < rez) {
                    printf("\">\"");
                }
                else printf("\"<\"");
                printf(")\n");
                first = 0;
            }

            char c;
            scanf_s("%c", &c);
            while (c != '<' && c != '>' && c != '=') {
                printf("Введите символ из списка [<, >, =]: ");
                scanf_s("%c", &c);
            }
            if (c == '<') {
                r = (l + r) / 2;
            }
            else if (c == '=') {
                printf("Отлично! Количество затраченных попыток: %d\n", kolv);
                system("pause");
                return 0;
            }
            else {
                l = (l + r) / 2;
            }
        }

    }
    system("pause");
    return 0;
}