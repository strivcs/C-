template<class T>
void SG(T);
template<class T>
void SG2(T[], int, int, int);
template<class T>
void SG3(T [], int, int, int);
template <class T1, class T2>
bool judge(T1, T2 *, int);
template<class T>
void Gray_Code(T);
int gcd(int, int);
int A(int, int);
int fun2(int);
int fun(int);
int Fibonacci2(int);
int Fibonacci(int);
int Fibonacci(int x)
{
	if (x == 1)
	{
		return 1;
	}
	else if (x == 2)
	{
		return 1;
	}
	else if (x < 1)
	{
		exit(1);
	}
	else
	{
		return Fibonacci(x - 1) + Fibonacci(x - 2);
	}
}

int Fibonacci2(int x)
{
	int *a = new int [x];
	a[0] = a[1] = 1;
	for (int i = 2; i < x; i++)
	{
		a[i] = a[i - 1] + a[i - 2];
	}
	return a[x - 1];
}

int fun(int x)
{
	if (x % 2 == 0)
	{
		return x / 2;
	}
	else if(x % 2 == 1)
	{
		return fun(3 * x + 1);
	}
	else
	{
		exit(1);
	}
}

int fun2(int x)
{
	if (x % 2 == 0)
	{
		return x / 2;
	}
	else if (x % 2== 1)
	{
		return (3 * x + 1) / 2;
	}
	else
	{
		exit(1);
	}
}

int A(int x,int y)
{
	if ((x == 1) && (y >= 1))
	{
		return (int)pow(2, y);
	}
	else if ((x >= 2) && (y ==1))
	{
		return A(x - 1, 2);
	}
	else if ((x >= 2) && (y >= 2))
	{
		return A(x - 1, A(x, y - 1));
	}
	else
	{
		exit(1);
	}
}

int gcd(int x, int y)
{
	if (y == 0)
	{
		return x;
	}
	else if(y > 0)
	{
		return gcd(y, x%y);
	}
	else
	{
		exit(1);
	}
}

template <class T1,class T2>
bool judge(T1 x, T2 *a, int len)
{
	if (len > 0)
	{
		if (x == a[len - 1])
		{
			return true;
		}
		else
		{
			return judge(x, a, --len);//注意此处--len与len--的区别，后者无限循环
		}
	}
	else
	{
		return false;
	}
}

template<class T>
void SG(T len)
{
	int *a = new int[len]();
	for (int i = 0; i <= len; i++)
	{
		SG3(a, 0, len, i);
	}
}

template<class T>
void SG2(T list[], int begin, int end, int count)
{
	std::copy(list, list + end, std::ostream_iterator<T>(std::cout, " "));
	std::cout << std::endl;
}

template<class T>
void SG3(T list[], int begin, int end ,int count)
{
	if ((end - begin) == count)
	{
		for (int i = 0; i < begin; i++)
		{
			std::cout << list[i] << " ";
		}
		for (int i = begin; i < end; i++)
		{
			std::cout << 1 << " ";
		}
		std::cout << std::endl;
	}
	else
	{
		if (count == 0)
		{
			SG2(list, end, end, 0);
		}
		else if (count == 1)
		{
			list[begin] = 1;			
			for (int i = begin; i < end; i++)
			{
				std::swap(list[begin], list[i]);
				SG2(list, begin + 1, end, count);
				std::swap(list[begin], list[i]);
			}
		}
		else
		{
			list[begin] = 1;
			SG3(list, begin + 1, end, count - 1);
			list[begin] = 0;
			SG3(list, begin + 1, end, count);
		}
	}
}

template<class T>
void Gray_Code(T n)
{
	if (n == 1)
	{
		std::cout << 1 << " ";
	}
	else
	{
		Gray_Code(n - 1);
		std::cout << n << " ";
		Gray_Code(n - 1);
	}
}