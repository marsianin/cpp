#include <iostream>

struct Expression
{
    virtual double evaluate() const = 0;
};

struct Number : Expression
{
    Number(double value)
        : value(value)
    {}
    
    double evaluate() const{
        return value;
    } 

private:
    double value;
};

struct BinaryOperation : Expression
{
    BinaryOperation(Expression const * left, char op, Expression const * right)
        : left(left), op(op), right(right)
    { }
    double evaluate() const {
        if (op == '+') {
		return left->evaluate()+right->evaluate();
	}
        if (op == '-') {
                return left->evaluate()-right->evaluate();
        }
        if (op == '*') {
                return left->evaluate()*right->evaluate();
        }
        if (op == '/') {
                return left->evaluate()/right->evaluate();
        }
    }
    ~BinaryOperation(){
        delete left;
        delete right;
    }
private:
    Expression const * left;
    Expression const * right;
    char op;
};

bool instanceOf(Expression const *left, Expression const *right)
{
    int* vptrLeft =  *(int**)left;
    int* vptrRight =  *(int**)right;    
    return vptrLeft == vptrRight;

    // put your code here
}


int main(){
    Expression * sube = new BinaryOperation(new Number(4.5), '*', new Number(5));
    Expression * expr = new BinaryOperation(new Number(3), '+', sube);
    std::cout << expr->evaluate() << std::endl;
   
    std::cout << (instanceOf(sube, new Number(3)) ? "Yes" : "No") << std::endl;    

    delete expr;
}
