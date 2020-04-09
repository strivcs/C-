/*
���ݷ��������������˼��
STL������
	initializer_list����ʼ���б����ģ�������
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
	void rKnap(int currentLevel);//�����㺯��
	double profitBound(int currentLevel);//�������纯��
	double *capacity;//��������Pj
	int numberOfObjects;//��Ʒ����
	double *condition1;//����Ʒ�Ĳ���1
	double *condition2;//����Ʒ�Ĳ���2
	double *condition3;//����Ʒ�Ĳ���3
	double *condition4;//����Ʒ�Ĳ���4
	double *condition5;//����Ʒ�Ĳ���5
	double *profit;//����Ʒ������
	double *w = new double[10]();//Ҷ���·����������
	double profitFromCurrentPacking;//���·����������
	double maxProfitSoFar;//������������
	double *answer = new double[60]();//��¼���Ž�
	//��ʱ�����Ʒ�����Ľṹ�����ڹ鲢����
	struct element
	{
		int id;//��¼λ��
		double profitDensity;//�����ܶ�
		//���캯��
		template<class T>
		element(int i, T p)
		{
			id = i;
			profitDensity = (double)p;
		}
		//Ĭ�Ϲ��캯��
		element() {}
		//���ز�����
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
double MAX = 0;//��¼ͻ�ƺ�����ǰ���ֵ��ֵ���������
//�鲢������
template<class T>
void mergeSort2(T[], int);
template<class T>
void mergePass2(T[], T[], int, int);
template<class T>
void merge2(T[], T[], int, int, int);
//��ֵ������
template<class T>
double Backtracking2::knapsack2(std::initializer_list<T> pl, std::initializer_list<T> cl, int theNumberOfObjects,
	std::initializer_list<T> il, std::initializer_list<T> il2,
	std::initializer_list<T> il3, std::initializer_list<T> il4,
	std::initializer_list<T> il5)
{
	numberOfObjects = theNumberOfObjects;
	profitFromCurrentPacking = 0.0;
	maxProfitSoFar = 0.0;
	//����ʼ���б����ֵ��¼����Ӧ����ָ�룬ptr0~ptr6
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
	//ͬ��
	double *theProfit = new double[pl.size()];
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
	double *wb = new double[il2.size()];
	auto ptr3 = il2.begin();
	i = 0;
	while (ptr3 != il2.end())
	{
		wb[i] = *ptr3;
		ptr3++;
		i++;
	}
	//ͬ��
	double *wc = new double[il3.size()];
	auto ptr4 = il3.begin();
	i = 0;
	while (ptr4 != il3.end())
	{
		wc[i] = *ptr4;
		ptr4++;
		i++;
	}
	//ͬ��
	double *wd = new double[il4.size()];
	auto ptr5 = il4.begin();
	i = 0;
	while (ptr5 != il4.end())
	{
		wd[i] = *ptr5;
		ptr5++;
		i++;
	}
	//ͬ��
	double *we = new double[il5.size()];
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
	for (int i = 1; i <= numberOfObjects; i++)
	{
		q[i - 1] = element(i, theProfit[i - 1] / wb[i - 1]);
	}

	//�鲢���򣬰��������ܶ�����
	mergeSort2(q, numberOfObjects);

	//��ʼ�������鲢������������ϵ�����
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

	rKnap(1);//�����㺯��
	std::cout << "���������д�����" << x << std::endl;
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
	return maxProfitSoFar;
}

//�����㺯��
void Backtracking2::rKnap(int currentLevel)
{
	x++;//��¼����
	//������ֵ����ʱ��������������󣬲�������һ��E-��㣬��ʱ����Ҷ���
	if (currentLevel > numberOfObjects)
	{
		maxProfitSoFar = profitFromCurrentPacking;
		MAX = std::max(MAX, profitFromCurrentPacking);
		if ((MAX == profitFromCurrentPacking) && (MAX >= 16537))
		{
			std::cout << "�ѵ�������: " << x << "��!" << std::endl;
			std::cout << "�������: " << MAX << std::endl;
			for (int o = 1; o < 51; o++)
			{
				std::cout << answer[o] << " ";
			}
			std::cout << std::endl;
		}
		else if ((MAX == profitFromCurrentPacking) && (MAX < 16537))
		{
			std::cout << "�ѵ�������: " << x << "��!" << std::endl;
			std::cout << "�������: " << MAX << std::endl;
		}
		return;
	}

	//δ����Ҷ���ʱ�����������������������飬�������ñ����綨�������
	//����������
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

	//����������
	if (profitBound(currentLevel + 1) > maxProfitSoFar)
	{
		rKnap(currentLevel + 1);
	}
}

//�����綨������������������1���������󣬹ʼ�
double Backtracking2::profitBound(int currentLevel)
{
	//double *remainingCapacity = new double[10]();
	double remainingCapacity = capacity[1] - w[1];//����1��ʣ��ռ�
	/*remainingCapacity[1] = capacity[1] - w[1];
	remainingCapacity[2] = capacity[2] - w[2];
	remainingCapacity[3]= capacity[3] - w[3];
	remainingCapacity[4]= capacity[4] - w[4];*/
	double profitBound = profitFromCurrentPacking;//��������

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

	//�����ܶ�*ʣ��ռ�
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