/* 
https://blog.csdn.net/CoderAldrich/article/details/83115299
https://blog.csdn.net/CoderAldrich/article/details/83115394


适配器模式在以下场合下最适用：
1.  使用一个已经存在的类，如果它的接口和你实际要求的不一致时，可以考虑使用适配器模式；
2.  要在调用者和功能提供者双方都不太容易修改的时候再使用适配器模式，而不是一有不同时就使用它

*/

// 类适配器的实现代码
#include <iostream>
using namespace std;
 
// Targets
class Target
{
public:
    virtual void Request()
    {
        cout<<"Target::Request"<<endl;
    }
};
 
// Adaptee
class Adaptee
{
public:
    void SpecificRequest()
    {
        cout<<"Adaptee::SpecificRequest"<<endl;
    }
};
 
// Adapter
class Adapter : public Target, Adaptee
{
public:
    void Request()
    {
        Adaptee::SpecificRequest();
    }
};
 
// Client
int main(int argc, char *argv[])
{
    Target *targetObj = new Adapter();
    targetObj->Request();
 
    delete targetObj;
    targetObj = NULL;
 
    return 0;
}




// ========================================================================

//  对象适配器的代码实现
#include <iostream>
using namespace std;
 
class Target
{
public:
    Target(){}
    virtual ~Target(){}
    virtual void Request()
    {
        cout<<"Target::Request"<<endl;
    }
};
 
class Adaptee
{
public:
    void SpecificRequest()
    {
        cout<<"Adaptee::SpecificRequest"<<endl;
    }
};
 
class Adapter : public Target
{
public:
    Adapter() : m_Adaptee(new Adaptee) {}
 
    ~Adapter()
    {
        if (m_Adaptee != NULL)
        {
            delete m_Adaptee;
            m_Adaptee = NULL;
        }
    }
 
    void Request()
    {
        m_Adaptee->SpecificRequest();
    }
 
private:
    Adaptee *m_Adaptee;
};
 
int main(int argc, char *argv[])
{
    Target *targetObj = new Adapter();
    targetObj->Request();
 
    delete targetObj;
    targetObj = NULL;
 
    return 0;
}