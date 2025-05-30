#include <iostream>
using namespace std;

void func(int& x)
{
	cout << "Lvalue overload f(" << x << ")" << endl;
}
void func(const int& x)
{
	cout << "const Lvalue overload f(" << x << ")" << endl;
}
void func(int&& x)
{
	cout << "Rvalue overload f(" << x << ")" << endl;
}

void func(const int&& x)
{
	cout << "const Rvalue overload f(" << x << ")" << endl;
}

template<class T>
void function(T&& t)
{
	//func(t);
	func(forward<T>(t)); // use this can avoid changed Rvalue to Lvalue
}


int main()
{
	function(10);
	int a = 20;
	function(a);
	function(move(a));
	const int b = 8;
	function(b);
	function(move(b));
	return 0;
}