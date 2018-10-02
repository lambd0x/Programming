package main

import "fmt"

func main() {
	// array of int
	ids := []int{33, 76, 54, 23, 11, 2}

	//Loop through ids
	for i, id := range ids {
		fmt.Printf("%d - ID: %d\n", i, id)
	}

	//Loop not using index
	for _, id := range ids {
		fmt.Printf("ID: %d\n", id)
	}

	//Loop and add all ids together
	sum := 0
	for _, id := range ids {
		sum += id
	}
	fmt.Printf("ID sum: %d\n", sum)

	//Range with map
	emails := map[string]string{"Bob": "bob@gmail.com", "Alice": "alice@gmail.com", "Steven": "steven@gmail.com"}

	for k, v := range emails {
		fmt.Printf("Individual %s, email %s\n", k, v)
	}
}
