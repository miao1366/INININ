1. c++ user group
2. 腾讯TEG和Modern C++开源社区purecpp

3. https://blog.csdn.net/jeffasd/article/details/84667090        enable_if

    template <bool, typename T=void>
        struct enable_if {
    };
 
    template <typename T>
        struct enable_if<true, T> {
        using type = T;
    };
    由上可知，只有当第一个模板参数为 true 时，type 才有定义，否则使用 type 会产生编译错误，并且默认模板参数可以让你不必指定类型.
    下面说说它的几种使用方法：

    用法一：类型偏特化
        在使用模板编程时，经常会用到根据模板参数的某些特性进行不同类型的选择，或者在编译时校验模板参数的某些特性。例如：
        template <typename T, typename Enable=void>
        struct check;

        template <typename T>
        struct check<T, typename std::enable_if<T::value>::type> {
          static constexpr bool value = T::value;
        };
        上述的 check 只希望选择 value==true 的 T，否则就报编译时错误。如果想给用户更友好的提示，可以提供结构体的原型定义，并在其中进行 static_assert 的静态检查，给出更明确的字符串说明

    用法二：控制函数返回类型
        对于模板函数，有时希望根据不同的模板参数返回不同类型的值，进而给函数模板也赋予类型模板特化的性质。典型的例子可以参看 tuple 的获取第 k 个元素的 get 函数：
        template <std::size_t k, class T, class... Ts>
        typename std::enable_if<k==0, typename element_type_holder<0, T, Ts...>::type&>::type
        get(tuple<T, Ts...> &t) {
          return t.tail; 
        }

        template <std::size_t k, class T, class... Ts>
        typename std::enable_if<k!=0, typename element_type_holder<k, T, Ts...>::type&>::type
        get(tuple<T, Ts...> &t) {
          tuple<Ts...> &base = t;
          return get<k-1>(base); 
        }
        由于函数模板不能偏特化，通过 enable_if 便可以根据 k 值的不同情况选择调用哪个 get，进而实现函数模板的多态。

    用法三：校验函数模板参数类型
        有时定义的模板函数，只希望特定的类型可以调用，参考 cppreference 官网示例，很好的说明了如何限制只有整型可以调用的函数定义：
        
        template <typename T>
        typename std::enable_if<std::is_integral<T>::value, bool>::type
        is_odd(T t) {
          return bool(t%2);
        }
        
        template <typename T, typename = typename std::enable_if<std::is_integral<T>::value>::type>
        bool is_even(T t) {
          return !is_odd(t); 
        }
        一个通过返回值，一个通过默认模板参数，都可以实现校验模板参数是整型的功能。

4. constexpr
对于修饰Object来说，
const并未区分出编译期常量和运行期常量
constexpr限定在了编译期常量

5.  integral_constant
    这个类是所有traits类的基类，分别提供了以下功能：
    value_type 表示值的类型
    value表示值
    type 表示自己, 因此可以用::type::value来获取值

    template<typename _Tp, _Tp __v>
    struct integral_constant {
      static constexpr _Tp                  value = __v;
      typedef _Tp                           value_type;
      typedef integral_constant<_Tp, __v>   type;
      constexpr operator value_type() const noexcept { return value; }
    };

    /// is_enum
    template<typename _Tp>
    struct is_enum
    : public integral_constant<bool, __is_enum(_Tp)>
    { };

    /// is_union
    template<typename _Tp>
    struct is_union
    : public integral_constant<bool, __is_union(_Tp)>
    { };

    /// is_class
    template<typename _Tp>
    struct is_class
    : public integral_constant<bool, __is_class(_Tp)>
    { };

6. std::is_pod
当一个数据类型满足了”平凡的定义“和”标准布局“，我们则认为它是一个POD数据，非静态成员都是”平凡的“
1.平凡的
2.平凡的
3.非静态成员“平凡的”
#include <iostream>
#include <type_traits>
struct A {
    int m;
};
struct B {
    int m1;
private:
    int m2;
};
struct C {
    virtual void foo();
};
int main() {
    std::cout << std::boolalpha;
    std::cout << std::is_pod<A>::value << '\n';
    std::cout << std::is_pod<B>::value << '\n';
    std::cout << std::is_pod<C>::value << '\n';
}
输出：
true
false
false

7. POD类型
上一篇：《深入理解C++11》笔记–列表初始化
本编继续介绍第三章的内容：POD类型，plain old data。Plain代表数据是普通类型，old代表能与C兼容支持memcpy、memset等函数。POD分为两个部分，trivial(平凡的)和(s’tan’dard layout)标准布局的，必须同时满足才是POD类型。
平凡的类或结构体必须满足以下的条件：
- 平凡的默认构造函数和析构函数。只要是自己定义了函数，即使实现为空，也不再平凡。所以就是说不能自定义默认构造函数和析构函数。
- 平凡的拷贝构造函数和移动构造函数。
- 平凡的赋值构造函数。
- 不能包含虚函数和虚基类。
另外，可以用std::is_trivial来判断是不是一个平凡类型，std::is_trivial<T>::value，
class TrivialA {
};
class TrivialB {
public :
    int a;
};
class TrivialC {
    TrivialC() {}                   // 有默认构造函数，不平凡
};
class TrivialD {
    TrivialD(const TrivialD& a) {}   // 有赋值构造函数，不平凡
};
class TrivialE {
    TrivialE(TrivalE&& a) {}        // 有移动构造函数，不平凡
};
class TrivialF {
    TrivialF& operator=(const TrivialF& a) {}   // 有赋值构造函数，不平凡
};
class TrivialG {
    virtual void func() = 0;                  // 有虚函数，不平凡
};
class TrivialH: virtual public TrivialA {               // 有虚基类，不平凡
};

