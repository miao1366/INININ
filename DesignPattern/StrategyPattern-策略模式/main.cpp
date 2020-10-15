/*
https://blog.csdn.net/CoderAldrich/article/details/83270248

当存在以下情况时使用Strategy模式：
许多相关的类仅仅是行为有异。“策略”提供了一种用多个行为中的一个行为来配置一个类的方法；
需要使用一个算法的不同变体；
算法使用客户不应该知道的数据。可使用策略模式以避免暴露复杂的、与算法相关的数据结构；
一个类定义了多种行为，并且这些行为在这个类的操作中以多个条件语句的形式出现。将相关的条件分支移入它们各自的Strategy类中以替代这些条件语句。（是不是和状态模式有点一样哦？）

*/

#include <iostream>
using namespace std;
 
// The abstract strategy
class Strategy
{
public:
     virtual void AlgorithmInterface() = 0;
};
 
class ConcreteStrategyA : public Strategy
{
public:
     void AlgorithmInterface()
     {
          cout<<"I am from ConcreteStrategyA."<<endl;
     }
};
 
class ConcreteStrategyB : public Strategy
{
public:
     void AlgorithmInterface()
     {
          cout<<"I am from ConcreteStrategyB."<<endl;
     }
};
 
class ConcreteStrategyC : public Strategy
{
public:
     void AlgorithmInterface()
     {
          cout<<"I am from ConcreteStrategyC."<<endl;
     }
};
 
class Context
{
public:
     Context(Strategy *pStrategyArg) : pStrategy(pStrategyArg)
     {
     }
     void ContextInterface()
     {
          pStrategy->AlgorithmInterface();
     }
private:
     Strategy *pStrategy;
};
 
int main()
{
     // Create the Strategy
     Strategy *pStrategyA = new ConcreteStrategyA;
     Strategy *pStrategyB = new ConcreteStrategyB;
     Strategy *pStrategyC = new ConcreteStrategyC;
     Context *pContextA = new Context(pStrategyA);
     Context *pContextB = new Context(pStrategyB);
     Context *pContextC = new Context(pStrategyC);
     pContextA->ContextInterface();
     pContextB->ContextInterface();
     pContextC->ContextInterface();
 
     if (pStrategyA) delete pStrategyA;
     if (pStrategyB) delete pStrategyB;
     if (pStrategyC) delete pStrategyC;
 
     if (pContextA) delete pContextA;
     if (pContextB) delete pContextB;
     if (pContextC) delete pContextC;
}