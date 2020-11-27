# var https://github.com/unknwon/the-way-to-go_ZH_CN/blob/master/eBook/04.8.md
声明变量的一般形式是使用 var 关键字：var identifier type。
需要注意的是，Go 和许多编程语言不同，它在声明变量时将变量的类型放在变量的名称之后。

放后面的原因
- 避免含糊不清
c语言中 int * a，b；
b不是指针类型，用var a b *int； 能很清晰的表示出来都是 *int类型

- 从左往右的顺序阅读，容易理解

知识点
- 当一个变量被声明之后，系统自动赋予它该类型的零值
- 变量的命名规则遵循骆驼命名法，即首个单词小写，每个新单词的首字母大写，例如：numShips 和 startDate。
- var a这种语法是不正确的，因为编译器没有任何可以用于自动推断类型的依据
- var（a=15; b=false）这种写法用于包级别的全局变量
- := 当你在函数体内声明局部变量时，应使用简短声明语法 :=

