#include "all.h"

int main()
{
	double a[10] = {1,2,3,4,5,6,7,8,9,10};
	fastQueue que;
	que = fastQueue_init(a,10);
	for (int i = 0; i < 10; i++)
	{
		printf("%.2f ",readQueue(que, i));
	}
	printf("\n");
	for (int j = 20; j < 30; j++)
	{
		que = writeQueue(que, (double)j);
		for (int i = 0; i < 10; i++)
		{
			printf("%.2f ", readQueue(que, i));
		}
		printf("\n");
	}
}
