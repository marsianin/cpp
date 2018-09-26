/**
Задача на программирование: различные слагаемые
По данному числу 1≤n≤109 найдите максимальное число k, для которого n можно
представить как сумму k различных натуральных слагаемых. Выведите в первой
строке число k, во второй — k слагаемых.
 */

package main

import (
	"fmt"
)

func main() {
	var num int
	fmt.Scanf("%d", &num)

	if num == 1 || num == 2 {
		fmt.Println(1)
		fmt.Println(num)
		return
	}

	i := 1
	parts := make([]int, 0, num/2)


	for {
		if (num - i) < (i + 1) {
			parts = append(parts, num)
			break
		} else {
			parts = append(parts, i)
		}

		num = num - i
		i++
	}

	fmt.Println(len(parts))
	for _, v := range parts {
		fmt.Print(v, " ")
	}
}