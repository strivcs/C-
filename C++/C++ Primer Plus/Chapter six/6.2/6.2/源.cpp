#include<iostream>
const int Max = 5;
int main()
{
	using namespace std;
	double fish[Max];
	cout << "Please enter the weights of your fish.\n";
	cout << "You may enter up to " << Max << " fish <q to terminate>.\n";
	cout << "fish #1: ";
	int i = 0;
	while (i<Max and cin >> fish[i])
	{
		if (++i < Max)
			cout << "fish #" << i + 1 << ": ";
	}
	cin.get();
	double total = 0.0;
	for (int j = 0; j < i; j++)
		total += fish[j];
	if (i == 0)
		cout << "No dish\n";
	else
		cout << total / i << " = average weight of " << i << "Done.\n ";
	system("pause");
	return 0;
}	