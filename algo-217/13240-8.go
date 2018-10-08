package main

import (
	"fmt"
	"bufio"
	"os"
	"strings"
)

/**
Задача на программирование: очередь с приоритетами


Первая строка входа содержит число операций 1≤n≤105. Каждая из последующих n строк задают операцию одного из следующих двух типов:

𝙸𝚗𝚜𝚎𝚛𝚝 𝚡, где 0≤x≤109 — целое число;
𝙴𝚡𝚝𝚛𝚊𝚌𝚝𝙼𝚊𝚡.
Первая операция добавляет число x в очередь с приоритетами, вторая — извлекает максимальное число и выводит его.

Sample Input:

6
Insert 200
Insert 10
ExtractMax
Insert 5
Insert 500
ExtractMax

Sample Output:
200
500
 */

func up(heap *[]int, i int)  {
 	i = i - 1
 	if i == 0 {
 		return
	}

	for (*heap)[i] > (*heap)[(i-1)/2] {
		(*heap)[i], (*heap)[(i-1)/2] = (*heap)[(i-1)/2], (*heap)[i]
		i = (i-1)/2
	}
}

func down(heap *[]int, i int, heapSize int) {
	for (2*i + 1) <= heapSize {
		left := 2*i + 1
		right := 2*i + 2

		j := left
		if right <= heapSize && (*heap)[right] > (*heap)[left] {
			j = right
		}

		if (*heap)[i] >= (*heap)[j] {
			break
		}

		(*heap)[i], (*heap)[j] = (*heap)[j], (*heap)[i]
		i = j
	}
}

func extractMax(heap *[]int, heapSize *int) int {
    max := (*heap)[0]
	(*heap)[0] = (*heap)[*heapSize - 1]
	(*heap)[*heapSize - 1] = 0
	*heapSize = *heapSize - 1
    down(heap, 0, *heapSize)
    return max
}

func insert(heap *[]int, elem int, heapSize *int) {
	(*heap)[*heapSize] = elem
	*heapSize = *heapSize + 1
	up(heap, *heapSize)
}

func main()  {
	var n int

	fmt.Scanf("%d", &n)

	heap := make([]int, n + 1, n + 1)

	heapSize := 0
	var tmp int

	reader := bufio.NewReader(os.Stdin)
	for i:=0;i<n;i++  {
		tmpStr,_ := reader.ReadString('\n')
		tmpStr = strings.Trim(tmpStr, "\n")

		if tmpStr == "ExtractMax" {
			fmt.Println(extractMax(&heap, &heapSize))
		} else {
			fmt.Sscanf(tmpStr, "Insert %d", &tmp)
			insert(&heap, tmp, &heapSize)
		}
	}
}