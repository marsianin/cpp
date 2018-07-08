#include <cstddef>
#include <iostream>
#include <string>
#include <new>

using namespace std;

struct NonCopyable {
    // copy and assignment not allowed
    NonCopyable(const int value ): value_(value) {};
    NonCopyable& operator=(const NonCopyable & obj) = delete;
private:
    int value_;
};


template<typename T>
class Array {
public:
public:
    explicit Array(size_t size, const T& value = T())
            : data_(static_cast<T*>(operator new[](size * sizeof(T))))
            , size_(size) {
        for(int i = 0; i != size; ++i)
            new (data_ + i) T(value);
    }

    Array() {
        size_ = 0;
        data_ = 0;
    }

    Array(const Array &a)
            : data_(static_cast<T*>(operator new[](size_ * sizeof(T))))
            , size_(a.size()) {
        for (int i = 0; i != size_; ++i)
            //data_[i] = a.data_[i];
            new (data_ + i) T(a[i]);
    }

    ~Array() {
        for(int i = 0; i != size_; ++i)
            data_[i].~T();
        operator delete[] (data_);
    }

    Array& operator=(const Array & a) {
        if (this != &a) {
            operator delete [] (data_);
            size_ = a.size();
            data_ = static_cast<T*>(operator new[](size_ * sizeof(T)));
            for (int i = 0; i != size_; ++i)
                new (data_ + i) T(a[i]);
        }
        return *this;
    }

    size_t size() const { return size_; }

    //   две версии оператора доступа по индексу.
    T& operator[](size_t i) { return data_[i]; }
    const T& operator[](size_t i) const { return data_[i]; }

    void prnt()
    {
        for (size_t i = 0; i < size_; ++i)
            cout << *(data_ + i);
        cout << endl;
    }
private :
    T *data_;
    size_t size_;
};


int main() {
    Array<int> *arr0 = new Array<int>();
    Array<int> *arr1 = new Array<int>(10,7);
    Array<float> *arr2 = new Array<float>(5,8.88f);
    Array<float> arr3 = Array<float>(*arr2);
    Array<float> arr4;
    Array<string> *arr5 = new Array<string>(10,"42");
    Array<NonCopyable> *arr6 = new Array<NonCopyable>(5, 10);
    arr4 = arr3;
ы
    for (size_t i = 0; i < arr0->size(); i++)
        cout << "Value of " << i << " element is " << (*arr1)[i] << endl;
    cout<<endl;
    for (size_t i = 0; i < arr1->size(); i++)
        cout << "Value of " << i << " element is " << (*arr1)[i] << endl;
    cout<<endl;
    for (size_t i = 0; i < arr5->size(); i++)
        cout << "Value of " << i << " element is " << (*arr5)[i] << endl;

    cout<<endl;

    for (size_t i = 0; i < arr4.size(); i++)
        cout << "Value of " << i << " element is " << arr4[i] << endl;


    //system("pause");
    return 0;

}