#include<iostream>
#include<algorithm>
#include<string>
#include<stdlib.h>
#include<chrono>
#include<random>
using namespace std;
using namespace chrono;
using std::default_random_engine;
using std::uniform_real_distribution;
static default_random_engine e(time(0));
static uniform_real_distribution<double> u(0, 1);
int bestnumber = 0;
int temp_Maxvalue = 0;//PSO����
int temp_time1 = 0;//PSO����
int temp_time2 = 0;//PSO����
int temp_time3 = 0;//PSO����
int out = 0;
int temp_length = 0;//��¼��¡�����Ⱥ����
int TIMES = 0;//�ܵ�������
int Maxvalue = 0;//�������
int up = 1;//����Ⱥ�㷨����
const double T0 = 200.0;//����
const int Num = 50;//��Ʒ����
const int Iteration_times = 1000;//��������
const double T = 0.98;//�¶ȱ仯��
const double TF = 0.01;//��ֹ�¶�
const double N = 1000;//��������
const int PS = 2000;//Population Size,��Ⱥ��ģ
const double Random_rate = 0.5;//�����������������
const double PC1 = 0.92;//���򽻲���
const double PC2 = 0.92;//���彻����
double PV1 = 0.02;//���������
double PV2 = 0.06;//���������
const int value[Num] = { 560,1125,300,620,2100,431,68,328,47,122,322,196,41,25,425,4260,416,115,82,22,631,132,420,86,42,103,215,81,91,26,49,420,316,72,71,49,108,116,90,738,1811,430,3060,215,58,296,620,418,47,81 };//��Ʒ��ֵ
const int w1[Num] = { 40,91,10, 30, 160, 20, 3, 12, 3, 18, 9, 25, 1, 1, 10, 280, 10, 8, 1, 1, 49, 8, 21,6 ,1,5, 10, 8, 2, 1, 0, 10, 42, 6, 4, 8, 0, 10 ,1, 40, 86, 11, 120, 8, 3, 32, 28, 13, 2, 4 };//��Ʒ��������1
const int w2[Num] = { 16, 92, 41, 16, 150, 23, 4, 18, 6, 0, 12, 8, 2, 1, 0, 200, 20, 6, 2, 1, 70, 9, 22 ,4,1 ,5,10, 6, 4, 0, 4, 12, 8, 4, 3, 0, 10, 0, 6, 28, 93, 9 ,30, 22 ,0, 36, 45, 13, 2 ,2 };//��Ʒ��������2
const int w3[Num] = { 38 ,39, 32, 71, 80, 26, 5, 40, 8, 12, 30, 15, 0, 1, 23, 100, 0, 20, 3, 0, 40, 6, 8, 0,6 ,4,22 ,4 ,6 ,1 ,5 ,14 ,8 ,2 ,8 ,0 ,20 ,0 ,0 ,6 ,12, 6 ,80 ,13 ,6 ,22 ,14 ,0 ,1 ,2 };//��Ʒ��������3
const int w4[Num] = { 8, 71, 30, 60, 200, 18, 6, 30, 4 ,8, 31, 6, 3, 0 ,18 ,60 ,21 ,4 ,0 ,2 ,32 ,15 ,31 ,2,2 ,7,8 ,2 ,8 ,0 ,2 ,8 ,6 ,7 ,1 ,0 ,0 ,20 ,8 ,14 ,20 ,2 ,40 ,6 ,1 ,14 ,20, 12 ,0 ,1 };//��Ʒ��������4
const int w5[Num] = { 38 ,52 ,30, 42, 170, 9, 7, 20, 0, 3, 21, 4, 1, 2, 14, 310, 8, 4, 6, 1, 18, 15, 38, 10,4 ,8,6 ,0 ,0 ,3 ,0 ,10 ,6 ,1 ,3 ,0 ,3 ,5 ,4 ,0 ,30 ,12 ,16 ,18 ,3 ,16 ,22 ,30 ,4 ,0 };//��Ʒ��������5
const int condition[5] = { 800,650,550,550,650 };//������������
struct antibody
{
	int gene[Num];//����
	double average_affinity;//ƽ�������׺���
	int antibody_affinity;//��ԭ�׺���
	antibody()
	{
		average_affinity = 0;
		antibody_affinity = 0;
		for (int i = 0; i < Num; i++)
		{
			gene[i] = 0;	
		}
	}
};

class Antibody
{
public:
	//��ʼ��ÿ������Ļ���
	void Init();
	//��������
	void ReInit();
	//�����������
	int Random_Gene();
	//���㿹���뿹��֮����׺���
	double Antibody_Affinity(int number1, int number2);
	//����ĳ�����ƽ���׺���***(�˴�������������Сʱ�临�Ӷ�)
	double Average_Antibody_Affinity(int number);
	//���㿹���뿹ԭ֮����׺���
	int Antigen_Affinity(int number);
	//�жϿ����Ƿ�����
	double IsTolerance(int number);
	//ѡ��
	void Select();
	//��¡���壬��ԭ�׺���Խ�ߣ������׺���Խ��Խ�п��ܱ���¡
	void Clone();
	//����
	void Cross();
	//����
	void Variation();
	//���
	void Start();
	//���¼���ϸ��
	void Update();
private:
	//antibody best;
	antibody pp[PS];
};

