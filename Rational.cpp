#include <iostream>

struct Rational {
    Rational(int numerator = 0, int denominator = 1) : numerator_(numerator), denominator_(denominator) {};

    void add(Rational rational) {
        numerator_ = numerator_ * rational.denominator_ + rational.numerator_ * denominator_;
        denominator_ *= rational.denominator_;
    }

    void sub(Rational rational) {
        numerator_ = numerator_ * rational.denominator_ - rational.numerator_ * denominator_;
        denominator_ *= rational.denominator_;
    }

    void mul(Rational rational) {
        numerator_ *= rational.numerator_;
        denominator_ *= rational.denominator_;
    }

    void div(Rational rational) {
        numerator_ *= rational.denominator_;
        denominator_ *= rational.numerator_;
    }

    void neg() {
        numerator_ = -numerator_;
    }

    void inv() {}

    double to_double() const {
        return numerator_ / (double) denominator_;
    }

    Rational & operator += (int i){
        numerator_ += i*denominator_;
        return *this;
    }

    Rational & operator += (const Rational & r){
        this->add(r);
        return *this;
    }

    Rational & operator -= (int i){
        numerator_ -= i*denominator_;
        return *this;
    }

    Rational & operator -= (const Rational & r){
        this->sub(r);
        return *this;
    }

    Rational & operator *= (int i){
        numerator_ = i*numerator_;
        return *this;
    }

    Rational & operator *= (const Rational & r){
        this->mul(r);
        return *this;
    }

    Rational & operator /= (int i){
        denominator_ = i*denominator_;
        return *this;
    }

    Rational & operator /= (const Rational & r){
        this->div(r);
        return *this;
    }


    Rational operator +(int i) const {
        return Rational(numerator_ + i*denominator_, denominator_);
    }

    Rational operator +(Rational const r) const {
        return Rational(numerator_ * r.denominator_ + r.numerator_ * denominator_, denominator_*r.denominator_);
    }

    Rational operator -(int i) const {
        return Rational(numerator_ - i*denominator_, denominator_);
    }

    Rational operator -(Rational const r) const {
        return Rational(numerator_ * r.denominator_ - r.numerator_ * denominator_, denominator_*r.denominator_);
    }

    Rational operator *(int i) const {
        return Rational(numerator_ * i, denominator_);
    }

    Rational operator *(Rational const r) const {
        return Rational(numerator_ * r.numerator_, denominator_*r.denominator_);
    }

    Rational operator /(int i) const {
        return Rational(numerator_, denominator_ * i);
    }

    Rational operator /(Rational const r) const {
        return Rational(numerator_ * r.denominator_, denominator_*r.numerator_);
    }

private:
    int numerator_;
    int denominator_;
};

/*
 * UNARY operators
 */
Rational const operator - (Rational r){
    r.neg();
    return r;
}

Rational const operator + (Rational r){
    return r;
}

/*
 * BINARY operators
 */
Rational operator +(int i, Rational const r) {
    return r+i;
}

Rational operator -(int i, Rational const r) {
    return -(r-i);
}

Rational operator *(int i, Rational const r) {
    return r*i;
}

Rational operator /(int i, Rational const r) {
    return Rational(i)/r;
}

int main() {
    Rational r1(1, 2);
    Rational r2(1, 3);
    Rational r3(5);
    Rational r5(575);

    r1.add(r2);
    std::cout << r1.to_double() << std::endl;
    r1.sub(r2);
    std::cout << r1.to_double() << std::endl;
    r1.neg();
    std::cout << r1.to_double() << std::endl;
    r3.mul(r1);
    std::cout << r3.to_double() << std::endl;
    r3.div(r2);
    std::cout << r3.to_double() << std::endl;

    +r5;
    std::cout << r5.to_double() << std::endl;

    r3 += r5;
    std::cout << r3.to_double() << std::endl;
}
