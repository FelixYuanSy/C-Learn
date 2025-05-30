#include <iostream>
using namespace std;

class live_Longer
{
public:
	live_Longer(const string& name): _name(name)
	{	
		cout << "live_Longer constructor :" <<_name <<endl;
	}
	~live_Longer()
	{
		cout << "live_Longer destructor :" << _name << endl;
	}
private:
	string _name;

};

live_Longer createLonger(const string& name)
{
	return live_Longer(name);
}
int main2()
{
	cout << "--------no reference---------" << endl;
	string s1 = "no_ref";
	createLonger(s1);
	cout << "--------Reference(Lvalue)-----" << endl;
	string s2 = "With_ref";
	const live_Longer& lf = createLonger(s2);
	cout << "--------Reference(Rvalue)-----" << endl;
	const live_Longer& lf2 = createLonger(string("123"));
	cout << "---------end of main--------" << endl;
	return 0;

	
}