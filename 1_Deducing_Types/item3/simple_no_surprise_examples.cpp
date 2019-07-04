// Item 3: Understand decltype
// - Given a name or an expression, decltype will tell you its type. In most cases, there
//   are no surprises, and the result is exactly what you would expect.

#include <cstddef>

const int i = 0;          // decltype(i) is const int

class Widget
{
    //...
};

bool f(const Widget& w)   // decltype(f) is bool(const Widget&)
{                         // decltype(w) is const Widget&
    //...
}
struct Point              // decltype(Point::x) is int
{                         // decltype(Point::y) is int
    int x, y;
};

template<typename T>      // Simplified version of std::vector
class vector
{
public:
    T& operator[](std::size_t index)
    {
        //...
    }
};

int main()
{
    Widget w;             // decltype(w) is Widget

    if (f(w))             // decltype(f(w)) is bool
    {
        //...
    }

    vector<int> v;        // decltype(v) is vector<int>

    if (v[0] == 0)        // decltype(v[0]) is int&
    {
        //...
    }

    // See? No surprises!

    return 0;
}