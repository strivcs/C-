#include<iostream>
#include<cstring>

int main()
{
	using namespace std;
	char animal[20] = "bear";
	const char *bird = "wren";
	char * ps;

	cout << animal << " and " << bird << endl;
	// ps << endl;
	cout << "Enter a kind of animals: ";
	cin >> animal;
	ps = animal;
	cin.get();
	cout << ps << "!\n";
	cin.get();
	return 0;
}