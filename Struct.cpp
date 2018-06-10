#include <iostream>
using namespace std;

struct Cls {
    Cls(char c, double d, int i): c(c), d(d), i(i)
    {}
private:
    char c;
    double d;
    int i;
};

char &get_private_c(Cls &cls) {
    char* ptr = (char*)&cls;
    return *(ptr);
}

double &get_private_d(Cls &cls) {
    double* ptr = (double*)&cls;
    return *(ptr+1);
}

int &get_private_i(Cls &cls) {
    int* ptr = (int*)&cls;
    return *(ptr+4);
}

int main()
{
	Cls * cls = new Cls('t', 1.0, 5);
	char & refC = get_c(*cls); 
	double & refD = get_d(*cls);
	int & refI = get_i(*cls);

	cout << refC << endl;	
        cout << refD << endl;
	cout << refI << endl;
}
