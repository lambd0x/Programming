package main

import "fmt" //required for I/O print

//Global var assignment only this form works
var name2 string = "Nicolas2"

// name2 := "Nicolas2" won't.

func main() {
	// To run a code do: go run yourfile.go
	// To compile and be able to run from any machine do: go install and execute the generated binary over the bin folder
	/*
		main data types: string, bool, int, int8, int16, int32, int64, uint, uint8, uint16, uint32, uint64, uintptr,
		byte (alias for int8), rune (alias for int32), float32, float64, complex64, complex128
	*/

	// Using var (Go can infer the data type, but for your own awareness keep track of the types)
	// Vars using assignment type 1
	var name string = "Nicolas"
	var age int = 23
	var isCool bool = true
	const isCool2 bool = true // Cannot modify it anymore

	//Vars using assignment type 2 (shorthand) only within functions and u cannot cast inferred types, to do this swap to assignment type 1
	name3 := "Nicolas3"
	size := 1.4
	// also these two could be assigned using the single line assignment
	name4, size2 := "Nicolas4", 1.5

	fmt.Println(name, age, isCool, name3, size, name4, size2)
	// Find the type of the data stored in a var using fmt.Printf("%T", your var) other verbs over https://golang.org/pkg/fmt/
	fmt.Printf("%T %T %T %T %T %T %T %T %T\n", name, age, isCool, isCool2, name2, name3, size, name4, size2)
}
