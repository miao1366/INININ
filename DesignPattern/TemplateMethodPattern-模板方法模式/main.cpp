/*
https://blog.csdn.net/CoderAldrich/article/details/83270337

定义一个操作中的算法的骨架，而将一些步骤延迟到子类中。Template Method 使得子类可以不改变一个算法的结构即可重定义该算法的某些特定步骤


*/

#include <iostream>
using namespace std;
 
class AbstractClass
{
public:
     void TemplateMethod()
     {
          PrimitiveOperation1();
          cout<<"TemplateMethod"<<endl;
          PrimitiveOperation2();
     }
 
protected:
     virtual void PrimitiveOperation1()
     {
          cout<<"Default Operation1"<<endl;
     }
 
     virtual void PrimitiveOperation2()
     {
          cout<<"Default Operation2"<<endl;
     }
};
 
class ConcreteClassA : public AbstractClass
{
protected:
          virtual void PrimitiveOperation1()
     {
          cout<<"ConcreteA Operation1"<<endl;
     }
 
     virtual void PrimitiveOperation2()
     {
          cout<<"ConcreteA Operation2"<<endl;
     }
};
 
class ConcreteClassB : public AbstractClass
{
protected:
          virtual void PrimitiveOperation1()
     {
          cout<<"ConcreteB Operation1"<<endl;
     }
 
     virtual void PrimitiveOperation2()
     {
          cout<<"ConcreteB Operation2"<<endl;
     }
};
 
int main()
{
     AbstractClass *pAbstractA = new ConcreteClassA;
     pAbstractA->TemplateMethod();
 
     AbstractClass *pAbstractB = new ConcreteClassB;
     pAbstractB->TemplateMethod();
 
     if (pAbstractA) delete pAbstractA;
     if (pAbstractB) delete pAbstractB;
}

