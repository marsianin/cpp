/**
Задача на программирование: покрыть отрезки точками


По данным n отрезкам необходимо найти множество точек минимального размера, для которого каждый из отрезков содержит хотя бы одну из точек.

В первой строке дано число 1≤n≤100 отрезков. Каждая из последующих n строк содержит по два числа 0≤l≤r≤109, задающих начало и конец отрезка. Выведите оптимальное число m точек и сами m точек. Если таких множеств точек несколько, выведите любое из них.

 */
#include <iostream>
#include <utility>
#include <vector>
#include <algorithm>

using Segment = std::pair<int, int>;

bool sortbysec(const Segment &a, const Segment &b) {
    return (a.second < b.second);
}

std::vector <int> get_covering_set(std::vector <Segment> segments) {
    std::vector <int> result;
    sort(segments.begin(), segments.end(), sortbysec);

    for(std::size_t i = 0; i < segments.size(); i++) {
        int right = segments.at(i).second;
        result.push_back(segments[i].second);

        for (int k = i+1; k < segments.size(); k++) {
            if (segments.at(k).first <= right) {
                i++;
            } else {
                break;
            }
        }
    }

    return result;
}

int main(void) {
    int segments_count;
    std::cin >> segments_count;
    std::vector <Segment> segments(segments_count);
    for (auto &s:segments) {
        std::cin >> s.first >> s.second;
    }

    auto points = get_covering_set(std::move(segments));
    std::cout << points.size() << std::endl;
    for (auto point:points) {
        std::cout << point << " ";
    }
    std::cout << std::endl;
}