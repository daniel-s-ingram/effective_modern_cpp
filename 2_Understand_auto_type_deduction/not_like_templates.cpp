// Item 2: Understand auto type deduction
// - auto type deduction works like template type deduction in all but one case. This is the one case.

#include <initializer_list>
#include <vector>

template<typename T>
void f(T param) {}

template<typename T>
void g(std::initializer_list<T> param) {}

/* 
auto type deduction for function return type is only valid for C++14 and above.
However, in this context, auto type deduction uses TEMPLATE type deduction (weird), 
so the below function would not compile (see below for the why).

auto createInitList()
{
    return {1, 2, 3};
}
*/

int main()
{
    int x1 = 27;    // x1 is an int with value 27
    int x2(27);     // x2 is an int with value 27
    int x3 = {27};  // x3 is an int with value 27
    int x4{27};     // x4 is an int with value 27

    auto y1 = 27;   // y1 is deduced as an int with value 27
    auto y2(27);    // y2 is deduced as an int with value 27
    auto y3 = {27}; // y3 is deduced as a std::initializer_list<int> with value 27
    auto y4{27};    /* y4 is MAYBE deduced as a std::initializer_list<int> with value 27.
                       This depends on whether or not your compiler implements N3922, which
                       eliminates the special auto type deduction rule for direct braced 
                       initialization i.e. when there is no "=" preceding a braced initialization. 
                       The C++ Standardization Committee adopted N3922 in November 2014, but it is 
                       not part of the standard, though many compilers implement it.*/

    //f({27});      // Template deduction fails for braced initialization and this will not compile, unless...
    g({27});        // std::initializer is part of the type specifier for the template as in the function g


    /*
    This treatment of braced initialization is the ONLY way in which template and auto
    deduction differ. auto type deduction assumes that a braced initializer represents
    a std::initializer_list (again, unless your compiler implements N3922 and we're talking
    about direct braced initialization), while template type deduction will never 
    make that assumption. 
    */

    std::vector<int> v;
    auto resetV = [&v](const auto& newValue){v = newValue;};
    /*
    resetV({1, 2, 3}); 
    The above line would not compile for the same reason the function createInitList would not compile.
    If auto is used in a function return type OR a in lambda argument, template type deduction occurs,
    and template type deduction will never deduce braced initializers.
    */
    return 0;
}
