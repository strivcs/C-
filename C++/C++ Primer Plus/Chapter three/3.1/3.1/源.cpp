#include<iostream>
#include<climits>

int main()
{
	using namespace std;
	int n_int = INT_MAX;
	short n_short = SHRT_MAX;
	long n_long = LONG_MAX;
	long long n_llong = LLONG_MAX;

	cout << sizeof(int) << endl;
	cout << sizeof(short) << endl;
	cout << sizeof(long) << endl;
	cout << sizeof(LLONG_MAX) << endl<< endl;

	cout << n_int << endl << n_short << endl << n_long << endl << n_llong << endl;
	cin.get();
	return 0;
}