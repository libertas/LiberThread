#include <stdio.h>
#include "liberthread.h"

void thread(lt *p)
{
	LT_BEGIN(p);
	LT_WAIT_FOR(p, 1==2);
	LT_END(p);
	LT_EXIT(p);
}

int main()
{
	lt t1;
	LT_INIT(&t1);
	while(t1.lc!=LT_DEAD)
		thread(&t1);
	return -1;
}
