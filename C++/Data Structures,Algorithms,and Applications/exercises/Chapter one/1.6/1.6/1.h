enum method
{
	add = 0,
	mult = 1
};

template<typename T1>
T1& accumulate1(typename std::vector<T1>::iterator begin, typename std::vector<T1>::iterator end, T1& thesum)
{
	thesum = 0;
	while (begin!=end)
	{
		thesum +=*begin;
		begin++;
	}
	return thesum;
}

template<typename T1>
T1& accumulate2(typename std::vector<T1>::iterator begin, typename std::vector<T1>::iterator end,  T1& thesum, method method)
{
	if(method == 0)
	{ 
		thesum = 0;
		while (begin != end)
		{
			thesum += *begin;
			begin++;
		}
		return thesum;
	}
	else if (method == 1)
	{
		thesum = 1;
		while (begin != end)
		{
			thesum *= *begin;
			begin++;
		}
		return thesum;
	}
}

template<typename T>
void copy1(typename std::vector<T>::iterator begin1, typename std::vector<T>::iterator end1, typename std::vector<T>::iterator begin2)
{
	while (begin1 != end1)
	{
		*begin2 = *begin1;
		begin2++;
		begin1++;
	}
}

template<class T>
void permutations1(T list[], int k, int m)
{
	std::sort(list+k, list+m+1);
	do
	{
		std::copy(list, list +m+1 , std::ostream_iterator<T>(std::cout, " "));
		std::cout << std::endl;
	} while (std::next_permutation(list, list + m + 1));
}

template<class T>
void permutations2(T list[], int k, int m)
{
	T *a = new T[sizeof(list)];
	std::copy(list, list + m + 1,a);
	do
	{
		std::copy(a, a + m + 1, std::ostream_iterator<T>(std::cout, " "));
		std::cout << std::endl;
	} 
	while (std::next_permutation(a, a + m + 1));
	std::cout << "----------------" << std::endl;
	std::copy(list, list + m + 1, a);
	while (std::prev_permutation(a, a + m + 1))
	{
		std::copy(a, a + m + 1, std::ostream_iterator<T>(std::cout, " "));
		std::cout << std::endl;
	}
}

template<class T>
void permutations3(T list[], int k, int m)
{
	while (std::next_permutation(list, list + m + 1)) { ; }
	do
	{
		std::copy(list, list + m + 1, std::ostream_iterator<T>(std::cout, " "));
		std::cout << std::endl;
	} while (std::next_permutation(list, list + m + 1));
}

template<typename T>
int count2(typename std::vector<T>::iterator begin, typename std::vector<T>::iterator end, T value,int time=0)
{
	while (begin != end)
	{
		if (*begin == value)
		{
			time++;
		}
		begin++;
	}
	return time;
}

template<typename T>
void fill2(typename std::vector<T>::iterator begin, typename std::vector<T>::iterator end, T value)
{
	while (begin != end)
	{
		*begin = value;
		begin++;
	}
}

template<typename T>
T inner_product2(typename std::vector<T>::iterator begin1, typename std::vector<T>::iterator end1, typename std::vector<T>::iterator begin2 ,T value)
{
	while (begin1 != end1)
	{
		value += (*begin1)*(*begin2);
		begin1++;
		begin2++;
	}
	return value;
}

template<typename T>
void iota2(typename std::vector<T>::iterator begin, typename std::vector<T>::iterator end, T value)
{
	while (begin != end)
	{
		*begin+=value;
		begin++;
	}
}

template<typename T>
T is_sorted2(typename std::vector<T>::iterator begin, typename std::vector<T>::iterator end)
{
	while ((end-begin)>=2)
	{
		if(((*(begin+1))-(*begin))*((*(begin+2))-(*(begin+1)))<0)
		{ 
			return 0;
		}
		else
		{
			begin++;
		}
	}
	return 1;
}

template<typename T>
std::pair<typename std::vector<T>::iterator, typename std::vector<T>::iterator> mismatch2(typename std::vector<T>::iterator begin1, typename std::vector<T>::iterator end1, typename std::vector<T>::iterator begin2)
{
	while ((begin1 != end1) && (*begin1 == *begin2))
	{
		begin1++;
		begin2++;
	}
	std::pair<std::vector<T>::iterator,std::vector<T>::iterator> s=std::make_pair(begin1,begin2);
	return s;
}