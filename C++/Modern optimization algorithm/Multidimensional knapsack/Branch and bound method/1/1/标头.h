#include<iostream>
#include<algorithm>
#include<queue>
#include<algorithm>
double *weight = new double[10]();//累计重量
class heapNode;
std::priority_queue<heapNode> liveNodeMaxHeap;//大根堆

//普通节点类型
class bbNode
{
public:
	bbNode* parent;      //父母
	bool leftChild;      //是否为左孩子
	//普通节点的构造函数
	bbNode(bbNode* theParent, bool theLeftChild)
	{
		parent = theParent;
		leftChild = theLeftChild;
	};
};

class Branchbound
{
public:

	template<class T>
	double answer(std::initializer_list<T> pl, std::initializer_list<T> cl, int theNumberOfObjects,
		std::initializer_list<T> il, std::initializer_list<T> il2,
		std::initializer_list<T> il3, std::initializer_list<T> il4,
		std::initializer_list<T> il5);
	double profitBound(int currentLevel);
	void addLiveNode(double upperProfit, double theProfit,
		double a1, double a2, double a3, double a4, double a5, int theLevel, bbNode* theParent,
		bool leftChild);
	double maxProfitBBKnapsack();
	double *bestPackingSoFar = new double[60]();//记录最佳结果
	double *capacity;//背包总容量
	int numberOfObjects;//总物品数
	double *profit;//物体价值
	double *condition1;//物体重量
	double *condition2;
	double *condition3;
	double *condition4;
	double *condition5;
	double profitFromCurrentPacking;//累计价值
	//double weightOfCurrentPacking;//当前节点重量
	double maxProfitSoFar;//最大价值
	struct element
	{
		int id;
		double profitDensity;
		template<class T>
		element(int i, T p)
		{
			id = i;
			profitDensity = (double)p;
		}
		element() {}
		template<class T>
		T& operator[](int a);
		bool operator==(const Branchbound::element& x);
		bool operator!=(const Branchbound::element& x);
		bool operator<(const Branchbound::element& x);
		bool operator>(const Branchbound::element& x);
		bool operator<=(const Branchbound::element& x);
		bool operator>=(const Branchbound::element& x);
	};

};

class heapNode
{
public:	
	heapNode(double a) { upperProfit = a; }
	bbNode* liveNode;
	double upperProfit;//节点的最大猜想价值
	double profit;
	double upperWeight;    // 上限
	int level;          // level of live node
	double ValueDensity;
	// constructors
	heapNode() {};

	heapNode(bbNode* theLiveNode, double theUpperProfit,
		double theProfit, double a1, double a2, double a3, double a4, double a5, int theLevel)
	{
		liveNode = theLiveNode;
		upperProfit = theUpperProfit;
		profit = theProfit;
		weight[0] = a1;
		weight[1] = a2;
		weight[2] = a3;
		weight[3] = a4;
		weight[4] = a5;
		level = theLevel;
	}

	bool operator<(const heapNode &right) const
	{
		return upperProfit < right.upperProfit;
	}

	// type conversion to enable arithmetics etc.
	operator double() { return upperProfit; }
};

template<class T>
void changeLength1D(T *&, int, int);

