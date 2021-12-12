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
       defer_lock_t     不获得互斥的所有权
       try_to_lock_t    尝试获得互斥的所有权而不阻塞
       adopt_lock_t     假设调用方线程已拥有互斥的所有权

25. namespace std {

// Specialize lock_guard and unique_lock
template <typename Mutex>
class lock_guard<bvar::MutexWithRecorder<Mutex> >
    : public ::bvar::detail::
                LockGuardBase< ::bvar::MutexWithRecorder<Mutex> > {
public:
    typedef ::bvar::detail::
            LockGuardBase<bvar::MutexWithRecorder<Mutex> > Base;
    explicit lock_guard(::bvar::MutexWithRecorder<Mutex> &mutex) 
        : Base(mutex)
    {}
};

26.   try_lock
        上锁操作，调用它所管理的 Mutex 对象的 try_lock 函数，如果上锁成功，则返回 true，否则返回 false
      try_lock_for
      
      try_lock_until

27. std :: fill()
    fill()函数是算法标头的库函数，用于将值分配给容器给定范围内的所有元素，它接受指向容器中开始和结束位置的迭代器以及要分配的值给定范围内的元素，并分配值
    std::fill(iterator start, iterator end, value);

28. atomic<T>提供了常见且容易理解的方法：
    store
    load
    exchange    T exchange (A* obj, T val) noexcept
    exchange 会将 val 指定的值替换掉之前该原子对象封装的值，并返回之前该原子对象封装的值，整个过程是原子的(因此exchange 操作也称为 read-modify-write 操作)

    compare_exchange_weak
    compare_exchange_strong
    store是原子写操作，而load则是对应的原子读操作。
    exchange允许2个数值进行交换，并保证整个过程是原子的。

    1. compare_exchange_weak和compare_exchange_strong则是著名的CAS（compare and set）。参数会要求在这里传入期待的数值和新的数值。
       它们对比变量的值和期待的值是否一致，如果是，则替换为用户指定的一个新的数值。如果不是，则将变量的值和期待的值交换
    2. weak版和strong版的区别：
       weak版本的CAS允许偶然出乎意料的返回（比如在字段值和期待值一样的时候却返回了false），不过在一些循环算法中，这是可以接受的。通常它比起strong有更高的性能

template< class T>
struct atomic<T*>
{
public:
bool compare_exchange_weak( T& expected, T desired,
                            std::memory_order success,
                            std::memory_order failure );
bool compare_exchange_weak( T& expected, T desired,
                            std::memory_order success,
                            std::memory_order failure ) volatile;
bool compare_exchange_weak( T& expected, T desired,
                            std::memory_order order =
                                std::memory_order_seq_cst );
bool compare_exchange_weak( T& expected, T desired,
                            std::memory_order order =
                                std::memory_order_seq_cst ) volatile;
bool compare_exchange_strong( T& expected, T desired,
                              std::memory_order success,
                              std::memory_order failure );
bool compare_exchange_strong( T& expected, T desired,
                              std::memory_order success,
                              std::memory_order failure ) volatile;    
bool compare_exchange_strong( T& expected, T desired,
                              std::memory_order order =
                                  std::memory_order_seq_cst );
bool compare_exchange_strong( T& expected, T desired,
                              std::memory_order order =
                                  std::memory_order_seq_cst ) volatile;
...
}
当前值与期望值(expect)相等时，修改当前值为设定值(desired)，返回true
当前值与期望值(expect)不等时，将期望值(expect)修改为当前值，返回false

29. __cxa_demangle()    //
    C/C++语言在编译以后，函数的名字会被编译器修改，改成编译器内部的名字，这个名字会在链接的时候用到。
    将C++源程序标识符(original C++ source identifier)转换成C++ ABI标识符(C++ ABI identifier)的过程称为mangle；相反的过程称为demangle。

30. typeid

31. 不同编译单元中全局变量的初始化顺序是未定义的

32. multiset<>

33.  template< class ForwardIt >
     ForwardIt next( ForwardIt it, typename std::iterator_traits<ForwardIt>::difference_type n = 1 );
    it  -- 迭代指针
    n   -- 向前进的元素个数，缺省默认为1
Return value
The nth successor of iterator it.（返回it的第n个后继迭代指针）

34. unordered_map: unordered_map内部实现了一个哈希表（也叫散列表，通过把关键码值映射到Hash表中一个位置来访问记录，查找的时间复杂度可达到O(1)
    其在海量数据处理中有着广泛应用）。因此，其元素的排列顺序是无序的。哈希表详细介绍

35. 当一个对象被用作右值的时候，用的是对象的值（内容）；当对象被用作左值的时候，用的是对象的身份（在内存中的位置）。左值有持久的状态，而右值要么是字面常量，
    要么是在表达式求值过程中创建的对象，即左值持久，右值短暂

36. C++ memory order循序渐进
    https://blog.csdn.net/wxj1992/article/details/103649056?spm=1001.2014.3001.5501

37. fetch_add
    描述 (Description) 它自动原子地将参数添加到存储在原子对象中的值，并获得先前保存的值

38. EPOLLONESHOT epoll的总结之四LT和ET使用EPOLLONESHOT
        在前面说过，epoll有两种触发的方式即LT（水平触发）和ET（边缘触发）两种，在前者，只要存在着事件就会不断的触发，直到处理完成，
        而后者只触发一次相同事件或者说只在从非触发到触发两个状态转换的时候儿才触发。
        这会出现下面一种情况，如果是多线程在处理，一个SOCKET事件到来，数据开始解析，这时候这个SOCKET又来了同样一个这样的事件，而你的数据解析尚未完成，
        那么程序会自动调度另外一个线程或者进程来处理新的事件，这造成一个很严重的问题，不同的线程或者进程在处理同一个SOCKET的事件，
        这会使程序的健壮性大降低而编程的复杂度大大增加！！即使在ET模式下也有可能出现这种情况！！
        解决这种现象有两种方法，一种是在单独的线程或进程里解析数据，也就是说，接收数据的线程接收到数据后立刻将数据转移至另外的线程。
        第一种方法
        第二种方法就是本文要提到的EPOLLONESHOT这种方法，可以在epoll上注册这个事件，注册这个事件后，如果在处理写成当前的SOCKET后不再重新注册相关事件，
        那么这个事件就不再响应了或者说触发了。要想重新注册事件则需要调用epoll_ctl重置文件描述符上的事件，
        这样前面的socket就不会出现竞态这样就可以通过手动的方式来保证同一SOCKET只能被一个线程处理，不会跨越多个线程。

        EPOLLONESHOT：只监听一次事件，当监听完这次事件之后，如果还需要继续监听这个socket的话，需要再次把这个socket加入到EPOLL队列里

39. inl.h
    在内联函数较多的情况下，为了避免头文件过长、版面混乱，可以将所有的内联函数定义移到一个单独的文件中去，然后再 用#include指令将它包含到类声明的后面（类的头文件的底部）。
    这样的文件称为一个内联函数定义文件。inl文件中也可以包含头文件的，因为内联函数中可能包含其他文件中定义的东西。按照惯例， 应该将这个文件命名为“filename.inl”，
    其中“filename”与相应的头文件和实现文件相同

40. push_heap    大顶堆
#include <iostream>
#include <algorithm>
#include <vector>
int main() {
    std::vector<int> v { 3, 1, 4, 1, 5, 9 };
    std::make_heap(v.begin(), v.end());
    std::cout << "v: ";
    for (auto i : v) std::cout << i << ' ';
    std::cout << '\n';
    v.push_back(6);
    std::cout << "before push_heap: ";
    for (auto i : v) std::cout << i << ' ';
    std::cout << '\n';
    std::push_heap(v.begin(), v.end());
    std::cout << "after push_heap:  ";
    for (auto i : v) std::cout << i << ' ';
    std::cout << '\n';
}
    Output:
        v: 9 5 4 1 1 3 
        before push_heap: 9 5 4 1 1 3 6 
        after push_heap:  9 5 6 1 1 3 4
push_heap()：把元素添加在底层vector的end()处，然后重新调整堆序
pop_heap() ：把堆顶元素取出来，放到了数组或者是vector的末尾，用原来末尾元素去替代，
            然后end迭代器减1（后常跟vector的pop_back()操作

            将第一个元素与最后一个元素互换之后,再将除最后一个元素重组织成堆

41. make_heap  用于把一个可迭代容器变成一个堆，默认是大顶堆
    pop_heap()用于将堆的第零个元素与最后一个元素交换位置，然后针对前n - 1个元素调用make_heap()函数，它也有三个参数，参数意义与make_heap()相同，第三个参数应与make_heap时的第三个参数保持一致。
    push_heap()用于把数据插入到堆中，它也有三个参数，其意义与make_heap()的相同，第三个参数应与make_heap时的第三个参数保持一致。
            在使用push_heap()前，请确保已经把数据通过q.push_back()传入q中，而不是在push_heap()后再使用q.push_back(t)！

42. fetch_or
    描述 (Description)
    它以原子方式在参数和原子对象的值之间执行按位OR，并获得先前保存的值

43. ctor    构造函数
    dtor    析构函数

44. posix多线程有感--自旋锁
转自：http://www.csdn123.com/html/blogs/20130509/11141.htm
自旋锁是SMP架构中的一种low-level的同步机制。
    当线程A想要获取一把自旋锁而该锁又被其它线程锁持有时，线程A会在一个循环中自旋以检测锁是不是已经可用了。对于自选锁需要注意：
    由于自旋时不释放CPU，因而持有自旋锁的线程应该尽快释放自旋锁，否则等待该自旋锁的线程会一直在那里自旋，这就会浪费CPU时间。
    持有自旋锁的线程在sleep之前应该释放自旋锁以便其它线程可以获得自旋锁。（在内核编程中，如果持有自旋锁的代码sleep了就可能导致整个系统挂起，
    最近刚解决了一个内核中的问题就是由于持有自旋锁时sleep了，然后导致所有的核全部挂起（是一个8核的CPU））
    使用任何锁需要消耗系统资源（内存资源和CPU时间），这种资源消耗可以分为两类：

建立锁所需要的资源
当线程被阻塞时锁所需要的资源
Pthreads提供的与Spin Lock锁操作相关的API主要有：

1）初始化自旋锁
int pthread_spin_init(pthread_spinlock_t *lock int pshared)  
    On success, there functions return zero.  On failure, they return an error numbe
用来申请使用自旋锁所需要的资源并且将它初始化为非锁定状态。pshared的取值及其含义：
PTHREAD_PROCESS_SHARED：该自旋锁可以在多个进程中的线程之间共享。
PTHREAD_PROCESS_PRIVATE：仅初始化本自旋锁的线程所在的进程内的线程才能够使用该自旋锁。

2）获得一个自旋锁 int pthread_spin_lock(pthread_spinlock_t *lock);
    用来获取（锁定）指定的自旋锁. 如果该自旋锁当前没有被其它线程所持有，则调用该函数的线程获得该自旋锁.
    否则该函数在获得自旋锁之前不会返回。如果调用该函数的线程在调用该函数时已经持有了该自旋锁，则结果是不确定的。

3）尝试获取一个自旋锁int pthread_spin_trylock(pthread_spinlock_t *lock);
   会尝试获取指定的自旋锁，如果无法获取则理解返回失败。

4）释放（解锁）一个自旋锁 int pthread_spin_unlock(pthread_spinlock_t *lock)
   用于释放指定的自旋锁。

5）销毁一个自旋锁int int pthread_spin_destroy(pthread_spinlock_t *lock)
pthread_spin_destroy 用来销毁指定的自旋锁并释放所有相关联的资源（所谓的所有指的是由pthread_spin_init自动申请的资源）在调用该函数之后如果没有调用 pthread_spin_init重新初始化自旋锁，则任何尝试使用该锁的调用的结果都是未定义的。如果调用该函数时自旋锁正在被使用或者自旋锁未被初 始化则结果是未定义的。
互斥量和自旋锁的区别：
Pthreads提供的Mutex锁操作相关的API主要有：

从实现原理上来讲，Mutex属于sleep-waiting类型的 锁。例如在一个双核的机器上有两个线程(线程A和线程B)，它们分别运行在Core0和Core1上。
假设线程A想要通过 pthread_mutex_lock操作去得到一个临界区的锁，而此时这个锁正被线程B所持有，那么线程A就会被阻塞(blocking)，
Core0 会在此时进行上下文切换(Context Switch)将线程A置于等待队列中，此时Core0就可以运行其他的任务(例如另一个线程C)而不必进行忙等待。而Spin lock则不然，
它属于busy-waiting类型的锁，如果线程A是使用pthread_spin_lock操作去请求锁，那么线程A就会一直在 Core0上进行忙等待并不停的进行锁请求，直到得到这个锁为止。
如果大家去查阅Linux glibc中对pthreads API的实现NPTL(Native POSIX Thread Library) 
的源码的话(使用”getconf GNU_LIBPTHREAD_VERSION”命令可以得到我们系统中NPTL的版本号)，就会发现pthread_mutex_lock()操作如果 
没有锁成功的话就会调用system_wait()的系统调用并将当前线程加入该mutex的等待队列里。而spin lock则可以理解为在一个while(1)循环中用内嵌的汇编代码实现的锁操作
(印象中看过一篇论文介绍说在linux内核中spin lock操作只需要两条CPU指令，解锁操作只用一条指令就可以完成)。有兴趣的朋友可以参考另一个名为sanos的微内核中pthreds API的实现：mutex.c spinlock.c，尽管与NPTL中的代码实现不尽相同，但是因为它的实现非常简单易懂，对我们理解spin lock和mutex的特性还是很有帮助的。
对于自旋锁来说，它只需要消耗很少的资源来建立锁；随后当线程被阻塞时，它就会一直重复检查看锁是否可用了，也就是说当自旋锁处于等待状态时它会一直消耗CPU时间。
对于互斥锁来说，与自旋锁相比它需要消耗大量的系统资源来建立锁；随后当线程被阻塞时，线程的调度状态被修改，并且线程被加入等待线程队列；最后当锁可用 时
，在获取锁之前，线程会被从等待队列取出并更改其调度状态；但是在线程被阻塞期间，它不消耗CPU资源。
因此自旋锁和互斥锁适用于不同的场景。自旋锁适用于那些仅需要阻塞很短时间的场景，而互斥锁适用于那些可能会阻塞很长时间的场景。

自旋锁与linux内核进程调度关系
　　如果临界区可能包含引起睡眠的代码则不能使用自旋锁，否则可能引起死锁。
　　那么为什么信号量保护的代码可以睡眠而自旋锁就不能呢？
　　先看下自旋锁的实现方法吧，自旋锁的基本形式如下：
　　spin_lock(&mr_lock); 　　//临界区 　　spin_unlock(&mr_lock); 　　跟踪一下spin_lock(&mr_lock)的实现 　　#define spin_lock(lock) _spin_lock(lock) 　　#define _spin_lock(lock) __LOCK(lock) 　　#define __LOCK(lock) \ 　　do { preempt_disable(); __acquire(lock); (void)(lock); } while (0)
        注意到“preempt_disable()”，这个调用的功能是“关抢占”（在spin_unlock中会重新开启抢占功能）。从 中可以看出，使用自旋锁保护的区域是工作在非抢占的状态；即使获取不到锁，在“自旋”状态也是禁止抢占的。了解到这，我想咱们应该能够理解为何自旋锁保护 的代码不能睡眠了。试想一下，如果在自旋锁保护的代码中间睡眠，此时发生进程调度，则可能另外一个进程会再次调用spinlock保护的这段代码。而我们 现在知道了即使在获取不到锁的“自旋”状态，也是禁止抢占的，而“自旋”又是动态的，不会再睡眠了，也就是说在这个处理器上不会再有进程调度发生了，那么 死锁自然就发生了。

　　咱们可以总结下自旋锁的特点：
　　● 单处理器非抢占内核下：自旋锁会在编译时被忽略；
　　● 单处理器抢占内核下：自旋锁仅仅当作一个设置内核抢占的开关；
　　● 多处理器下：此时才能完全发挥出自旋锁的作用，自旋锁在内核中主要用来防止多处理器中并发访问临界区，防止内核抢占造成的竞争。
linux抢占发生的时间
　　最后在了解下linux抢占发生的时间，抢占分为用户抢占和内核抢占。
　　用户抢占在以下情况下产生：
　　● 从系统调用返回用户空间
　　● 从中断处理程序返回用户空间
　　内核抢占会发生在：
　　● 当从中断处理程序返回内核空间的时候，且当时内核具有可抢占性；
　　● 当内核代码再一次具有可抢占性的时候。（如:spin_unlock时）
　　● 如果内核中的任务显式的调用schedule()
　　● 如果内核中的任务阻塞。
　　基本的进程调度就是发生在时钟中断后，并且发现进程的时间片已经使用完了，则发生进程抢占。通常我们会利用中断处理程序返回内核空间的时候可以进行内核抢占这个特性来提高一些I/O操作的实时性，
   如：当I/O事件发生的是时候，对应的中断处理程序被激活，当它发现有进程在等待这个I/O事件的时候，它 会激活等待进程，并且设置当前正在执行进程的need_resched标志，
   这样在中断处理程序返回的时候，调度程序被激活，原来在等待I/O事件的进程 （很可能）获得执行权，从而保证了对I/O事件的相对快速响应（毫秒级）。
   可以看出，在I/O事件发生的时候，I/O事件的处理进程会抢占当前进程，系统 的响应速度与调度时间片的长度无关。

总结：
（1）Mutex适合对锁操作非常频繁的场景，并且具有更好的适应性。尽管相比spin lock它会花费更多的开销（主要是上下文切换），
    但是它能适合实际开发中复杂的应用场景，在保证一定性能的前提下提供更大的灵活度。
（2）spin lock的lock/unlock性能更好(花费更少的cpu指令)，但是它只适应用于临界区运行时间很短的场景。而在实际软件开发中，
    除非程序员对自己的程序的锁操作行为非常的了解，否则使用spin lock不是一个好主意(通常一个多线程程序中对锁的操作有数以万次，
    如果失败的锁操作(contended lock requests)过多的话就会浪费很多的时间进行空等待)。
（3）更保险的方法或许是先（保守的）使用 Mutex，然后如果对性能还有进一步的需求，可以尝试使用spin lock进行调优。毕竟我们的程序不像Linux kernel
     那样对性能需求那么高(Linux Kernel最常用的锁操作是spin lock和rw lock)。

futex 
    futex是一个高效的同步组件，futex由一个内核态的队列和一个用户态的integer构成，有竞争时会放到等待队列供后面唤醒，整个操作主要用到了自旋锁来保护临界区。
    基于futex构造锁到时候一个典型的模式是先通过对一个原子变量进行cas操作尝试直接获取锁，如果没竞争直接返回，有竞争调用futex_wait。
    简单来说，futex主要包括等待和唤醒两个方法：futex_wait和futex_wake，简化后的定义如下
    
    //uaddr指向一个地址，val代表这个地址期待的值，当*uaddr==val时，才会进行wait
    int futex_wait(int *uaddr, int val);
    //唤醒n个在uaddr指向的锁变量上挂起等待的进程
    int futex_wake(int *uaddr, int n);

    1) futex_wait：
        加自旋锁
        检测*uaddr是否等于val，如果不相等则会立即返回
        将进程状态设置为TASK_INTERRUPTIBLE
        将当期进程插入到等待队列中
        释放自旋锁
        创建定时任务：当超过一定时间还没被唤醒时，将进程唤醒
        挂起当前进程
    2) futex_wake：
        找到uaddr对应的futex_hash_bucket
        对其加自旋锁
        遍历f链表，找到uaddr对应的节点
        调用wake_futex唤起等待的进程
        释放自旋锁
    
    butex
    

    我们都知道可以通过/proc/$pid/来获取指定进程的信息，例如内存映射、CPU绑定信息等等。如果某个进程想要获取本进程的系统信息，
    就可以通过进程的pid来访问/proc/$pid/目录。但是这个方法还需要获取进程pid，在fork、daemon等情况下pid还可能发生变化。
    为了更方便的获取本进程的信息，linux提供了/proc/self/目录，这个目录比较独特，不同的进程访问该目录时获得的信息是不同的，
    内容等价于/proc/本进程pid/。进程可以通过访问/proc/self/目录来获取自己的系统信息，而不用每次都获取pid

    定位内存泄漏基本上是从宏观到微观，进而定位到代码位置。
    从/proc/meminfo可以看到整个系统内存消耗情况，使用top可以看到每个进程的VIRT(虚拟内存)和RES(实际占用内存)，基本上就可以将泄漏内存定位到进程范围。
    之前也大概了解过/proc/self/maps，基于里面信息能大概判断泄露的内存的属性，是哪个区域在泄漏、对应哪个文件。辅助工具procmem输出更可读的maps信息。

    procmem 介绍
    procmem：针对每一个进程具体分析就要使用procmem工具了。
    procmem 给出了procrank中VSS、RSS、PSS、USS的每一部分组成，包括进程可执行程序本身、共享库、堆、栈的内存占用。这里的信息应该是从/proc/pid/maps文件中获取的.

    procrank是按照内存占用情况对进程进行排序。因为它需要遍历／proc下的所有进程获取内存占用情况，所以在运行时候需要有root权限。可用排序的有VSS、RSS、PSS、USS。
    VSS：Virtual Set Size，虚拟内存耗用内存，包括共享库的内存
    RSS：Resident Set Size，实际使用物理内存，包括共享库
    PSS：Proportional Set Size，实际使用的物理内存，共享库按比例分配
    USS：Unique Set Size，进程独占的物理内存，不计算共享库，也可以理解为将进程杀死能释放出的内存

    Android系统中提供了两个命令行工具procrank、procmem用于查看系统中的内存使用情况。procrank可以查看系统中所有进程的整体内存占用情况，并按照规则排序。
    而procmem可以针对某个特定的进程分析其堆、栈、共享库等内存占用情况。这两个工具对于我们分析内存相关问题非常有效

    std::unique_ptr 是 c++11中用来取代 std::auto_ptr 指针的指针容器。 它不能与其他unique_ptr类型的指针对象共享所指对象的内存。这种所有权仅能够通过std::move函数来转移。unique_ptr是一个删除了拷贝构造函数、
    保留了移动构造函数的指针封装类型。 调用release 会切断unique_ptr 和它原来管理的对象的联系。release 返回的指针通常被用来初始化另一个智能指针或给另一个智能指针赋值。
    如果不用另一个智能指针来保存release返回的指针，程序就要负责资源的释放。

    std::unique_ptr    release()    移动构造

