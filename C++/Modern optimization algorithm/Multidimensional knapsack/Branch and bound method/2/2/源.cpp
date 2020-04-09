#include<iostream>
#include"maxHeap.h"
#include"heapNode.h"
#include<time.h>
#include<algorithm>
#include<chrono>  
using namespace std;
using namespace chrono;
maxHeap<heapNode> liveNodeMaxHeap;
//#include<queue>
unsigned short int *bestPackingSoFar = new unsigned short int[50]();//存储最优解的数组
int xx = 0;//记录程序执行次数
//template<class T>
//void changeLength1D(T *&, int, int);
//归并排序函数
template<class T>
void mergeSort2(T[], int);
template<class T>
void mergePass2(T[], T[], int, int);
template<class T>
void merge2(T[], T[], int, int, int);
//std::priority_queue<heapNode> liveNodeMaxHeap;//大根堆
//用于记录结果，从最佳叶结点沿二叉树至根结点的路径即为最优解
//建立大根堆对象
//分支定界法的前期准备，导入数据、按照收益密度稳定排序、调用主计算函数
class BranchBound
{
public:
	//构造函数
	template<class T>
	double knapsack2(std::initializer_list<T> pl, std::initializer_list<T> cl, int theNumberOfObjects,
		std::initializer_list<T> il, std::initializer_list<T> il2,
		std::initializer_list<T> il3, std::initializer_list<T> il4,
		std::initializer_list<T> il5
	);
	double rKnap(int currentLevel);	//主计算函数
	unsigned short int profitBound(unsigned char currentLevel, unsigned short int tttttt);	//背包界定函数
	unsigned short int *capacity = new unsigned short int[50]();//限制条件Pj
	unsigned char numberOfObjects;//物品总数
	unsigned short int *condition1 = new unsigned short int[50]();//各物品的参数1
	unsigned short int *condition2 = new unsigned short int[50]();//各物品的参数2
	unsigned short int *condition3 = new unsigned short int[50]();//各物品的参数3
	unsigned short int *condition4 = new unsigned short int[50]();//各物品的参数4
	unsigned short int *condition5 = new unsigned short int[50]();//各物品的参数5
	unsigned short int *profit = new unsigned short int[50]();//各物品的利润
	unsigned short int profitFromCurrentPacking;//结点路径的总利润
	unsigned short int maxProfitSoFar = 0;//结点的利润上限
	//临时存放物品参数的结构，用于归并排序
	struct element
	{
		unsigned char id;//记录位置
		float profitDensity;//收益密度
		//构造函数
		template<class T>
		element(unsigned char i, T p)
		{
			id = i;
			profitDensity = (float)p;
		}
		//默认构造函数
		element() {}
		//重载操作符
		template<class T>
		T& operator[](int a);
		bool operator==(const BranchBound::element& x);
		bool operator!=(const BranchBound::element& x);
		bool operator<(const BranchBound::element& x);
		bool operator>(const BranchBound::element& x);
		bool operator<=(const BranchBound::element& x);
		bool operator>=(const BranchBound::element& x);
	};
};

unsigned short int MAX = 0;//记录突破函数当前最大值的值，用于输出


//加入活动结点
void addLiveNode(unsigned short int, unsigned short int,
	unsigned short int, unsigned short int,
	unsigned short int, unsigned short int,
	unsigned short int
	, unsigned char, bbNode*, bool);
