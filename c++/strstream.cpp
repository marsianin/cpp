#include <iostream>
using namespace std;

/** Dynamic allocate memory for STDIN */
char *resize(const char *str, unsigned size, unsigned new_size)
{
    char * resizedStr = new char[new_size];

    if (size >= new_size) {
        size = new_size;
    }

    for (int i=0; i<size; i++){
        *(resizedStr+i) = *(str+i);
    }

    delete [] str;

    return resizedStr;
}

char *cinStreamRead()
{
    char c;
    int i = 0;
    unsigned size = 4;
    char* res = new char[size];
    while (std::cin.get(c) && c != '\n') {
        if (i == size) {
            res = resize(res, size, size*2);
            size *= 2;
        }

        res[i] = c;
        i++;
    }

    res[size] = '\0';

    return res;
}

int main()
{
    char * res = cinStreamRead();

    for (char * i = res ; *i != '\0'; i++) {
        cout << *i;
    }
}
