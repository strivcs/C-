/*
回溯法：深度优先搜索思想
STL函数：
	initializer_list：初始化列表，大规模输入参数
*/
#include<time.h>
#include<algorithm>
class Backtracking2
{
public:
	template<class T>
	double knapsack2(std::initializer_list<T> pl, std::initializer_list<T> cl, int theNumberOfObjects,
		std::initializer_list<T> il, std::initializer_list<T> il2,
		std::initializer_list<T> il3, std::initializer_list<T> il4,
		std::initializer_list<T> il5
	);
	void rKnap(int currentLevel);//主计算函数
	double profitBound(int currentLevel);//背包定界函数
	double *capacity;//限制条件Pj
	int numberOfObjects;//物品总数
	double *condition1;//各物品的参数1
	double *condition2;//各物品的参数2
	double *condition3;//各物品的参数3
	double *condition4;//各物品的参数4
	double *condition5;//各物品的参数5
	double *profit;//各物品的利润
	double *w = new double[10]();//叶结点路径的总重量
	double profitFromCurrentPacking;//结点路径的总利润
	double maxProfitSoFar;//结点的利润上限
	double *answer = new double[60]();//记录最优解
	//临时存放物品参数的结构，用于归并排序
	struct element
	{
		int id;//记录位置
		double profitDensity;//收益密度
		//构造函数
		template<class T>
		element(int i, T p)
		{
			id = i;
			profitDensity = (double)p;
		}
		//默认构造函数
		element() {}
		//重载操作符
		template<class T>
		T& operator[](int a);
		bool operator==(const Backtracking2::element& x);
		bool operator!=(const Backtracking2::element& x);
		bool operator<(const Backtracking2::element& x);
		bool operator>(const Backtracking2::element& x);
		bool operator<=(const Backtracking2::element& x);
		bool operator>=(const Backtracking2::element& x);
	};
};
double x = 0;
double MAX = 0;//记录突破函数当前最大值的值，用于输出
//归并排序函数
template<class T>
void mergeSort2(T[], int);
template<class T>
void mergePass2(T[], T[], int, int);
template<class T>
void merge2(T[], T[], int, int, int);
//赋值主函数
template<class T>
double Backtracking2::knapsack2(std::initializer_list<T> pl, std::initializer_list<T> cl, int theNumberOfObjects,
	std::initializer_list<T> il, std::initializer_list<T> il2,
	std::initializer_list<T> il3, std::initializer_list<T> il4,
	std::initializer_list<T> il5)
{
	numberOfObjects = theNumberOfObjects;
	profitFromCurrentPacking = 0.0;
	maxProfitSoFar = 0.0;
	//将初始化列表的数值记录到相应数组指针，ptr0~ptr6
	double *theCapacity = new double[cl.size()];
	auto ptr0 = cl.begin();
	int i = 0;
	while (ptr0 != cl.end())
	{
		theCapacity[i] = *ptr0;
		ptr0++;
		i++;
	}
	capacity = theCapacity;
	//同上
	double *theProfit = new double[pl.size()];
	auto ptr1 = pl.begin();
	i = 0;
	while (ptr1 != pl.end())
	{
		theProfit[i] = *ptr1;
		ptr1++;
		i++;
	}
	//同上
	double *wa = new double[il.size()];
	auto ptr2 = il.begin();
	i = 0;
	while (ptr2 != il.end())
	{
		wa[i] = *ptr2;
		ptr2++;
		i++;
	}
	//同上
	double *wb = new double[il2.size()];
	auto ptr3 = il2.begin();
	i = 0;
	while (ptr3 != il2.end())
	{
		wb[i] = *ptr3;
		ptr3++;
		i++;
	}
	//同上
	double *wc = new double[il3.size()];
	auto ptr4 = il3.begin();
	i = 0;
	while (ptr4 != il3.end())
	{
		wc[i] = *ptr4;
		ptr4++;
		i++;
	}
	//同上
	double *wd = new double[il4.size()];
	auto ptr5 = il4.begin();
	i = 0;
	while (ptr5 != il4.end())
	{
		wd[i] = *ptr5;
		ptr5++;
		i++;
	}
	//同上
	double *we = new double[il5.size()];
	auto ptr6 = il5.begin();
	i = 0;
	while (ptr6 != il5.end())
	{
		we[i] = *ptr6;
		ptr6++;
		i++;
	}

	//初始化element，用于归并排序，按照收益密度导入数据
	element *q = new element[numberOfObjects];
	for (int i = 1; i <= numberOfObjects; i++)
	{
		q[i - 1] = element(i, theProfit[i - 1] / wb[i - 1]);
	}

	//归并排序，按照收益密度排序
	mergeSort2(q, numberOfObjects);

	//初始化各数组并导入已排序完毕的数据
	profit = new double[numberOfObjects + 1];
	condition1 = new double[numberOfObjects + 1];
	condition2 = new double[numberOfObjects + 1];
	condition3 = new double[numberOfObjects + 1];
	condition4 = new double[numberOfObjects + 1];
	condition5 = new double[numberOfObjects + 1];
	for (int i = 1; i <= numberOfObjects; i++)
	{
		profit[i] = theProfit[q[numberOfObjects - i].id - 1];
		condition1[i] = wa[q[numberOfObjects - i].id - 1];
		condition2[i] = wb[q[numberOfObjects - i].id - 1];
		condition3[i] = wc[q[numberOfObjects - i].id - 1];
		condition4[i] = wd[q[numberOfObjects - i].id - 1];
		condition5[i] = we[q[numberOfObjects - i].id - 1];
	}

	rKnap(1);//主计算函数
	std::cout << "程序总运行次数：" << x << std::endl;
	//std::cout<<profitBound(1);
	/*std::cout << " 程序最优解为：";
	for (int o = 1; o < 51; o++)
	{
		std::cout << condition1[o] << " ";
	}
	std::cout << std::endl;
	for (int o = 1; o < 51; o++)
	{
		std::cout << condition2[o] << " ";
	}
	std::cout << std::endl;
	for (int o = 1; o < 51; o++)
	{
		std::cout << condition3[o] << " ";
	}
	std::cout << std::endl;
	for (int o = 1; o < 51; o++)
	{
		std::cout << condition4[o] << " ";
	}
	std::cout << std::endl;
	for (int o = 1; o < 51; o++)
	{
		std::cout << condition5[o] << " ";
	}*/
	//std::cout << std::endl;
	return maxProfitSoFar;
}

