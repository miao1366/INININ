/*

  https://blog.csdn.net/CoderAldrich/article/details/83114648
  适用场合
    工厂方法模式的意义是定义一个创建产品对象的工厂接口，将实际创建工作推迟到子类当中。核心工厂类不再负责产品的创建，这样核心类成为一个抽象工厂角色，
    仅负责具体工厂子类必须实现的接口，这样进一步抽象化的好处是使得工厂方法模式可以使系统在不修改具体工厂角色的情况下引进新的产品。

   1.  在设计的初期，就考虑到产品在后期会进行扩展的情况下，可以使用工厂方法模式；
       产品结构较复杂的情况下，可以使用工厂方法模式；
   2.  由于使用设计模式是在详细设计时，就需要进行定夺的，所以，需要权衡多方面的因素，而不能为了使用设计模式而使用设计模式。

*/

#include <iostream>
using namespace std;
 
class Product
{
public:
    virtual void Show() = 0;
};
 
class ProductA : public Product
{
public:
    void Show()
    {
        cout<< "I'm ProductA"<<endl;
    }
};
 
class ProductB : public Product
{
public:
    void Show()
    {
        cout<< "I'm ProductB"<<endl;
    }
};
 
class Factory
{
public:
    virtual Product *CreateProduct() = 0;
};
 
class FactoryA : public Factory
{
public:
    Product *CreateProduct()
    {
        return new ProductA ();
    }
};
 
class FactoryB : public Factory
{
public:
    Product *CreateProduct()
    {
        return new ProductB ();
    }
};
 
int main(int argc , char *argv [])
{
    Factory *factoryA = new FactoryA ();
    Product *productA = factoryA->CreateProduct();
    productA->Show();
 
    Factory *factoryB = new FactoryB ();
    Product *productB = factoryB->CreateProduct();
    productB->Show();
 
    if (factoryA != NULL)
    {
        delete factoryA;
        factoryA = NULL;
    }
 
    if (productA != NULL)
    {
        delete productA;
        productA = NULL;
    }
 
    if (factoryB != NULL)
    {
        delete factoryB;
        factoryB = NULL;
    }
 
    if (productB != NULL)
    {
        delete productB;
        productB = NULL;
    }
    return 0;
}