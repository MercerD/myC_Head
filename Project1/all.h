/* --------------------
 * 作者：我是一颗小白菜
 * 邮箱：muzdong@qq.com
 * ------------------------------
 * 本头文件用于一些常用函数的集合
 * ------------------------------
 */
#pragma once
#include <stdio.h>
#include <math.h>
#include <string.h>

/*-----已经建立的函数库-----*/
#include "queue.h"
#include "fft_ld.h"

/*以下为函数声明集合*/

void X_LU(double **L, double **U, double **X, int n);
double interpolation_line(double x1, double y1, double x2, double y2, double x0);

/*----版本更新及说明----*/
/* 版本：V0.0.0
 * 2020.10.8-22：42
 * 创建ldC_dead.h头文件，用于一些常用函数的集合
 * 加入关于复数的各种运算，包括加减乘共轭和实数转复数的运算
 * 加入按位反转的反转函数，显示复数的函数
 * ps：代码均在其他文件测试过，类型符合的情况下均无bug，未在本头文件中单独测试
 */
 /* 版本：V0.0.1
  * 2020.10.8-10：51
  * 加入LU(Doolittle)分解
  * 加入插值运算,包括线性插值运算
  * ps：LU分解有bug无法使用，传入数据为二维数组的时候的指针问题
 */
 /* 版本：V0.0.2
  * 2020.10.19-19：27
  * 加入环形队列定义和队列求和运算
 */
 /* 版本：V0.1.0
  * 2020.10.27-12：45
  * 精简化处理，将不同模块的函数分类到不同的头文件，并用all.h包含
  * fft_ld.h中含有复数运算的算法和fft运算
  * queue.h中含有快速队列的算法
 */

/*---------------以下是暂存的函数定义--------------------*/

/* 线性插值
 * @功能  ：线性插值计算
 * @参数1\2 ：已知点1的x、y坐标
 * @参数3\4 ：已知点2的x、y坐标
 * @参数5 ：未知点0的x坐标
 * @返回值：返回未知点0处的线性插值y0
 * @注意  ：需要注意参数的类型以及对应的范围
 */
double interpolation_line(double x1, double y1, double x2, double y2, double x0)
{
	return (y1 - y2) / (x1 - x2) * (x0 - x1) + y1;
}

/* 二次插值
 * @功能  ：二次线性插值计算
 * @参数1\2 ：已知点1的x、y坐标
 * @参数3\4 ：已知点2的x、y坐标
 * @参数5\6 ：已知点3的x、y坐标
 * @参数5 ：未知点0的x坐标
 * @返回值：返回未知点0处的线性插值y0
 * @注意  ：需要注意参数的类型以及对应的范围
 */
double interpolation_quad(double x1, double y1, double x2, double y2, double x3, double y3, double x0)
{
	return (y1 - y2) / (x1 - x2) * (x0 - x1) + y1;
}

/* 矩阵LU(Doolittle)分解
 * @功能  ：将矩阵进行LU分解
 * @参数1 ：分解矩阵L
 * @参数2 ：分解矩阵U
 * @参数3 ：被分解矩阵X
 * @参数4 ：矩阵阶数n
 * @返回值：无返回值
 * @注意  ：需要注意参数的类型以及对应的范围
 */
void X_LU(double **L, double **U, double **X, int n)
{
	double temp = 0;
	for (int i = 0; i < n; i++)
	{
		U[0][i] = X[0][i];
		L[i][i] = 1;
	}
	for (int i = 0; i < n - 1; i++)
	{
		for (int j = i + 1; j < n; j++)
		{
			for (int k = 0; k < i; k++)
				temp += L[j][k] * U[k][i];
			L[j][i] = (X[j][i] - temp) / U[i][i];
			temp = 0;
		}
		for (int j = i + 1; j < n; j++)
		{
			for (int k = 0; k < i + 1; k++)
				temp += L[i + 1][k] * U[k][j];
			U[i + 1][j] = X[i + 1][j] - temp;
			temp = 0;
		}
	}
}