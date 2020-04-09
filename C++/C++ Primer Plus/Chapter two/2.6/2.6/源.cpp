#include<iostream>

int stonetolb(int);
int main()
{
	using namespace std;
	int stone;
	cout << "Enter the weight in stone: "<<endl;
	cin >> stone;
	cin.get();
	int pounds = stonetolb(stone);
	cout << stone << " stone = " << pounds << " pounds." << endl;
	cin.get();
	return 0;
}

int stonetolb(int sts)
{
	return 14 * sts;
}