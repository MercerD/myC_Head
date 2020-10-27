#include "queue.h"

/* 队列依次求和
 * @功能  ：将指定队列中数据依次加起来
 * @参数1 ：指定队列
 * @返回值：求和的数据
 * @注意  ：需要注意参数的类型以及对应的范围
 */
double fastQueue_sumSequ(fastQueue queue)
{
	double sum = 0;
	for (unsigned int i = 0; i < queue.length; i++)
		sum += readQueue(queue, i);
	return sum;
}

/* 队列快速求和
 * @功能  ：将新的数据加和到求和数据中，并将队头的数据剔除
 * @参数1 ：指定队列
 * @参数2 ：求和数据
 * @参数3 ：新的数据
 * @注意  ：需要注意参数的类型以及对应的范围
 */
double fastQueue_sumFast(fastQueue queue, double sum, double data_new)
{
	sum -= *queue.head;
	sum += data_new;
	return sum;
}

/* 队列初始化
 * @功能  ：根据数组创建对应的队列结构体
 * @参数1 ：需要指定的数组
 * @参数2 ：数组长度
 * @返回值：初始化完成的队列结构体
 * @注意  ：需要注意参数的类型以及对应的范围
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

/* 读取队列数据
 * @功能  ：读取队列指定位置数据
 * @参数1 ：指定队列
 * @参数2 ：指定位置
 * @返回值：指定位置的数据
 * @注意  ：需要注意参数的类型以及对应的范围
 */
double readQueue(fastQueue queue, unsigned int count)
{
	double *p = queue.head;
	p += count;
	for (; p >= queue.addr_end; p -= queue.length)
		;
	return *p;
}

/* 在末尾写入数据
 * @功能  ：在队列末尾写入数据
 * @参数1 ：指定队列
 * @参数2 ：新的数据
 * @返回值：新的队列
 * @注意  ：需要注意参数的类型以及对应的范围
 */
fastQueue writeQueue(fastQueue queue, double number)
{
	queue = shiftQueue(queue);
	*queue.tail = number;
	return queue;
}

/* 位移queue指针
 * @功能  ：将队列首尾指针向后位移一位
 * @参数1 ：指定队列
 * @返回值：新的队列
 * @注意  ：需要注意参数的类型以及对应的范围
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