int main(int argc, char **argv)
{
    std::cout << std::is_trivial<TrivialA>::value << std::endl;     // 1
    std::cout << std::is_trivial<TrivialB>::value << std::endl;     // 1
    std::cout << std::is_trivial<TrivialC>::value << std::endl;     // 从这里开始都是0
    std::cout << std::is_trivial<TrivialD>::value << std::endl;
    std::cout << std::is_trivial<TrivialE>::value << std::endl;
    std::cout << std::is_trivial<TrivialF>::value << std::endl;
    std::cout << std::is_trivial<TrivialG>::value << std::endl;
    std::cout << std::is_trivial<TrivialH>::value << std::endl;

    return 0;
}
标准布局的类或结构体必须满足以下的条件：

所有非静态成员有相同的访问权限。
在类或结构体继承时满足以下两个条件之一：
1、派生类中有非静态成员，且只有仅包含静态成员的基类。
2、基类有非静态成员，而派生类没有非静态成员。
其实就是派生类和基类中不允许同时出现非静态成员，因为同时有非静态成员就无法进行memcpy
类中第一个非静态成员的类型与基类不同。
C++标准允许，在基类没有成员时，派生类第一个成员与基类共享地址。但是当派生类中第一个数据成员类型为基类类型时，有趣的问题就来了。首先，这时派生类的内存布局包括基类部分的内存布局，同时自己又添加了另外一个基类类型的变量，如果编译器优化实现第一个成员和基类部分共享地址，那么就违背了C++标准的另一个要求，同类型的不同对象地址必须不同。
没有虚函数和虚基类。
所有非静态成员均符合标准布局，其基类也符合标准布局。
另外，可以用std::is_standard_layout来判断是不是一个标准布局，std::is_standard_layout<T>::value，例如：

class StdLayoutA {
};
class StdLayoutB {
public :
    int a;
    int b;
};
class StdLayoutC : public StdLayoutA {
public:
    int a;
    int b;
    void fun() {}
};
class StdLayoutD : public StdLayoutA  {
public:
    int a;
    StdLayoutA sla;
};
class StdLayoutE : public StdLayoutA , public StdLayoutC {
};
class StdLayoutF {
public:
    static int a;
};
class StdLayoutG : public StdLayoutF {
public:
    int a;
};
class StdLayoutH: public StdLayoutA {   // 第一个非静态成员是基类，所以不标准，如果sla的位置和b交换，那么是标准的
public:
    StdLayoutA sla;
    int b;
};
class StdLayoutI : public StdLayoutB {   // 基类和派生类都有非静态变量，所以不标准，如果基类或者派生类中只有静态变量，那么是标准的
public:
    int a;
};
class StdLayoutJ: public StdLayoutI {    // 基类不标准，所以不标准，如果StdLayoutI标准，那么是标准的
};
class StdLayoutK{    // 非静态成员权限不同，所以不标准，如果a或b有一个是静态，那么是标准的
public:
    int a;
private:
    int b;
};

int main(int argc, char **argv)
{
    std::cout << std::is_standard_layout<StdLayoutA>::value << std::endl;
    std::cout << std::is_standard_layout<StdLayoutB>::value << std::endl;
    std::cout << std::is_standard_layout<StdLayoutC>::value << std::endl;
    std::cout << std::is_standard_layout<StdLayoutD>::value << std::endl;
    std::cout << std::is_standard_layout<StdLayoutE>::value << std::endl;
    std::cout << std::is_standard_layout<StdLayoutF>::value << std::endl;
    std::cout << std::is_standard_layout<StdLayoutG>::value << std::endl;
    std::cout << std::is_standard_layout<StdLayoutH>::value << std::endl;   // 以上都是1，从这里开始都是0
    std::cout << std::is_standard_layout<StdLayoutI>::value << std::endl;
    std::cout << std::is_standard_layout<StdLayoutJ>::value << std::endl;
    std::cout << std::is_standard_layout<StdLayoutK>::value << std::endl;

    return 0;
}

针对POD类型也有模板类：std::is_pod<T>::value。了解了POD类型的要求，再来解释POD类型的好处：

字节赋值，可以使用memset和memcpy。
兼容C语言的内存布局
保证静态初始化安全有效

