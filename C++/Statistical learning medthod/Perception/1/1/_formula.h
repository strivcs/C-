//常用公式
#include<iostream>
#include<vector>
using namespace std;
//范数
template<class T1,class T2>
T2 norm(vector<T1> w, unsigned char p)
{
	T2 count = 0;
	typename vector<T1>::iterator it;
	if (p > 1)
	{
		for (it = w.begin(); it != w.end(); it++)
		{
			count += pow(*it, p);
		}
		return pow(count, 1.0 / p);
	}	
	else if (p = 1)
	{
		for (it = w.begin(); it != w.end(); it++)
		{
			count += abs(*it);
		}
		return count;
	}
	else
	{
		return -1;
	}
}