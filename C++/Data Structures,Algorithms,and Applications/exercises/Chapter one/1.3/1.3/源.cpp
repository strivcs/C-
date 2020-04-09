#include<iostream>
#include"1.h"
const int ROWS = 10;
const int SIZE = 3;
int main()
{
	using namespace std;

	//创建1.12未声明内存的二维指针数组
	int **a;

	//创建1.13动态一维指针数组，并为1.12提供另一个已经声明的一维数组
	int *b;
	b = new int[ROWS];
	for (int i = 0; i < ROWS; i++)
	{
		b[i] = i;
	}

	//创建1.14动态二维指针数组
	int **c;
	c = new int *[ROWS];
	for (int i = 0; i < ROWS; i++)
	{
		c[i] = new int[SIZE];
	}
	for (int i = 0; i < ROWS; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			*(*(c + i) + j) = i + j;
		}
	}
	
	//cout << a[3] << endl;//验证，1.12
	make2dArray(a, ROWS, b);
	cout << a[3] << endl << endl;

	cout << b[3] <<" "<< b[8] << " " << b[9] << endl;
	changeLength1D(b, ROWS, 9);
	cout << b[3] << " " << b[8] << endl<< endl;
	//cout << b[9] << endl;//验证，1.13

	cout << c[1][1] << " " << c[8][1] << " " << c[9][2] << endl;
	changeLength2D(c, ROWS, SIZE, 9, 2);
	cout << c[1][1] << " " << c[8][1] << endl;
	//cout << a[9][2] << end;//验证，1.14
	system("Pause");
	return 0;
}