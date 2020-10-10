#include <iostream>
class A {
public:  
    A() {
        std::cout << "A is created"  <<std::endl;
        Print();
    }
    ~A() {
        std::cout << "A is deleted"  <<std::endl;
    }

    virtual void Print() {
        std::cout << "A:: Print()."  <<std::endl;
    }
};

class B : public A {
public:  
    B() {
        std::cout << "B is created"  <<std::endl;
        Print();
    }
    ~B() {
        std::cout << "B is deleted"  <<std::endl;
    }
    virtual void Print() {
        std::cout << "B:: Print()."  <<std::endl;
    }
};

int main(void) {
   A* a = new B();
   delete a;
   return 0;
}