#include <stdio.h>
#include "liberthread.h"

static unsigned short count1 = 1;


void thread1(lt *p)
{
	printf("Thread1:%d\n", count);
	LT_BEGIN(p);
	LT_WAIT_FOR(p, count == 60);
	LT_END(p);
	LT_EXIT(p);
}

void thread2(lt *p)
{
	printf("Thread2:%d\n", count);
	LT_BEGIN(p);
	LT_WAIT_FOR(p, count == 50);
	LT_END(p);
	LT_EXIT(p);
}


int main()
{
	lt t1, t2;
	LT_INIT(&t1);
	LT_INIT(&t2);
	while(t1.lc!=LT_DEAD)
	{
		thread1(&t1);
		thread2(&t2);
		count++;
	}
	return -1;
}
