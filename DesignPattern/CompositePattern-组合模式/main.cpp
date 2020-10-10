/*
https://blog.csdn.net/CoderAldrich/article/details/83115374

组合模式的优点
    将对象组合成树形结构以表示“部分-整体”的层次结构。组合模式使得用户对单个对象和组合对象的使用具有一致性。

使用场景
   1. 你想表示对象的部分-整体层次结构；
   2. 希望用户忽略组合对象与单个对象的不同，用户将统一地使用组合结构中的所有对象。
   引用大话设计模式的片段：“当发现需求中是体现部分与整体层次结构时，以及你希望用户可以忽略组合对象与单个对象的不同，
   统一地使用组合结构中的所有对象时，就应该考虑组合模式了。”

总结
    通过上面的简单讲解，我们知道了，组合模式意图是通过整体与局部之间的关系，通过树形结构的形式进行组织复杂对象，屏蔽对象内部的细节，
    对外展现统一的方式来操作对象，是我们处理更复杂对象的一个手段和方式。现在再结合上面的代码，想想文章开头提出的公司OA系统如何进行设计

有点类似于qt的类
*/

#include <iostream>
#include <string>
#include <vector>
using namespace std;
// 抽象的部件类描述将来所有部件共有的行为
class Component
{
public:
     Component(string name) : m_strCompname(name){}
     virtual ~Component(){}
     virtual void Operation() = 0;
     virtual void Add(Component *) = 0;
     virtual void Remove(Component *) = 0;
     virtual Component *GetChild(int) = 0;
     virtual string GetName()
     {
          return m_strCompname;
     }
     virtual void Print() = 0;
protected:
     string m_strCompname;
};
class Leaf : public Component
{
public:
     Leaf(string name) : Component(name)
     {}
     void Operation()
     {
          cout<<"I'm "<<m_strCompname<<endl;
     }
     void Add(Component *pComponent){}
     void Remove(Component *pComponent){}
     Component *GetChild(int index)
     {
          return NULL;
     }
     void Print(){}
};
class Composite : public Component
{
public:
     Composite(string name) : Component(name)
     {}
     ~Composite()
     {
          vector<Component *>::iterator it = m_vecComp.begin();
          while (it != m_vecComp.end())
          {
               if (*it != NULL)
               {
                    cout<<"----delete "<<(*it)->GetName()<<"----"<<endl;
                    delete *it;
                    *it = NULL;
               }
               m_vecComp.erase(it);
               it = m_vecComp.begin();
          }
     }
     void Operation()
     {
          cout<<"I'm "<<m_strCompname<<endl;
     }
     void Add(Component *pComponent)
     {
          m_vecComp.push_back(pComponent);
     }
     void Remove(Component *pComponent)
     {
          for (vector<Component *>::iterator it = m_vecComp.begin(); it != m_vecComp.end(); ++it)
          {
               if ((*it)->GetName() == pComponent->GetName())
               {
                    if (*it != NULL)
                    {
                         delete *it;
                         *it = NULL;
                    }
                    m_vecComp.erase(it);
                    break;
               }
          }
     }
     Component *GetChild(int index)
     {
          if (index > m_vecComp.size())
          {
               return NULL;
          }
          return m_vecComp[index - 1];
     }
     void Print()
     {
          for (vector<Component *>::iterator it = m_vecComp.begin(); it != m_vecComp.end(); ++it)
          {
               cout<<(*it)->GetName()<<endl;
          }
     }
private:
     vector<Component *> m_vecComp;
};
int main(int argc, char *argv[])
{
     Component *pNode = new Composite("Beijing Head Office");
     Component *pNodeHr = new Leaf("Beijing Human Resources Department");
     Component *pSubNodeSh = new Composite("Shanghai Branch");
     Component *pSubNodeCd = new Composite("Chengdu Branch");
     Component *pSubNodeBt = new Composite("Baotou Branch");
     pNode->Add(pNodeHr);
     pNode->Add(pSubNodeSh);
     pNode->Add(pSubNodeCd);
     pNode->Add(pSubNodeBt);
     pNode->Print();
     Component *pSubNodeShHr = new Leaf("Shanghai Human Resources Department");
     Component *pSubNodeShCg = new Leaf("Shanghai Purchasing Department");
     Component *pSubNodeShXs = new Leaf("Shanghai Sales department");
     Component *pSubNodeShZb = new Leaf("Shanghai Quality supervision Department");
     pSubNodeSh->Add(pSubNodeShHr);
     pSubNodeSh->Add(pSubNodeShCg);
     pSubNodeSh->Add(pSubNodeShXs);
     pSubNodeSh->Add(pSubNodeShZb);
     pNode->Print();
     // 公司不景气，需要关闭上海质量监督部门
     pSubNodeSh->Remove(pSubNodeShZb);
     if (pNode != NULL)
     {
          delete pNode;
          pNode = NULL;
     }
     return 0;
}