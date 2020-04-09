#ifndef CHAPTER_ONE_
#define CHAPTER_ONE_

template<class T>
T swap(T& x, T& y)//利用形参来交换两数
{
	T temp=x;
	x = y;
	y = temp;
	return x, y;
}

template<class T>
T fill(const T *const a, const T& value, const T& len)
{
	int j = 0;
	for (int i = 0; i< len; i++)
	{
		if (a[i] == value)
		{
			j++;
		}
	}
	return j;
}

template<class T>
T fill(const T * const a, const T& value, const T& start, const T& end)//重载函数fill
{
	int j = 0;
	for (int i = start; i < end; i++)
	{
		if (a[i] == value)
		{
			j++;
		}
	}
	return j;
}

template<class T>
T inner_product(const T * const a, const T * const b, int len)
{	
	if (len > 1)
	{
		return inner_product(a, b, len - 1) + a[len - 1] * b[len - 1];
	}
	else
		return a[0] * b[0];
}

template<class T>
T iota(int * const a, const T& value, const int len)
{
	for (int i = 0; i < len; i++)
	{	
		a[i] = value + i;
	}
	return *a;
}

template<class T>
bool is_sorted(const T * const a,const int len)
{
	for (int i = 0; i < len - 2; i++)
	{
		if ((a[i + 1] - a[i])*(a[i + 2] - a[i + 1]) < 0)
		{
			return false;
		}
	}
	return true;
}

template<class T>
int mismatch(const T * const a, const T * const b, const int len)
{
	for (int i = 0; i < len; i++)
	{
		if (a[i] != b[i])
		{
			return i;
		}
	}
	return 0;
}


#endif // !CHAPTER_ONE_