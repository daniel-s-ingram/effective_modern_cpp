// Item 2: Understand auto type deduction
// - auto type deduction works like template type deduction in all but one case. These are those cases.

void someFunc(int, double) {}

int main()
{
    /*
    When declaring variables with auto, auto plays the role of T in the template
    and the type specifier acts as ParamType.

    For "auto x = 27", x is deduced in the same way param would be if you were to do

    template<typename T>
    void f(T param) {}

    f(27);

    Same with "const auto& rx = x" being equivalent to

    template<typename T>
    void g(const T& param) {}

    g(x);
    */

    auto x = 27;            // Like 1.3: x is neither ptr nor reference
    const auto cx = x;      // Like 1.3: cx is neither ptr nor reference
    const auto& rx = x;     // Like 1.1: rx is a non-universal reference

    auto&& uref1 = x;       // Like 1.2: x is lvalue int, uref1 is int&
    auto&& uref2 = cx;      // Like 1.2: cx is lvalue const int, uref2 is const int&
    auto&& uref3 = 27;      // Like 1.2: 27 is rvalue int, uref3 is int&&

    const char name[] = "D. S. Ingram";
    auto arr1 = name;       // arr1 is const char*
    auto& arr2 = name;      // arr2 is const char (&)[13]

    auto func1 = someFunc;  // func1 is void (*)(int, double)
    auto& func2 = someFunc; // func2 is void (&)(int, double)

    return 0;
}