1. initialization order fiasco
    Static Initialization Order Fiasco (SIOF)
        ：对于一个static变量，不管它是全局的或者是类的成员变量，访问它的时候不一定总是成功的，甚至会造成程序crash，
        因为不能保证它在被访问时已经被初始化了（跟初始化的顺序有关，所以称为初始化顺序的Fiasco）。以下将制造一个非常简单的SIOF情形

        如果不确定在使用时它是否已经被初始化，就要使用函数包装static变量来防止Static Initialization Order FIASCO!

        static initialization order fiasco是对C++的一个非常微妙的并且常见的误解。不幸的是，错误发生在main()开始之前，很难检测到。
        简而言之，假设你有存在于不同的源文件x.cpp 和y.cpp的两个静态对象x 和 y。再假定y对象的构造函数会调用x对象的某些方法。就是这些。就这么简单。
        结局是你完蛋不完蛋的机会是50%-50%。如果碰巧x.cpp的编辑单元先被初始化，这很好。但如果y.cpp的编辑单元先被初始化，然后y的构造函数比x的构造函数先运行。
        也就是说，y的构造函数会调用x对象的方法，而x对象还没有被构造。
        
        注意：static initialization order fiasco不作用于内建的／固有的类型，象int 或 char*。例如，如果创建一个static float对象，不会有静态初始化次序的问题。
        静态初始化次序真正会崩溃的时机只有在你的static或全局对象有构造函数时。

