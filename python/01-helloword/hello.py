

print("Hello Python")
a='test'
print(a)
a=123
print(a)
a, b, c = 1, 2, "liangdianshui"
print(a,b,c)
if a>=0:
    print('yes')
else:
    print('no')
str3='''你好："你哈"'''
print(str3)
list1=['两点水','san','si']
print(list1)

print(list1[0])
print(list1[1:3])

del list1[2]
print(list1)


for i in range(1, 10):
    print('你好' ,i)

def  division ( num1, num2 ):
    	# 求商与余数
         a = num1 % num2
         b = (num1-a) / num2
         return b , a

num1 , num2 = division(9,4)
tuple1 = division(9,4)

print (num1,num2)
print (tuple1)


def print_user_info( name , age , sex = '男' ):
    # 打印用户信息
    print('昵称：{}'.format(name) , end = ' ')
    print('年龄：{}'.format(age) , end = ' ')
    print('性别：{}'.format(sex))
    return;

# 调用 print_user_info 函数

print_user_info( '两点水' , 18 , '女')
print_user_info( '三点水' , 25 )


# 3、for 循环也可以迭代 dict （字典）
dict1 = {'name':'两点水','age':'23','sex':'男'}

for key in dict1 :    # 迭代 dict 中的 key
    print ( key , end = ' ' )