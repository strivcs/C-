#include<iostream>
#include<random>
#include<stdlib.h>
#include<chrono>

int main()
{
	using namespace std;
	using namespace chrono;
	using std::default_random_engine;
	using std::uniform_real_distribution;
	default_random_engine e(time(NULL));
	static uniform_real_distribution<double> u(1, 39);
	std::cout << std::round(u(e))<< std::endl;
	system("pause");
	return 0;
}