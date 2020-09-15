#include<stdio.h>

typedef struct {
    int a;
}A;
#define clib_min(x,y)				\
({						\
  __typeof__ (x) _x = (x);			\
  __typeof__ (y) _y = (y);			\
  _x < _y ? _x : _y;				\
})
int main()
{
    int a;

    __typeof__(a) _v;
    __typeof__(A) _a;
    _v =20;
    _a.a =40;
    printf("%d\n",_v);
    printf("%d\n",_a.a);
    printf("%d\n",clib_min(1,3));
    return 0;
}
