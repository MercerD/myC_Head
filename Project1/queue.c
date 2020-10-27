#include "queue.h"

/* �����������
 * @����  ����ָ���������������μ�����
 * @����1 ��ָ������
 * @����ֵ����͵�����
 * @ע��  ����Ҫע������������Լ���Ӧ�ķ�Χ
 */
double fastQueue_sumSequ(fastQueue queue)
{
	double sum = 0;
	for (unsigned int i = 0; i < queue.length; i++)
		sum += readQueue(queue, i);
	return sum;
}

/* ���п������
 * @����  �����µ����ݼӺ͵���������У�������ͷ�������޳�
 * @����1 ��ָ������
 * @����2 ���������
 * @����3 ���µ�����
 * @ע��  ����Ҫע������������Լ���Ӧ�ķ�Χ
 */
double fastQueue_sumFast(fastQueue queue, double sum, double data_new)
{
	sum -= *queue.head;
	sum += data_new;
	return sum;
}

/* ���г�ʼ��
 * @����  ���������鴴����Ӧ�Ķ��нṹ��
 * @����1 ����Ҫָ��������
 * @����2 �����鳤��
 * @����ֵ����ʼ����ɵĶ��нṹ��
 * @ע��  ����Ҫע������������Լ���Ӧ�ķ�Χ
 */
fastQueue fastQueue_init(double *queue, unsigned int length)
{
	fastQueue fq;
	fq.length = length;
	fq.addr_start = queue;
	fq.addr_end = queue + length;
	fq.head = fq.addr_start;
	fq.tail = fq.addr_end;
	return fq;
}

/* ��ȡ��������
 * @����  ����ȡ����ָ��λ������
 * @����1 ��ָ������
 * @����2 ��ָ��λ��
 * @����ֵ��ָ��λ�õ�����
 * @ע��  ����Ҫע������������Լ���Ӧ�ķ�Χ
 */
double readQueue(fastQueue queue, unsigned int count)
{
	double *p = queue.head;
	p += count;
	for (; p >= queue.addr_end; p -= queue.length)
		;
	return *p;
}

/* ��ĩβд������
 * @����  ���ڶ���ĩβд������
 * @����1 ��ָ������
 * @����2 ���µ�����
 * @����ֵ���µĶ���
 * @ע��  ����Ҫע������������Լ���Ӧ�ķ�Χ
 */
fastQueue writeQueue(fastQueue queue, double number)
{
	queue = shiftQueue(queue);
	*queue.tail = number;
	return queue;
}

/* λ��queueָ��
 * @����  ����������βָ�����λ��һλ
 * @����1 ��ָ������
 * @����ֵ���µĶ���
 * @ע��  ����Ҫע������������Լ���Ӧ�ķ�Χ
 */
fastQueue shiftQueue(fastQueue queue)
{
	queue.head++;
	queue.tail++;
	if (queue.head >= queue.addr_end)
		queue.head = queue.addr_start;
	else if (queue.tail >= queue.addr_end)
		queue.tail = queue.addr_start;
	return queue;
}