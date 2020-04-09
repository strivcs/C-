/*
��֧���編�������������˼��
STL������
	priority_queue�����ȶ��У�����ʵ��E-����������ȡ
	initializer_list����ʼ���б����ģ�������
������������룬δʹ��priority_queue
*/

#include<time.h>
#include<algorithm>
//#include<queue>
unsigned short int *bestPackingSoFar = new unsigned short int[50]();//�洢���Ž������
int xx = 0;//��¼����ִ�д���
class heapNode;
template<class T>
class maxHeap;
template<class T>
void changeLength1D(T *&, int, int);

//std::priority_queue<heapNode> liveNodeMaxHeap;//�����
//���ڼ�¼����������Ҷ����ض�������������·����Ϊ���Ž�
class bbNode
{
public:
	bbNode* parent;      //��ĸ
	bool leftChild;      //�Ƿ�Ϊ����

	//���캯��
	bbNode(bbNode* theParent, bool theLeftChild)
	{
		parent = theParent;
		leftChild = theLeftChild;
	};
};

//�����
class heapNode
{
public:
	//�����Ĭ�Ϲ��캯��
	heapNode() {};
	heapNode(unsigned short int a1, unsigned short int a2, unsigned short int a3,
		unsigned short int a4, unsigned short int a5, unsigned short int a6, unsigned short int a7
		, unsigned char b1, bbNode* b2);
	unsigned short int w1;//��ǰ���·����������1
	unsigned short int w2;//��ǰ���·����������2
	unsigned short int w3;//��ǰ���·����������3
	unsigned short int w4;//��ǰ���·����������4
	unsigned short int w5;//��ǰ���·����������5
	unsigned char  level;//��ǰ���Ĳ���
	unsigned short int upperprofit;//��ǰ������������(�ɱ����綨����(profitBound)����õ�)
	unsigned short int _profit;//��ǰ���·����������
	bbNode* liveNode;//��ǰ����Ӧ�ļ�¼���

