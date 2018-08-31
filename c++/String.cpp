#include <iostream>
#include <cstddef> // size_t
#include <cstring> // strlen, strcpy
#include <string>

using namespace std;

struct StringInner;

struct String {
    String(const char *str = ""){
        size = strlen (str);
        this->str = new char[size+1];
        strcpy(this->str, str);
    }
    
    String(size_t n, char c){
         this->size = n;
         this->str = new char[n+1];
  
         for (unsigned i = 0; i < n; i++){
            str[i] = c;
         } 
         str[n] = '\0';
    } 

    String(const String &other) : 
        size(other.size), str(new char[size+1])
    {
        for(size_t i = 0; i != size; ++i){
            str[i] = other.str[i];
        }
        
        str[size] = '\0';
    }

    String &operator=(const String &other) {
        if (this == &other) {
            return *this;
        }
        
        delete [] str;
        size = other.size;
        str = new char[size+1];
        strcpy(str, other.str);
        
        return *this;
    }

    void append(String &other)
    {
       size_t prevSize = size;
       size += other.size;
       char * tmp = new char[prevSize + size + 1];
       strcpy(tmp, str);
       strcpy(tmp + prevSize, other.str);
       tmp[size] = '\0';
       
       delete[] str;
       str = tmp;
    }

    StringInner operator[] (int k) const;

    /* и деструктор */
    ~String() {
        delete [] str;
    }
 
    size_t size;
    char *str;
};

class StringInner {
    public:

    StringInner(const char *str = "", size_t start = 0){
        size = strlen (str);
        this->start = start;
        this->str = new char[size+1];
        strcpy(this->str, str);
    }

    String operator[] (int k) const {
        char* tmp = new char[k-start];

        for (unsigned i = 0; i < k-start; i++){
            tmp[i] = str[i];
        }

        tmp[k-start] = '\0';
        String s(tmp);
        delete [] tmp;

        return s;
    }

    /* и деструктор */
    ~StringInner() {
        delete [] str;
    }

    size_t size;
    size_t start;
    char *str;
};

StringInner String::operator[] (int k) const {
    char* tmp = new char[size-k+1];

    for (unsigned i = k; i < size; i++){
        tmp[i-k] = str[i];
    }

    tmp[size-k] = '\0';

    StringInner s(tmp, k);
    delete [] tmp;

    return s;
}

int main(){
    String s1("Hello,");
    String s2(" world!");

    String s123("hello");

    // Copy three characters of s1 (starting
    // from position 1)
    cout << "===" <<  s123[0][4].str << "===" << s123[0][4].size << endl;
    cout << "===" <<  s123[1][4].str << "===" << s123[1][4].size << endl;
    cout << "===" <<  s123[5][5].str << "===" << s123[5][5].size << endl;

    s1.append(s2);

    cout << s1.str << endl;
}