void Antibody::Start()
{
	Init();
	//auto start = system_clock::now();
	//auto end = system_clock::now();
	//auto duration = duration_cast<microseconds>(end - start);
	while (TIMES <= Iteration_times)
	{
		//start = system_clock::now();
		TIMES++;
		for (int i = 0; i < PS; i++)
		{
			Antigen_Affinity(i);
			//Average_Antibody_Affinity(i);
		}
		//Update();
		//if (temp_Maxvalue == Maxvalue)
		//{
		//	temp_time1++;
		//	temp_time3++;
		//}
		//else
		//{
		//	temp_Maxvalue = Maxvalue;
		//	temp_time1 = 0;
		//	temp_time3 = 0;
		//	out = 0;
		//}
		//if (temp_time3 == 200)
		//{
		//	up = 1;
		//	PV1 = 0.7;
		//	PV2 = 0.7;
		//	out++;
		//	temp_time3 = 0;
		//}
		//if (temp_time1 == 50)
		//{
		//	up = 1.5;
		//	temp_time1 = 0;
		//	temp_time2 = 1;
		//	PV1 = 0.5;
		//	PV2 = 0.5;
		//}
		//if (temp_time2 == 1&& temp_time1==1&&temp_time3==1)
		//{
		//	up = 1;
		//	temp_time2 = 0;
		//	PV1 = 0.2;
		//	PV2 = 0.2;
		//}
		//if (out == 10)
		//{
		//	break;
		//}
		Select();
		//std::cout << temp_time1 << " " << temp_time2 << " " << temp_time3 << " " << out << std::endl;
		//end = system_clock::now();
		//duration = duration_cast<microseconds>(end - start);
		//std::cout << "������ʱ��" << double(duration.count()) * microseconds::period::num / microseconds::period::den << "s" << std::endl;
		
		//Clone();

		//ReInit();

		//end = system_clock::now();
		//duration = duration_cast<microseconds>(end - start);
		//std::cout << "������ʱ��" << double(duration.count()) * microseconds::period::num / microseconds::period::den << "s" << std::endl;

		Cross();

		Variation();
		

		
		//end = system_clock::now();
		//duration = duration_cast<microseconds>(end - start);
		//std::cout << "������ʱ��" << double(duration.count()) * microseconds::period::num / microseconds::period::den << "s" << std::endl;
		//ReInit();
	}
	std::cout << TIMES << std::endl;
	std::cout <<"�������: "<<Maxvalue << std::endl;
}

//��ʼ������
void Antibody::Init()
{
	int w1sum, w2sum, w3sum, w4sum, w5sum;//�������������ܺ�
	for (int i = 0; i < PS; i++)
	{
		w1sum = 0;
		w2sum = 0;
		w3sum = 0;
		w4sum = 0;
		w5sum = 0;
		for (int j = 0; j < Num; j++)
		{
			pp[i].gene[j] = Random_Gene();
			w1sum += pp[i].gene[j] * w1[j];
			w2sum += pp[i].gene[j] * w2[j];
			w3sum += pp[i].gene[j] * w3[j];
			w4sum += pp[i].gene[j] * w4[j];
			w5sum += pp[i].gene[j] * w5[j];
		}
		if (w1sum > condition[0] || w2sum > condition[1]
			|| w3sum > condition[2] || w4sum > condition[3]
			|| w5sum > condition[4])    //�������������ĸ���
		{
			i--;
		}
	}
}

void Antibody::ReInit()
{
	int w1sum, w2sum, w3sum, w4sum, w5sum;//�������������ܺ�
	for (; temp_length < PS; temp_length++)
	{
		w1sum = 0;
		w2sum = 0;
		w3sum = 0;
		w4sum = 0;
		w5sum = 0;
		for (int j = 0; j < Num; j++)
		{
			pp[temp_length].gene[j] = Random_Gene();
			w1sum += pp[temp_length].gene[j] * w1[j];
			w2sum += pp[temp_length].gene[j] * w2[j];
			w3sum += pp[temp_length].gene[j] * w3[j];
			w4sum += pp[temp_length].gene[j] * w4[j];
			w5sum += pp[temp_length].gene[j] * w5[j];
		}
		if (w1sum > condition[0] || w2sum > condition[1]
			|| w3sum > condition[2] || w4sum > condition[3]
			|| w5sum > condition[4])    //�������������ĸ���
		{
			temp_length--;
		}
	}
}

int Antibody::Random_Gene()
{
	return (u(e) < Random_rate) ? 1 : 0;//��������ʷ���0-1
}

