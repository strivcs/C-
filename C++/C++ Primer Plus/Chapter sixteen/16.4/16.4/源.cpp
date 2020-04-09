#include<iostream>
#include<string>

int main()
{
	using namespace std;
	string empty;
	string small = "bit";
	string larger = "Elephants are a girl's best friend";
	cout << "Sizes:\n";
	cout << "\tempty: " << empty.size() << endl;
	cout << "\tsmall: " << small.size() << endl;
	cout << "\tlarger: " << larger.size() << endl;
	cout << "Capacities: " << endl;
	cout << "\tempty: " << empty.capacity() << endl;
	cout << "\tsmall: " << small.capacity() << endl;
	cout << "\tlarger: " << larger.capacity() << endl;
	int i = 100;
	empty.reserve(i);
	small.reserve(i);
	larger.reserve(i);
	cout << empty.capacity() << endl;
	cout << small.capacity() << endl;
	cout << larger.capacity() << endl;
	system("Pause");
	return 0;
}