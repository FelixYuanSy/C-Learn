#include <iostream>
using namespace std;


int main1()
{
	//左值: 可以取地址	
	int p = 0;
	int *x = new int(0);
	const int b = 20;
	*x = 10;
	string s("1054");
	s[1] = 'x';

	cout << &p << endl;
	cout << & x << endl;
	cout << &b << endl;
	cout << &s << endl;
	//右值无法取地址
	double dx = 10.0;
	double dy = 10.2;
	dx + dy;
	10;
	string("eerer");
	/*cout << &(dx + dy) << end;*/ // 表达式为右值无法取地址
	/*cout << &(10);*/	//常量无法打印地址
	/*cout << &string("eerer") << endl; *///无法打印地址(error:'&' requires l-value)

	// lvalue reference
	int& r1 = p;
	int*& r2 = x;
	int& r3 = *x;//不能都去掉*, x为指针他的类型为int*, 所以要引用x必须用类型为int*的变量.*x为x指针所指向的数值,所以需要int来引用.
	string& r4 = s;//如果右边为*s(error:no operator "*" matches these operands)
	char& r5 = s[0];
	

	//Rvalue reference
	int&& rr1 = 10;
	string&& rr2 = string("eerer");
	double&& rr3 = dx + dy;

	//Lvalue reference can not direct reference Rvalue, 
	//but const Lvalue can reference Rvalue

	/*double& lr1 = dx + dy;*/	//error: initial value of reference to non-const must be an lvalue
	const double& lr2 = dx + dy;// It's legal;
	
	//Rvalue reference can not reference Lvalue unless use move()
	/*int&& rrx1 = p;*/	//error:an rvalue reference cannot be bound to an lvalue
	int&& rrx2 = move(p);

	//After Rvalue reference, they are changed to Lvalue
	int& lrr = rr1;	//it's legal;
	cout << &rr1 << endl;
	cout << &lrr << endl;	//it' the same address


	return 0;
}
