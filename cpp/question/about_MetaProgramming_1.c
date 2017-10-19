#include <string>
#include <iostream>

using namespace std;

constexpr int ipow(int x, int n)
{
	return n > 0 ? (x * ipow(x, n - 1)) : 1;
}

template <char c> constexpr int b3_helper()
{
	static_assert(c < '3', "not a ternary digit");
	return c;
}

template <char c, char... args> constexpr int b3_helper()
{
	static_assert(c < '3', "not a ternary digit");
	return (ipow(3, sizeof... (args)) * (c - '0')
		/*+ b3_helper<args...>()*/); //error C2668 Why???
}

template <char... args> int operator"" _b3()
{
	int temp = b3_helper<args...>();
	std::cout << temp << endl;
	return temp;
}


/*
template <> constexpr int b3_helper() instead of 
template <char c> constexpr int b3_helper()
will compile successfully
*/
int main()
{
	int test = 201_b3;
	std::cout << test << endl;
}
