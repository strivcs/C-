#include<iostream>
void simon(int);

int main()
{
	using namespace std;
	simon(3);
	cout << "Pick an integer:" << endl;
	int count;
	cin >> count;
	cin.get();
	simon(count);
	cout << "Done!" << endl;
	cin.get();
	return 0;
}

void simon(int n)
{
	using namespace std;
	cout << "Simon says touch your toes " << n << " times." << endl;
}