8.  迭代器
    输入迭代器input_iterator： 只读，且只能一次读操作，支持操作：++p,p++,!=,==,=*p,p->；
    输出迭代器output_iterator： 只写，且只能一次写操作，支持操作：++p,p++；
    正向迭代器forward_iterator： 可多次读写，支持输入输出迭代器的所有操作；
    双向迭代器bidirectional_iterator： 支持正向迭代器的所有操作，且支持操作：--p,--p；
    随机访问迭代器random_access_iterator： 除了支持双向迭代器操作外，还支持：p[n],p+n,
    n+p,p-n,p+=n,p-=n,p1-p2,p1<p2,p1>p2,p1>=p2,p1<=p2；

        /*五中迭代器类型*/  https://blog.csdn.net/qq_34777600/article/details/80427463
    struct input_iterator_tag {};  
    struct output_iterator_tag {};  
    struct forward_iterator_tag : public input_iterator_tag {};  
    struct bidirectional_iterator_tag : public forward_iterator_tag {};  
    struct random_access_iterator_tag : public bidirectional_iterator_tag {};  

9.  原来在C++语言中的确规定了空结构体和空类所占内存大小为1，而C语言中空类和空结构体占用的大小是0（在gcc中测试为0，其他编译器不一定）。
    原来，C++语言标准中规定了这样一个原则：“no object shall have the same address in memory as any other variable”，即任何不同的对象不能拥有相同的内存地址。如果空类对象大小为0，那么此类数组中的各个对象的地址将会一致，明显违反了此原则。

10. 显示调用主动调用析构函数

11. const_cast 简单地说, 修改const对象会导致未定义的行为. 因此上述代码中, 无论出现什么结果, 都是'未定义行为'的一种. 只不过刚好一个成功一个失败

12. new 

class Element {
public:
    Element(/* args */):a(0),b(0){}
    ~Element(){}
    int a;
    int b;
};
class Bucket {
public:
    Bucket() {
        new (element_space) Element();
    }
    Element& element() {
        void* spaces = element_space; // Suppress strict-aliasing
        return *reinterpret_cast<Element*>(spaces);
    }
private:
    char element_space[sizeof(Element)];
};

int main(void) {
    Bucket b;
    b.element().a = 1;
    return 0;
}

13.     std::string* temp_string = (std::string*)temp->buf;
        temp_string->~basic_string();

14.  <cdefs.h>
#ifdef	__cplusplus
# define __BEGIN_DECLS	extern "C" {
# define __END_DECLS	}
#else
# define __BEGIN_DECLS
# define __END_DECLS
#endif

15. GCC 原子操作中 Acquire/Release/Consume/Relaxed 内存模型

16. c++函数重载可以重载 int int64_t char等等多种重载。  void *也能重载。

17. 区域锁(Scoped locking) std::lock_guard<std::mutex> lck(mtx);
    RAII(Resource Acquisition Is Initialization)翻译成中文叫“资源获取即初始化”

18. 函数模板
#include <iostream>
using namespace std;
template <typename T1, typename T2, typename T3>
T1 add(T2 a, T3 b) {
    T1 ret;
    ret = static_cast<T1>(a + b);
    return ret; 
}
void main() {
    int c = 12;
    float d = 23.4;
    //cout << add(c, d) << endl;	//error，无法自动推导函数返回值
    cout << add<float>(c, d) << endl;	//返回值在第一个类型参数中指定
    cout << add<int, int, float>(c, d) << endl;
    system("pause");
}

19. std::remove_reference    std::boolalpha    //引用移除
#include <iostream> // std::cout
#include <type_traits> // std::is_same
template<class T1, class T2>
void print_is_same() {
    std::cout << std::is_same<T1, T2>() << '\n';
}
int main() {
  std::cout << std::boolalpha;
  print_is_same<int, int>();
  print_is_same<int, int &>();
  print_is_same<int, int &&>();
  print_is_same<int, std::remove_reference<int>::type>();
  print_is_same<int, std::remove_reference<int &>::type>();
  print_is_same<int, std::remove_reference<int &&>::type>();
}
Output:
true false false true true true
引用折叠规则
  A& & 折叠成 A&
  A& && 折叠成 A&
  A&& & 折叠成 A&
  A&& && 折叠成 A&&

20. 这里有个有意思的地方，就是如果T是POD类型，new T()和 new T是不同的，例如，new int()和 new int 是不同的，前者值是0，后者未初始化

21. unique_lock是个类模板，工作中，一般lock_guard(推荐使用)；lock_guard取代了mutex的lock()和unlock();
    unique_lock比lock_guard灵活很多，效率上差一点，内存占用多一点

22. 
    通配符是一种特殊语句，主要有星号(*)和问号(?)，用来模糊搜索文件。当查找文件夹时，可以使用它来代替一个或多个真正字符；当不知道真正字符或者懒得输入完整名字时，
    常常使用通配符代替一个或多个真正的字符。 实际上用“*Not?pad”可以对应Notepad\MyNotepad【*可以代表任何字符串；?仅代表单个字符串，但此单字必须存在】

23. std::ifstream
    C++对文件操作相关：
    ifs.is_open()         判断文件是否打开
    ifs.get()             获取文件的一个字符
    ifs.good()            判断文件是否结束
    std::ifstream::in     以只读的方式打开

24. 