//赋值主函数
template<class T>
double BranchBound::knapsack2(std::initializer_list<T> pl, std::initializer_list<T> cl, int theNumberOfObjects,
	std::initializer_list<T> il, std::initializer_list<T> il2,
	std::initializer_list<T> il3, std::initializer_list<T> il4,
	std::initializer_list<T> il5)
{
	numberOfObjects = theNumberOfObjects;
	profitFromCurrentPacking = 0;
	maxProfitSoFar = 0;
	//将初始化列表的数值记录到相应数组指针，ptr0~ptr6
	unsigned short int *theCapacity = new unsigned short int[cl.size()];
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
	unsigned short int *theProfit = new unsigned short int[pl.size()];
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
	unsigned short int *wb = new unsigned short int[il2.size()];
	auto ptr3 = il2.begin();
	i = 0;
	while (ptr3 != il2.end())
	{
		wb[i] = *ptr3;
		ptr3++;
		i++;
	}
	//同上
	unsigned short int *wc = new unsigned short int[il3.size()];
	auto ptr4 = il3.begin();
	i = 0;
	while (ptr4 != il3.end())
	{
		wc[i] = *ptr4;
		ptr4++;
		i++;
	}
	//同上
	unsigned short int *wd = new unsigned short int[il4.size()];
	auto ptr5 = il4.begin();
	i = 0;
	while (ptr5 != il4.end())
	{
		wd[i] = *ptr5;
		ptr5++;
		i++;
	}
	//同上
	unsigned short int *we = new unsigned short int[il5.size()];
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
	for (unsigned char i = 1; i <= numberOfObjects; i++)
	{
		q[i - 1] = element(i, (float)(theProfit[i - 1] / wa[i - 1]));
	}

	//归并排序，按照收益密度排序
	mergeSort2(q, numberOfObjects);

	//初始化各数组并导入已排序完毕的数据
	profit = new unsigned short int[numberOfObjects + 1];
	condition1 = new unsigned short int[numberOfObjects + 1];
	condition2 = new unsigned short int[numberOfObjects + 1];
	condition3 = new unsigned short int[numberOfObjects + 1];
	condition4 = new unsigned short int[numberOfObjects + 1];
	condition5 = new unsigned short int[numberOfObjects + 1];
	for (int i = 1; i <= numberOfObjects; i++)
	{
		profit[i] = theProfit[q[numberOfObjects - i].id - 1];
		condition1[i] = wa[q[numberOfObjects - i].id - 1];
		condition2[i] = wb[q[numberOfObjects - i].id - 1];
		condition3[i] = wc[q[numberOfObjects - i].id - 1];
		condition4[i] = wd[q[numberOfObjects - i].id - 1];
		condition5[i] = we[q[numberOfObjects - i].id - 1];
		/*liveNodeMaxHeap.push(heapNode(profit[i], condition1[i],
			condition2[i], condition3[i],
			condition4[i], condition5[i], i));*/
	}
	//liveNodeMaxHeap.push(heapNode(profit[1], condition1[1],
	//	condition2[1], condition3[1],
		//condition4[1], condition5[1],1));
	rKnap(1);//主计算函数
	std::cout << "程序总运行次数：" << xx << std::endl;
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
	return maxProfitSoFar;//返回最优值
}

