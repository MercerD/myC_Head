/* --------------------
 * ���ߣ�����һ��С�ײ�
 * ���䣺muzdong@qq.com
 * ------------------------------
 * ��ͷ�ļ�Ϊ���ٶ��в���ͷ�ļ�
 * ------------------------------
 */
#pragma once
#include <stdio.h>
#include <math.h>
#include <string.h>
 /*����Ϊ�궨�弯��*/

/*����Ϊ�ṹ��ȫ�ֱ�������弯��*/

typedef struct fastQueue //ָ����нṹ�嶨��
{
	double *addr_start; //���пռ���ʼ��ַ
	double *addr_end;   //���пռ������ַ
	double *head;       //���ж�ͷ��ַ
	double *tail;       //���ж�β��ַ
	unsigned int length;//�ռ䳤��
}fastQueue;

/*����Ϊ������������*/

fastQueue fastQueue_init(double *queue, unsigned int length);
fastQueue shiftQueue(fastQueue queue);
double readQueue(fastQueue queue, unsigned int count);
fastQueue writeQueue(fastQueue queue, double number);
double fastQueue_sumSequ(fastQueue queue);
double fastQueue_sumFast(fastQueue queue, double sum, double data_new);

/* �汾��V0.0.2
 * 2020.10.19-19��27
 * ���뻷�ζ��ж���Ͷ����������
*/
