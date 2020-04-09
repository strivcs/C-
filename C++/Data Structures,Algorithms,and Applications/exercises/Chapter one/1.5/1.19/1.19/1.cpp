#include <sstream>
#include <iostream>
#include <vector>
#include <numeric>
#include <iterator>
#include <algorithm>
#include "1.h"



int main()
{
	using namespace std;
	int n = 10;
	int result = 1;
	for (int i = 0; i < n; i++)
	{
		result *= (i+1);
	}
	cout << "The results of 10! is: "<<result << endl;//1.19

	cout << Fibonacci(10) << endl;//1.20.1
	cout << Fibonacci2(10) << endl;//1.20.3

	cout << fun(5) << "," << fun(7) << endl;//1.21.3
	cout << fun2(5) << "," << fun2(7) << endl;//1.21.4

	cout << A(1, 2) << endl;
	cout << A(2, 1) << endl;
	cout << A(2, 2) << endl;//1.22.3

	cout << gcd(20, 30) << "," << gcd(112, 42) << endl;//1.23.3

	int x = 1000;
	int a[10] = { 1,2,3,4,5,6,7,8,9,0 };
	int b[10] = { 1,2,3,4,5,6,7,8,9,1000 };
	cout << judge(x, a, 10) << "," << judge(x, b, 10) << endl;//1.24

	SG(5);//1.25

	Gray_Code(4);//1.26
	std::system("pause");
	return 0;
}

