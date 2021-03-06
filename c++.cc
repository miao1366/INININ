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
