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

Теория
http://neerc.ifmo.ru/wiki/index.php?title=%D0%94%D0%B2%D0%BE%D0%B8%D1%87%D0%BD%D0%B0%D1%8F_%D0%BA%D1%83%D1%87%D0%B0
 */

type heap struct {
	data []int
	size int
}

func (h *heap) up(i int)  {
 	i = i - 1
 	if i == 0 {
 		return
	}

	for h.data[i] > h.data[(i-1)/2] {
		h.data[i], h.data[(i-1)/2] = h.data[(i-1)/2], h.data[i]
		i = (i-1)/2
	}
}

func (h *heap) down(i int) {
	for (2*i + 1) <= h.size {
		left := 2*i + 1
		right := 2*i + 2

		j := left
		if right <= h.size && h.data[right] > h.data[left] {
			j = right
		}

		if h.data[i] >= h.data[j] {
			break
		}

		h.data[i], h.data[j] = h.data[j], h.data[i]
		i = j
	}
}


func (h *heap) extractMax() int {
    max := h.data[0]
	h.data[0] = h.data[h.size - 1]
	h.data[h.size - 1] = 0
	h.size--
	h.down(0)

    return max
}

func (h *heap) insert(elem int) {
	h.data[h.size] = elem
	h.size++
	h.up(h.size)
}

func main()  {
	var n int

	fmt.Scanf("%d", &n)

	heapObj := heap{
		make([]int, n + 1, n + 1),
		0,
	}

	var tmp int

	reader := bufio.NewReader(os.Stdin)
	for i:=0;i<n;i++  {
		tmpStr,_ := reader.ReadString('\n')
		tmpStr = strings.Trim(tmpStr, "\n")

		if tmpStr == "ExtractMax" {
			fmt.Println(heapObj.extractMax())
		} else {
			fmt.Sscanf(tmpStr, "Insert %d", &tmp)
			heapObj.insert(tmp)
		}
	}
}