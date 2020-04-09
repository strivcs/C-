#include <math.h>
#include <chrono>  
#include <time.h>
#include <iostream>
#define TF 0.1
#define T 0.99
const double T0 = 1000000;
#define N 50
#define M 50
int profit[M] = { 560,1125,300,620,2100,431,68,328,47,122,322,196,41,25,425,4260,416,115,82,22,631,132,420,86,42,103,215,81,91,26,49,420,316,72,71,49,108,116,90,738,1811,430,3060,215,58,296,620,418,47,81 },
	weight[M] = { 40,91,10, 30, 160, 20, 3, 12, 3, 18, 9, 25, 1, 1, 10, 280, 10, 8, 1, 1, 49, 8, 21,6 ,1,5, 10, 8, 2, 1, 0, 10, 42, 6, 4, 8, 0, 10 ,1, 40, 86, 11, 120, 8, 3, 32, 28, 13, 2, 4 },
	weight1[M]={ 16, 92, 41, 16, 150, 23, 4, 18, 6, 0, 12, 8, 2, 1, 0, 200, 20, 6, 2, 1, 70, 9, 22 ,4,1 ,5,10, 6, 4, 0, 4, 12, 8, 4, 3, 0, 10, 0, 6, 28, 93, 9 ,30, 22 ,0, 36, 45, 13, 2 ,2 }, 
	weight2[M]= { 38 ,39, 32, 71, 80, 26, 5, 40, 8, 12, 30, 15, 0, 1, 23, 100, 0, 20, 3, 0, 40, 6, 8, 0,6 ,4,22 ,4 ,6 ,1 ,5 ,14 ,8 ,2 ,8 ,0 ,20 ,0 ,0 ,6 ,12, 6 ,80 ,13 ,6 ,22 ,14 ,0 ,1 ,2 },
	weight3[M]= { 8, 71, 30, 60, 200, 18, 6, 30, 4 ,8, 31, 6, 3, 0 ,18 ,60 ,21 ,4 ,0 ,2 ,32 ,15 ,31 ,2,2 ,7,8 ,2 ,8 ,0 ,2 ,8 ,6 ,7 ,1 ,0 ,0 ,20 ,8 ,14 ,20 ,2 ,40 ,6 ,1 ,14 ,20, 12 ,0 ,1 },
	weight4[M]= { 38 ,52 ,30, 42, 170, 9, 7, 20, 0, 3, 21, 4, 1, 2, 14, 310, 8, 4, 6, 1, 18, 15, 38, 10,4 ,8,6 ,0 ,0 ,3 ,0 ,10 ,6 ,1 ,3 ,0 ,3 ,5 ,4 ,0 ,30 ,12 ,16 ,18 ,3 ,16 ,22 ,30 ,4 ,0 },
	condition[M]= { 800,650,550,550,650 };

int premaxp = 0, bestmaxp = 0;

int a[M] = { 0 }, preseq[M] = { 0 }, bestseq[M] = { 0 };

int calprofit(int a[M])
{
	int i = 0;
	int p = 0;
	for (i = 0; i < M; i++)
		p = p + (a[i] * profit[i]);

	return p;
}

int calweight(int a[M])
{
	int i = 0;
	int w = 0;
	for (i = 0; i < M; i++)
	{
		w = w + (weight[i] * a[i]);
	}
	return w;
}

int calweight1(int a[M])
{
	int i = 0;
	int w1 = 0;
	for (i = 0; i < M; i++)
	{
		w1 = w1 + (weight1[i] * a[i]);
	}
	return w1;
}

int calweight2(int a[M])
{
	int i = 0;
	int w2 = 0;
	for (i = 0; i < M; i++)
	{
		w2 = w2 + (weight2[i] * a[i]);
	}
	return w2;
}

int calweight3(int a[M])
{
	int i = 0;
	int w3 = 0;
	for (i = 0; i < M; i++)
	{
		w3 = w3 + (weight3[i] * a[i]);
	}
	return w3;
}

int calweight4(int a[M])
{
	int i = 0;
	int w4 = 0;
	for (i = 0; i < M; i++)
	{
		w4 = w4 + (weight4[i] * a[i]);
	}
	return w4;
}

void initialize(void)
{
	int i = 0;

	for (i = 0; i < M; i++)
	{
		a[i] = 0;
		preseq[i] = 0;
		bestseq[i] = 0;
	}
	premaxp = calprofit(a);
	bestmaxp = premaxp;
}

void getrand(int *i, int *j)
{
	*i = 0;
	*j = 0;
	
	while (*i == *j)
	{
		*i = rand() % 50;
		*j = rand() % 50;
	}
}

void change(void)
{
	int r1 = 0, r2 = 0;
	getrand(&r1, &r2);
	a[r1] = 1;
	a[r2] = 1;

	if (calweight(a) > condition[0]||
		calweight1(a) > condition[1]||
		calweight2(a) > condition[2]||
		calweight3(a) > condition[3]||
		calweight4(a) > condition[4])
	{
		a[r1] = 0;
		a[r2] = 0;		
	}
}

void SA(void)
{
	double t = T0;
	int i = 0, j = 0;
	int dif1 = 0, dif2 = 0;
	double p = 0.0;

	while (t > TF)
	{
		for (i = 0; i < N; i++)
		{
			change();

			dif1 = calprofit(a) - bestmaxp;
			if (dif1 > 0)
			{
				for (j = 0; j < M; j++)
				{
					preseq[j] = a[j];
					bestseq[j] = a[j];
				}
				premaxp = calprofit(a);
				bestmaxp = premaxp;
			}
			else
			{
				dif2 = calprofit(a) - premaxp;
				if (dif2 > 0)
				{
					for (j = 0; j < M; j++)
					{
						preseq[j] = a[j];
					}
					premaxp = calprofit(a);
				}
				else
				{
					p = rand() % 20001 / 20000.0;
					if (exp((dif2) / t) > p)
					{
						for (j = 0; j < M; j++)
						{
							preseq[j] = a[j];
						}
						premaxp = calprofit(a);
					}
					else
					{
						for (j = 0; j < M; j++)
						{
							a[j] = preseq[j];
						}
					}
				}
			}
		}

		t = t * T;
	}


}

int main(void)
{
	using namespace std;
	using namespace chrono;
	auto start = system_clock::now();
	int i;
	srand((unsigned)time(NULL));
	initialize();
	SA();
	for (i = 0; i < M; i++)
	{
		std::cout << bestseq[i];
		std::cout << " ";
	}
	std::cout << std::endl;
	std::cout << calweight(a) << " " << calweight1(a) << " "
		<< calweight2(a) << " "
		<< calweight3(a) << " "
		<< calweight4(a) << " " << std::endl;
	std::cout<<std::endl;
	std::cout << "The best value is: " << bestmaxp << std::endl;
	auto end = system_clock::now();
	auto duration = duration_cast<microseconds>(end - start);
	std::cout << "程序用时：" << double(duration.count()) * microseconds::period::num / microseconds::period::den << "s" << std::endl;
	system("pause");
	return 1;
}
