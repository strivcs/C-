#include<iostream>
#include"currency.h"

using namespace std;

int main()
{
	currency t;
	t.input();
	t.output();//(1)

	currency q(30);
	q.output();
	t.subtract(q);
	t.output();//(2)

	t.percent(50);
	t.output();//(3)

	t.multiply(3);
	t.output();//(4)

	t.divide(3);
	t.output();//(5)

	system("Pause");
	return 0;
}
