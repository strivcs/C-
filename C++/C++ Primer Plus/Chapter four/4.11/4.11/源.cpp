#include<iostream>

struct inflatable
{
	char name[20];
	float volume;
	double price;
};

int main()
{
	using namespace std;
	inflatable guest =
	{
		"Glorioous Gloria",
		1.88,
		29.99
	};
	
	inflatable pal =
	{
		"a",
		3.12,
		32.99
	};

	guest.name = char("hgfhgfhgf");
	cout << "Expend your guest list with " << guest.price;
	cin.get();
	return 0;



}