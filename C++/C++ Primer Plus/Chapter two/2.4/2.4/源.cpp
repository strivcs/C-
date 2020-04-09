#include<iostream>
#include<cmath>

int main()
{
	using namespace std;

	double area;
	cout << "Enter the floor area, in square feet, of your home: "<<endl;
	cin >> area;
	cin.get();
	double side;
	side = sqrt(area);
	cout << "That's the equivalent of a square " << side
		<< " feet to the side." << endl
		<< "How fascinating!" << endl;
	cin.get();
	return 0;
}