	//���ز����������ȶ��е������㷨Ҫ��
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

//����ѹ��캯����ʵ��
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

//��֧���編��ǰ��׼�����������ݡ����������ܶ��ȶ����򡢵��������㺯��
class BranchBound
{
public:
	//���캯��
	template<class T>
	double knapsack2(std::initializer_list<T> pl, std::initializer_list<T> cl, int theNumberOfObjects,
		std::initializer_list<T> il, std::initializer_list<T> il2,
		std::initializer_list<T> il3, std::initializer_list<T> il4,
		std::initializer_list<T> il5
	);
	double rKnap(int currentLevel);	//�����㺯��
	unsigned short int profitBound(unsigned char currentLevel, unsigned short int tttttt);	//�����綨����
	unsigned short int *capacity = new unsigned short int[50]();//��������Pj
	unsigned char numberOfObjects;//��Ʒ����
	unsigned short int *condition1 = new unsigned short int[50]();//����Ʒ�Ĳ���1
	unsigned short int *condition2 = new unsigned short int[50]();//����Ʒ�Ĳ���2
	unsigned short int *condition3 = new unsigned short int[50]();//����Ʒ�Ĳ���3
	unsigned short int *condition4 = new unsigned short int[50]();//����Ʒ�Ĳ���4
	unsigned short int *condition5 = new unsigned short int[50]();//����Ʒ�Ĳ���5
	unsigned short int *profit = new unsigned short int[50]();//����Ʒ������
	unsigned short int profitFromCurrentPacking;//���·����������
	unsigned short int maxProfitSoFar = 0;//������������
	//��ʱ�����Ʒ�����Ľṹ�����ڹ鲢����
	struct element
	{
		unsigned char id;//��¼λ��
		float profitDensity;//�����ܶ�
		//���캯��
		template<class T>
		element(unsigned char i, T p)
		{
			id = i;
			profitDensity = (float)p;
		}
		//Ĭ�Ϲ��캯��
		element() {}
		//���ز�����
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

unsigned short int MAX = 0;//��¼ͻ�ƺ�����ǰ���ֵ��ֵ���������

//�鲢������
template<class T>
void mergeSort2(T[], int);
template<class T>
void mergePass2(T[], T[], int, int);
template<class T>
void merge2(T[], T[], int, int, int);
//�������
void addLiveNode(unsigned short int, unsigned short int,
	unsigned short int, unsigned short int,
	unsigned short int, unsigned short int,
	unsigned short int
	, unsigned char, bbNode*, bool);
//��ֵ������
template<class T>
double BranchBound::knapsack2(std::initializer_list<T> pl, std::initializer_list<T> cl, int theNumberOfObjects,
	std::initializer_list<T> il, std::initializer_list<T> il2,
	std::initializer_list<T> il3, std::initializer_list<T> il4,
	std::initializer_list<T> il5)
{
	numberOfObjects = theNumberOfObjects;
	profitFromCurrentPacking = 0;
	maxProfitSoFar = 0;
	//����ʼ���б����ֵ��¼����Ӧ����ָ�룬ptr0~ptr6
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
	//ͬ��
	unsigned short int *theProfit = new unsigned short int[pl.size()];
	auto ptr1 = pl.begin();
	i = 0;
	while (ptr1 != pl.end())
	{
		theProfit[i] = *ptr1;
		ptr1++;
		i++;
	}
	//ͬ��
	double *wa = new double[il.size()];
	auto ptr2 = il.begin();
	i = 0;
	while (ptr2 != il.end())
	{
		wa[i] = *ptr2;
		ptr2++;
		i++;
	}
	//ͬ��
	unsigned short int *wb = new unsigned short int[il2.size()];
	auto ptr3 = il2.begin();
	i = 0;
	while (ptr3 != il2.end())
	{
		wb[i] = *ptr3;
		ptr3++;
		i++;
	}
	//ͬ��
	unsigned short int *wc = new unsigned short int[il3.size()];
	auto ptr4 = il3.begin();
	i = 0;
	while (ptr4 != il3.end())
	{
		wc[i] = *ptr4;
		ptr4++;
		i++;
	}
	//ͬ��
	unsigned short int *wd = new unsigned short int[il4.size()];
	auto ptr5 = il4.begin();
	i = 0;
	while (ptr5 != il4.end())
	{
		wd[i] = *ptr5;
		ptr5++;
		i++;
	}
	//ͬ��
	unsigned short int *we = new unsigned short int[il5.size()];
	auto ptr6 = il5.begin();
	i = 0;
	while (ptr6 != il5.end())
	{
		we[i] = *ptr6;
		ptr6++;
		i++;
	}

	//��ʼ��element�����ڹ鲢���򣬰��������ܶȵ�������
	element *q = new element[numberOfObjects];
	for (unsigned char i = 1; i <= numberOfObjects; i++)
	{
		q[i - 1] = element(i, (float)(theProfit[i - 1] / wa[i - 1]));
	}

	//�鲢���򣬰��������ܶ�����
	mergeSort2(q, numberOfObjects);

	//��ʼ�������鲢������������ϵ�����
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
	rKnap(1);//�����㺯��
	std::cout << "���������д�����" << xx << std::endl;
	//std::cout<<profitBound(1);
	/*std::cout << " �������Ž�Ϊ��";
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
	return maxProfitSoFar;//��������ֵ
}

//�����㺯��
double BranchBound::rKnap(int currentLevel)
{
	bbNode* eNode = NULL;//��ʼ����¼���
	unsigned char eNodelevel = 1;//��ʼ������
	unsigned short int *w = new unsigned short int[5]();//��ʼ��Ҷ���·����������
	unsigned short int maxPossibleProfitInSubtree = profitBound(1, w[0]);//���ݱ����綨������ý����������

	//��ѭ��������������飬�Һ����ñ����綨������֦(����������ǰ�������������ܶȸ���)
	while (eNodelevel != numberOfObjects + 1)
	{
		xx++;//��¼����
		//������ֵ����ʱ���������������
		MAX = std::max(MAX, profitFromCurrentPacking);
		if ((MAX == profitFromCurrentPacking) && (MAX >= 16500))
		{
			std::cout << "�ѵ�������: " << xx << "��!" << std::endl;
			std::cout << "�������: " << MAX << std::endl;
		}
		else if ((MAX == profitFromCurrentPacking) && (MAX < 16500))
		{
			std::cout << "�ѵ�������: " << xx << "��!" << std::endl;
			std::cout << "�������: " << MAX << std::endl;
		}
		/*double LeftChild1 = w[0] + condition1[eNodelevel];
		double LeftChild2 = w[1] + condition2[eNodelevel];
		double LeftChild3 = w[2] + condition3[eNodelevel];
		double LeftChild4 = w[3] + condition4[eNodelevel];
		double LeftChild5 = w[4] + condition5[eNodelevel];*/
		//������ӽ��
		if ((w[0] + condition1[eNodelevel] <= capacity[0])
			&& (w[1] + condition2[eNodelevel] <= capacity[1])
			&& (w[2] + condition3[eNodelevel] <= capacity[2])
			&& (w[3] + condition4[eNodelevel] <= capacity[3])
			&& (w[4] + condition5[eNodelevel] <= capacity[4])
			)
		{
			//�ж������Ƿ����
			if (profitFromCurrentPacking + profit[eNodelevel] > maxProfitSoFar)
			{
				maxProfitSoFar = profitFromCurrentPacking + profit[eNodelevel];
			}
			//�����Ӽ��뵽�����
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

		//�ж��Һ����Ƿ����
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

		//����E-���
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

	//��¼���Ž����ݲ����
	std::cout << "���������" << xx << "��!" << std::endl;
	std::cout << "�������" << profitFromCurrentPacking << std::endl;
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

//�������к���
void addLiveNode(unsigned short int a1, unsigned short int a2,
	unsigned short int a3, unsigned short int a4,
	unsigned short int a5, unsigned short int a6,
	unsigned short int a7
	, unsigned char b1, bbNode* b2, bool leftChild)
{
	bbNode *b = new bbNode(b2, leftChild);//д����λ��
	//heapNode a = heapNode(a1, a2, a3, a4, a5, a6, a7, b1, b2);
	liveNodeMaxHeap.push(heapNode(a1, a2, a3, a4, a5, a6, a7, b1, b));//���뵽�����
	//delete[] b;
}

//�����綨������������������1���������󣬹ʼ�
unsigned short int BranchBound::profitBound(unsigned char currentLevel, unsigned short int tttttt)
{
	//double *remainingCapacity = new double[10]();
	unsigned short int remainingCapacity = capacity[0] - tttttt;//����1��ʣ��ռ�
	/*remainingCapacity[1] = capacity[1] - w[1];
	remainingCapacity[2] = capacity[2] - w[2];
	remainingCapacity[3]= capacity[3] - w[3];
	remainingCapacity[4]= capacity[4] - w[4];*/
	unsigned short int profitBound = profitFromCurrentPacking;//��������

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

	//�����ܶ�*ʣ��ռ�
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