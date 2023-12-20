#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include "modes.h"

void main() {
    char program_mode[20] = {0}; // название режима работы программы
        
    printf("Select the program operating mode: \n");
    printf("- mode1;\n"); // Однократный расчет функции в заданной точке
    printf("- mode2;\n"); // Серийный эксперимент
    printf("Enter 'mode1' or 'mode2': ");
    
    fgets(program_mode, sizeof(program_mode), stdin);
    program_mode[strcspn(program_mode, "\n")] = 0; // управляющий символ новой строки \n зануляется

    // проверка на ввод названия режима работы
    while ((strcmp(program_mode, "mode1") != 0) && (strcmp(program_mode, "mode2") != 0)) {
        printf("This program operating mode doesn't exist.\n");
        printf("Try again. Enter the correct name of the program mode: ");
        fgets(program_mode, sizeof(program_mode), stdin);
        program_mode[strcspn(program_mode, "\n")] = 0;
    }
    if (strcmp(program_mode, "mode1") == 0) {
        mode1();
    } else if (strcmp(program_mode, "mode2") == 0) {
        mode2();
    }
}
