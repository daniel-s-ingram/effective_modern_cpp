// Item 1: Understand template type deduction
// - Case 2: ParamType is a Universal Reference.
//    1. If the argument is an lvalue, both T and ParamType are deduced to be lvalue references.
//    2. If the argument is an rvalue, Case 1 rules apply.

template<typename T>
void f(T&& param) {}

int main()
{
    int x = 27;
    const int cx = x;
    const int& rx = x;

    f(x);  // Argument is lvalue and type is int, T is int&, param type is int&
    f(cx); // Argument is lvalue and type is const int, T is const int&, param type is const int&
    f(rx); // Argument is lvalue and type is const int&, T is const int&, param type is const int&
    f(27); // Argument is rvalue and type is int, T is int, param type is int&&

    return 0;
}