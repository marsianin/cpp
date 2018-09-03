#include <iostream>
#include <map>
#include <string>
#include <sstream>

/**
Попробуйте решить задачу в общем случае. В первой строке вам дается число задач N.
В следующей строке идет описание задач, для каждой задачи вам дана ее
продолжительность - Ti (где i - это номер задачи, от 0 до N−1 не включительно).
На выход вам требуется вывести номера задач (задачи нумеруются с 0) в порядке,
который минимизирует среднее время ожидания завершения задачи, как это было объяснено ранее.

Гарантируется, что 0<N≤10000 и 0<Ti≤10000 и все числа целые.

Sample Input:

3
9 7 3
Sample Output:

2 1 0
 */

int main() {
    int n;
    std::string input;

    std::cin >> n;
    std::cin.ignore();
    std::getline(std::cin,input);

    std::multimap<int,int> timePlanSpendMap;

    std::string buf;
    std::stringstream ss(input);

    int i=0;
    while (ss >> buf) {
        timePlanSpendMap.insert(std::pair<int,int>(std::stoi(buf), i++));
    }

    for (auto const& x : timePlanSpendMap)
    {
        std::cout << x.second << " ";
    }

    std::cout << std::endl;

    return 0;
}