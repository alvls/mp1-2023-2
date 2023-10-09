#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>

int main() {
    setlocale(LC_ALL, "rus");
    int mode = 0, kolv = 0;
    srand(time(NULL));
    while (mode != 1 && mode != 2) {
        printf("Выберите режим [1/2]: "); // choose mode
        scanf_s("%d", &mode);
    }
    if (mode == 1) {
        int rez = rand() % 1000;
        int guess = 0;
        printf("Число было загадано! Введите свое предположение: "); // the number is taken! Enter you guess:
        while (guess != rez) {
            kolv++;
            scanf_s("%d", &guess);
            if (guess < rez) {
                printf("Загаданное число больше. Введите свое предположение:\n"); // the number is bigger.  Enter you guess:
            }
            else if (guess > rez) {
                printf("Загаданное число меньше. Введите свое предположение:\n"); // the number is smaller.  Enter you guess:
            }
        }
        printf("Вы угадали! Количество попыток: %d\n", kolv); // You guessed it! Number of attempts:
    }
    else {
        int rez, l = 1, r = 1000;
        printf("Введите загаданное Вами число: "); // enter the number you've made
        scanf_s("%d", &rez);
        while (!(0 < rez && rez < 1000)) {
            printf("Так нечестно! Введите число в диапазоне от 1 до 999 включительно: "); // It's not fair! Enter a number in the range from 1 to 999 inclusive:
            scanf_s("%d", &rez);
        }
        int guess = (l + r) / 2;
        int first = 1;
        while (1) {
            kolv++;
            guess = (l + r) / 2;
            printf("Вы загадали число %d? ", guess); // Have you made number %d?
            if (first) {
                printf("Введите \"<\", если загаданное число меньше, \">\", если загаданное число больше, или \"=\", если загаданное число равно предполагаемому. (Сейчас, например, нужно ввести "); //"Enter \"<\" if the hidden number is less, \">\" if the hidden number is greater, or \"=\" if the hidden number is equal to the assumed one. (Now, for example, you need to enter "
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
                printf("Введите символ из списка [<, >, =]: "); // Enter a character from the list [<, >, =]:
                scanf_s("%c", &c);
            }
            if (c == '<') {
                r = (l + r) / 2;
            }
            else if (c == '=') {
                printf("Отлично! Количество затраченных попыток: %d\n", kolv); // Nice! Number of attempts:
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