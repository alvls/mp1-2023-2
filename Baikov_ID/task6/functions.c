typedef double (*FunctionPointer)(double);

double sin_a(double x) {
    return sin(x);
}

double cos_a(double x) {
    return cos(x);
}

double exp_a(double x) {
    return exp(x);
}

double ln1plusx_a(double x) {
    return log(1 + x);
}
void calculate(FunctionPointer func, double x, int precision, int max_terms, double* result, int* num_terms) {
    double true_value = func(x);
    double estimate = 0.0;
    double term = 1.0;

    for (int term_count = 1; term_count <= max_terms; ++term_count) {
        term *= x / term_count;
        estimate += term;

        if (fabs(term) < pow(10, -precision)) {
            break;
        }
    }

    *result = estimate;
    *num_terms = max_terms;
}

void print_results(double true_value, double estimate, double difference, int precision, int num_terms) {
    printf("Точное значение: %.*f\n", precision, true_value);
    printf("Расчетное значение: %.*f\n", precision, estimate);
    printf("Разница: %.*f\n", precision, difference);
    printf("Количество слагаемых: %d\n", num_terms);
}

int menu() {
    int user_choice;
    printf("Выберите режим работы:\n");
    printf("1 - Однократный расчет\n");
    printf("2 - Серийный эксперимент\n");
    scanf("%d", &user_choice);

    return user_choice;
}

void get_input(int mode, int* func_choice, double* x, double* precision, int* max_terms) {
    printf("Выберите функцию:\n");
    printf("1 - sin(x)\n");
    printf("2 - cos(x)\n");
    printf("3 - exp(x)\n");
    printf("4 - ln(1+x)\n");
    scanf("%d", func_choice);

    printf("Введите точку x: ");
    scanf("%lf", x);

    if (mode == 1) {
        printf("Введите точность вычисления: ");
        scanf("%lf", precision);

        printf("Введите число элементов ряда: ");
        scanf("%d", max_terms);
    }
}