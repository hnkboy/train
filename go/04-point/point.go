package main

import "fmt"

func main() {
	var p *int
	p = new(int)
	*p = 1
	fmt.Println(p, &p, *p)
}
