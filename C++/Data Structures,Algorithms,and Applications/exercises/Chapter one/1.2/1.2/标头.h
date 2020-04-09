#ifndef CHAPTER_ONE_
#define CHAPTER_ONE_

template<class T>
T fill(const T *const a, const T& value, const T& len)
{
	if (len < 1)
	{
		throw 1;
	}
	int j = 0;
	for (int i = 0; i < len; i++)
	{
		if (a[i] == value)
		{
			j++;
		}
	}
	return j;
}

int abc(int a, int b, int c)
{
	if (a < 0 and b < 0 and c < 0)
	{
		throw 1;
	}
	else if (a == 0 and b == 0 and c == 0)
	{
		throw 2;
	}
	return a + b * c;
}
#endif // !CHAPTER_ONE_