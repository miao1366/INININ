/*
在父类的构造函数中调用虚函数是不能够实现多态的，这个问题涉及到vptr指针的初始化问题。
比如在构造子类对象c时，执行到父类的构造函数时，这个c.vptr指向的是父类的虚函数表，这时调用虚函数，执行的是父类的虚函数，不是多态。
当执行完父类的构造函数，执行到子类的构造函数时，这个c.vptr指针这时才指向本身自己的虚函数表。注意，每一个对象都有一个vptr指针和一个虚函数表，
这个是在编译时就提前布局了，而不是在运行时


总结：虚函数表是针对类的，一个类的所有对象的虚函数表都一样


*/

#include <iostream>
class A {
public:  
    A() {
        std::cout << "A is created"  << std::endl;
        std::cout << this << std::endl;
        Print();
    }
    virtual ~A() {
        Print();
        std::cout << "A is deleted"  << std::endl;
    }

    virtual void Print() {
        std::cout << "A:: Print()."  << std::endl;
    }
};

class B : public A {
public:  
    B() {
        std::cout << "B is created"  << std::endl;
        std::cout << this << std::endl;
        Print();
    }
    ~B() {
        std::cout << "B is deleted"  << std::endl;
    }
    virtual void Print() {
        std::cout << "B:: Print()."  << std::endl;
    }
};

int main(void) {
   A* a = new B();
   delete a;
   return 0;
}