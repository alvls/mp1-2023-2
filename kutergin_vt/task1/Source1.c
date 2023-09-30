#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

void main(){
    int DVP, DSP, wood; // плотности ДВП, ДСП И древесины дверей (кг/м^3)
    int num_of_shelves; // число полок (нужно рассчитать в программе)
    // размеры в метрах
    float h, w, t1 = 0.005; // накладная задняя стенка
    float d, t2 = 0.015; // 2 боковины с той же высоты h
    float t3 = 0.015; // накладная верхняя и нижняя крышка с той же шириной w и глубиной d
    float t4 = 0.01; // 2 накладные двери с той же высотой h и общей шириной w
    float t5 = 0.015; // несколько полок с уменьшенной шириной и той же глубиной d
    float M, M1, M2, M3, M4, M5; // массы позиций с 1 по 5 + масса всего шкафа
    
    printf("Enter the densities of DVP, DSP and wood (in kg per m^3): \n");
    scanf("%d %d %d", &DVP, &DSP, &wood);
    
    printf("Enter the height h (from 1.8 to 2.2 m) and width w (from 0.8 to 1.2 m) of the back panel: \n");
    scanf("%f %f", &h, &w);
    printf("Enter the depth d (from 0.5 to 0.9 m) of the two sides: \n");
    scanf("%f", &d);
    // больше данных о размере шкафа от пользователя не требуется
    
    num_of_shelves = h / (0.4 + t5); // целое число (полок+пробелов), помещаемых по вертикали
    
    M1 = h * w * t1 * DVP;
    M2 = 2 * h * d * t2 * DSP;
    M3 = 2 * w * d * t3 * DSP;
    M4 = h * w * t4 * wood;
    M5 = (w - 2*t2) * d * t5 * DSP * num_of_shelves;
    
    M = M1 + M2 + M3 + M4 + M5;
    printf("Cabinet weight: %.3f \n", M);
}
// Проверка: DVP = 950, DSP = 750, wood = 700, h = 2, w = 1, d = 0.7 ; Результат: M = 101.305

