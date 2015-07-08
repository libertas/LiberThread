#include <stdio.h>
#include "liberthread.h"

int main()
{
	lt t1;
	LT_INIT(&t1);
	LT_EXIT(&t1);
	return -1;
}
