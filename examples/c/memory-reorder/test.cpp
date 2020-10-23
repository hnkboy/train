#include <iostream>
#include <atomic>
#include <thread>
#include <cassert>
using namespace std;

int x, y, a, b;

int test1() {
  x = y = 0;
  a = b = 0;
  __sync_synchronize();
  assert(x == 0 && y == 0 && a == 0 && b == 0);

  auto proc1 = [&]() {
    x = 1;
    asm volatile("" ::: "memory");
    //作用是防止编译器reorder,但是不影响硬件的reorder
    //__sync_synchronize();
    if (y == 0) {
      a = 1;
    }
  };

  auto proc2 = [&]() {
    y = 1;
    asm volatile("" ::: "memory");
    //__sync_synchronize();
    if (x == 0) {
      b = 1;
    }
  };

  thread t1(proc1);
  thread t2(proc2);

  t1.join();
  t2.join();

  __sync_synchronize();
  if (a == 1 && b == 1) {
    printf("got x == 0 && y == 0\n");
    return 1;
  }

  return 0;
}

int main(int argc, char** argv)
{
  for (int i = 0; i < 100000000; i++) {
    if (test1() == 1) {
      printf("i: %d\n", i);
    }
  }

  return 1;
}


/*
asm volatile ("" ::: "memory")只是一个编译器障碍。
asm volatile ("mfence" ::: "memory")既是编译器障碍又是MFENCE
__sync_synchronize()也是编译器屏障和完整内存屏障。
所以asm volatile ("" ::: "memory")本身不会阻止CPU重新排序独立的数据指令。
正如所指出的，x86-84具有强大的内存模型，但StoreLoad重新排序仍然是可能的。
如果您的算法需要完整的内存屏障，那么您需要__sync_synchronize
*/