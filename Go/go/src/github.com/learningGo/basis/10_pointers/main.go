package main

import "fmt"

func main() {
	a := 5
	b := &a // b is a pointer of a

	fmt.Println(a, b)
	fmt.Printf("%T %T\n", a, b)

	// Use * to read val from address
	fmt.Println(a, *b)

	// Change de value with the pointer
	*b = 6
	fmt.Println(a, *b)
}
