// Item 1: Understand template type deduction
// - Case 3: ParamType is a Neither a Pointer nor a Reference
//    1. If the argument is a reference, ignore the reference part.
//    2. Also ignore argument's const-ness or volatile-ness (unless it's the const-ness of data a pointer argument is pointing to).

template<typename T>
void f(T param) {}

int main()
{
    int x = 27;
    const int cx = x;
    const int& rx = x;
    const int* px = &x;

    f(x);  // Argument type is int, T is int, param type is int
    f(cx); // Argument type is const int, T is int, param type is int
    f(rx); // Argument type is const int&, T is int, param type is int
    f(px); // Argument type is const int*, T is const int*, param type is const int*

    return 0;
}