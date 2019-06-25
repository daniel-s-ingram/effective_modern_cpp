//Item 1: Understand template type deduction

#include <iostream>
#include <boost/type_index.hpp>

using boost::typeindex::type_id_with_cvr;

template<typename T>
void f1(T& param)
{
    std::cout << "T is deduced to be type " << type_id_with_cvr<T>().pretty_name();
    std::cout << ", and param is deduced to be type " << type_id_with_cvr<decltype(param)>().pretty_name() << ".\n";
}

template<typename T>
void f2(const T& param)
{
    std::cout << "T is deduced to be type " << type_id_with_cvr<T>().pretty_name();
    std::cout << ", and param is deduced to be type " << type_id_with_cvr<decltype(param)>().pretty_name() << ".\n";
}

template<typename T>
void f3(T* param)
{
    std::cout << "T is deduced to be type " << type_id_with_cvr<T>().pretty_name();
    std::cout << ", and param is deduced to be type " << type_id_with_cvr<decltype(param)>().pretty_name() << ".\n";
}

template<typename T>
void f4(T&& param)
{
    std::cout << "T is deduced to be type " << type_id_with_cvr<T>().pretty_name();
    std::cout << ", and param is deduced to be type " << type_id_with_cvr<decltype(param)>().pretty_name() << ".\n";
}

template<typename T>
void f5(T param)
{
    std::cout << "T is deduced to be type " << type_id_with_cvr<T>().pretty_name();
    std::cout << ", and param is deduced to be type " << type_id_with_cvr<decltype(param)>().pretty_name() << ".\n";
}

int main()
{
    int x = 27;
    const int cx = x;
    const int& rx = x;
    const int* px = &x;

    //Case 1: ParamType is a Reference or Pointer, but not a universal reference.
    //ParamType is T&
    std::cout << "\ntemplate<typename T>\nvoid f1(T& param);\n";
    std::cout << "For an argument of type " << type_id_with_cvr<decltype(x)>().pretty_name() << ", ";
    f1(x);
    std::cout << "For an argument of type " << type_id_with_cvr<decltype(cx)>().pretty_name() << ", ";
    f1(cx);
    std::cout << "For an argument of type " << type_id_with_cvr<decltype(rx)>().pretty_name() << ", ";
    f1(rx);

    //ParamType is const T&
    std::cout << "\ntemplate<typename T>\nvoid f2(const T& param);\n";
    std::cout << "For an argument of type " << type_id_with_cvr<decltype(x)>().pretty_name() << ", ";
    f2(x);
    std::cout << "For an argument of type " << type_id_with_cvr<decltype(cx)>().pretty_name() << ", ";
    f2(cx);
    std::cout << "For an argument of type " << type_id_with_cvr<decltype(rx)>().pretty_name() << ", ";
    f2(rx);

    //ParamType is T*
    std::cout << "\ntemplate<typename T>\nvoid f3(T* param);\n";
    std::cout << "For an argument of type " << type_id_with_cvr<decltype(&x)>().pretty_name() << ", ";
    f3(&x);
    std::cout << "For an argument of type " << type_id_with_cvr<decltype(px)>().pretty_name() << ", ";
    f3(px);

    //Case 2: ParamType is a Universal Reference
    std::cout << "\ntemplate<typename T>\nvoid f4(T&& param);\n";
    std::cout << "For an lvalue argument of type " << type_id_with_cvr<decltype(x)>().pretty_name() << ", ";
    f4(x);
    std::cout << "For an lvalue argument of type " << type_id_with_cvr<decltype(cx)>().pretty_name() << ", ";
    f4(cx);
    std::cout << "For an lvalue argument of type " << type_id_with_cvr<decltype(rx)>().pretty_name() << ", ";
    f4(rx);
    std::cout << "For an rvalue argument of type " << type_id_with_cvr<decltype(27)>().pretty_name() << ", ";
    f4(27);

    //Case 3: ParamType is a Neither a Pointer nor a Reference
    std::cout << "\ntemplate<typename T>\nvoid f5(T param);\n";
    std::cout << "For an argument of type " << type_id_with_cvr<decltype(x)>().pretty_name() << ", ";
    f5(x);
    std::cout << "For an argument of type " << type_id_with_cvr<decltype(cx)>().pretty_name() << ", ";
    f5(cx);
    std::cout << "For an argument of type " << type_id_with_cvr<decltype(rx)>().pretty_name() << ", ";
    f5(rx);

    std::cout << std::endl;
    return 0;
}