2. code-gen 

3.
struct A {
  A() { ++instances; }
  ~A() { --instances; }
  inline static int instances = 0;
};

但从c++11以后，普通的类的成员变量都可以在类的声明中直接初始化了，而静态成员变量（除const static）外，却仍然延袭老的固有的应用方式，就显得有点土味儿了。
正所谓，有需求，就会有变化，c++17就给它增加了一个关键字inline，实现了同质化的操作

4. 
template<bool B, class T = void>
struct enable_if {}; //此时B为false
 
template<class T>
struct enable_if<true, T> { typedef T type; }; //此时B为true

当 enable_if 的条件为true 时，优先匹配 struct enable_if<true,T> 这个模板，因此会多一个 type 类型， 和T 保持一致。
template< bool B, class T = void >
using enable_if_t = typename enable_if<B,T>::type;

基本原理是SFINAE。只有当第一个参数是true的时候才有type，否则就会发生Substitution Failure，这个时候模版实例化就会失败，也就不会产生任何代码

5. 
头文件：is_convertible

#include<type_traits>
模板类别：

template< class From, class To >
struct is_convertible;

template< class From, class To >
struct is_nothrow_convertible;
用法:

is_convertible <A*, B*>::value;
参数：它采用A和B两种数据类型：

A:它代表要转换的参数。
B:它代表参数A隐式转换的参数。
返回值：

