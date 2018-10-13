package main

import (
	"fmt"
	"runtime"
	"sync"
	"sync/atomic"
)

// This code does multithreading with race condition treated: has two or more things happening at the same time over the CPU.
// go run code.go
// vs
// go run -race code.go

//Ensures that go takes all the host's CPU threads to execute this code
func init() {
	runtime.GOMAXPROCS(runtime.NumCPU())
}

// Defines a go-thread synchronizer
var wg sync.WaitGroup
var counter int32
var mutex sync.Mutex

// Multiple go-threads can go within a thread. It is less costly because of the system architecture.
func incrementor(s string) {
	for i := 0; i < 20; i++ {
		// abstracts the race cond
		atomic.AddInt32(&counter, 1)
		fmt.Println(s, i, " Counter ", counter)
	}
	wg.Done()
}

func main() {
	// We define two go-threads (foo, bar) + main which controls then
	wg.Add(2)
	go incrementor("foo:")
	go incrementor("bar:")
	wg.Wait()
	fmt.Println("Final counter: ", counter)
}
