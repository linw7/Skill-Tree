package main

import (
	"math"
	"fmt"
)

type DataStruct struct {
	Data []int
}

func (d *DataStruct) Find(k int) int {
	left, right, mid := 1, len(d.Data), 0
	for {
		mid = int(math.Floor(float64((left + right) / 2)))
		if d.Data[mid] > k {
			right = mid - 1
		} else if d.Data[mid] < k {
			left = mid + 1
		} else {
			break
		}
		if left > right {
			mid = -1
			break
		}
	}
	return mid
}

func main() {
	a1 := DataStruct{[]int{1, 2, 5, 7, 15, 25, 30, 36, 39, 51, 67, 78, 80, 82, 85, 91, 92, 97}}
	fmt.Println(a1.Find(30))
}