// Item 1: Understand template type deduction
// - Array/function arguments and pointer decay

#include <array>
#include <iostream>

template<typename T>
void f(T param) {}

template<typename T>
void g(T& param) {}

template<typename T, std::size_t N>
constexpr std::size_t arraySize(T (&)[N]) noexcept
{
    return N;
}

void someFunc(int, double) {}

int main()
{
    const char name[] = "D. S. Ingram";
    const char* ptrToName = name;

    f(name);      // Argument type is const char [13], T is const char*, param type is const char* <- WRONG
    f(ptrToName); // Argument type is const char*, T is const char*, param type is const char*

    g(name);      // Argument type is const char [13], T is const char (&)[13], param type is const char (&)[13] <- RIGHT

    /*
    This one is weird. If a built-in array is passed as a by-value argument to a templated function, something called pointer decay
    occurs in which the argument type is deduced to be a pointer to whatever data is stored in the array. Now for the weird part.
    If the array is passed as a by-reference argument instead, the type is correctly deduced to be a built-in array that we now have
    a reference to in the function. Weird. I think the lesson here is to use std::array.
    */

    int keyVals[] = {1, 3, 7, 9, 11, 22, 35};
    std::array<int, arraySize(keyVals)> mappedVals; // Compile-time array size. Pretty cool!

    f(someFunc); // Argument type is void(int, double), T and param type are void (*)(int, double) <- BAD
    g(someFunc); // Argument type is void(int, double), T and param type are void (&)(int, double) <- GOOD

    return 0;
}