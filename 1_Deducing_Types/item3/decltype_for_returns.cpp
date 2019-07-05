// Item 3: Understand decltype
// - Using decltype for improvement to function return type deduction

#include <deque>
#include <string>

void authenticateUser()
{
    //...
}

/*
In the below function, auto in the return type position is NOT used for type deduction. Instead, it is used to
indicate that C++11's trailing return type syntax is being used. This simply means that the return type is defined
AFTER the parameter list; the advantage to this is that the function's parameters can be used to specify the return
type. If we were to use decltype(c[i]) in place of auto, this would not compile since c and i would not have been
declared yet.
*/
template<typename Container, typename Index>
auto authAndAccess_cpp11(Container& c, Index i) -> decltype(c[i]) // C++11
{
    authenticateUser();
    return c[i];
}  

/*
In C++14, the return type of a function CAN be deduced by auto, even with multiple returns, so long as all the
returns are of the same type. However, this can lead to undesired behavior.
*/
template<typename Container, typename Index>
auto authAndAccess_cpp14(Container& c, Index i) // C++14
{
    authenticateUser();
    return c[i];
}
/*
What is the problem with the above function? c[i] returns an int&. However, type deduction will strip off that reference
(refer to items 1 & 2), so the return type of the function is an rvalue int. Why is this a problem?

std::deque<int> d;
...

authAndAccess_cpp14(d, 5) = 10;

The above line will not compile. Here, we are attempting to return a reference to d[5] to which we can then assign the value
of 10. However, as explained above, does not return int& - it returns an int. So, we are trying to assign an rvalue to an rvalue,
and this will not work. See below for the fix.
*/

template<typename Container, typename Index>
decltype(auto) authAndAccess_cpp14_v2(Container& c, Index i) // decltype(auto) says to deduce the type but not strip anything off
{
    authenticateUser();
    return c[i];
}
/*
Now, the function will return exactly what c[i] returns, so we're good, right? Not quite. Currently, the function accepts an
lvalue reference to a non-const container. So, if we wanted to pass an rvalue container to the function, our code would not
compile. Something using the makeStringDeque function below like this:

auto s = authAndAccess_cpp14_v2(makeStringDeque(), 5)

would not work. On to v3!
*/

template<typename Container, typename Index>
decltype(auto) authAndAccess_cpp14_v3(Container&& c, Index i) // Universal reference!
{
    authenticateUser();
    return c[i];
}
/*
The only change required here is to change the type for parameter c from Container& to Container&&. Container& is
an lvalue reference, and while Container&& appears to be an rvalue reference at first glance, it can actually be
either an lvalue OR an rvalue reference. This is because Container&& is what's known as a universal (or forwarding) 
reference since the type of Container is being deduced here. See item 24 for details.

There is one more problem though. Even if we passed an rvalue for c, once that value enters this function, it's an
lvalue since we're able to refer to it as c. If we want to avoid unnecessary copying and take advantage of move
semantics, we need to ensure that rvalues remain rvalues. Our choices are std::move and std::forward. std::move
will unconditionally cast a value to an rvalue, while std::forward will only cast a value to an rvalue if it was
ALREADY an rvalue.

*/

template<typename Container, typename Index>
decltype(auto) authAndAccess_cpp14_final(Container&& c, Index i)
{
    authenticateUser();
    return std::forward<Container>(c)[i]; // Now we're talking!
}

std::deque<std::string> makeStringDeque()
{
    std::deque<std::string> s;
    //...

    return s;
}

int main()
{
    return 0;
}

