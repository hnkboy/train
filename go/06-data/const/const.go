package main

import "fmt"

const Pi = 3.14159
const st string = "abc" //显示类型
const st1 = "abc"       //隐式类型 因为编译器可以根据变量的值来推断其类型。

//数字型的常量是没有大小和符号的，并且可以使用任何精度而不会导致溢出：
//当常量赋值给一个精度过小的数字型变量时，可能会因为无法正确表达常量所代表的数值而导致溢出，这会在编译期间就引发错误
const Ln2 = 0.693147180559945309417232121458176568075500134360255254120680009
const Log2E = 1 / Ln2 // this is a precise reciprocal
const Billion = 1e9   // float constant
const hardEight = (1 << 100) >> 97

//常量也允许使用并行赋值的形式：
const beef, two, cc = "eat", 2, "veg"
const Monday, Tuesday, Wednesday, Thursday, Friday, Saturday = 1, 2, 3, 4, 5, 6
const (
	Monday1, Tuesday1, Wednesday1 = 1, 2, 3
	Thursday1, Friday1, Saturday1 = 4, 5, 6
)

//第一个 iota 等于 0，每当 iota 在新的一行被使用时，它的值都会自动加 1，并且没有赋值的常量默认会应用上一行的赋值表达式：
const (
	a = iota
	b = iota
	c = iota
)
const (
	e = iota
	f = iota
	g = iota
)

func main() {
	fmt.Println(a, b, c)
	fmt.Println(e, f, g)
	fmt.Printf("hello, world\n")
}