int Antibody::Antigen_Affinity(int number)
{
	int affinity = 0;

	int a = IsTolerance(number);
	if (a == -1)
	{
		pp[number].antibody_affinity = 0;
		pp[number].average_affinity = 0;
		return affinity;
	}
	for (int i = 0; i < Num; i++)
	{
		affinity += pp[number].gene[i] * value[i];
	}
	if (affinity >= Maxvalue)
	{
		//best = pp[number];
		bestnumber = number;
		Maxvalue = affinity;
		std::cout << "��ǰ��������: " << TIMES << std::endl;
		std::cout << "�������: " << Maxvalue << std::endl;
	}
	pp[number].antibody_affinity = affinity;
	return affinity;
}

double Antibody::Average_Antibody_Affinity(int number)
{
	double temp = 0;
	//for (int i = 0; i < PS; i++)
	//{
	//	temp += Antibody_Affinity(number, i);
	//}
	temp = Antibody_Affinity(number, bestnumber);
	pp[number].average_affinity = temp;
	return temp;
}

double Antibody::Antibody_Affinity(int number1, int number2)
{
	int temp = 0;
	for (int i = 0; i < Num; i++)
	{
		temp += (pp[number1].gene[i] == pp[number2].gene[i]);
	}
	return temp / (double)Num;
}

double Antibody::IsTolerance(int number)
{
	int w1sum = 0,
		w2sum = 0,
		w3sum = 0,
		w4sum = 0, 
		w5sum = 0;
	for (int i = 0; i < Num; i++)
	{
		w1sum += pp[number].gene[i] * w1[i];
		w2sum += pp[number].gene[i] * w2[i];
		w3sum += pp[number].gene[i] * w3[i];
		w4sum += pp[number].gene[i] * w4[i];
		w5sum += pp[number].gene[i] * w5[i];
	}
	if (w1sum > condition[0] || w2sum > condition[1]
		|| w3sum > condition[2] || w4sum > condition[3]
		|| w5sum > condition[4])
	{
		return -1;
	}
	else
	{
		return 0;
	}
}

void Antibody::Select()
{
	int fit_sum = 0, i, j;
	double rand_rate;//���0-1
	double cur_rate;//�ۼƸ���
	double selected_rate[PS];//ѡ�����
	antibody new_zq[PS];
	for (i = 0; i < PS; i++) 
	{
		fit_sum += pp[i].antibody_affinity ;
	}
	//ʹ���ֶķ�����ѡ��
	selected_rate[0] = pp[0].antibody_affinity/ fit_sum;
	for (i = 1; i < PS; i++) 
	{
		cur_rate = selected_rate[i - 1] + (double)pp[i].antibody_affinity/fit_sum;
		selected_rate[i] = cur_rate;
	}
	for (i = 0; i < PS; i++)
	{
		for (j = 0; j < PS; j++) 
		{
			if (u(e) <= selected_rate[j])
			{
				new_zq[i] = pp[j];
				break;
			}
		}
	}
	for (i = 0; i < PS; i++) 
	{
		pp[i] = new_zq[i];
		//cout<<zq[i].fit<<endl;
	}
}

void Antibody::Clone()
{
	double total_average_affinity = 0.0;//Ⱥ��ƽ�������׺���
	int average_antibody_affinity = 0;//Ⱥ��ƽ����ԭ�׺���
	for (int i = 0; i < PS; i++)
	{
		total_average_affinity += pp[i].average_affinity;
		average_antibody_affinity += pp[i].antibody_affinity;
	}
	total_average_affinity /= (double)PS;
	average_antibody_affinity /= (double)PS;
	temp_length = 0;
	for (int i = 0; i < PS; i++)
	{
		double random = 0.1*u(e) + 0.95;
		if ((pp[i].antibody_affinity)*(1 - pp[i].average_affinity)*random >
			total_average_affinity*average_antibody_affinity)
		{		
			pp[temp_length] = pp[i];
			temp_length++;
		}
	}
}


void Antibody::Cross()
{
	int i, j;
	for (i = 0; i < PS - 1; i += 2)
	{
		antibody en1 = pp[i];
		antibody en2 = pp[i + 1];

		for (j = 0; j < Num; j++)
		{
			if (u(e) <= PC1)
			{
				int tmp = en1.gene[j];
				en1.gene[j] = en2.gene[j];
				en2.gene[j] = tmp;
			}
		}
		pp[i] = en1;
		pp[i + 1] = en2;
	}
}


void Antibody::Variation()
{
	for (int i = 0; i < PS; i++) 
	{
		if (u(e) <= PV1)
		{
			for (int j = 0; j < Num; j++)
			{
				if (u(e) <= PV2) 
				{
					pp[i].gene[j] = pp[i].gene[j] ? 0 : 1;
				}
			}
		}
	}
}

void Antibody::Update()
{
	double MaxSimilarity = 0.0;
	int id = 0;
	for (int i = 0; i < PS; i++)
	{
		if (pp[i].antibody_affinity >= 0.8*Maxvalue)
		{
			for (int j = 0; (j < PS) && (j != i); j++)
			{
				double Similarity = Antibody_Affinity(i, j);
				if (Similarity >= MaxSimilarity)
				{
					id = j;
					MaxSimilarity = Similarity;
				}
			}
			pp[id] = pp[i];
		}
	}
}
