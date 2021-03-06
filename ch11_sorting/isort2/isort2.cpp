/*
file name: isort2.cpp
purpose: 
	P110
	isort2在isort1的基础上，将swap实现为内联(inline)函数，以增加速度。

	isort1:
	筛选过程通过一个从右到左的循环实现，该循环使用变量j跟踪被筛选的元素。
	只要该元素具有前驱（即j>0）且没有到达最终位置（即该元素小于它的前驱），循环就交换该元素和它的前驱。
creator: Guangwei Jiang
create time: 2012-08-01

modify history:

notes:
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ARRAY_SIZE		50000

// notes: bigrand should at least 64bits
unsigned long long bigrand()
{
	return RAND_MAX*rand() + rand();
}

static inline void swap(int *p1, int *p2)
{
	int tmp;
	tmp = *p1;
	*p1 = *p2;
	*p2 = tmp;
}

void isort2(int *array_data, int array_size)
{
	int i, j, temp;

	for (i = 0; i < array_size; i++)
	{
		for (j = i; j > 0 && array_data[j-1] > array_data[j]; j--)
		{
			swap(array_data+(j-1), array_data+j);
			//temp = array_data[j];
			//array_data[j] = array_data[j-1];
			//array_data[j-1] = temp;
		}
	}
}

int main()
{
	clock_t start, finish;
	double duration;	
	int *array_data;
	int i;

	array_data = (int*) malloc (sizeof(int)*ARRAY_SIZE);
	if (array_data == NULL)
	{
		printf("memory(array_bitmap) allocate failed\n");
		goto _free_mem;
	}
	
	printf("Generate the test data...\n");
	srand(time(0));
	for (i = 0; i < ARRAY_SIZE; i++)
	{
		array_data[i] = bigrand()%RAND_MAX;
	}

	printf("Sorting data...\n");
	start = clock();
	isort2(array_data, ARRAY_SIZE);
	finish = clock();
	duration = (double)(finish - start) / CLOCKS_PER_SEC;
	printf("Test data number is %d\n", ARRAY_SIZE);
	printf("the duration is %f seconds\n\n", duration);

_free_mem:
	if (array_data != NULL)
	{
		free(array_data);
		array_data = NULL;
	}

	return 0;
}
