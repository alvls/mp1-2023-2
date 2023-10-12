#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>

int main() {
    setlocale(LC_ALL, "rus");
    int mode = 0, kolv = 0;
    srand(time(NULL));
    while (mode != 1 && mode != 2) {
        printf("�������� ����� [1/2]: "); // choose mode
        scanf_s("%d", &mode);
    }
    if (mode == 1) {
        int rez = rand() % 1000;
        int guess = 0;
        printf("����� ���� ��������! ������� ���� �������������: "); // the number is taken! Enter you guess:
        while (guess != rez) {
            kolv++;
            scanf_s("%d", &guess);
            if (guess < rez) {
                printf("���������� ����� ������. ������� ���� �������������:\n"); // the number is bigger.  Enter you guess:
            }
            else if (guess > rez) {
                printf("���������� ����� ������. ������� ���� �������������:\n"); // the number is smaller.  Enter you guess:
            }
        }
        printf("�� �������! ���������� �������: %d\n", kolv); // You guessed it! Number of attempts:
    }
    else {
        int rez, l = 1, r = 1000;
        printf("������� ���������� ���� �����: "); // enter the number you've made
        scanf_s("%d", &rez);
        while (!(0 < rez && rez < 1000)) {
            printf("��� ��������! ������� ����� � ��������� �� 1 �� 999 ������������: "); // It's not fair! Enter a number in the range from 1 to 999 inclusive:
            scanf_s("%d", &rez);
        }
        int guess = (l + r) / 2;
        int first = 1;
        while (1) {
            kolv++;
            guess = (l + r) / 2;
            printf("�� �������� ����� %d? ", guess); // Have you made number %d?
            if (first) {
                printf("������� \"<\", ���� ���������� ����� ������, \">\", ���� ���������� ����� ������, ��� \"=\", ���� ���������� ����� ����� ���������������. (������, ��������, ����� ������ "); //"Enter \"<\" if the hidden number is less, \">\" if the hidden number is greater, or \"=\" if the hidden number is equal to the assumed one. (Now, for example, you need to enter "
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
                printf("������� ������ �� ������ [<, >, =]: "); // Enter a character from the list [<, >, =]:
                scanf_s("%c", &c);
            }
            if (c == '<') {
                r = (l + r) / 2;
            }
            else if (c == '=') {
                printf("�������! ���������� ����������� �������: %d\n", kolv); // Nice! Number of attempts:
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