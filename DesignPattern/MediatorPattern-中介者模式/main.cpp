/* 
https://blog.csdn.net/CoderAldrich/article/details/83183587

与外观模式的区别

我在看中介者模式时，第一眼就感觉中介者模式和外观模式超级像。外观模式与中介者模式的不同之处在于它是对一个对象子系统进行抽象，
从而提供了一个更为方便的接口；外观模式的协议是单向的，即外观模式向子系统提出请求，但反过来则不行；而对于中介者模式，是进行多个对象之间的协作，通信是多向的。

*/



#include <iostream>
using namespace std;
 
#define SAFE_DELETE(p) if (p) { delete p; p = NULL; }
 
class Mediator;
 
class Colleague
{
public:
     Colleague(Mediator *pMediator) : m_pMediator(pMediator){}
 
     virtual void Send(wchar_t *message) = 0;
 
protected:
     Mediator *m_pMediator;
};
 
class ConcreteColleague1 : public Colleague
{
public:
     ConcreteColleague1(Mediator *pMediator) : Colleague(pMediator){}
 
     void Send(wchar_t *message);
 
     void Notify(wchar_t *message)
     {
          wcout<<message<<endl;
     }
};
 
class ConcreteColleague2 : public Colleague
{
public:
     ConcreteColleague2(Mediator *pMediator) : Colleague(pMediator){}
 
     void Send(wchar_t *message);
 
     void Notify(wchar_t *message)
     {
          cout<<"ConcreteColleague2 is handling the message."<<endl;
          wcout<<message<<endl;
     }
};
 
class Mediator
{
public:
     virtual void Sent(wchar_t *message, Colleague *pColleague) = 0;
};
 
class ConcreteMediator : public Mediator
{
public:
     // The mediator forward the message
     void Sent(wchar_t *message, Colleague *pColleague)
     {
          ConcreteColleague1 *pConcreteColleague1 = dynamic_cast<ConcreteColleague1 *>(pColleague);
          if (pConcreteColleague1)
          {
               cout<<"The message is from ConcreteColleague1. Now mediator forward it to ConcreteColleague2"<<endl;
               if (m_pColleague2)
               {
                    m_pColleague2->Notify(message);
               }
          }
          else
          {
               if (m_pColleague1)
               {
                    m_pColleague1->Notify(message);
               }
          }
     }
 
     void SetColleague1(Colleague *pColleague)
     {
          m_pColleague1 = dynamic_cast<ConcreteColleague1 *>(pColleague);
     }
 
     void SetColleague2(Colleague *pColleague)
     {
          m_pColleague2 = dynamic_cast<ConcreteColleague2 *>(pColleague);
     }
 
private:
     // The Mediator knows all the Colleague
     ConcreteColleague1 *m_pColleague1;
     ConcreteColleague2 *m_pColleague2;
};
 
void ConcreteColleague1::Send(wchar_t *message)
{
     // The second parameter mark where the message comes from
     m_pMediator->Sent(message, this);
}
 
void ConcreteColleague2::Send(wchar_t *message)
{
     m_pMediator->Sent(message, this);
}
 
int main()
{
     // Create the mediator
     Mediator *pMediator = new ConcreteMediator();
 
     Colleague *pColleague1 = new ConcreteColleague1(pMediator);
     Colleague *pColleague2 = new ConcreteColleague2(pMediator);
 
     ConcreteMediator *pConcreteMediator = dynamic_cast<ConcreteMediator *>(pMediator);
     pConcreteMediator->SetColleague1(pColleague1);
     pConcreteMediator->SetColleague2(pColleague2);
 
     wchar_t message[260] = L"Where are you from?";
     pColleague1->Send(message);
 
     return 0;
}