//主计算函数
double BranchBound::rKnap(int currentLevel)
{
	bbNode* eNode = NULL;//初始化记录结点
	unsigned char eNodelevel = 1;//初始化层数
	unsigned short int *w = new unsigned short int[5]();//初始化叶结点路径的总重量
	unsigned short int maxPossibleProfitInSubtree = profitBound(1, w[0]);//根据背包界定函数求得结点利润上限

	//主循环，左孩子正常检查，右孩子用背包界定函数剪枝(由于左孩子在前，故左孩子收益密度更大)
	while (eNodelevel != numberOfObjects + 1)
	{
		xx++;//记录次数
		//当最优值更新时，输出次数及利润
		MAX = std::max(MAX, profitFromCurrentPacking);
		if ((MAX == profitFromCurrentPacking) && (MAX >= 16500))
		{
			std::cout << "正在输出第" << xx << "次!" << std::endl;
			std::cout << "最大利润：" << MAX << std::endl;
		}
		else if ((MAX == profitFromCurrentPacking) && (MAX < 16500))
		{
			std::cout << "正在输出第" << xx << "次!" << std::endl;
			std::cout << "最大利润：" << MAX << std::endl;
		}
		/*double LeftChild1 = w[0] + condition1[eNodelevel];
		double LeftChild2 = w[1] + condition2[eNodelevel];
		double LeftChild3 = w[2] + condition3[eNodelevel];
		double LeftChild4 = w[3] + condition4[eNodelevel];
		double LeftChild5 = w[4] + condition5[eNodelevel];*/
		//检查左孩子结点
		if ((w[0] + condition1[eNodelevel] <= capacity[0])
			&& (w[1] + condition2[eNodelevel] <= capacity[1])
			&& (w[2] + condition3[eNodelevel] <= capacity[2])
			&& (w[3] + condition4[eNodelevel] <= capacity[3])
			&& (w[4] + condition5[eNodelevel] <= capacity[4])
			)
		{
			//判断左孩子是否可行
			if (profitFromCurrentPacking + profit[eNodelevel] > maxProfitSoFar)
			{
				maxProfitSoFar = profitFromCurrentPacking + profit[eNodelevel];
			}
			//将左孩子加入到活动队列
			addLiveNode(maxPossibleProfitInSubtree,
				profitFromCurrentPacking + profit[eNodelevel],
				w[0] + condition1[eNodelevel],
				w[1] + condition2[eNodelevel],
				w[2] + condition3[eNodelevel],
				w[3] + condition4[eNodelevel],
				w[4] + condition5[eNodelevel],
				eNodelevel + 1, eNode, true);
		}
		maxPossibleProfitInSubtree = profitBound(eNodelevel + 1, w[0]);

		//判断右孩子是否可行
		if (maxPossibleProfitInSubtree >= maxProfitSoFar)
		{
			addLiveNode(maxPossibleProfitInSubtree,
				profitFromCurrentPacking,
				w[0],
				w[1],
				w[2],
				w[3],
				w[4],
				eNodelevel + 1, eNode, false);
		}

		//更新E-结点
		heapNode nextENode = liveNodeMaxHeap.top();
		liveNodeMaxHeap.pop();
		eNode = nextENode.liveNode;
		w[0] = nextENode.w1;
		w[1] = nextENode.w2;
		w[2] = nextENode.w3;
		w[3] = nextENode.w4;
		w[4] = nextENode.w5;
		profitFromCurrentPacking = nextENode._profit;
		maxPossibleProfitInSubtree = nextENode.upperprofit;
		eNodelevel = nextENode.level;
	}

	//记录最优解数据并输出
	std::cout << "正在输出第" << xx << "次!" << std::endl;
	std::cout << "最大利润：" << profitFromCurrentPacking << std::endl;
	for (int j = numberOfObjects; j > 0; j--)
	{
		bestPackingSoFar[j] = (eNode->leftChild) ? 1 : 0;
		eNode = eNode->parent;
	}
	for (int j = 1; j <= numberOfObjects; j++)
	{
		std::cout << bestPackingSoFar[j] << " ";
	}
	std::cout << std::endl;
	return profitFromCurrentPacking;
}

//加入活动队列函数
void addLiveNode(unsigned short int a1, unsigned short int a2,
	unsigned short int a3, unsigned short int a4,
	unsigned short int a5, unsigned short int a6,
	unsigned short int a7
	, unsigned char b1, bbNode* b2, bool leftChild)
{
	bbNode *b = new bbNode(b2, leftChild);//写入结点位置
	//heapNode a = heapNode(a1, a2, a3, a4, a5, a6, a7, b1, b2);
	liveNodeMaxHeap.push(heapNode(a1, a2, a3, a4, a5, a6, a7, b1, b));//插入到活动队列
	//delete[] b;
}

