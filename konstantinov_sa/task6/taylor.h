#pragma once


double TrigArgWrap(double arg);

void tpSin(double x, unsigned n, double* t, double* ans);

void Taylor(void(*func)(double, unsigned, double*, double*), double(*etalon)(double), double x, unsigned n, unsigned e, int mode);
