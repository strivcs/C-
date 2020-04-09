class Backtracking
{
public:
	template<class T>
	double knapsack1(std::initializer_list<T> pl, std::initializer_list<T> cl, int theNumberOfObjects, 
		std::initializer_list<T> il, std::initializer_list<T> il2);
	void rKnap(int currentLevel);
	double profitBound(int currentLevel);
//protected:
	double *capacity;
	int numberOfObjects;
	double *condition1;
	double *condition2;
	double *profit;
	double *w=new double[10]();
	double profitFromCurrentPacking;
	double maxProfitSoFar;
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
		element(){}
		template<class T>
		T& operator[](int a);
		bool operator==(const Backtracking::element& x);
		bool operator!=(const Backtracking::element& x);
		bool operator<(const Backtracking::element& x);
		bool operator>(const Backtracking::element& x);
		bool operator<=(const Backtracking::element& x);
		bool operator>=(const Backtracking::element& x);
	};
};

template<class T>
void mergeSort(T[], int);
template<class T>
void mergePass(T[], T[], int, int);
template<class T>
void merge(T[], T[], int, int, int);
template<class T>
double Backtracking::knapsack1(std::initializer_list<T> pl, std::initializer_list<T> cl, int theNumberOfObjects,
	std::initializer_list<T> il, std::initializer_list<T> il2)
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
	element *q = new element [numberOfObjects];
	for (int i = 1; i <= numberOfObjects; i++)
	{		
		q[i - 1] = element(i, theProfit[i - 1] / wb[i - 1]);
	}

	mergeSort(q, numberOfObjects);
	
	profit = new double[numberOfObjects + 1];
	condition1 = new double[numberOfObjects + 1];
	condition2 = new double[numberOfObjects + 1];
	for (int i = 1; i <= numberOfObjects; i++)
	{
		profit[i] = theProfit[q[numberOfObjects - i].id - 1];
		condition1[i] = wa[q[numberOfObjects - i].id - 1];
		condition2[i] = wb[q[numberOfObjects - i].id - 1];
	}

	rKnap(1);
	return maxProfitSoFar;
}

void Backtracking::rKnap(int currentLevel)
{
	if (currentLevel > numberOfObjects)
	{
		maxProfitSoFar = profitFromCurrentPacking;
		return;
	}
	
	if ((w[0] + condition1[currentLevel] <= capacity[0]) &&
		(w[1] + condition2[currentLevel] <= capacity[1]))
	{
		w[0] += condition1[currentLevel];
		w[1] += condition2[currentLevel];
		profitFromCurrentPacking += profit[currentLevel];
		rKnap(currentLevel + 1);
		w[0] -= condition1[currentLevel];
		w[1] -= condition2[currentLevel];
		profitFromCurrentPacking -= profit[currentLevel];
	}

	if (profitBound(currentLevel + 1) > maxProfitSoFar)
	{
		rKnap(currentLevel + 1);
	}

}

double Backtracking::profitBound(int currentLevel)
{
	double remainingCapacity = capacity[1] - w[1];
	double profitBound = profitFromCurrentPacking;

	while ((currentLevel <= numberOfObjects) && (condition2[currentLevel] <= remainingCapacity))
	{
		remainingCapacity -= condition2[currentLevel];
		profitBound += profit[currentLevel];
		currentLevel++;
	}

	if (currentLevel <= numberOfObjects)
	{
		profitBound += (profit[currentLevel] / condition2[currentLevel]) * remainingCapacity;
	}
	return profitBound;
}

template<class T>
void mergeSort(T a[], int n)
{
	T *b = new T[n];
	int segmentSize = 1;
	while (segmentSize < n)
	{
		mergePass(a, b, n, segmentSize);
		segmentSize += segmentSize;
		mergePass(b, a, n, segmentSize);
		segmentSize += segmentSize;
	}
	delete[] b;
}

template<class T>
void mergePass(T x[], T y[], int n, int segmentSize)
{
	int i = 0;
	while (i <= n - 2 * segmentSize)
	{
		merge(x, y, i, i + segmentSize - 1, i + 2 * segmentSize - 1);
		i = i + 2 * segmentSize;
	}

	if (i + segmentSize < n)
	{
		merge(x, y, i, i + segmentSize - 1, n - 1);
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
void merge(T c[], T d[], int startOfFirst, int endOfFirst, int endOfSecend)
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
T& Backtracking::element::operator[](int a)
{
	return profitDensity;
}

bool Backtracking::element::operator<(const Backtracking::element& x)
{
	return profitDensity < x.profitDensity;
}

bool Backtracking::element::operator>(const Backtracking::element& x)
{
	return profitDensity > x.profitDensity;
}

bool Backtracking::element::operator<=(const Backtracking::element& x)
{
	return profitDensity <= x.profitDensity;
}

bool Backtracking::element::operator>=(const Backtracking::element& x)
{
	return profitDensity >= x.profitDensity;
}

bool Backtracking::element::operator==(const Backtracking::element& x)
{
	return profitDensity == x.profitDensity;
}

bool Backtracking::element::operator!=(const Backtracking::element& x)
{
	return profitDensity != x.profitDensity;
}