template<class T>
double Branchbound::answer(std::initializer_list<T> pl, std::initializer_list<T> cl, int theNumberOfObjects,
	std::initializer_list<T> il, std::initializer_list<T> il2,
	std::initializer_list<T> il3, std::initializer_list<T> il4,
	std::initializer_list<T> il5)
{
	numberOfObjects = theNumberOfObjects;
	profitFromCurrentPacking = 0.0;
	maxProfitSoFar = 0.0;
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
	double *theProfit = new double[pl.size()];
	auto ptr1 = pl.begin();
	i = 0;
	while (ptr1 != pl.end())
	{
		theProfit[i] = *ptr1;
		ptr1++;
		i++;
	}
	double *wa = new double[il.size()];
	auto ptr2 = il.begin();
	i = 0;
	while (ptr2 != il.end())
	{
		wa[i] = *ptr2;
		ptr2++;
		i++;
	}
	double *wb = new double[il2.size()];
	auto ptr3 = il2.begin();
	i = 0;
	while (ptr3 != il2.end())
	{
		wb[i] = *ptr3;
		ptr3++;
		i++;
	}
	double *wc = new double[il3.size()];
	auto ptr4 = il3.begin();
	i = 0;
	while (ptr4 != il3.end())
	{
		wc[i] = *ptr4;
		ptr4++;
		i++;
	}
	double *wd = new double[il4.size()];
	auto ptr5 = il4.begin();
	i = 0;
	while (ptr5 != il4.end())
	{
		wd[i] = *ptr5;
		ptr5++;
		i++;
	}
	double *we = new double[il5.size()];
	auto ptr6 = il5.begin();
	i = 0;
	while (ptr6 != il5.end())
	{
		we[i] = *ptr6;
		ptr6++;
		i++;
	}
	element *q = new element[numberOfObjects];
	for (int i = 1; i <= numberOfObjects; i++)
	{
		q[i - 1] = element(i, theProfit[i - 1] / wa[i - 1]);
	}

	mergeSort2(q, numberOfObjects);

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

	maxProfitSoFar=maxProfitBBKnapsack();
	//std::cout << "程序总运行次数：" << x << std::endl;
	for (int i = 0; i < 50; i++)
	{
		std::cout << bestPackingSoFar[i] << " ";
	}
	return maxProfitSoFar;
}

//背包界定函数，返回计算后的总价值

double Branchbound::profitBound(int currentLevel)
{
	double *remainingCapacity = new double[10]();
	remainingCapacity[0] = capacity[0] - weight[0];
	remainingCapacity[1] = capacity[1] - weight[1];
	remainingCapacity[2] = capacity[2] - weight[2];
	remainingCapacity[3] = capacity[3] - weight[3];
	remainingCapacity[4] = capacity[4] - weight[4];
	double profitBound = profitFromCurrentPacking;

	while ((currentLevel <= numberOfObjects) &&
		(condition1[currentLevel] <= remainingCapacity[0]) &&
		(condition2[currentLevel] <= remainingCapacity[1]) &&
		(condition3[currentLevel] <= remainingCapacity[2]) &&
		(condition4[currentLevel] <= remainingCapacity[3]) &&
		(condition5[currentLevel] <= remainingCapacity[4]))
	{
		remainingCapacity[0] -= condition1[currentLevel];
		profitBound += profit[currentLevel];
		currentLevel++;
	}

	if (currentLevel <= numberOfObjects)
	{
		profitBound += (profit[currentLevel] / condition1[currentLevel]) * remainingCapacity[0];
	}
	delete[] remainingCapacity;
	return profitBound;
}

//加入活动节点
void Branchbound::addLiveNode(double upperProfit, double theProfit,
	double a1, double a2, double a3, double a4, double a5, int theLevel, bbNode* theParent,
	bool leftChild)
{
	bbNode * b = new bbNode(theParent, leftChild);

	liveNodeMaxHeap.push(heapNode(b, upperProfit, theProfit,
		a1, a2, a3, a4, a5, theLevel));
}

