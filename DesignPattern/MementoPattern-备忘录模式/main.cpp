/*

https://blog.csdn.net/CoderAldrich/article/details/83183650

在以下情况下使用备忘录模式：
1. 必须保存一个对象在某一个时刻的部分或完整状态，这样以后需要时它才能恢复到先前的状态；
2. 如果一个用接口来让其它对象直接得到这些状态，将会暴露对象的实现细节并破坏对象的封装性

*/

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class STMemento
{
private:
        int iVitality;
public:
        STMemento(){}
        STMemento(int iVitality)
        {
                this->iVitality = iVitality;
        }

        int GetVitality() const
        {
                return this->iVitality;
        }
};

class STOriginator
{
private:
        int iVitality;
        string name;
public:
        STOriginator(string strName, int iVit): iVitality(iVit), name(strName)
        {

        }

        STMemento* SaveState()
        {
                return new STMemento(iVitality);
        }

        void RecoverState(const STMemento* stMemento)
        {
                this->iVitality = stMemento->GetVitality();
        }

        void SetVitality(int iVit)
        {
                this->iVitality = iVit;
        }

        void Show()
        {
                cout<< "Name: "<< name<< endl;
                cout<< "Live: "<< iVitality<< endl;
        }
};

class STCareTaker
{
private:
        vector<STMemento*> vecStMemento;

public:
        void AddMemento(STMemento* stMemento)
        {
                vecStMemento.push_back(stMemento);
        }

        STMemento* GetMemento(int Iindex)
        {
                if (Iindex >= vecStMemento.size())
                        return NULL;
                else
                        return vecStMemento[Iindex];
        }
};

int main(int argc, char* argv[])
{
        STOriginator* pstOriginator = new STOriginator("xxx", 100);
        cout<< "原始状态： "<< endl;
        pstOriginator->Show();

        STCareTaker* pstCareTaker = new STCareTaker();
        pstCareTaker->AddMemento(pstOriginator->SaveState());

        pstOriginator->SetVitality(50);
        cout<< "战斗后状态： "<< endl;
        pstOriginator->Show();

        pstOriginator->RecoverState(pstCareTaker->GetMemento(0));
        cout<< "归档后状态： "<< endl;
        pstOriginator->Show();

        return 0;
}
