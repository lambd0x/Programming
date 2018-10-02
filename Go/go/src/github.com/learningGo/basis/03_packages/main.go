package main

// This is the correct way to have multiple libs from each package called
import (
	"fmt"
	"github.com/learningGo/basis/03_packages/strutil"
	"math"
)

func main() {
	fmt.Println(math.Floor(2.7))
	fmt.Println(math.Ceil(2.7))
	fmt.Println(math.Sqrt(4))
	fmt.Println(math.Floor(2.7))
	fmt.Println(strutil.Reverse("Nicolas"))
}
