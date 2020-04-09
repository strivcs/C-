//判断是否被传染
template<class T>
void is_contagion(T &a, int i, int j, int &infected_number, double infection_rate1, double infection_rate2, int &total_number)
{
	float p;
	p = infection_rate1 * (a[i - 1][j] % 2, a[i][j - 1] % 2, a[i][j + 1] % 2, a[i + 1][j] % 2) +
		infection_rate2 * (a[i - 1][j - 1] % 2, a[i - 1][j + 1] % 2, a[i + 1][j - 1] % 2, a[i + 1][j + 1] % 2);
	if ((rand() % 1000 / (float)1000) < p)
	{
		a[i][j] = 1;
		infected_number += 1;
		total_number += 1;
	}
}

template<class T>
void timelapse(T &a, T &timer, int &infected_number, int scale, int T1, int T2, double infection_rate1, double infection_rate2, double disobedience, int length, int &total_number)
{
	//最外一圈不考虑
	for (int i = 1; i < scale - 1; i++)
	{
		for (int j = 1; j < scale - 1; j++)
		{
			//若为易感状态，判断当天是否会被传染
			if (a[i][j] == 0)
			{
				is_contagion(a, i, j, infected_number, infection_rate1, infection_rate2, total_number);
			}
			//若为感染状态，判断当天是否治愈
			else if(a[i][j] == 1)
			{
				timer[i][j] += 1;
				if (timer[i][j] >= T1)
				{
					a[i][j] = 2;
					infected_number -= 1;
					timer[i][j] = 0;
				}
			}
			//若为免疫状态，判断免疫时间是否结束
			else if (a[i][j] == 2)
			{
				timer[i][j] += 1;
				if (timer[i][j] >= T2)
				{
					a[i][j] = 0;
					timer[i][j] = 0;
				}
			}
		}
	}

	// 随机游走
	for (int i = 1; i < scale - 1; i++)
	{
		for (int j = 1; j < scale - 1; j++)
		{
			if ((rand() % 1000 / (float)1000) < disobedience)
			{
				int dx = (int)std::round(2 * length *(rand() % 1000 / (float)1000)) - length;
				int dy = (int)std::round(2 * length *(rand() % 1000 / (float)1000)) - length;
				if ((i + dx) > 1 and (i + dx) < scale - 1)
				{
					if ((i + dy) > 1 and (i + dy) < scale - 1)
					{
						int m1 = a[i][j];
						int m2 = timer[i][j];
						a[i][j] = a[i + dx][i + dy];
						timer[i][j] = timer[i + dx][i + dy];
						a[i + dx][i + dy] = m1;
						timer[i + dx][i + dy] = m2;
					}
				}
			}
		}
	}
}
