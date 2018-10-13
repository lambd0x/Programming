package main

import (
	"fmt"
	"sync"
)

// This code does concurrency: has two or more things happening, but the CPU can only handle a single thing per clock.

// Defines a go-thread synchronizer
var wg sync.WaitGroup

// Multiple go-threads can go within a thread. It is less costly because of the system architecture.
func foo() {
	for i := 0; i < 45; i++ {
		fmt.Println("Foo", i)
	}
	wg.Done()
}

func bar() {
	for i := 0; i < 45; i++ {
		fmt.Println("Bar", i)
	}
	wg.Done()
}

func main() {
	// We define two go-threads (foo, bar) + main which controls then
	wg.Add(2)
	go foo()
	go bar()
	wg.Wait()
}
