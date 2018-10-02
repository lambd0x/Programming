package main

import "fmt" //required for I/O print

func greeting(name string) string {
	return "Hello " + name
}

func sum(num1 int, num2 int) int {
	return num1 + num2
}

func sum2(num1, num2 int) int {
	return num1 + num2
}

func main() {
	// To run a code do: go run yourfile.go
	// To compile and be able to run from any machine do: go install and execute the generated binary over the bin folder
	fmt.Println(greeting("Nicolas"))
	fmt.Println(sum(4, 6))
	fmt.Println(sum2(1, 6))
}
