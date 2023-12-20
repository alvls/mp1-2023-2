#ifndef myfunctions_h
#define myfunctions_h

#define MAX_N 20 // больше 20 чисел бернулли высчитывать не будем

double bernoulli_numbers[MAX_N];

// факториал
double factorial(int n) {
    double fact = 1;
    for (int i = 1; i <= n; i++)
        fact *= i;
    return fact;
}

// число сочетаний из n по k
double binomial_coefficient(int n, int k) {
    return factorial(n) / (factorial(k) * factorial(n - k));
}

// функция модуля
double Abs(double value) {
    // союз преобразует double в long long, изменяет значение и возвращает в типе double
    // при изменении одной переменной в союзе, изменится значение и в других переменных в этом союзе,
    // поскольку переменные разных типов данных хранятся в союзе в одной и той же области памяти
    union dbl_long_long {
        long long l;
        double d;
    };
    
    union dbl_long_long val; // объявление союза
    
    val.d = value; // значение value хранится в области памяти, которую и val.d и val.l используют
    val.l &= ~ (1LLU << 63); //единица типа long long unsigned (1 и 63 нуля) инвертируется в 0 и 63 единицы
    // происходит побитовое умножение и первый бит (знаковый) зануляется при любом случае
    // итог - получено абсолютное значение числа
    return val.d;
}

// вычисление первых MAX_N чисел Бернулли
void calculate_bernoulli_numbers() {
    bernoulli_numbers[0] = 1.0;
    bernoulli_numbers[1] = -0.5;
    for (int n = 2; n < MAX_N; n++) {
        bernoulli_numbers[n] = 0;
        for (int k = 1; k <= n; k++)
            bernoulli_numbers[n] += binomial_coefficient(n + 1, k + 1) * bernoulli_numbers[n - k];
        bernoulli_numbers[n] /=  -(n + 1);
        if (bernoulli_numbers[n] == 0)
            bernoulli_numbers[n] = Abs(bernoulli_numbers[n]);
    }
    bernoulli_numbers[20] =  -174611/330;
}
//double bernoulli[] = {1, -1/2, 1/6, 0, -1/30, 0, 1/42, 0, -1/30, 0, 5/66, 0, -691/2730, 0, 7/6, 0, -3617/510, 0, 43867/798, 0, -174611/330, 0, 854513/138};

double my_sin(double x, double accuracy, int N) {
    double result = x; // итоговая сумма членов (заложим первый член уже в сумму)
    double term = x; // член ряда Тейлора
    int k = 0; // счетчик членов
    
    while ((Abs(term) > accuracy) && (k + 1 < N)) { // пока модуль члена ряда больше заданной точности (т.е. результат менее точный) и число членов не достигло нужного количества (первый член уже в сумме, поэтому знак неравенства строгий)
        k++;
        term *= -x * x / ((2*k) * (2*k + 1)); // рекурсивный подсчет каждого члена
        result += term; // добавляем член в итоговую сумму
    }
    printf("\nCalculated number of terms: %d \n", k);
    
    return result;
}

double my_cos(double x, double accuracy, int N) {
    double result = 1.0; // итоговая сумма членов (заложим первый член уже в сумму)
    double term = 1.0; // член ряда Тейлора
    int k = 0; // счетчик членов
    
    while ((Abs(term) > accuracy) && (k + 1 < N)) { // пока модуль члена ряда больше заданной точности (т.е. результат менее точный) и число членов не достигло нужного количества (первый член уже в сумме, поэтому знак неравенства строгий)
        k++;
        term *= -x * x / ((2*k) * (2*k - 1)); // рекурсивный подсчет каждого члена
        result += term; // добавляем член в итоговую сумму
    }
    printf("\nCalculated number of terms: %d \n", k);
    
    return result;
}

