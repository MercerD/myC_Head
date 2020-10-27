/* --------------------
 * 作者：我是一颗小白菜
 * 邮箱：muzdong@qq.com
 * ------------------------------
 * 本头文件为快速队列操作头文件
 * ------------------------------
 */
#pragma once
#include <stdio.h>
#include <math.h>
#include <string.h>
 /*以下为宏定义集合*/

/*以下为结构体全局变变量定义集合*/

typedef struct fastQueue //指针队列结构体定义
{
	double *addr_start; //队列空间起始地址
	double *addr_end;   //队列空间结束地址
	double *head;       //队列队头地址
	double *tail;       //队列队尾地址
	unsigned int length;//空间长度
}fastQueue;

/*以下为函数声明集合*/

fastQueue fastQueue_init(double *queue, unsigned int length);
fastQueue shiftQueue(fastQueue queue);
double readQueue(fastQueue queue, unsigned int count);
fastQueue writeQueue(fastQueue queue, double number);
double fastQueue_sumSequ(fastQueue queue);
double fastQueue_sumFast(fastQueue queue, double sum, double data_new);

/* 版本：V0.0.2
 * 2020.10.19-19：27
 * 加入环形队列定义和队列求和运算
*/
