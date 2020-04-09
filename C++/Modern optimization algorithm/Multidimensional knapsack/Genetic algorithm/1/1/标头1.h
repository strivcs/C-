#include<iostream>
#include<string>
#include<stdlib.h>
#include<chrono>  
#include<random>	
using namespace std;
using namespace chrono;
using std::default_random_engine;
using std::uniform_real_distribution;
default_random_engine e(time(NULL));
static uniform_real_distribution<double> u(0, 1);
const unsigned short int PACK_MAX_W1 = 800;
const unsigned short int PACK_MAX_W2 = 650;
const unsigned short int PACK_MAX_W3 = 550;
const unsigned short int PACK_MAX_W4 = 550;
const unsigned short int PACK_MAX_W5 = 650;
const unsigned char NUM = 50;
const unsigned short int MAX_GENERATION = 5000;//遗传最大代数
const unsigned short int PS = 2000;        //种群规模
const float PC = 0.90;                      //交叉率
const float PV1 = 0.02;//个体变异率
const float PV2 = 0.05;//基因变异率

const int value[NUM] = { 560,1125,300,620,2100,431,68,328,47,122,322,196,41,25,425,4260,416,115,82,22,631,132,420,86,42,103,215,81,91,26,49,420,316,72,71,49,108,116,90,738,1811,430,3060,215,58,296,620,418,47,81 };
const int w1[NUM] = { 40,91,10, 30, 160, 20, 3, 12, 3, 18, 9, 25, 1, 1, 10, 280, 10, 8, 1, 1, 49, 8, 21,6 ,1,5, 10, 8, 2, 1, 0, 10, 42, 6, 4, 8, 0, 10 ,1, 40, 86, 11, 120, 8, 3, 32, 28, 13, 2, 4 };
const int w2[NUM] = { 16, 92, 41, 16, 150, 23, 4, 18, 6, 0, 12, 8, 2, 1, 0, 200, 20, 6, 2, 1, 70, 9, 22 ,4,1 ,5,10, 6, 4, 0, 4, 12, 8, 4, 3, 0, 10, 0, 6, 28, 93, 9 ,30, 22 ,0, 36, 45, 13, 2 ,2 };
const int w3[NUM] = { 38 ,39, 32, 71, 80, 26, 5, 40, 8, 12, 30, 15, 0, 1, 23, 100, 0, 20, 3, 0, 40, 6, 8, 0,6 ,4,22 ,4 ,6 ,1 ,5 ,14 ,8 ,2 ,8 ,0 ,20 ,0 ,0 ,6 ,12, 6 ,80 ,13 ,6 ,22 ,14 ,0 ,1 ,2 };
const int w4[NUM] = { 8, 71, 30, 60, 200, 18, 6, 30, 4 ,8, 31, 6, 3, 0 ,18 ,60 ,21 ,4 ,0 ,2 ,32 ,15 ,31 ,2,2 ,7,8 ,2 ,8 ,0 ,2 ,8 ,6 ,7 ,1 ,0 ,0 ,20 ,8 ,14 ,20 ,2 ,40 ,6 ,1 ,14 ,20, 12 ,0 ,1 };
const int w5[NUM] = { 38 ,52 ,30, 42, 170, 9, 7, 20, 0, 3, 21, 4, 1, 2, 14, 310, 8, 4, 6, 1, 18, 15, 38, 10,4 ,8,6 ,0 ,0 ,3 ,0 ,10 ,6 ,1 ,3 ,0 ,3 ,5 ,4 ,0 ,30 ,12 ,16 ,18 ,3 ,16 ,22 ,30 ,4 ,0 };
//随机产生01
int pp()
{
	float p;
	p = u(e);
	if (p < 0.5)
	{//cout<<0<<" ";
		return 0;
	}
	else
	{//cout<<1<<" ";
		return 1;
	}
}

//个体类
struct Entity
{
public:
	int fit;
	double average_affinity = 0;
	unsigned short int sum_w1;
	unsigned short int sum_w2;
	unsigned short int sum_w3;
	unsigned short int sum_w4;
	unsigned short int sum_w5;
	unsigned short int sum_val;
	bool gene[NUM];
	unsigned short int _count;
	Entity()
	{
		fit = 0;
		sum_w1 = 0;
		sum_w2 = 0;
		sum_w3 = 0;
		sum_w4 = 0;
		sum_w5 = 0;
		sum_val = 0;
		int i;
		for (i = 0; i < NUM; i++)
			gene[i] = 0;
	}
};

