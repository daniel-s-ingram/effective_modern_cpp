// Item 1: Understand template type deduction
// - Case 1: ParamType is a Reference or Pointer, but not a universal reference.
//    1. If the argument is a reference (or pointer), ignore the reference (or pointer) part.
//    2. Pattern-match argument type against param type to determine T.

template<typename T>
void f(T& param) {}

template<typename T>
void g(const T& param) {}

template<typename T>
void h(T* param) {}

int main()
{
    int x = 27;
    const int cx = x;
    const int& rx = x;
    const int* px = &x;

    f(x);   // Argument type is int, T is int, param type is int&
    f(cx);  // Argument type is const int, T is const int, param type is const int&
    f(rx);  // Argument type is const int&, T is const int, param type is const int&

    g(x);   // Argument type is int, T is int, param type is const int&
    g(cx);  // Argument type is const int, T is int, param type is const int&
    g(rx);  // Argument type is const int&, T is int, param type is const int&

    h(&x);  // Argument type is int*, T is int, param type is int*
    h(px);  // Argument type is const int*, T is const int, param type is const int*

    return 0;
}