//背包界定函数，这里由于条件1的相关性最大，故简化
unsigned short int BranchBound::profitBound(unsigned char currentLevel, unsigned short int tttttt)
{
	//double *remainingCapacity = new double[10]();
	unsigned short int remainingCapacity = capacity[0] - tttttt;//条件1的剩余空间
	/*remainingCapacity[1] = capacity[1] - w[1];
	remainingCapacity[2] = capacity[2] - w[2];
	remainingCapacity[3]= capacity[3] - w[3];
	remainingCapacity[4]= capacity[4] - w[4];*/
	unsigned short int profitBound = profitFromCurrentPacking;//利润上限

	while ((currentLevel <= numberOfObjects) &&
		(condition1[currentLevel] <= remainingCapacity)
		/*&&
		(condition2[currentLevel] <= remainingCapacity[1]) &&
		(condition3[currentLevel] <= remainingCapacity[2]) &&
		(condition4[currentLevel] <= remainingCapacity[3]) &&
		(condition5[currentLevel] <= remainingCapacity[4]) )*/
		)
	{
		remainingCapacity -= condition1[currentLevel];
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
		profitBound += (profit[currentLevel] / condition1[currentLevel]) * remainingCapacity;
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
T& BranchBound::element::operator[](int a)
{
	return profitDensity;
}

bool BranchBound::element::operator<(const BranchBound::element& x)
{
	return profitDensity < x.profitDensity;
}

bool BranchBound::element::operator>(const BranchBound::element& x)
{
	return profitDensity > x.profitDensity;
}

bool BranchBound::element::operator<=(const BranchBound::element& x)
{
	return profitDensity <= x.profitDensity;
}

bool BranchBound::element::operator>=(const BranchBound::element& x)
{
	return profitDensity >= x.profitDensity;
}

bool BranchBound::element::operator==(const BranchBound::element& x)
{
	return profitDensity == x.profitDensity;
}

bool BranchBound::element::operator!=(const BranchBound::element& x)
{
	return profitDensity != x.profitDensity;
}

template<class T>
void changeLength1D(T *&a, int oldLength, int newLength)
{
	if (newLength < 0)
	{
		throw 3;
	}
	T* temp = new T[newLength]();
	int number = std::min(oldLength, newLength);
	std::copy(a, a + number, temp);
	delete[] a;
	a = temp;
}
int main()
{
	BranchBound a;
	auto start = system_clock::now();
	std::cout << "程序最优值为：" <<
		a.knapsack2({ 560,1125,300,620,2100,431,68,328,47,122,322,196,41,25,425,4260,416,115,82,22,631,132,420,86,42,103,215,81,91,26,49,420,316,72,71,49,108,116,90,738,1811,430,3060,215,58,296,620,418,47,81 },
			{ 800,650,550,550,650 },
			50,
			{ 40,91,10, 30, 160, 20, 3, 12, 3, 18, 9, 25, 1, 1, 10, 280, 10, 8, 1, 1, 49, 8, 21,6 ,1,5, 10, 8, 2, 1, 0, 10, 42, 6, 4, 8, 0, 10 ,1, 40, 86, 11, 120, 8, 3, 32, 28, 13, 2, 4 },
			{ 16, 92, 41, 16, 150, 23, 4, 18, 6, 0, 12, 8, 2, 1, 0, 200, 20, 6, 2, 1, 70, 9, 22 ,4,1 ,5,10, 6, 4, 0, 4, 12, 8, 4, 3, 0, 10, 0, 6, 28, 93, 9 ,30, 22 ,0, 36, 45, 13, 2 ,2 },
			{ 38 ,39, 32, 71, 80, 26, 5, 40, 8, 12, 30, 15, 0, 1, 23, 100, 0, 20, 3, 0, 40, 6, 8, 0,6 ,4,22 ,4 ,6 ,1 ,5 ,14 ,8 ,2 ,8 ,0 ,20 ,0 ,0 ,6 ,12, 6 ,80 ,13 ,6 ,22 ,14 ,0 ,1 ,2 },
			{ 8, 71, 30, 60, 200, 18, 6, 30, 4 ,8, 31, 6, 3, 0 ,18 ,60 ,21 ,4 ,0 ,2 ,32 ,15 ,31 ,2,2 ,7,8 ,2 ,8 ,0 ,2 ,8 ,6 ,7 ,1 ,0 ,0 ,20 ,8 ,14 ,20 ,2 ,40 ,6 ,1 ,14 ,20, 12 ,0 ,1 },
			{ 38 ,52 ,30, 42, 170, 9, 7, 20, 0, 3, 21, 4, 1, 2, 14, 310, 8, 4, 6, 1, 18, 15, 38, 10,4 ,8,6 ,0 ,0 ,3 ,0 ,10 ,6 ,1 ,3 ,0 ,3 ,5 ,4 ,0 ,30 ,12 ,16 ,18 ,3 ,16 ,22 ,30 ,4 ,0 }
	) << std::endl;
	auto end = system_clock::now();
	auto duration = duration_cast<microseconds>(end - start);
	std::cout << "程序用时：" << double(duration.count()) * microseconds::period::num / microseconds::period::den << "s" << std::endl;
	std::system("pause");
	return 0;
}
