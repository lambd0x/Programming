package main

import "fmt"

func main() {
	// Define a map where each string (key) will hold a string (value)
	emails := make(map[string]string)

	//assign kvs
	emails["Bob"] = "bob@gmail.com"
	emails["Alice"] = "alice@gmail.com"
	emails["Steven"] = "steven@gmail.com"

	fmt.Println(emails)
	fmt.Println(len(emails)) // To get the size of the map
	fmt.Println(emails["Bob"])

	// Delete a key
	delete(emails, "Bob")
	fmt.Println(emails)

	fmt.Println()

	// Second way to declare and assign kvs
	emails2 := map[string]string{"Bob": "bob@gmail.com", "Alice": "alice@gmail.com", "Steven": "steven@gmail.com"}

	fmt.Println(emails2)
	fmt.Println(len(emails2)) // To get the size of the map
	fmt.Println(emails2["Bob"])

}
