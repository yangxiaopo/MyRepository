#include <iostream>

namespace N
{
	class A{};
	void f(A)
	{
		std::cout << "I am void f(A)" << std::endl;
	}
};

void f(int)
{
	std::cout << "I am void f(int)" << std::endl;
}

template <typename T>
void g(T t)
{
	f(t);
}

void f(double)
{
	std::cout << "I am void f(double)" << std::endl;
}

/*
output:
I am void f(A)
I am void f(int)
I am void f(double)

but bj say: the last one causes f(int) to be called; f(double) not considered
and why???
*/
int main()
{
	g(N::A());
	g(2);
	g(2.1);
}