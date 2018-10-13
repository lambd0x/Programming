package main

import (
	"fmt"
	"runtime"
	"sync"
)

// This code does multithreading: has two or more things happening at the same time over the CPU.

//Ensures that go takes all the host's CPU threads to execute this code
func init() {
	runtime.GOMAXPROCS(runtime.NumCPU())
}

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
