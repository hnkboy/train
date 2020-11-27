package main

import (
	"fmt"
	fm "fmt"
)      //   note1： alias3
type ( //note2: typedef
	IZ int
)

var a IZ = 5

func calc(index string, a, b int) int {
	ret := a + b
	fmt.Println(index, a, b, ret)
	return ret
}
func calc2(index string, a, b int) (t1 int, t2 int) {
	ret := a + b
	fmt.Println(index, a, b, ret)
	return 0, ret
}

func main() {
	c := int(a)
	b := 5.1
	d := int(b) //note2: 强制转换
	fm.Println(a, c, d)
	e, f := calc2("test", 1, 2)
	fm.Println(e, f)
	fm.Println("hello world")
}
