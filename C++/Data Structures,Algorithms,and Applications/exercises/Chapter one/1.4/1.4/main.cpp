#include<iostream>
#include"currency.h"

int main()
{
	using namespace std;
	currency g;
	currency h;//(6)
	currency m;
	h = 30;
	m = 3.00000000;//(6)

	cout << m << endl;//(6)

	cin >> g;
	cout << g << endl;//(1)

	cout << g - h << endl;//(2)

	cout << g % 50 << endl;//(3)

	cout << g * 3 << endl;//(4)

	cout << g / 3 << endl;//(5)

	system("pause");
	return 0;
}