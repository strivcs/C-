/*
分支定界法：广度优先搜索思想
STL函数：
	priority_queue：优先队列，用于实现E-结点的排序及提取
	initializer_list：初始化列表，大规模输入参数
本程序自造代码，未使用priority_queue
*/

#include<time.h>
#include<algorithm>
//#include<queue>
unsigned short int *bestPackingSoFar = new unsigned short int[50]();//存储最优解的数组
int xx = 0;//记录程序执行次数
class heapNode;
template<class T>
class maxHeap;
template<class T>
void changeLength1D(T *&, int, int);

//std::priority_queue<heapNode> liveNodeMaxHeap;//大根堆
//用于记录结果，从最佳叶结点沿二叉树至根结点的路径即为最优解
class bbNode
{
public:
	bbNode* parent;      //父母
	bool leftChild;      //是否为左孩子

	//构造函数
	bbNode(bbNode* theParent, bool theLeftChild)
	{
		parent = theParent;
		leftChild = theLeftChild;
	};
};

//大根堆
class heapNode
{
public:
	//大根堆默认构造函数
	heapNode() {};
	heapNode(unsigned short int a1, unsigned short int a2, unsigned short int a3,
		unsigned short int a4, unsigned short int a5, unsigned short int a6, unsigned short int a7
		, unsigned char b1, bbNode* b2);
	unsigned short int w1;//当前结点路径的总重量1
	unsigned short int w2;//当前结点路径的总重量2
	unsigned short int w3;//当前结点路径的总重量3
	unsigned short int w4;//当前结点路径的总重量4
	unsigned short int w5;//当前结点路径的总重量5
	unsigned char  level;//当前结点的层数
	unsigned short int upperprofit;//当前结点的利润上限(由背包界定函数(profitBound)计算得到)
	unsigned short int _profit;//当前结点路径的总利润
	bbNode* liveNode;//当前结点对应的记录结点

	//重载操作符，优先队列的排序算法要求
	bool operator<(const heapNode &right) const
	{
		return upperprofit < right.upperprofit;
	}
	//bool operator>(const heapNode &right) const
	//{
	//	return upperprofit > right.upperprofit;
	//}
	//bool operator<=(const heapNode &right) const
	//{
	//	return upperprofit <= right.upperprofit;
	//}
	bool operator>=(const heapNode &right) const
	{
		return upperprofit >= right.upperprofit;
	}
};

//大根堆构造函数的实现
heapNode::heapNode(unsigned short int a1, unsigned short int a2, unsigned short int a3,
	unsigned short int a4, unsigned short int a5, unsigned short int a6, unsigned short int a7
	, unsigned char b1, bbNode* b2)
{
	upperprofit = a1;
	_profit = a2;
	w1 = a3;
	w2 = a4;
	w3 = a5;
	w4 = a6;
	w5 = a7;
	level = b1;
	liveNode = b2;
	//delete[]b2;
};

template<class T>
class maxHeap
{
public:
	~maxHeap() {};
	int heapSize;
	T* heap = new T[8000000]();
	T top() { return heap[1]; };
	void push(const T& theElement);
	void pop();
};
maxHeap<heapNode> liveNodeMaxHeap;
template<class T>
void maxHeap<T>::push(const T& theElement)
{
	int currentNode = ++heapSize;
	while (currentNode != 1 && heap[currentNode / 2] < theElement)
	{
		heap[currentNode] = heap[currentNode / 2];
		currentNode /= 2;
	}

	heap[currentNode] = theElement;
};

template<class T>
void maxHeap<T>::pop()
{
	if (heapSize == 0)
	{
		throw - 1;
	}
	heap[1].~T();
	T lastElement = heap[heapSize--];
	int currentNode = 1, child = 2;
	while (child <= heapSize)
	{
		if (child < heapSize && heap[child] < heap[child + 1])
		{
			child++;
		}
		if (lastElement >= heap[child])
		{
			break;
		}
		heap[currentNode] = heap[child];
		currentNode = child;
		child *= 2;
	}
	heap[currentNode] = lastElement;
}

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

//归并排序函数
template<class T>
void mergeSort2(T[], int);
template<class T>
void mergePass2(T[], T[], int, int);
template<class T>
void merge2(T[], T[], int, int, int);
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
			std::cout << "已迭代次数: " << xx << "次!" << std::endl;
			std::cout << "最大利润: " << MAX << std::endl;
		}
		else if ((MAX == profitFromCurrentPacking) && (MAX < 16500))
		{
			std::cout << "已迭代次数: " << xx << "次!" << std::endl;
			std::cout << "最大利润: " << MAX << std::endl;
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