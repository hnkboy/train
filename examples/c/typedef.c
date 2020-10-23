#include <stdio.h>
#include <string.h>
/*
 *介绍typedef 指针的两种表示方法
 * typedef void    *MARKER[0];
*/


typedef int *(funct1) (int * vm);
typedef int *(*funct2) (int * vm);
__extension__
typedef void    *MARKER[0];


struct rte_mbuf {
	MARKER cacheline0;  /*就是声明，但是不分配实际内存，此结构体按照void* 字节对齐*/
    char buf_addr[9];
};


int (*p) (int x);  /*定义一个函数指针*/

funct1 *f1;
funct2 f2;

int * vlib_init_function(int *vm)
{
    return 0;
}
int vlib_init2_function(int vm)
{
    return 0;
}

int main()
{
    f1 = vlib_init_function;
    f2 = vlib_init_function;
    p = vlib_init2_function;
    printf("\n%d\n",sizeof(struct rte_mbuf));


    return 0;
}