True:如果将给定的数据类型A转换为数据类型B。
False:如果给定的数据类型A没有转换为数据类型B。

下面是演示C++中std::is_convertible的程序：
#include <bits/stdc++.h> 
#include <type_traits> 
using namespace std; 
class A { 
}; 
class B:public A { 
}; 
class C { 
}; 
int main() 
{ 
    cout << boolalpha; 
    bool BtoA = is_convertible<B*, A*>::value; 
    cout << BtoA << endl; 

    bool AtoB = is_convertible<A*, B*>::value; 
    cout << AtoB << endl; 

    bool BtoC = is_convertible<B*, C*>::value; 
    cout << BtoC << endl; 
    cout << "int to float:"<< is_convertible<int, float>::value << endl; 
    cout << "int to const int:"<< is_convertible<int, const int>::value << endl; 
    return 0; 
}
输出：
true
false
false
int to float:true
int to const int:true

6. initializer_list是一种标准库类型，用于表示某种特定类型的值的数组。和vector一样，initializer_list也是一种模板类型，定义initializer_list对象时，必须说明列表中所含元素的类型。
   和vector不一样的是，initializer_list对象中的元素永远是常量值，我们无法改变initializer_list对象中元素的值

7. std::string_view
c++ 17提供了一个新的性能工具std::string_view。它有着类似std::string的接口易于使用，但是又不拥有字符串的内存，避免了很多拷贝内存操作，性能接近原始c字符串指针

8.  std::default_delete 是不指定删除器时 std::unique_ptr 所用的默认删除策略。 default_delete 的特化在典型实现上为空类，并且用于空基类优化。
    非特化的 default_delete 用 delete 解分配单个对象的内存。
    亦为提供数组类型的使用 delete[] 的部分特化。

    int main()
    {
        //    {
        //        std::shared_ptr<int> shared_bad(new int[10]);
        //    } // 析构函数调用 delete ，未定义行为
    
        {
            std::shared_ptr<int> shared_good(new int[10], std::default_delete<int[]>());
        } // 析构函数调用 delete[] ， ok
    
        {
            std::unique_ptr<int> ptr(new int(5));
        } // 析构函数调用 default_delete<int> ok 
    
        {
            std::unique_ptr<int[]> ptr(new int[10]);
        } // 析构函数调用 default_delete<int[]>
    
    }

9. __attribute__ ((packed)); 的作用就是告诉编译器取消结构在编译过程中的优化对齐,按照实际占用字节数进行对齐，是GCC特有的语法