package main

import "fmt" //required for I/O print
func main() {
	x := 5
	y := 10

	// Common convention is to not use ( ) but it you do, it won't conplain
	// Supported binary operations: <, >, <=, >=, ==, !=
	// Supported binary operations: ||, &&
	// if else
	if x < y {
		fmt.Printf("%d is lesser than %d\n", x, y)
	} else {
		fmt.Printf("%d is higher than than %d\n", x, y)
	}

	// if else
	color := "red"
	if color == "red" {
		fmt.Println("Color is red")
	} else if color == "blue" {
		fmt.Println("Color is blue")
	} else {
		fmt.Println("Color is not blue or red")
	}

	// switch
	switch color {
	case "red":
		fmt.Println("Color is red")
	case "blue":
		fmt.Println("Color is blue")
	default:
		fmt.Println("Color is not red or blue")
	}
}