//主计算函数
void Backtracking2::rKnap(int currentLevel)
{
	x++;//记录次数
	//当最优值更新时，输出次数及利润，并返回上一个E-结点，此时到达叶结点
	if (currentLevel > numberOfObjects)
	{
		maxProfitSoFar = profitFromCurrentPacking;
		MAX = std::max(MAX, profitFromCurrentPacking);
		if ((MAX == profitFromCurrentPacking) && (MAX >= 16537))
		{
			std::cout << "已迭代次数: " << x << "次!" << std::endl;
			std::cout << "最大利润: " << MAX << std::endl;
			for (int o = 1; o < 51; o++)
			{
				std::cout << answer[o] << " ";
			}
			std::cout << std::endl;
		}
		else if ((MAX == profitFromCurrentPacking) && (MAX < 16537))
		{
			std::cout << "已迭代次数: " << x << "次!" << std::endl;
			std::cout << "最大利润: " << MAX << std::endl;
		}
		return;
	}

	//未到达叶结点时，检查子树，左子树正常检查，右子树用背包界定函数检查
	//搜索左子树
	if ((w[0] + condition1[currentLevel] <= capacity[0]) &&
		(w[1] + condition2[currentLevel] <= capacity[1]) &&
		(w[2] + condition3[currentLevel] <= capacity[2]) &&
		(w[3] + condition4[currentLevel] <= capacity[3]) &&
		(w[4] + condition5[currentLevel] <= capacity[4])
		)
	{
		w[0] += condition1[currentLevel];
		w[1] += condition2[currentLevel];
		w[2] += condition3[currentLevel];
		w[3] += condition4[currentLevel];
		w[4] += condition5[currentLevel];
		answer[currentLevel] = 1;
		profitFromCurrentPacking += profit[currentLevel];
		rKnap(currentLevel + 1);
		w[0] -= condition1[currentLevel];
		w[1] -= condition2[currentLevel];
		w[2] -= condition3[currentLevel];
		w[3] -= condition4[currentLevel];
		w[4] -= condition5[currentLevel];
		profitFromCurrentPacking -= profit[currentLevel];
		answer[currentLevel] = 0;
	}

	//搜索右子树
	if (profitBound(currentLevel + 1) > maxProfitSoFar)
	{
		rKnap(currentLevel + 1);
	}
}

