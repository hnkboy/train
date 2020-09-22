package main
import (
	"fmt"
    "time"
)
func producer(ch chan string) {
	fmt.Println("producer start")
	ch <- "a"
	ch <- "b"
	ch <- "c"
	ch <- "d"
	fmt.Println("producer end")
}

func customer(ch chan string) {
	for {
		msg := <- ch
		fmt.Println(msg)
	}
}

func main() {
	fmt.Println("main start")
	ch := make(chan string, 3)
	go producer(ch)
	time.Sleep(1 * time.Second)
	go customer(ch)
	fmt.Println("main end")
}
