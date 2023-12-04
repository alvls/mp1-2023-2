#include "print_info.h"
#include "Menu.h"

void list_of_files(struct file_info* files, int count)
{
    printf("FILE       SIZE\n");
    printf("----       ----\n");
    for (int i = 0; i < count; i++) {
        printf("%-12.12s  %10ld\n", files[i].name, files[i].size);
    }
    char ch;
    printf("\n Чтобы вернуться к настройке сортировки нажмите Enter");
    do {
        ch = _getch();
    } while (ch != ENTER);
}