#include<iostream>
#include<vector>
#include<chrono>
#include<time.h>
#include"contagion.h"
//strivcs
int SCALE = 2917 + 2;//Ԫ���ռ��ģ,�ο�ŦԼ�����˿�
int TIME = 100;//Ԥ��ʱ��
int Control_Start = 33;//ŦԼ��������ʼ�ܿص�ʱ��
int T1 = 10;//����ʱ��
int T2 = TIME;//ʧȥ����ʱ��,�ٶ���������
double infection_rate1 = 0.5;
double infection_rate2 = 0.1;
double disobedience = 0.2;//������ߵ���������
double disobedience2 = 0.1;//��ʼ�ܿغ�
int length = 10;//������ߵĳ���(���Է�ӳ�Ӵ�������)
int length2 = 5;//��ʼ�ܿغ�
int b[200];
int c[200];
int main()
{
	using namespace std;
	using namespace chrono;	
	srand(time(NULL));
	auto start = system_clock::now();
	int infected_number = 1;//��ǰ��Ⱦ����
	int total_number = 1;//�ܸ�Ⱦ����
	int **a;//Ԫ���ռ�a
	a = new int *[SCALE];	
	for (int i = 0; i < SCALE; i++)
	{
		a[i] = new int[SCALE];
	}
	for (int i = 0; i < SCALE; i++)
	{
		for (int j = 0; j < SCALE; j++)
		{
			a[i][j] = 0;
		}
	}
	a[(int)floor(SCALE / 2)][(int)floor(SCALE / 2)] = 1;//����Ԫ���ռ�����Ϊ��ȾԴ
	int **timer;//��ʱ��������Ԫ��״̬ת��
	timer = new int *[SCALE];
	for (int i = 0; i < SCALE; i++)
	{
		timer[i] = new int[SCALE];
	}
	for (int i = 0; i < SCALE; i++)
	{
		for (int j = 0; j < SCALE; j++)
		{
			timer[i][j] = 0;
		}
	}
	timer[(int)floor(SCALE / 2)][(int)floor(SCALE / 2)] = 0;//����Ԫ���ռ�����Ϊ��ȾԴ
	cout<<"�ִ没��Ԥ�����ܲ�������Ԥ�⣺"<<endl;
	for (int i = 0; i < Control_Start; i++)
	{
		timelapse(a, timer, infected_number, SCALE, T1, T2, infection_rate1, infection_rate2, disobedience, length, total_number);//ʱ�俪ʼ����
		b[i] = infected_number;
		c[i] = total_number;
		cout << "\t��" << i + 1 << "���ִ�" << infected_number << "������ȷ��" << total_number << "��" << endl;
	}
	for (int i = Control_Start; i < TIME; i++)
	{
		//�ܿؿ�ʼ����������ʶ�������ԣ����������߶�
		disobedience = disobedience2 * pow(0.9, i);
		length = length2 * pow(0.9, i);

		timelapse(a, timer, infected_number, SCALE, T1, T2, infection_rate1, infection_rate2, disobedience, length, total_number);//ʱ�俪ʼ����
		b[i] = infected_number;
		c[i] = total_number;
		cout << "\t��" << i + 1 << "���ִ�" << infected_number << "������ȷ��" << total_number << "��" << endl;
	}
	for (int i = 0; i < TIME; i++)
	{
		cout << b[i] << endl;
	}
	for (int i = 0; i < TIME; i++)
	{
		cout << c[i] << endl;
	}

	auto end = system_clock::now();
	auto duration = duration_cast<microseconds>(end - start);
	cout << "��������ʱ��: " << double(duration.count()) * microseconds::period::num / microseconds::period::den << "s" << endl;

	system("pause");
}

