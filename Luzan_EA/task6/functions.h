#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>

#define SIZE 4
#define pi 3.141592653589793

double intervals[SIZE][2];

typedef double (*TfuncPart) (double, unsigned long long*, double*, unsigned long long*, unsigned int );

typedef double (*TfuncInpWork) (double);      //������� �� �������� ���������� �������� ���������� 
									    	  //��� ����� ������������� ������ �������
typedef double (*TfuncArgCheck) (double*, int*, double[SIZE][2], int*);

void mode1(TfuncPart Tfunc, TfuncInpWork TMath, double x, int sgn);

void mode2(TfuncPart Tfunc, TfuncInpWork TMath, double x, int sgn);

int getMode();

int getfNum();

double getArgument();

void simplArgument(double* x, int* sgn, double noPeriodZone[SIZE][2], int* i);

void checkArgument(double* x, int* sgn, double RoAV[SIZE][2], int* index);

void checkArgumentIntervl(double* x, int* sgn, double RoAV[SIZE][2], int* index);

double expPart(double x, unsigned long long* n, double* preX, unsigned long long* preFac, unsigned int elmInd);

double sinPart(double x, unsigned long long* n, double* preX, unsigned long long* preFac, unsigned int elmInd);

double cosPart(double x, unsigned long long* n, double* preX, unsigned long long* preFac, unsigned int elmInd);

double arthPart(double x, unsigned long long* n, double* preX, unsigned long long* preFac, unsigned int elmInd);