#include <iostream>
#include <map>

/**
https://stepik.org/lesson/44327/step/15?unit=22137

 2.4 Страничная организация памяти

Проверим, как вы поняли paging. Для этого вам предлагается выступить в качестве процессора и преобразовать несколько логических адресов в физические. Формат входных данных следующий:

в первой строке вам даны 3 числа m,q,r≥0 , где q - это количество запросов, на которые вам нужно ответить, r - физический адрес корневой таблицы страниц
следующих m строках записаны пары paddr и value - описание физической памяти, каждая пара значит, что по физическому адресу paddr хранится 64 битное значение value, при этом гарантируется, что все paddr различны, выровнены на границу 8 байт и помещаются в 64 бита
в последних q строках идут целые числа - логические адреса, которые вам нужно преобразовать в физические, для каждого из этих чисел нужно вывести на отдельной строке либо физический адрес, либо слово "fault", если преобразовать логический адрес в физический нельзя.
Считайте, что таблица страниц имеет формат 64 битного режима x86 (4 уровня, каждая страница 4 KB, каждая запись 8 байт, формат записи был показан в лекциях), но вы можете игнорировать все поля, кроме бита присутствия (на картинке бит P - нулевой бит) и собственно физического адреса.

Для всех физических адресов, не указанных во входных данных (среди m пар paddr value), считайте, что по этим адресам хранятся нули.

ВАЖНО: это было неочевидно из видео, но все физические адреса, которые хранятся в записях таблицы страниц должны быть выровнены, как минимум, на границу 4096 байт (4Kb), т. е. младшие 12 бит физических адресов всегда равны 0, соответственно, хранить младшие биты нет смысла и в записе таблицы страниц они не хранятся - их место занимают специальные флаги. Убедитесь, что вы понимаете приведенный пример.

ВАЖНО2: после каждой неверной попытки вам требуется скачать новый набор данных и использовать его для следующей попытки.

Sample Input:

4 4 0
0 4097
4096 8193
8192 12289
12288 16385
0
4096
42
131313
Sample Output:

16384
fault
16426
fault
Задача на данные — Обработайте индивидуальный набор данных за отведённое время


 */

const uint64_t from47to39 = 0xFF8000000000;
const uint64_t from38to30 = 0x7FC0000000;
const uint64_t from29to21 = 0x3FE00000;
const uint64_t from20to12 = 0x1FF000;
const uint64_t from51to12 = 0xFFFFFFFFFF000;

const uint64_t from47to39shift = 39;
const uint64_t from38to30shift = 30;
const uint64_t from29to21shift = 21;
const uint64_t from20to12shift = 12;

bool isInPresent(uint64_t addr) {
    return (addr & 1) == 1;
}

struct PageFaultException : public std::exception {
    const char * what () const throw () {
        return "fault";
    }
};

uint64_t getSegmentOffset(uint64_t type, uint64_t number) {
    switch (type) {
        case from47to39shift:
            return (number & from47to39) >> from47to39shift;
        case from38to30shift:
            return (number & from38to30) >> from38to30shift;
        case from29to21shift:
            return (number & from29to21) >> from29to21shift;
        case from20to12shift:
            return (number & from20to12) >> from20to12shift;
        default:
            return 0;
    }
}

uint64_t convertVirtualAddrToPhisicalAddr(uint64_t cr, std::map<uint64_t, uint64_t> &memoryMap, uint64_t virtualAddr) {
    uint64_t  tmp;

    uint64_t p4offset = getSegmentOffset(from47to39shift, virtualAddr);
    uint64_t p3offset = getSegmentOffset(from38to30shift, virtualAddr);
    uint64_t p2offset = getSegmentOffset(from29to21shift, virtualAddr);
    uint64_t p1offset = getSegmentOffset(from20to12shift, virtualAddr);

    tmp = cr + (p4offset * 8);
    tmp = memoryMap[tmp];

    if (!isInPresent(tmp)) {
        throw PageFaultException();
    }

    tmp = tmp & from51to12;
    tmp = tmp + (p3offset * 8);
    tmp = memoryMap[tmp];
    if (!isInPresent(tmp)) {
        throw PageFaultException();
    }

    tmp = tmp & from51to12;
    tmp = tmp + (p2offset * 8);
    tmp = memoryMap[tmp];
    if (!isInPresent(tmp)) {
        throw PageFaultException();
    }

    tmp = tmp & from51to12;
    tmp = tmp + (p1offset * 8);
    tmp = memoryMap[tmp];

    if (!isInPresent(tmp)) {
        throw PageFaultException();
    }

    tmp = tmp & from51to12;

    uint64_t result = tmp + (virtualAddr & 0xFFF);

    return result;
}

int main() {
    uint64_t m,q,r;

    std::cin >> m >> q >> r;
    std::map<uint64_t,uint64_t> memoryMap;

    for (int i = 0; i < m; ++i) {
        uint64_t pAddr, value;
        std::cin >> pAddr >> value;

        memoryMap[pAddr] = value;
    }

    for (int i = 0; i < q; ++i) {
        uint64_t vAddr;

        std::cin >> vAddr;
        try {
            std::cout << convertVirtualAddrToPhisicalAddr(r, memoryMap, vAddr) << std::endl;
        } catch (PageFaultException& e) {
            std::cout << e.what() << std::endl;
        }
    }

    return 0;
}
