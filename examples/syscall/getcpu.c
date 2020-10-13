#include<stdio.h>
#include <sys/syscall.h>
void  main()
{
	  unsigned cpu, node;
	  syscall (__NR_getcpu, &cpu, &node, 0);
	  printf("cpu:%d, numa:%d\n", cpu, node);		
}
