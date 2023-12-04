#pragma once

#define UP 72
#define DOWN 80
#define ENTER 13

extern int sort_id;
extern int type_of_sort;

char* menu[5][80];
char* submenu[2][7][20];

void printMenu(int selected, char* menu[20], int count);
void Sub_Menu(int choice);