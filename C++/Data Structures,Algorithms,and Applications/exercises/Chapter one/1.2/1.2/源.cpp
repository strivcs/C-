#include<iostream>
#include"标头.h"


int main()
{
	using namespace std;
	int a, b, c;
	cin >> a >> b >> c;
	try { cout << abc(a, b, c) << endl; }
	catch (int e)
	{
		if (e == 1)
		{
			cout << "a,b,c不能都小于0" << endl;
			cout << e << endl;
			system("pause");
			return 1;
			//exit(1);
		}
		else if(e==2)
		{
			cerr << "a,b,c不能都等于0" << endl;
			cerr << e << endl;
			system("pause");
			return 1;
			//exit(1);
		}
	}//1.10

	int d[12] = { 1,2,3,4,5,2,3,4,5,2,3,1 };
	int value = 3;
	int len = 0;
	try { fill(d, value, len); }
	catch (int e)
	{
		if (e == 1)
		{
			cout << "数组长度不能小于1" << endl;
			system("pause");
			return 1;
		}
	}//1.11


	system("pause");
	return 0;
}