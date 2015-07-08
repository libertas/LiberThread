#include <stdio.h>
#include "liberthread.h"

static unsigned short count = 1;


void thread1(lt *p)
{
	LT_BEGIN(p);
	LT_WAIT_FOR(p, count == 60);
	LT_EXIT(p);
	LT_END(p);
}

void thread2(lt *p)
{
	LT_BEGIN(p);
	LT_WAIT_FOR(p, count == 50);
	LT_EXIT(p);
	LT_END(p);
}


int main()
{
	lt t1, t2;
	LT_INIT(&t1);
	LT_INIT(&t2);
	while(t1.lc!=LT_DEAD || t2.lc!=LT_DEAD)
	{
		thread1(&t1);
		thread2(&t2);
		printf("%d:\n", count);
		printf("\tt1:%d\n", (int)(t1.lc));
		printf("\tt2:%d\n", (int)(t2.lc));
		count++;
	}
	return -1;
}
