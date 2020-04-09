#include <iostream>
#include <vector>
#include <numeric>
#include <iterator>
#include <algorithm>
#include <stack> 
#include"1.h"

using namespace std;

int main() {
	vector<int> v(10);
	vector<int> u(5);
	vector<int> w(10);
	vector<int>::iterator begin1 = v.begin();
	vector<int>::iterator end1 = v.end();
	vector<int>::iterator begin2 = u.begin();
	vector<int>::iterator end2 = u.end();
	for (int i = 0; i < 10; i++)
	{
		v[i] =i;
	}

	u[0] = 4;
	u[1] = 2;
	u[2] = 3;
	u[3] = 1;
	u[4] = 0;

	for (int i = 0; i < 9; i++)
	{
		w[i] = i;
	}
	w[9] = 8;

	int sum;
	
	cout << accumulate1(begin1, end1, sum)<<endl;//1.27

	cout << accumulate2(begin1, end1, sum, add) << endl;//1.28.1
	cout << accumulate2(begin1+1, begin1+10, sum, mult) << endl;//1.28.2

	copy1<int>(begin2, end2, begin1);
	for (; begin1 != end1; ++begin1)
	{
		cout << *begin1 << ' ';
	}//1.29

	int *a = new int[sizeof(u)];
	if (!u.empty())
	{
		memcpy(a, &u[0], u.size() * sizeof(int));
	}
	

	permutations1(a, 0, 4);//1.30

	permutations2(a, 0, 4);//1.31

	permutations3(a, 0, 4);//1.32

	cout << std::count(v.begin(), v.begin() + 5, 0) << endl;//1.33
	cout << count2(v.begin(), v.begin() + 5, 0) << endl;//1.39

	std::fill(v.begin(), v.begin() + 5, 777);//1.34
	for (int i = 0; i < 5; i++)
	{
		cout << v[i] << " ";
	}
	cout << endl;//验证1.34

	fill2(v.begin(), v.begin() + 5, 777);//1.40
	for (int i = 0; i < 5; i++)
	{
		cout << v[i] << " ";
	}
	cout << endl;//验证1.40
	
	cout << std::inner_product(begin2, begin2 + 5, begin1, 0) << endl;//1.35
	cout << inner_product2(begin2, begin2 + 5, begin1, 0) << endl;//1.41

	std::iota(begin2, begin2 + 5, 777);//1.36
	for (int i = 0; i < 5; i++)
	{
		cout << u[i] << " ";
	}
	cout << endl;//验证1.36

	iota2(begin2, begin2 + 5, 777);//1.42
	for (int i = 0; i < 5; i++)
	{
		cout << u[i] << " ";
	}
	cout << endl;//验证1.42

	cout << std::is_sorted(begin2, begin2 + 5) << endl;//1.37
	cout << is_sorted2<int>(begin2, begin2 + 5) << endl;//1.43

	pair<vector<int>::iterator, vector<int>::iterator> t1;
	t1 = std::mismatch(v.begin(), v.begin() + 9, w.begin());
	cout << *t1.first << endl;
	cout << *t1.second << endl;//1.44

	pair<vector<int>::iterator, vector<int>::iterator> t2;
	t2 = mismatch2<int>(v.begin(), v.begin() + 9, w.begin());
	cout << *t2.first << endl;
	cout << *t2.second << endl;//1.44
	system("pause");
	return 0;		
}                                                                                                                                       