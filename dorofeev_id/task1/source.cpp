#include <stdio.h>
#include <math.h>
#include <locale.h>

float max(float a, float b)
{
    if (a > b)
    {
        return a;
    }
    else
    {
        return b;
    }
}

float min(float a, float b)
{
    if (a < b)
    {
        return a;
    }
    else
    {
        return b;
    }
}


int main()
{
    setlocale (LC_ALL, "rus");
    float x1, x2, y1, y2, r1, r2 = 0.0f;
    printf("введите координаты 1ой окружности\n");
    scanf("%f %f", &x1, &y1);

    printf("введите координаты 2ой окружности\n");
    scanf("%f %f", &x2, &y2);

    printf("введите радиус 1ой окружности\n");
    scanf("%f", &r1);

     printf("введите радиус 2ой окружности\n");
    scanf("%f", &r2);


    float rast = sqrt((x1 - x2)*(x1 - x2) + (y1 - y2)*(y1 - y2));

    if (rast == (r1 + r2))
    {
        printf("Окружности соприкасаются внешне\n");
    }

    else if (max(r1, r2) == (rast + min(r1, r2)))
    {
        printf("Окружности соприкасаются внутренне\n");
    }

    else if (rast > (r1 + r2))
    {
        printf("Окружности не соприкасаются\n");
    }

    else if (rast < (r1 + r2))
    {
        printf("Окружности пересекаются\n");
    }

    else if ((max(r1, r2) < (rast + min(r1, r2))) && (x1 == x2) && (y1 == y2))
    {
        printf("Окружности располагаются одна в другой, центры совпадают\n");
    }

    else if ((max(r1, r2) < (rast + min(r1, r2))) && ((x1 != x2) || (y1 != y2)))
    {
        printf("Окружности располагаются одна в другой, центры не совпадают\n");
    }

    else if ((x1 == x2) && (y1 == y2) && (r1 == r2))
    {
        printf("Окружности совпадают\n");
    }

    else
    {
        printf("Ошибка\n");
    }
    
    return 0;
}


