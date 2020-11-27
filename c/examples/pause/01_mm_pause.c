#include <emmintrin.h>
int ready_flag = -1;
void main(int argn, char argv[])
{

    while(-1  == ready_flag)
    {
        //dosomething
        _mm_pause();
    }
    return;
}
