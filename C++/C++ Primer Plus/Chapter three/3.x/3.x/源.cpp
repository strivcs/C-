#include<iostream>
int main()
{
	using namespace std;
	cout.setf(ios_base::floatfield);
	cout << 1.e2<<endl;
	cout.setf(ios_base::fixed,ios_base::floatfield);
	cout << 1.e2<<endl;
	cout.setf(ios_base::fixed);
	cout << 1.e2<<endl;
	cin.get();
	return 0;
}