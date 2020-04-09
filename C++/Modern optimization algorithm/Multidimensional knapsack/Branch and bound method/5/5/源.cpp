#include<iostream>
#include<thread>
#include<chrono>
using namespace std;
using namespace std::this_thread;
using namespace chrono;

void fun_1()
{
	while (true)
	{
		cout << "fun_1:" << 7777777 << endl;
	}
}
void fun_2()
{
	while (true)
	{
		cout << "fun_2:" << 6 << endl;
	}

}
int main()
{
	thread t_1(fun_1);
	t_1.detach();
	thread t_2(fun_2);
	t_2.detach();
	system("pause");
	return 0;
}
