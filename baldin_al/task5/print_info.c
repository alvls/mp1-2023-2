#include "print_info.h"
#include "Menu.h"

void list_of_files(struct file_info* files, int count)
{
    printf("FILE         TIME CREATE %13c TIME ACCESS %13c TIME WRITE %16c SIZE\n", ' ', ' ', ' ');
    printf("----         ----------- %13c ----------- %13c ---------- %16c ----\n", ' ', ' ', ' ');
    for (int i = 0; i < count; i++) {
        char buffer1[30];
        char buffer2[30];
        char buffer3[30];
        ctime_s(buffer1, _countof(buffer1), &files[i].time_create);
        ctime_s(buffer2, _countof(buffer2), &files[i].time_access);
        ctime_s(buffer3, _countof(buffer3), &files[i].time_write);
        printf("%-12.12s %.24s  %.24s  %.24s %10ld\n", files[i].name, buffer1, buffer2, buffer3, files[i].size);
    }
    char ch;
    printf("\n Чтобы вернуться к настройке сортировки нажмите Enter");
    do {
        ch = _getch();
    } while (ch != ENTER);
}