#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>

void main1(){
    float x1, y1, x2, y2; //координаты центров
    float r1, r2; //радиусы окружностей
    float dist; //расстояние между центрами
    
    printf("enter the coordinates of the center of the first circle: \n");
    scanf("%f %f", &x1, &y1);
    printf("enter the coordinates of the center of the second circle: \n");
    scanf("%f %f", &x2, &y2);
    printf("enter the radii of the circles: \n");
    scanf("%f %f", &r1, &r2);
    
    dist = sqrtf(powf(fabsf(x2 - x1), 2) + powf(fabsf(y2 - y1), 2));
    printf("dist = %.2f \n", dist);
    
    if (dist > r1 + r2)
        printf("the circles are located externally and don't touch \n");
    else if (dist == r1 + r2)
        printf("circles touch externally \n");
    else if ((r1 + r2 > dist) && (r1 + dist > r2) && (r2 + dist > r1)) //треугольник
        printf("circles intersect (at 2 points) \n");
    else if (dist == fabsf(r2 - r1))
        printf("circles touch internally \n");
    else if (dist < fabsf(r2 - r1))
        printf("the circles are located internally, don't touch, and their centers don't coincide \n");
    else if (dist == 0)
        printf("the centers of the circles coincide \n");
}
