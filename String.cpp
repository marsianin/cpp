#include <cstddef> // size_t
#include <cstring> // strlen, strcpy

using namespace std;

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

    /* и деструктор */
    ~String() {
        delete [] str;
    }
 
    size_t size;
    char *str;
};

int main(){
    String s1("Hello,");
    String s2(" world!");

    s1.append(s2);
    
    cout << s1.str << endl;
}
