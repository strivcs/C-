#include<iostream>
#include<vector>
#include<chrono>
#include<time.h>
#include"contagion.h"
//strivcs
int SCALE = 2917 + 2;//元胞空间规模,参考纽约城市人口
int TIME = 100;//预测时间
int Control_Start = 33;//纽约市政府开始管控的时间
int T1 = 10;//治愈时间
int T2 = TIME;//失去免疫时间,假定永久免疫
double infection_rate1 = 0.5;
double infection_rate2 = 0.1;
double disobedience = 0.2;//随机游走的人数概率
double disobedience2 = 0.1;//开始管控后
int length = 10;//随机游走的长度(可以反映接触的人数)
int length2 = 5;//开始管控后
int b[200];
int c[200];
int main()
{
	using namespace std;
	using namespace chrono;	
	srand(time(NULL));
	auto start = system_clock::now();
	int infected_number = 1;//当前感染人数
	int total_number = 1;//总感染人数
	int **a;//元胞空间a
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
	a[(int)floor(SCALE / 2)][(int)floor(SCALE / 2)] = 1;//设置元胞空间中心为传染源
	int **timer;//计时器，控制元胞状态转换
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
	timer[(int)floor(SCALE / 2)][(int)floor(SCALE / 2)] = 0;//设置元胞空间中心为传染源
	cout<<"现存病例预测与总病例数量预测："<<endl;
	for (int i = 0; i < Control_Start; i++)
	{
		timelapse(a, timer, infected_number, SCALE, T1, T2, infection_rate1, infection_rate2, disobedience, length, total_number);//时间开始推移
		b[i] = infected_number;
		c[i] = total_number;
		cout << "\t第" << i + 1 << "天现存" << infected_number << "例，总确诊" << total_number << "例" << endl;
	}
	for (int i = Control_Start; i < TIME; i++)
	{
		//管控开始后，人们逐渐意识到严重性，慢慢不再走动
		disobedience = disobedience2 * pow(0.9, i);
		length = length2 * pow(0.9, i);

		timelapse(a, timer, infected_number, SCALE, T1, T2, infection_rate1, infection_rate2, disobedience, length, total_number);//时间开始推移
		b[i] = infected_number;
		c[i] = total_number;
		cout << "\t第" << i + 1 << "天现存" << infected_number << "例，总确诊" << total_number << "例" << endl;
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
	cout << "程序运行时间: " << double(duration.count()) * microseconds::period::num / microseconds::period::den << "s" << endl;

	system("pause");
}

