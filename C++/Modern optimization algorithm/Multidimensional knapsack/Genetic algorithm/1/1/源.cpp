#include <iostream>
//#include <fstream>
#include <string>
#include <stdlib.h>
#include<random>
#include<chrono>  
#include <windows.h>
using namespace std;
using namespace chrono;
using std::default_random_engine;
using std::uniform_real_distribution;

#include"标头.h"
int main() 
{
	GA *temp = new GA[1000];
	int aaa = 0;
	int aa = 0;
	//for (int i = 0; i < 1000; i++)
	//{
	//	//default_random_engine e(time(NULL));
	//	//static uniform_real_distribution<double> u(0, 1);
	//	aaa = temp[i].Run();
	//	//std::cout << time(NULL) << endl;
	//	std::cout << aaa << endl;
	//	if (aaa == 16537)
	//	{
	//		aa++;
	//	}
	//}
	aaa = temp[0].Run();
	std::cout << aaa << endl;
	std::cout << "最优解的概率为: " <<(double)aa / 1000 << std::endl;
	system("pause");
	return 0;
}