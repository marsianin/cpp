#include <iostream>

struct Expression {
    virtual double evaluate() const = 0;
};

struct Number : Expression {
    Number(double value)
            : value(value) {}

    double evaluate() const {
        return value;
    }

private:
    double value;
};

struct BinaryOperation : Expression {
    BinaryOperation(Expression const *left, char op, Expression const *right)
            : left(left), op(op), right(right) {}

    double evaluate() const {
        if (op == '+') {
            return left->evaluate() + right->evaluate();
        }
        if (op == '-') {
            return left->evaluate() - right->evaluate();
        }
        if (op == '*') {
            return left->evaluate() * right->evaluate();
        }
        if (op == '/') {
            return left->evaluate() / right->evaluate();
        }
    }

    ~BinaryOperation() {
        delete left;
        delete right;
    }

private:
    Expression const *left;
    Expression const *right;
    char op;
};

bool instanceOf(Expression const *left, Expression const *right) {
    int *vptrLeft = *(int **) left;
    int *vptrRight = *(int **) right;
    return vptrLeft == vptrRight;
}

struct ScopedPtr {
    explicit ScopedPtr(Expression *ptr = 0) : ptr_(ptr) {}

    ~ScopedPtr() {
        delete ptr_;
    }

    Expression *get() const {
        return ptr_;
    }

    void reset(Expression *ptr = 0) {
        delete ptr_;
        ptr_ = ptr;
    }

    Expression &operator*() const {
        return *ptr_;
    }

    Expression *operator->() const {
        return ptr_;
    }

    Expression *release() {
        Expression *tmp = ptr_;
        ptr_ = NULL;
        return tmp;
    }

private:
    // запрещаем копирование ScopedPtr
    ScopedPtr(const ScopedPtr &);

    ScopedPtr &operator=(const ScopedPtr &);

    Expression *ptr_;
};

struct SharedPtr {
    explicit SharedPtr(Expression *ptr = 0) : ptr_(ptr), c_(0) {
        if (ptr_ != 0) {
            c_ = new size_t(1);
        }
    }

    //Copy constructor
    SharedPtr(const SharedPtr &ptr) {
        if (ptr.ptr_ != 0) {
            this->ptr_ = ptr.ptr_;
            this->c_ = ptr.c_;
            ++(*c_);
        }
    }

    //Assignment operator
    SharedPtr &operator=(const SharedPtr &ptr) {
        if (ptr_ == 0 && ptr.ptr_ == 0) {
            return *this;
        }

        if (this == &ptr) {
            return *this;
        }

        remove();
        ptr_ = ptr.ptr_;
        c_ = ptr.c_;

        if (c_!= 0) {
            ++(*c_);
        }

        return *this;
    }

    ~SharedPtr() {
        remove();
    }

    void reset(Expression *ptr = 0) {
        if (ptr_ == 0 && ptr == 0) {
            return;
        }

        remove();
        ptr_ = ptr;

        if (ptr == 0) {
            c_ = 0;
            return;
        }

        c_ = new size_t(1);
    }

    Expression *get() const {
        return ptr_;
    }

    void remove() {
        if (c_ == 0 || *c_ == 0) {
            return;
        }

        --(*c_);
        if (*c_ == 0) {
            delete ptr_;
            delete c_;
            ptr_ = 0;
            c_ = 0;
        }
    }

    Expression &operator*() const {
        return *ptr_;
    }

    Expression *operator->() const {
        return ptr_;
    }

    Expression *ptr_;
    size_t *c_;
};

int test789(SharedPtr sp) {
    sp.printC();
    return 1;
}

int main() {
    Expression *sube = new BinaryOperation(new Number(4.5), '*', new Number(5));
    Expression *expr = new BinaryOperation(new Number(3), '+', sube);

    SharedPtr sp(sube);
    sp.printC();

    test789(sp);
    sp.reset(0);

    sp.printC();
//    test789(sp2);
}
