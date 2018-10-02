package main

import (
	"fmt"
	"strconv" // To stringify other types
)

// There's no classes in Go, but its structs behave alike to C's structs
type Person struct {
	firstName string
	lastName  string
	city      string
	gender    string
	age       int
}

// Shortcut
type Person2 struct {
	firstName, lastname, city, gender string
	age                               int
}

// Methods go outside of the struct

// Greeting method (value receiver)
func (identifier Person) greet() string {
	return "Hello, my first name is " + identifier.firstName + " " + identifier.lastName + " and I'm " + strconv.Itoa(identifier.age)
}

// hasbirthday method (pointer receiver)
func (identifier2 *Person) hasBirthday() {
	identifier2.age++
}

//getMarried method (pointer receiver)
func (identifier3 *Person) getMarried(spouseLastName string) {
	if identifier3.gender == "f" {
		identifier3.lastName = spouseLastName
	}
}

func main() {
	// Init person using struct
	person1 := Person{firstName: "Samantha", lastName: "Smith", city: "Boston", gender: "f", age: 25}
	// Alternative method
	person2 := Person{"Alice", "Smith", "Boston", "f", 25}
	person3 := Person{"John", "Mice", "Boston", "m", 25}

	fmt.Println(person1)
	fmt.Println(person2)

	// Get field from struct
	fmt.Println(person2.firstName)

	// Change field from struct
	person1.age = 44
	fmt.Println(person1)

	// Methods can be value receivers (used for calculations and etc. where no actual change occur) or pointer receivers (used for when actual change is done)
	fmt.Println(person1.greet())
	person1.hasBirthday()
	person1.hasBirthday()
	fmt.Println(person1.greet())

	person1.getMarried("Williams")
	fmt.Println(person1.greet())

	person3.getMarried("Williams")
	fmt.Println(person3.greet())
}