//遗传算法类
class GA
{
private:
	Entity zq[PS];                          //种群
	Entity max_single;                      //最优个体
public:
	void Init();
	//计算个体价值重量
	unsigned short int Cal_SingleValue(int id);
	unsigned short int Cal_SingleW1(int id);
	unsigned short int Cal_SingleW2(int id);
	unsigned short int Cal_SingleW3(int id);
	unsigned short int Cal_SingleW4(int id);
	unsigned short int Cal_SingleW5(int id);
	//计算个体适应度
	void Cal_Fitness();
	//计算价值最大个体
	void Cal_Maxval_Single(int _generation);
	//最佳抗体亲和力
	void Antibody_Affinity();
	//选择
	void Select();
	//是否交叉
	bool IsCross() { return (u(e) <= PC); }
	//交叉
	void Cross();
	//是否变异
	bool IsVariation() { return (u(e) <= PV1); }
	bool IsVariation2() { return (u(e) <= PV2); }
	//变异
	void Variation();
	//进行遗传，每代几率变异
	int Run()
	{
		auto start = system_clock::now();
		int i;
		//readData();
		Init();
		for (i = 0; i < MAX_GENERATION; i++)
		{
			Cal_Fitness();
			Cal_Maxval_Single(i);
			//Antibody_Affinity();
			Select();
			Cross();
			/*if (i % 5 == 0 && i != 0) {
				Variation();
			}*/
			Variation();
		}
		Cal_Fitness();
		Cal_Maxval_Single(MAX_GENERATION);
		//cout << "The best value is:" << max_single.fit << endl;
		//cout << "The best entity's gene is:" << endl;
		/*for (int i = 0; i < NUM; i++)
		{
			cout << max_single.gene[i];
			if (i != NUM - 1)
				cout << " ";
		}*/
		/*std::cout << std::endl;
		cout << max_single.sum_w1 << endl <<
			max_single.sum_w2 << endl <<
			max_single.sum_w3 << endl <<
			max_single.sum_w4 << endl <<
			max_single.sum_w5 << endl <<
			max_single.sum_val << endl;*/
			//cout << endl;
		cout << "The best entity is in the " << max_single._count << " generation." << "	";
		auto end = system_clock::now();
		auto duration = duration_cast<microseconds>(end - start);
		std::cout << "程序用时：" << double(duration.count()) * microseconds::period::num / microseconds::period::den << "s" << std::endl;
		return max_single.fit;
	}
};

void GA::Init()
{
	unsigned short int i, j, w1sum, w2sum, w3sum, w4sum, w5sum;
	for (i = 0; i < PS; i++)
	{
		w1sum = 0;
		w2sum = 0;
		w3sum = 0;
		w4sum = 0;
		w5sum = 0;
		for (j = 0; j < NUM; j++)
		{
			zq[i].gene[j] = pp();
			w1sum += zq[i].gene[j] * w1[j];
			w2sum += zq[i].gene[j] * w2[j];
			w3sum += zq[i].gene[j] * w3[j];
			w4sum += zq[i].gene[j] * w4[j];
			w5sum += zq[i].gene[j] * w5[j];
		}
		if (w1sum > PACK_MAX_W1 || w2sum > PACK_MAX_W2
			|| w3sum > PACK_MAX_W3 || w4sum > PACK_MAX_W4
			|| w5sum > PACK_MAX_W5)    //产生符合条件的个体
		{
			i--;
		}
	}
}

unsigned short int GA::Cal_SingleValue(int id)
{
	int j, valuesum = 0;
	for (j = 0; j < NUM; j++)
	{
		valuesum += zq[id].gene[j] * value[j];
	}
	zq[id].sum_val = valuesum;
	return valuesum;
}

