#include<iostream>
#include<fstream>
#include<cstdlib>
const int SIZE = 60;
int main()
{
	using namespace std;

	char filename[SIZE];
	ifstream inFile;
	cout << "Enter name of data file: ";
	cin.getline(filename, SIZE);
	//inFile.open("D:\\C++\\C++ Primer Plus\\Chapter six\\6.15\\6.15\\scores.txt");
	inFile.open(filename);
	system("pause");
	if (!inFile.is_open())
	{
		cout << "Could not open the file " << filename << endl;
		cout << "Program terminating.\n";
		cin.get();
		exit(EXIT_FAILURE);
	}
	double value;
	double sum = 0.0;
	int count = 0;
	system("pause");
	inFile >> value; 
	while (inFile.good())
	{
		++count;
		sum += value;
		inFile >> value;
	}
	if (inFile.eof())
	{
		cout << "End of file reached.\n";
	}
	else if (inFile.fail())
	{
		cout << "Input terminated by data mismatch.\n";
	}
	else
		cout << "Input terminated for unknown reason.\n";
	if (count == 0)
	{
		cout << "No data processed.\n";
	}
	else
	{
		cout << "Items read: " << count << endl;
		cout << "Sum: " << sum << endl;
		cout << "Average: " << sum / count << endl;
	}
	system("pause");
	cin.get();
	inFile.close();
	cin.get();
	return 0;
}