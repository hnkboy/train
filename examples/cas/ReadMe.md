CAS是compare and swap,   简单来说就是，在写入新值之前， 读出旧值， 当且仅当旧值与存储中的当前值一致时，才把新值写入存储。__sync_bool_compare_and_swap是可供程序员调用的接口， 为什么需要CAS呢？ 



test.c 多线程不加锁，简单累加，结果错误

test2.c 加互斥锁正确

test.3c   __sync_bool_compare_and_swap









Gcc 4.1.2版本之后，对X86或X86_64支持内置原子操作。就是说，不需要引入第三方库（如pthread）的锁保护，即可对1、2、4、8字节的数值或指针类型，进行原子加/减/与/或/异或等操作。有了这套内置原子操作函数，写程序方便很多。老宋根据Gcc手册中《[Using the GNU Compiler Collection (GCC)](https://link.zhihu.com/?target=http%3A//gcc.gnu.org/onlinedocs/gcc-4.1.2/gcc/Atomic-Builtins.html)》章节内容，将__sync_系列17个函数声明整理简化如下：

1. **type __sync_fetch_and_add (type \*ptr, type value, ...)**
   // 将value加到*ptr上，结果更新到*ptr，并返回操作之前*ptr的值
2. **type __sync_fetch_and_sub (type \*ptr, type value, ...)**
   // 从*ptr减去value，结果更新到*ptr，并返回操作之前*ptr的值
3. **type __sync_fetch_and_or (type \*ptr, type value, ...)**
   // 将*ptr与value相或，结果更新到*ptr， 并返回操作之前*ptr的值
4. **type __sync_fetch_and_and (type \*ptr, type value, ...)**
   // 将*ptr与value相与，结果更新到*ptr，并返回操作之前*ptr的值
5. **type __sync_fetch_and_xor (type \*ptr, type value, ...)**
   // 将*ptr与value异或，结果更新到*ptr，并返回操作之前*ptr的值
6. **type __sync_fetch_and_nand (type \*ptr, type value, ...)**
   // 将*ptr取反后，与value相与，结果更新到*ptr，并返回操作之前*ptr的值
7. **type __sync_add_and_fetch (type \*ptr, type value, ...)**
   // 将value加到*ptr上，结果更新到*ptr，并返回操作之后新*ptr的值
8. **type __sync_sub_and_fetch (type \*ptr, type value, ...)**
   // 从*ptr减去value，结果更新到*ptr，并返回操作之后新*ptr的值
9. **type __sync_or_and_fetch (type \*ptr, type value, ...)**
   // 将*ptr与value相或， 结果更新到*ptr，并返回操作之后新*ptr的值
10. **type __sync_and_and_fetch (type \*ptr, type value, ...)**
    // 将*ptr与value相与，结果更新到*ptr，并返回操作之后新*ptr的值
11. **type __sync_xor_and_fetch (type \*ptr, type value, ...)**
    // 将*ptr与value异或，结果更新到*ptr，并返回操作之后新*ptr的值
12. **type __sync_nand_and_fetch (type \*ptr, type value, ...)**
    // 将*ptr取反后，与value相与，结果更新到*ptr，并返回操作之后新*ptr的值
13. **bool __sync_bool_compare_and_swap (type \*ptr, type oldval type newval, ...)**
    // 比较*ptr与oldval的值，如果两者相等，则将newval更新到*ptr并返回true
14. **type __sync_val_compare_and_swap (type \*ptr, type oldval type newval, ...)**
    // 比较*ptr与oldval的值，如果两者相等，则将newval更新到*ptr并返回操作之前*ptr的值
15. **__sync_synchronize (...)**
    // 发出完整内存栅栏
16. **type __sync_lock_test_and_set (type \*ptr, type value, ...)**
    // 将value写入*ptr，对*ptr加锁，并返回操作之前*ptr的值。即，try spinlock语义
17. **void __sync_lock_release (type \*ptr, ...)**
    // 将0写入到*ptr，并对*ptr解锁。即，unlock spinlock语义