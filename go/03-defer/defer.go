package main
import(
	"fmt"
)
func calc(index string, a, b int) int {
	ret := a + b
	fmt.Println(index, a, b, ret)
	return ret
}

func main() {
	x := 1
	y := 2
	tmp1 := calc("B", x, y)
	defer calc("A", x, tmp1)
	x = 3
	tmp2 := calc("D", x, y)
	defer calc("C", x, tmp2)
	y = 4
}
