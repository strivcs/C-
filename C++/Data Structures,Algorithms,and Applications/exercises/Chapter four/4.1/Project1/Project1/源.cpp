#include<iostream>
#include<vector>
#include<algorithm>
#include"1.h"
#include <utility>
const int ROWS = 10;
const int SIZE = 3;

bool cmp(iterator<int> a, iterator<int> b)
{
	return a < b;
}

int main()
{
	using namespace std;
	using namespace std::rel_ops;
	arrayList<int> a = arrayList<int>(12);
	arrayList<int> b = arrayList<int>(11);
	//arrayList<int> b = arrayList<int>(11);
	for (int i = 0; i < a.capacity(); i++)
	{
		a.insert(i, i+1);
	}
	for (int i = 0; i < b.capacity(); i++)
	{
		b.insert(i, i+1);
	}
	//a.insert(13, 99);
	//cout << a << endl;
	//cout << a.capacity() << endl;
	//a.Set_Upper(99);
	//a.insert(13, 99);
	//cout << a << endl;
	//cout << a.capacity() << endl;//5.4

	//a.trimToSize();//5.5

	//a.setSize(15);
	//a.insert(13, 98);
	//cout << a << endl;
	//cout << a.capacity() << endl;//5.6.1
	//a.setSize(5);
	//cout << a << endl;
	//cout << a.capacity() << endl;//5.6.2

	//a[2] = 100;
	//cout << a[2] << endl;//5.7

	//cout << (a == b) << endl;//5.8

	//cout << (a != b);//5.9

	//cout << (a < b) << endl << (b < a);//5.10

	//a.push_back(9999);
	//a.push_back(9999);
	//a.push_back(9999);
	//cout<<a.capacity()<<endl;
	//cout << a.size() << endl;
	//a.pop_back();
	//cout << a.capacity() << endl;
	//cout << a.size() << endl;
	//a.pop_back();
	//cout << a.capacity() << endl;
	//cout << a.size() << endl;
	//a.push_back(9999);
	//cout << a.capacity() << endl;
	//cout << a.size() << endl;
	//cout << a << endl;//5.11,5.12

	//a.swap(1,2);
	//cout << a << endl;//5.13

	//a.reserve(100);
	//cout << a.capacity();//5.14

	//a.set(1, 2);
	//cout << a << endl;//5.15

	//a.clear();
	//cout << a << endl;//5.16

	//a.removeRange(1, 3);
	//cout << a;//5.17

	//cout << a.lastIndexof(50);//5.18

	//cout << a.size() << " " << a.capacity() << endl;
	//a.reserve(100);
	//cout << a.size() << " " << a.capacity() << endl;
	//a.check_length();
	//cout << a.size() << " " << a.capacity() << endl;
	//a.pop_back(10);
	//cout << a.size() << " " << a.capacity() << endl;
	//cout << a;//5.20

	//cout << a << endl;
	//a.reverse();
	//cout << a << endl;//5.22.1

	//cout << a << endl;
	//reverse(a);
	//cout << a << endl;//5.22.4

	//cout << a << endl;
	//cout << a.size() << " " << a.capacity() << endl;
	//a.leftShift(2);
	//cout << a << endl;
	//cout << a.size() << " " << a.capacity() << endl;//5.23

	//cout << a << endl;
	//a.circularShift(2);
	//cout << a << endl;//5.24

	//cout << a << endl;
	//cout << a.size() << " " << a.capacity() << endl;
	//a.half();
	//cout << a << endl;
	//cout << a.size() << " " << a.capacity() << endl;
	//cout << b << endl;
	//b.half();
	//cout << b << endl;//5.25

	//cout << a << endl;
	//cout << a.size() << " " << a.capacity() << endl;
	//half(a);
	//cout << a << endl;
	//cout << a.size() << " " << a.capacity() << endl;
	//cout << b << endl;
	//half(b);
	//cout << b << endl;//5.26
	
	//arrayList<int>::iterator x = a.begin();
	//cout << *x << endl;
	//x + 5;
	//cout << *x << endl;
	//x++;
	//cout << *x << endl;
	//x - 1;
	//cout << *x << endl;
	//x--;
	//cout << *x << endl;
	//x -= 1;
	//cout << *x << endl;
	//x += 1;
	//cout << *x << endl;
	//cout << x[6] << " " << (x[6] < x[7]) << " " << (x[6] <= x[7]) <<
	//	" " << (x[6] > x[7]) <<
	//	" " << (x[6] >= x[7]) <<
	//	" " << (x[6] == x[7]) <<
	//	" " << (x[6] != x[7]) << endl;//text

	a.swap(1, 3);
	a.swap(2, 6);
	a.swap(3, 9);
	a.swap(4, 5);
	std::cout << a << std::endl;
	std::sort(a.begin(), a.end());
	std::cout << a << std::endl;//5.27	

	//arrayList<int> c;
	//c.meld(a, b);
	//std::cout << a << std::endl << b << std::endl;
	//std::cout << c.capacity()<<std::endl;
	//std::cout << c.size() << std::endl;
	//std::cout << c;//5.28

	std::cout << a << std::endl;
	std::cout << b << std::endl;
	arrayList<int> c;
	std::merge(a.begin(),a.end(),b.begin(),b.end(),std::ostream_iterator<int>(std::cout, " "));
	//std::merge(a.begin(), a.end(), b.begin(), b.end(), c);
	system("pause");
	return 0;
}