double Branchbound::maxProfitBBKnapsack()
{
	bbNode* eNode = NULL;//E-节点
	int eNodeLevel = 1;//层数
	double maxProfitSoFar = 0.0;//记录最大价值
	double maxPossibleProfitInSubtree = Branchbound::profitBound(1);//剩余最大猜想价值

	//若层数尚未超过物品数
	while (eNodeLevel != numberOfObjects + 1)
	{
		//w[0] += condition1[eNodeLevel];//加左孩子后的重量
		//w[1] += condition2[eNodeLevel];
		//w[2] += condition3[eNodeLevel];
		//w[3] += condition4[eNodeLevel];
		//w[4] += condition5[eNodeLevel];
		//若当前重量加左孩子重量仍未超重

		if (weight[0] + condition1[eNodeLevel] <= capacity[0] &&
			weight[1] + condition2[eNodeLevel] <= capacity[1] &&
			weight[2] + condition3[eNodeLevel] <= capacity[2] &&
			weight[3] + condition4[eNodeLevel] <= capacity[3] &&
			weight[4] + condition5[eNodeLevel] <= capacity[4])
		{

			//若当前价值加左孩子价值超过记录最大值，更新记录最大值
			if ((profitFromCurrentPacking + profit[eNodeLevel]) > maxProfitSoFar)
			{
				maxProfitSoFar = profitFromCurrentPacking + profit[eNodeLevel];
			}

			//左孩子未超重，有可能是更优解，因此加入到活动节点队列
			addLiveNode(maxPossibleProfitInSubtree,
				profitFromCurrentPacking + profit[eNodeLevel],
				weight[0] + condition1[eNodeLevel],
				weight[1] + condition2[eNodeLevel],
				weight[2] + condition3[eNodeLevel],
				weight[3] + condition4[eNodeLevel],
				weight[4] + condition5[eNodeLevel],
				eNodeLevel + 1, eNode, true);
		}
		//if (w[0] + condition1[eNodeLevel] <= capacity[0] &&
		//	w[1] + condition2[eNodeLevel] <= capacity[1] &&
		//	w[2] + condition3[eNodeLevel] <= capacity[2] &&
		//	w[3] + condition4[eNodeLevel] <= capacity[3] &&
		//	w[4] + condition5[eNodeLevel] <= capacity[4])
		//
		//{
		//	w[0] -= condition1[eNodeLevel];//加左孩子后的重量
		//	w[1] -= condition2[eNodeLevel];
		//	w[2] -= condition3[eNodeLevel];
		//	w[3] -= condition4[eNodeLevel];
		//	w[4] -= condition5[eNodeLevel];
		//}

		maxPossibleProfitInSubtree = profitBound(eNodeLevel + 1);//更新最大猜想价值

		//检查右孩子是否可行
		if (maxPossibleProfitInSubtree >= maxProfitSoFar)
		{
			addLiveNode(maxPossibleProfitInSubtree,
				profitFromCurrentPacking,
				weight[0], weight[1], weight[2], weight[3], weight[4],
				eNodeLevel + 1, eNode, false);
		}

		heapNode nextENode = liveNodeMaxHeap.top();
		liveNodeMaxHeap.pop();
		eNode = nextENode.liveNode;//更新E-节点为大根堆下一节点
		//weight[0] = nextENode.weight[0];
		//weight[1] = nextENode.weight[1];
		//weight[2] = nextENode.weight[2];
		//weight[3] = nextENode.weight[3];
		//weight[4] = nextENode.weight[4];
		profitFromCurrentPacking = nextENode.profit;
		maxPossibleProfitInSubtree = nextENode.upperProfit;
		eNodeLevel = nextENode.level;//更新信息
	}

	for (int j = numberOfObjects; j > 0; j--)
	{
		bestPackingSoFar[j] = (eNode->leftChild) ? 1 : 0;
		eNode = eNode->parent;
	}

	return profitFromCurrentPacking;
}


template<class T>
T& Branchbound::element::operator[](int a)
{
	return profitDensity;
}

bool Branchbound::element::operator<(const Branchbound::element& x)
{
	return (profitDensity < x.profitDensity);
}

bool Branchbound::element::operator>(const Branchbound::element& x)
{
	return (profitDensity > x.profitDensity);
}

bool Branchbound::element::operator<=(const Branchbound::element& x)
{
	return (profitDensity <= x.profitDensity);
}

bool Branchbound::element::operator>=(const Branchbound::element& x)
{
	return (profitDensity >= x.profitDensity);
}

bool Branchbound::element::operator==(const Branchbound::element& x)
{
	return (profitDensity == x.profitDensity);
}

bool Branchbound::element::operator!=(const Branchbound::element& x)
{
	return (profitDensity != x.profitDensity);
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