double my_exp(double x, double accuracy, int N) {
    double result = 1.0; // итоговая сумма членов (заложим первый член уже в сумму)
    double term = 1.0; // член ряда Тейлора
    int k = 0; // счетчик членов
    
    while ((Abs(term) > accuracy) && (k + 1 < N)) { // пока модуль члена ряда больше заданной точности (т.е. результат менее точный) и число членов не достигло нужного количества (первый член уже в сумме, поэтому знак неравенства строгий)
        k++;
        term *= x  / k; // рекурсивный подсчет каждого члена
        result += term; // добавляем член в итоговую сумму
    }
    printf("\nCalculated number of terms: %d \n", k);
    
    return result;
}

// ограничение ряда тейлора для гиперболического тангенса возьмём до 10 слагаемых (до 20-ого числа Бернулли)
double my_th(double x, double accuracy, int N) {
    double result = x; // итоговая сумма членов (заложим первый член уже в сумму)
    double term = x; // член ряда Тейлора
    int k = 0; // счетчик
    
    calculate_bernoulli_numbers();
    
    while ((Abs(term) > accuracy) && (k < N)) {// пока модуль члена ряда больше заданной точности (т.е. результат менее точный) и число членов не достигло нужного количества (первый член уже в сумме, поэтому знак неравенства строгий)
        k++;
        term = pow(2, 2*k) * bernoulli_numbers[2*k] * (pow(2, 2*k) - 1) * pow(x, 2*k - 1) / factorial(2*k); // Аналогично формуле, взятой из Википедии
        result += term;
    }
    printf("\nCalculated number of terms: %d \n", k);
    
    return result;
}

double my_sin_2(double x, int N) {
    double result = x; // итоговая сумма членов (заложим первый член уже в сумму)
    double term = x; // член ряда Тейлора
    int k = 0; // счетчик членов
    
    while (k + 1 < N) { // пока модуль члена ряда больше заданной точности (т.е. результат менее точный) и число членов не достигло нужного количества (первый член уже в сумме, поэтому знак неравенства строгий)
        k++;
        term *= -x * x / ((2*k) * (2*k + 1)); // рекурсивный подсчет каждого члена
        result += term; // добавляем член в итоговую сумму
    }
    
    return result;
}

double my_cos_2(double x, int N) {
    double result = 1.0; // итоговая сумма членов (заложим первый член уже в сумму)
    double term = 1.0; // член ряда Тейлора
    int k = 0; // счетчик членов
    
    while (k + 1 < N) { // пока модуль члена ряда больше заданной точности (т.е. результат менее точный) и число членов не достигло нужного количества (первый член уже в сумме, поэтому знак неравенства строгий)
        k++;
        term *= -x * x / ((2*k) * (2*k - 1)); // рекурсивный подсчет каждого члена
        result += term; // добавляем член в итоговую сумму
    }
    
    return result;
}

double my_exp_2(double x, int N) {
    double result = 1.0; // итоговая сумма членов (заложим первый член уже в сумму)
    double term = 1.0; // член ряда Тейлора
    int k = 0; // счетчик членов
    
    while (k + 1 < N) { // пока модуль члена ряда больше заданной точности (т.е. результат менее точный) и число членов не достигло нужного количества (первый член уже в сумме, поэтому знак неравенства строгий)
        k++;
        term *= x  / k; // рекурсивный подсчет каждого члена
        result += term; // добавляем член в итоговую сумму
    }
    
    return result;
}

// ограничение ряда тейлора для гиперболического тангенса возьмём до 10 слагаемых (до 20-ого числа Бернулли)
double my_th_2(double x, int N) {
    double result = x; // итоговая сумма членов (заложим первый член уже в сумму)
    double term = x; // член ряда Тейлора
    int k = 0; // счетчик
    
    calculate_bernoulli_numbers();
    
    while (k + 1 < N) {// пока модуль члена ряда больше заданной точности (т.е. результат менее точный) и число членов не достигло нужного количества (первый член уже в сумме, поэтому знак неравенства строгий)
        k++;
        term = pow(2, 2*k) * bernoulli_numbers[2*k] * (pow(2, 2*k) - 1) * pow(x, 2*k - 1) / factorial(2*k); // Аналогично формуле, взятой из Википедии
        result += term;
    }
    
    return result;
}

#endif


