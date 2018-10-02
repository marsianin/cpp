package main

import (
	"fmt"
	"container/heap"
)

/**
Задача на программирование: (де)кодирование Хаффмана


По данной непустой строке s длины не более 104, состоящей из строчных букв
латинского алфавита, постройте оптимальный беспрефиксный код. В первой
строке выведите количество различных букв k, встречающихся в строке, и размер
получившейся закодированной строки. В следующих k строках запишите коды букв
в формате "letter: code". В последней строке выведите закодированную строку.

Sample Input 1:
a

Sample Output 1:
1 1
a: 0
0

Sample Input 2:
abacabad

Sample Output 2:
4 14
a: 0
b: 10
c: 110
d: 111
01001100100111
 */

type letterList []*letter
type letterKeyMap map[string]int
type letterKeyMapList map[string]*letter

type letter struct {
    key   string
    value int
    code  string
    root  *letter
    left  *letter
    right *letter
}

func (a letterList) Len() int {
    return len(a)
}

func (a letterList) Less(i, j int) bool {
    return a[i].value < a[j].value
}

func (a letterList) Swap(i, j int) {
    a[i], a[j] = a[j], a[i]
}

func (a *letterList) Push(x interface{}) {
	item := x.(*letter)
	*a = append(*a, item)
}

func (a *letterList) Pop() interface{} {
	old := *a
	n := len(old)
	item := old[n-1]
	*a = old[0 : n-1]
	return item
}

func setupCodes(node *letter, prefix string, letterKeyMapListObj letterKeyMapList) {
	if node.left == nil && node.right == nil {
		letterKeyMapListObj[string(node.key)] = node
		node.code = prefix
		return
	}

	setupCodes(node.left, prefix + "0", letterKeyMapListObj)
	setupCodes(node.right, prefix + "1", letterKeyMapListObj)
}

func decodeSymbol(str *string, curStr string, node *letter) string {
	if len(curStr) > 0 && node.code == curStr {
		return node.key
	}

	tmp := (*str)[0:1]
	curStr = curStr + tmp
	*str = (*str)[1:]

	if tmp == "0" {
		return decodeSymbol(str, curStr, node.left)
	} else {
		return decodeSymbol(str, curStr, node.right)
	}
}

func decode(str string, root *letter) string {
	if len(str) == 0 {
		return str
	}

	var result string

	for len(str) > 0 {
		result += decodeSymbol(&str, "", root)
	}

	return result
}

func main() {
    var str string
    fmt.Scanf("%s", &str)

    letterKeyMapObj := make(letterKeyMap, len(str))
	letterKeyMapListObj := make(letterKeyMapList, len(str))
    letterListObj := make(letterList, 0, len(str))

    var key int
    var ok bool

    for _, v := range str {
        if key, ok = letterKeyMapObj[string(v)]; !ok {
            key = len(letterKeyMapObj)
            letterKeyMapObj[string(v)] = key
			letterListObj = append(letterListObj, &letter{key: string(v), value: 0})
        }

        letterListObj[key].value++
    }


    if len(letterListObj) == 1 {
		fmt.Println(1, len(str))
		fmt.Printf("%s: %s\n", letterListObj[0].key, "0")

		for range str {
			fmt.Print("0")
		}

		fmt.Println()
		return
	}

	heap.Init(&letterListObj)

	var curLeft, curRight, root *letter

	// Print the order by Priority of expiry
	for letterListObj.Len() > 0 {
		root = new (letter)
		curLeft = heap.Pop(&letterListObj).(*letter)
		curRight = heap.Pop(&letterListObj).(*letter)

		root.value = curLeft.value + curRight.value
		curLeft.root, curRight.root = root, root
		root.left, root.right = curLeft, curRight

		if (letterListObj.Len() == 0) {
			break
		}

	    heap.Push(&letterListObj, root)
	}

	setupCodes(root, "", letterKeyMapListObj)

	var result string
	for _, v := range str {
		result += letterKeyMapListObj[string(v)].code
	}

	fmt.Println(len(letterKeyMapListObj), len(result))

	for _, v := range letterKeyMapListObj {
		if len(v.key) > 0 {
			fmt.Printf("%s: %s\n", v.key, v.code)
		}
	}

	fmt.Println(result)
}