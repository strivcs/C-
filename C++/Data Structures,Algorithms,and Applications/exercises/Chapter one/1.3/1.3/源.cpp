#include<iostream>
#include"1.h"
const int ROWS = 10;
const int SIZE = 3;
int main()
{
	using namespace std;

	//����1.12δ�����ڴ�Ķ�άָ������
	int **a;

	//����1.13��̬һάָ�����飬��Ϊ1.12�ṩ��һ���Ѿ�������һά����
	int *b;
	b = new int[ROWS];
	for (int i = 0; i < ROWS; i++)
	{
		b[i] = i;
	}

	//����1.14��̬��άָ������
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
	
	//cout << a[3] << endl;//��֤��1.12
	make2dArray(a, ROWS, b);
	cout << a[3] << endl << endl;

	cout << b[3] <<" "<< b[8] << " " << b[9] << endl;
	changeLength1D(b, ROWS, 9);
	cout << b[3] << " " << b[8] << endl<< endl;
	//cout << b[9] << endl;//��֤��1.13

	cout << c[1][1] << " " << c[8][1] << " " << c[9][2] << endl;
	changeLength2D(c, ROWS, SIZE, 9, 2);
	cout << c[1][1] << " " << c[8][1] << endl;
	//cout << a[9][2] << end;//��֤��1.14
	system("Pause");
	return 0;
}