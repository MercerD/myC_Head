/* --------------------
 * ���ߣ�����һ��С�ײ�
 * ���䣺muzdong@qq.com
 * ------------------------------
 * ��ͷ�ļ����и���������㷨��fft����
 * ------------------------------
 */
#pragma once
#define pi 3.14159
#define N  2048
#define r  11
#define cp _C_double_complex  //���帴���ĺ궨�壬������Ҫʹ��double����

#include <stdio.h>
#include <math.h>
#include <string.h>

/*----------------------�����Ǹ������Ͷ���-------------------------*/

typedef struct _C_double_complex
{
	double _Val[2];
} _C_double_complex;

typedef struct _C_float_complex
{
	float _Val[2];
} _C_float_complex;

typedef struct _C_ldouble_complex
{
	long double _Val[2];
} _C_ldouble_complex;

/*----------------------�����Ǻ�������-------------------------*/

void fft_init();
int BR(int a, int _r);
cp pow_I(cp a, int b);
cp add_I(cp a, cp b);
cp sub_I(cp a, cp b);
cp mul_I(cp a, cp b);
cp double2cp(double a);
void fft(cp *X, double *x);
void printf_I(cp a);