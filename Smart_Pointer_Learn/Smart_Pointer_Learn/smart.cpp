#include <iostream>
#include "shared_ptr.h"
using namespace std;

struct Date
{
	int _year;
	int _month;
	int _day;

	Date(int year = 1, int month = 1, int day = 1)
		:_year(year), _month(month), _day(day)
	{ }

	~Date()
	{
		cout << "~Date()" << endl;
	}



};

int main()
{
	/*unique_ptr<Date> up1(new Date[5]);*/
	self::shared_ptr<Date> sp1(new Date(2001, 1, 2));
	self::shared_ptr<Date> sp2 = sp1;

	return 0;
}