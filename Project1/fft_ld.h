/* --------------------
 * 作者：我是一颗小白菜
 * 邮箱：muzdong@qq.com
 * ------------------------------
 * 本头文件含有复数运算的算法和fft运算
 * ------------------------------
 */
#pragma once
#define pi 3.14159
#define N  2048
#define r  11
#define cp _C_double_complex  //定义复数的宏定义，这里主要使用double类型

#include <stdio.h>
#include <math.h>
#include <string.h>

/*----------------------以下是复数类型定义-------------------------*/

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

/*----------------------以下是函数声明-------------------------*/

void fft_init();
int BR(int a, int _r);
cp pow_I(cp a, int b);
cp add_I(cp a, cp b);
cp sub_I(cp a, cp b);
cp mul_I(cp a, cp b);
cp double2cp(double a);
void fft(cp *X, double *x);
void printf_I(cp a);