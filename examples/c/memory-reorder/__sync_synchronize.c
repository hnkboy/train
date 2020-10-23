#include <stdio.h>

int main(){
  //__sync_synchronize();
  int x = 0, y = 0, z = 0;
  x=4;
  y=3;
  z = x+y;
  printf("%d\n",z);
  return 0;
}

/*我们在做多线程编程的时候，会涉及到一个称为memory order的问题。
例如
int x(0),y(0); x=4; y=3;
请问，实际执行的时候，这两条赋值语句谁先执行，谁后执行？ 会不会有某个时间点，在某个CPU看来，y比x大？
答案很复杂。本文的目的是从非常实践的角度来考虑这个问题。
首先，它分为两个层面。在编译器看来，x和y是两个没有关联的变量，那么编译器有权利调整这两行代码的执行顺序，只要它乐意。
其次，CPU也有权利这么做。
如果我非要严格要求顺序，那么就应该插入一个memory barrier
int x(0),y(0); x=4; 在此插入memory barrier指令 y=3;*/