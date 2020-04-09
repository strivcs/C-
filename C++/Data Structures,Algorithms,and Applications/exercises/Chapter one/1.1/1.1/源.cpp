#include<iostream>
#include"chapter-one.h"

int main()
{
	using std::cout;
	using std::endl;

	int x = 6,y = 7;
	int a[12] = { 1,2,3,4,5,2,3,4,5,2,3,1 };
	int b[12] = { 2,3,2,1,2,3,4,5,6,7,2,1 };
	int c[12] = { 1,2,3,4,5,6,7,8,9,10,12,13 };
	int start = 1, end = 9, value = 3;
	int len = sizeof(a) / sizeof(a[0]);
	int *p=new int [14];

	swap(x, y);
	cout << "1.1: x = " << x << " y = " << y << endl;//1.1
	cout << fill(a, value, len) << endl;//1.2
	cout << fill(a, value, start, end) << endl;//1.3
	cout << inner_product(a, b, len) << endl;//1.4
	iota(p, 4, 12);
	for (int i = 0; i < 12; i++)
		cout << p[0] << endl;//1.5
	cout << std::boolalpha<<is_sorted(a, 12) << endl;
	cout << std::boolalpha<<is_sorted(c, 12) << endl;//1.6
	cout << mismatch(a, c, len) << endl;//1.7





	system("Pause");
	return 0;
}