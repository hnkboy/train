# const
常量使用关键字 const 定义，用于存储不会改变的数据。
常量的值必须是能够在编译时就能够确定的；你可以在其赋值表达式中涉及计算过程，但是所有用于计算的值必须在编译期间就能获得。
正确的做法：const c1 = 2/3
错误的做法：const c2 = getNumber() // 引发构建错误: getNumber() used as value
因为在编译期间自定义函数均属于未知，因此无法用于常量的赋值，但内置函数可以使用，如：len()。


