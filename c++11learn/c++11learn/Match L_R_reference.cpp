#include<iostream>
using namespace std;

void f(int& x)
{
	cout << "Lvalue overload f(" << x << ")" << endl;
}
void f(const int& x)
{
	cout << "const Lvalue overload f(" << x << ")" << endl;
}
void f(int&& x)
{
	cout << "Rvalue overload f(" << x << ")" << endl;
}

int main()
{
	int i = 0;
	const int i1 = 10;

	f(i); //int& x
	f(i1);	//const int& x
	f(2); // if there is no int&&x func exists, it will use const int& x
			//int&& x
	f(move(i)); //int&& x
	int&& x = 1; //右值引用后整体值为左值
	f(x);	//int& x
	return 0;
}