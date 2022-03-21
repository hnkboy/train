# -*- coding: UTF-8 -*-
gen= (x * x for x in range(10))
print(gen)

# -*- coding: UTF-8 -*-
gen= (x * x for x in range(10))

for num  in  gen :
	print(num)

# -*- coding: UTF-8 -*-
def my_function():
    for i in range(10):
        print ( i )

my_function()

# -*- coding: UTF-8 -*-
def my_function():
    for i in range(10):
        yield i

print(my_function())

# -*- coding: UTF-8 -*-
def fibon(n):
    a = b = 1
    for i in range(n):
        yield a
        a, b = b, a + b

# 引用函数
for x in fibon(1000000):
    print(x , end = ' ')