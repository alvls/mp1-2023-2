#include "Menu.h"

int sort_id = -1;
int type_of_sort = -1;

char* menu[5][80] = {
 "Вывести информацию о файлах",
 "Выбрать метод сортировки",
 "Выбрать тип сортировки",
 "Отсортировать",
 "Exit"
};

char* submenu[2][7][20] = {
    {"1) Пузырьком","2) Выбором", "3) Вставками", "4) Слиянием", "5) Хоара", "6) Шелла", "7) Подсчётом"},
    {"По возрастанию","По убыванию"},
};

void printMenu(int selected, char* menu[20], int count) {
    for (int i = 0; i < count; i++) {
        if (i == selected) {
            printf("\033[31m%s\n\033[0m", menu[i]);
        }
        else {
            printf("%s\n", menu[i]);
        }
    }
}

void Sub_Menu(int choice) {
    if (choice == 1)
    {
        int subchoice = 0;
        while (1) {
            system("cls");
            printMenu(subchoice, submenu[choice - 1], 7);
            char c = getch();
            if (c == UP) {
                subchoice--;
                if (subchoice < 0)
                    subchoice = 7 + subchoice;
            }
            else if (c == DOWN) {
                subchoice++;
                subchoice = subchoice % 7;
            }
            else if (c == ENTER) {
                break;
            }
        }
        sort_id = subchoice;
    }
    else
    {
        int subchoice = 0;
        while (1) {
            system("cls");
            printMenu(subchoice, submenu[choice - 1], 2);
            char c = getch();
            if (c == UP) {
                subchoice--;
                if (subchoice < 0)
                    subchoice = 2 + subchoice;
            }
            else if (c == DOWN) {
                subchoice++;
                subchoice = subchoice % 2;
            }
            else if (c == ENTER) {
                break;
            }
        }
        type_of_sort = subchoice;
    }
}