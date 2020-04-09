#include<iostream>
#include<algorithm>
const int numberOfObjects = 50;
int value[numberOfObjects] = { 560,1125,300,620,2100,431,68,328,47,122,322,196,41,25,425,4260,416,115,82,22,631,132,420,86,42,103,215,81,91,26,49,420,316,72,71,49,108,116,90,738,1811,430,3060,215,58,296,620,418,47,81 };//物品价值
int w1[numberOfObjects] = { 40,91,10, 30, 160, 20, 3, 12, 3, 18, 9, 25, 1, 1, 10, 280, 10, 8, 1, 1, 49, 8, 21,6 ,1,5, 10, 8, 2, 1, 0, 10, 42, 6, 4, 8, 0, 10 ,1, 40, 86, 11, 120, 8, 3, 32, 28, 13, 2, 4 };//物品限制条件1
int w2[numberOfObjects] = { 16, 92, 41, 16, 150, 23, 4, 18, 6, 0, 12, 8, 2, 1, 0, 200, 20, 6, 2, 1, 70, 9, 22 ,4,1 ,5,10, 6, 4, 0, 4, 12, 8, 4, 3, 0, 10, 0, 6, 28, 93, 9 ,30, 22 ,0, 36, 45, 13, 2 ,2 };//物品限制条件2
int w3[numberOfObjects] = { 38 ,39, 32, 71, 80, 26, 5, 40, 8, 12, 30, 15, 0, 1, 23, 100, 0, 20, 3, 0, 40, 6, 8, 0,6 ,4,22 ,4 ,6 ,1 ,5 ,14 ,8 ,2 ,8 ,0 ,20 ,0 ,0 ,6 ,12, 6 ,80 ,13 ,6 ,22 ,14 ,0 ,1 ,2 };//物品限制条件3
int w4[numberOfObjects] = { 8, 71, 30, 60, 200, 18, 6, 30, 4 ,8, 31, 6, 3, 0 ,18 ,60 ,21 ,4 ,0 ,2 ,32 ,15 ,31 ,2,2 ,7,8 ,2 ,8 ,0 ,2 ,8 ,6 ,7 ,1 ,0 ,0 ,20 ,8 ,14 ,20 ,2 ,40 ,6 ,1 ,14 ,20, 12 ,0 ,1 };//物品限制条件4
int w5[numberOfObjects] = { 38 ,52 ,30, 42, 170, 9, 7, 20, 0, 3, 21, 4, 1, 2, 14, 310, 8, 4, 6, 1, 18, 15, 38, 10,4 ,8,6 ,0 ,0 ,3 ,0 ,10 ,6 ,1 ,3 ,0 ,3 ,5 ,4 ,0 ,30 ,12 ,16 ,18 ,3 ,16 ,22 ,30 ,4 ,0 };//物品限制条件5
int condition[5] = { 800,650,550,550,650 };//背包限制条件
int **fArray;
int *x;
void knapsack(int *, int *, int , int* , int **);
void traceback(int **, int *, int , int* , int *);
int main()
{
	using namespace std;
	x = new int[50];
	fArray = new int *[800];
	for (int i = 0; i < 800; i++)
	{
		fArray[i] = new int[800];
	}
	knapsack(value, w1, numberOfObjects, condition, fArray);
	traceback(fArray, w1, numberOfObjects, condition, x);
	for (int i = 1; i < 51; i++)
	{
		std::cout << x[i] << std::endl;
	}
	system("pause");
	return 0;
}

int f(int i, int theCapacity)
{
	if (fArray[i][theCapacity] >= 0)
	{
		return fArray[i][theCapacity];
	}
	if (i == numberOfObjects)
	{
		fArray[i][theCapacity] = (theCapacity < w1[numberOfObjects] ? 0 : value[numberOfObjects]);
		return fArray[i][theCapacity];
	}
	if (theCapacity < w1[i])
	{
		fArray[i][theCapacity] = f(i + 1, theCapacity);
	}
	else
	{
		fArray[i][theCapacity] = std::max(f(i + 1, theCapacity), f(i + 1, theCapacity - w1[i]) + value[i]);
	}
	return fArray[i][theCapacity];
}

void knapsack(int *profit, int *weight, int numberOfObjects, int *knapsackCapacity, int **f)
{
	int yMax = std::min(weight[numberOfObjects] - 1, knapsackCapacity[0]);
	for (int y = 0; y <= yMax; y++)
	{
		f[numberOfObjects][y] = 0;
	}
	for (int y = weight[numberOfObjects]; y <= knapsackCapacity[0]; y++)
	{
		f[numberOfObjects][y] = profit[numberOfObjects];
	}
	for (int i = numberOfObjects - 1; i > 1; i--)
	{
		yMax = std::min(weight[i] - 1, knapsackCapacity[0]);
		for (int y = 0; y <= yMax; y++)
		{
			f[i][y] = f[i + 1][y];
		}
		for (int y = weight[i]; y <= knapsackCapacity[0]; y++)
		{
			f[i][y] = std::max(f[i + 1][y], f[i + 1][y - weight[i]] + profit[i]);
		}
	}
	f[1][knapsackCapacity[0]] = f[2][knapsackCapacity[0]];
	if (knapsackCapacity[0] >= weight[1])
	{
		f[1][knapsackCapacity[0]] = std::max(f[1][knapsackCapacity[0]], f[2][knapsackCapacity[0] - weight[1]] + profit[1]);
	}
}

void traceback(int **f, int *weight, int numberOfObjects, int *knapsackCapacity, int *x)
{
	for (int i = 1; i < numberOfObjects; i++)
	{
		if (f[i][knapsackCapacity[0]] == f[i + 1][knapsackCapacity[0]])
		{
			x[i] = 0;
		}
		else
		{
			x[i] = 1;
			knapsackCapacity[0] -= weight[i];
		}
		x[numberOfObjects] = (f[numberOfObjects][knapsackCapacity[0]] > 0) ? 1 : 0;
	}
}