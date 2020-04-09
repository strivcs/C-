#include<iostream>
#include<vector>
#include"_formula.h"
using namespace std;

int main()
{
	vector<int> w = { 1,2,3,4,5 };
	std::cout << norm<int, double>(w, 2) << std::endl;
	system("pause");
	return 0;
}