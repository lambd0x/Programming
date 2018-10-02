package main

import "fmt" //required for I/O print
func main() {
	// Long method
	i := 1
	for i <= 10 {
		fmt.Println(i)
		// Supports: a++, a--, ++a, --a, a += b, a -= b, a *= b, a/= b
		i = i + 1
	}

	// Short method
	for i := 1; i <= 10; i++ {
		fmt.Printf("Number %d\n", i)
	}
	fmt.Println()

	// Fizzbuzz: loop 1 thro 100 and when i is multiple of 3 prints fizz, when i is multiple of 5 prints buzz, and if i is multiple of both 3 and 5 prints bizzbuss
	for i := 1; i <= 100; i++ {
		if i%15 == 0 {
			fmt.Printf("Fizzbuzz\n")
		} else if i%3 == 0 {
			fmt.Printf("Fizz\n")
		} else if i%5 == 0 {
			fmt.Printf("Buzz\n")
		} else {
			fmt.Printf("%d\n", i)
		}
	}
}
