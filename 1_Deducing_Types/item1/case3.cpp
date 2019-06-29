// Item 1: Understand template type deduction
// - Case 3: ParamType is a Neither a Pointer nor a Reference
//    1. If the argument is a reference (or pointer), ignore the reference (or pointer) part.
//    2. Also ignore arguments's const-ness or volatile-ness.

template<typename T>
void f(T param) {}

int main()
{
    int x = 27;
    const int cx = x;
    const int& rx = x;

    f(x);  // Argument type is int, T is int, param type is int
    f(cx); // Argument type is const int, T is int, param type is int
    f(rx); // Argument type is const int&, T is int, param type is int

    return 0;
}