//背包界定函数，这里由于条件1的相关性最大，故简化
double Backtracking2::profitBound(int currentLevel)
{
	//double *remainingCapacity = new double[10]();
	double remainingCapacity = capacity[1] - w[1];//条件1的剩余空间
	/*remainingCapacity[1] = capacity[1] - w[1];
	remainingCapacity[2] = capacity[2] - w[2];
	remainingCapacity[3]= capacity[3] - w[3];
	remainingCapacity[4]= capacity[4] - w[4];*/
	double profitBound = profitFromCurrentPacking;//利润上限

	while ((currentLevel <= numberOfObjects) &&
		(condition2[currentLevel] <= remainingCapacity)
		/*&&
		(condition2[currentLevel] <= remainingCapacity[1]) &&
		(condition3[currentLevel] <= remainingCapacity[2]) &&
		(condition4[currentLevel] <= remainingCapacity[3]) &&
		(condition5[currentLevel] <= remainingCapacity[4]) )*/
		)
	{
		remainingCapacity -= condition2[currentLevel];
		/*remainingCapacity[1] -= condition2[currentLevel];
		remainingCapacity[2] -= condition3[currentLevel];
		remainingCapacity[3] -= condition4[currentLevel];
		remainingCapacity[4] -= condition5[currentLevel];*/
		profitBound += profit[currentLevel];
		currentLevel++;
	}

	//收益密度*剩余空间
	if (currentLevel <= numberOfObjects)
	{
		profitBound += (profit[currentLevel] / condition2[currentLevel]) * remainingCapacity;
	}
	//delete[] remainingCapacity;
	return profitBound;
}

template<class T>
void mergeSort2(T a[], int n)
{
	T *b = new T[n];
	int segmentSize = 1;
	while (segmentSize < n)
	{
		mergePass2(a, b, n, segmentSize);
		segmentSize += segmentSize;
		mergePass2(b, a, n, segmentSize);
		segmentSize += segmentSize;
	}
	delete[] b;
}

template<class T>
void mergePass2(T x[], T y[], int n, int segmentSize)
{
	int i = 0;
	while (i <= n - 2 * segmentSize)
	{
		merge2(x, y, i, i + segmentSize - 1, i + 2 * segmentSize - 1);
		i = i + 2 * segmentSize;
	}

	if (i + segmentSize < n)
	{
		merge2(x, y, i, i + segmentSize - 1, n - 1);
	}
	else
	{
		for (int j = i; j < n; j++)
		{
			y[j] = x[j];
		}
	}
}

template<class T>
void merge2(T c[], T d[], int startOfFirst, int endOfFirst, int endOfSecend)
{
	int first = startOfFirst,
		second = endOfFirst + 1,
		result = startOfFirst;

	while ((first <= endOfFirst) && (second <= endOfSecend))
	{
		if (c[first] <= c[second])
		{
			d[result++] = c[first++];
		}
		else
		{
			d[result++] = c[second++];
		}
	}

	if (first > endOfFirst)
	{
		for (int q = second; q <= endOfSecend; q++)
		{
			d[result++] = c[q];
		}
	}
	else
	{
		for (int q = first; q <= endOfFirst; q++)
		{
			d[result++] = c[q];
		}
	}
}

template<class T>
T& Backtracking2::element::operator[](int a)
{
	return profitDensity;
}

bool Backtracking2::element::operator<(const Backtracking2::element& x)
{
	return profitDensity < x.profitDensity;
}

bool Backtracking2::element::operator>(const Backtracking2::element& x)
{
	return profitDensity > x.profitDensity;
}

bool Backtracking2::element::operator<=(const Backtracking2::element& x)
{
	return profitDensity <= x.profitDensity;
}

bool Backtracking2::element::operator>=(const Backtracking2::element& x)
{
	return profitDensity >= x.profitDensity;
}

bool Backtracking2::element::operator==(const Backtracking2::element& x)
{
	return profitDensity == x.profitDensity;
}

bool Backtracking2::element::operator!=(const Backtracking2::element& x)
{
	return profitDensity != x.profitDensity;
}