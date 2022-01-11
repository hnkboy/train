#include <stdio.h>
valatile int i=0;
void dosomething()
{
	printf("do one time\n");
}
int main(void)
{
while(1)
{
if(i)
dosomething();
}
}
/*Interruptserviceroutine.*/
void ISR_2(void)
{
i=1;
}

