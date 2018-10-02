package main

import "fmt" //required for I/O print

func main() {
	// Arrays cannot later receive more values, whereas slices can
	var fruitArray [2]string
	fruitArray[0] = "orange"
	fruitArray[1] = "apple"
	// Shorthand for arrays
	fruitArray2 := [2]string{"orange", "apple"}
	fmt.Println(fruitArray[0], fruitArray[1])
	fmt.Println(fruitArray2[0], fruitArray2[1])

	// Slices
	fruitSlice := []string{"orange", "apple"}
	fmt.Println(fruitSlice)
}
