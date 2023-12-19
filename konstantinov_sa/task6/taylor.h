#pragma once


double TrigArgWrap(double arg);

void tpSin(double x, unsigned n, double* t, double* ans);

void tpCos(double x, unsigned n, double* t, double* ans);

void tpExp(double x, unsigned n, double* t, double* ans);

void tpCh(double x, unsigned n, double* t, double* ans);

void tpSh(double x, unsigned n, double* t, double* ans);

void Taylor(void(*func)(double, unsigned, double*, double*), double(*etalon)(double), double x, unsigned n, unsigned e, int mode);