unsigned short int GA::Cal_SingleW1(int id)
{
	int j, w1sum = 0;
	for (j = 0; j < NUM; j++)
	{
		w1sum += zq[id].gene[j] * w1[j];
	}
	zq[id].sum_w1 = w1sum;
	return w1sum;
}
unsigned short int GA::Cal_SingleW2(int id)
{
	int j, w2sum = 0;
	for (j = 0; j < NUM; j++)
	{
		w2sum += zq[id].gene[j] * w2[j];
	}
	zq[id].sum_w2 = w2sum;
	return w2sum;
}
unsigned short int GA::Cal_SingleW3(int id)
{
	int j, w3sum = 0;
	for (j = 0; j < NUM; j++)
	{
		w3sum += zq[id].gene[j] * w3[j];
	}
	zq[id].sum_w3 = w3sum;
	return w3sum;
}
unsigned short int GA::Cal_SingleW4(int id)
{
	int j, w4sum = 0;
	for (j = 0; j < NUM; j++)
	{
		w4sum += zq[id].gene[j] * w4[j];
	}
	zq[id].sum_w4 = w4sum;
	return w4sum;
}

unsigned short int GA::Cal_SingleW5(int id)
{
	int j, w5sum = 0;
	for (j = 0; j < NUM; j++)
	{
		w5sum += zq[id].gene[j] * w5[j];
	}
	zq[id].sum_w5 = w5sum;
	return w5sum;
}

void GA::Cal_Fitness()
{
	int i, val, a1, a2, a3, a4, a5;
	for (i = 0; i < PS; i++)
	{
		a1 = Cal_SingleW1(i);
		a2 = Cal_SingleW2(i);
		a3 = Cal_SingleW3(i);
		a4 = Cal_SingleW4(i);
		a5 = Cal_SingleW5(i);
		val = Cal_SingleValue(i);
		if (a1 > PACK_MAX_W1 || a2 > PACK_MAX_W2
			|| a3 > PACK_MAX_W3 || a4 > PACK_MAX_W4
			|| a5 > PACK_MAX_W5)
		{
			zq[i].fit = 0;
			continue;
		}
		zq[i].fit = val;
		//cout<<zq[i].fit<<endl;
	}
}

void GA::Cal_Maxval_Single(int _generation)
{
	int i, maxval = zq[0].fit, id = 0;
	for (i = 0; i < PS; i++)
		if (maxval < zq[i].fit)
		{
			maxval = zq[i].fit;
			id = i;
		}
	if (maxval > max_single.fit)
	{
		max_single = zq[id];
		max_single._count = _generation;
	}
}

void GA::Antibody_Affinity()
{
	int same = 0;
	for (int i = 0; i < PS; i++)
	{
		//if(i!=)
		for (int j = 0; j < NUM; j++)
		{
			//same += ~zq[i].gene[j] ^ max_single.gene[j];
			if (zq[i].gene[j] == max_single.gene[j])
			{
				same++;
			}
			if (same == 50) { same = 50; }
			zq[i].average_affinity = (double)same / 50.0;
		}
		same = 0;
	}
}

void GA::Select()
{
	int i, j;
	double  fit_sum = 0;
	float rand_rate, cur_rate;
	float selected_rate[PS];
	Entity new_zq[PS];

	for (i = 0; i < PS; i++)
	{
		fit_sum += zq[i].fit / 2000;
	}
	//使用轮赌法进行选择
	selected_rate[0] = zq[0].fit  / fit_sum;

	for (i = 1; i < PS; i++)
	{
		cur_rate = selected_rate[i - 1] + zq[i].fit  / fit_sum;
		selected_rate[i] = cur_rate;
	}

	for (i = 0; i < PS; i++)
	{
		rand_rate = u(e);
		for (j = 0; j < PS; j++)
		{
			if (rand_rate <= selected_rate[j])
			{
				new_zq[i] = zq[j];
				break;
			}
		}
	}
	for (i = 0; i < PS; i++)
	{
		zq[i] = new_zq[i];
		//cout<<zq[i].fit<<endl;
	}

}

void GA::Cross()
{
	int i, j;
	for (i = 0; i < PS - 1; i += 2)
	{
		Entity en1 = zq[i];
		Entity en2 = zq[i + 1];
		for (j = 0; j < NUM; j++)
		{
			if (IsCross())
			{
				int tmp = en1.gene[j];
				en1.gene[j] = en2.gene[j];
				en2.gene[j] = tmp;
			}
		}
		zq[i] = en1;
		zq[i + 1] = en2;
	}
}

void GA::Variation()
{
	int i, j;
	for (i = 0; i < PS; i++)
	{
		if (IsVariation())
		{
			for (j = 0; j < NUM; j++)
			{
				if (IsVariation2())
				{
					zq[i].gene[j] = zq[i].gene[j] ? 0 : 1;
				}
			}
		}
	}
}
