#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>

typedef double (*TfuncPattern) (double, int, double*, unsigned long long* );

double expPart(double x, int n, double* preX, unsigned long long *preFac) { //preX first = 1, preFac = 1
	double res = 0.0;
	if (n == 0) 
		return 1;
	//printf("		%.20f   ***   %llu ___\n", *preX * x, n * *preFac);
	res = (*preX * x) / (double) (n * *preFac);
	*preX *= x; *preFac *= n;
	return res;
}


int main()
{
	double out = 0;
	double x = 3.5;
	double xpow = 1;
	unsigned long long fact = 1;
	TfuncPattern Tfunc = expPart;


	for (int i = 0; i < 18; i++) {
		out += Tfunc(x, i, &xpow, &fact);
		printf("on %i step: %.20f\n", i, out);
	}

	printf("MATH: %.20f\n", exp(3.5));
	system("pause");
	return 0;
}

/*мысль 1
typedef int func(void);


int breakCondition1(int funcMath, int funcUser) {

}


int breakCondition2(int funcMath, int funcUser) { //??? параметры тут надо номер эксперимента
}

float sinUser(double x, func breakCondition) {
	while (breakCondition())


}
*/

/*
double sinPart (double x, int n, int factorial_n_minus_1, int sign) {}
// ага, а как сравнивать со значением из маф? Если мы во внешней функции хз, какая там у нас функция
/// ... массив из указателей на функции??? звучит интересно
// на чётных местах расположить наши функции, а на нечётных их маф
// ввод тупо домножать на 2

// те пользователь вводит номер функции из списка и мы можем брать указатель на эту функцию по номеру
// и одновремнно с этим имет доступ к "идеальной" из маф, если задача на точность
// таким образом во внешней функции вообще пофиг, что мы считаем: синус, косинус и тд

// funcArr[n] = {*userSin, *mathSin, *userCos, *mathCos...}
// userSin == sinPart, вычисляет следующий член и передаёт во внешнюю, а там оно само
// для тригонометрических можно сделать скип значений, в которых они в ноль оюрашаются

// кст, таким методом будет очень большой бок объявления функций и более-менее общегоо вида main
*/