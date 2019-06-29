// Item 1: Understand template type deduction
// - Const pointer to const object

#include <cstddef>
#include <iostream>

template<typename T>
void f(T ptr)
{
    ptr = nullptr;
    std::cout << "This pointer is not const.\n";
}

int main()
{
    const char* const ptr = "Fun with pointers";
    f(ptr); // Argument type is const char* const, T is const char*, param type is const char*
    
    /* 
    In this scope, ptr itself is const (cannot be reassigned) and also points to data that is const (cannot be modified).
    However, when we pass it by value to the templated function f, we end up with a COPY of the pointer that is only 
    const char*, so it can be reassigned, but we still cannot modify the const data at which the original pointer points.
    Since we are passing the pointer by value, we cannot reassign the original, so we can safely ignore its const-ness 
    which will be preserved anyway. However, if the const-ness of what the pointer is pointing to was ignored, that would 
    be bad, but it's okay because that does not happen. Yay, templates!
    */

    return 0;
}