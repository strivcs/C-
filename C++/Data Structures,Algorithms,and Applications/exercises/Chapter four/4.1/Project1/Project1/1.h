#include<iostream>
#include<algorithm>
#include<iterator>
#include<initializer_list>
#include<typeinfo>
#include<vector>
#include<cmath>
template<class T>
class linearList
{
public:
	virtual ~linearList() {};
	virtual bool empty() const = 0;
	virtual int size() const = 0;
	virtual T& get(int theIndex) const = 0;
	virtual int indexOf(const T& theElement) const = 0;
	virtual void erase(int theIndex)= 0;
	virtual void insert(int theIndex, const T& theElement) = 0;
	virtual void output(std::ostream& out) const = 0;
};

template<class T>
class iterator : public std::iterator<std::random_access_iterator_tag, T>
{
public:
	typedef std::random_access_iterator_tag iterator_catrgory;
	typedef T value_type;
	typedef std::ptrdiff_t difference_type;
	typedef T* pointer;
	typedef T& reference;
	iterator<T>() { ; }
	iterator<T>(T a, T* theposition = 0)
	{
		position = theposition;
		if (a == 0) { p1 = theposition; }
		else if (a == 1) { p2 = theposition; }
	}
	T& operator*() const { return *position; }
	T* operator->() const { return &*position; }
	
	iterator& operator+(int a)
	{
		position += a;
		return *this;
	}
	iterator& operator+=(int a)
	{
		position += a;
		return *this;
	}
	iterator& operator-(int a) 
	{
		position -= a;
		return *this;
	}
	T operator-(iterator b) const
	{
		return position-b.position;
	}
	iterator& operator-=(int a)
	{
		position -= a;
		return *this;
	}
	iterator& operator++()
	{
		++position;
		return *this;
	}
	iterator operator++(int)
	{
		iterator old = *this;
		++position;
		return old;
	}
	iterator& operator--()
	{
		--position;
		return *this;
	}
	iterator operator--(int)
	{
		iterator old = *this;
		--position;
		return old;
	}
	bool operator!=(const iterator<int> &right) const
	{
		return position != right.position;
	}
	bool operator==(const iterator<int> &right) const
	{
		return position == right.position;
	}
	bool operator<(const iterator<int> &right) const
	{
		return position < right.position;
	}
	bool operator<=(const iterator<int> &right) const
	{
		return position <= right.position;
	}
	bool operator>(const iterator<int> &right) const
	{
		return position > right.position;
	}
	bool operator>=(const iterator<int> &right) const
	{
		return position >= right.position;
	}
	T operator[](int a)
	{
		return *(p1 + a);
	}
protected:
	T* p1;
	T* p2;
	T* position;
	T value;
};
 
template<class T>
class arrayList : public linearList<T>,public iterator<T>
{
public:
	bool operator==(const arrayList<T>& x) const;
	bool operator!=(const arrayList<T>& x) const;
	bool operator<(const arrayList<T>& x) const;
	bool operator>(const arrayList<T>& x) const;
	T& operator[](int a);
	arrayList(std::initializer_list<int> );
	arrayList(int initialCapacity = 500);
	arrayList(const arrayList<T>&);
	~arrayList() { delete[] element;}

	bool empty() const { return listSize == 0; }
	int size() const { return listSize; }
	T& get(int theIndex) const;
	int indexOf(const T& theElement) const;
	void erase(int theIndex);
	void insert(int theIndex, const T& theElement);
	void output(std::ostream& out) const; 
	int capacity() const { return arrayLength; }
	void Specified_Upper();
	void Set_Upper(int a);
	void push_back(int a);
	void pop_back(int a = 1);
	void swap(int a, int b);
	void reserve(int a);
	void trimToSize() { listSize = std::max(listSize, 1); }
	void setSize(int newsize);
	void set(int a, int b);
	void clear();
	void removeRange(int a, int b);
	int lastIndexof(int a);
	void check_length();
	void reverse();
	void leftShift(int a);
	void circularShift(int a);
	void half();
	void meld(arrayList<T> a, arrayList<T> b);
	iterator<T> begin() { return iterator<T>(0, element); }
	iterator<T> end() { return iterator<T>(1, element + listSize); }
protected:
	void checkIndex(int theIndex) const;
	T* element;
	//T* p;
	int arrayLength;
	int listSize;
	int upper = 0;
	int initialCapacity;
};

template<class T>
arrayList<T>::arrayList(std::initializer_list<int>);
template<class T>
arrayList<T>::arrayList(int initialCapacity);
template<class T>
arrayList<T>::arrayList(const arrayList<T>&);
template<class T>
void arrayList<T>::checkIndex(int) const;
template<class T>
T& arrayList<T>::get(int) const;
template<class T>
int arrayList<T>::indexOf(const T&) const;
template<class T>
void arrayList<T>::erase(int);
template<class T>
void arrayList<T>::insert(int, const T&);
template<class T>
void arrayList<T>::output(std::ostream &) const;
template<class T>
void arrayList<T>::Specified_Upper(); 
template<class T>
void arrayList<T>::Set_Upper(int);
template<class T>
void arrayList<T>::push_back(int);
template<class T>
void arrayList<T>::pop_back(int);
template<class T>
void arrayList<T>::reserve(int);
template<class T>
void arrayList<T>::swap(int,int);
template<class T>
void arrayList<T>::setSize(int);
template<class T>
void arrayList<T>::set(int, int);
template<class T>
void arrayList<T>::clear();
template<class T>
void arrayList<T>::removeRange(int, int);
template<class T>
int arrayList<T>::lastIndexof(int);
template<class T>
void arrayList<T>::check_length();
template<class T>
void arrayList<T>::reverse();
template<class T>
void arrayList<T>::leftShift(int);
template<class T>
void arrayList<T>::circularShift(int);
template<class T>
void arrayList<T>::half();
template<class T>
T& arrayList<T>::operator[](int);
template<class T>
bool arrayList<T>::operator==(const arrayList<T>&) const;
template<class T>
bool arrayList<T>::operator!=(const arrayList<T>&) const;
template<class T>
bool arrayList<T>::operator<(const arrayList<T>&) const;
template<class T>
bool arrayList<T>::operator>(const arrayList<T>&) const;
template<class T>
void changeLength1D(T *&, int, int);
template<class T>
void changeLength2D(T ** &, int, int, int, int);
template<class T>
void reverse(arrayList<T> &);
template<class T>
void half(arrayList<T> &);
template<class T>
void arrayList<T>::meld(arrayList<T> , arrayList<T>);

template<class T>
arrayList<T>::arrayList(int InitialCapacity)
{
	if (InitialCapacity < 1)
	{
		//std::ostringstream s;
		std::cout << "Initial capacity = " << InitialCapacity << " Must be > 0";
		throw 0;
	}
	arrayLength = InitialCapacity;
	initialCapacity = InitialCapacity;
	element = new T[arrayLength];
	listSize = 0;
}

template<class T>
arrayList<T>::arrayList(std::initializer_list<int> il)
{
	/*int initialCapacity = 0;
	for (auto ptr = il.begin(); ptr != il.end(); ptr++)
	{
		initialCapacity += *ptr;
	}
	arrayLength = initialCapacity;
	element = new T[arrayLength];
	auto ptr = il.begin();
	int i = 0;
	for (; ptr != il.end(); ptr++, i++)
	{
		p = new T [*ptr];  
		*(element+i) = *(p+i);
	}
	listSize = 0;*/
}

template<class T>
arrayList<T>::arrayList(const arrayList<T>& thelist)
{ 
	arrayLength = thelist.arrayLength;
	initialCapacity = thelist.arrayLength;
	listSize = thelist.listSize;
	element = new T[arrayLength]();
	std::copy(thelist.element, thelist.element + listSize, element);
}

template<class T>
void arrayList<T>::checkIndex(int theIndex) const
{
	if (theIndex < 0 || theIndex >= listSize)
	{
		//std::ostringstream s;
		std::cout << "index = " << theIndex << " size = " << listSize;
		throw 1;
	}
}

template<class T>
T& arrayList<T>::get(int theIndex) const
{
	checkIndex(theIndex);
	return element[theIndex];
}

template<class T>
int arrayList<T>::indexOf(const T& theElement) const
{
	int theIndex = (int)(std::find(element, element + listSize, theElement) - element);
	if (theIndex == listSize)
	{
		return -1;
	}
	else
	{
		return theIndex;
	}
}

template<class T>
void arrayList<T>::erase(int theIndex)
{
	checkIndex(theIndex);
	std::copy(element + theIndex + 1, element + listSize, element + theIndex);
	element[--listSize].~T();
	check_length();
}

template<class T>
void arrayList<T>::insert(int theIndex, const T& theElement)
{
	if (theIndex <0)
	{
		//std::ostringstream s;
		std::cout << "index = " << theIndex << " size = " << listSize;
		throw 2;
	}
	if (theIndex >= arrayLength)
	{
		Specified_Upper();
	}
	listSize = theIndex;
	std::copy_backward(element + theIndex, element + listSize, element + listSize + 1);
	element[theIndex] = theElement;
	listSize++;
}

template<class T>
void arrayList<T>::output(std::ostream& out) const
{
	std::copy(element, element + listSize, std::ostream_iterator<T>(out, " "));
}

template<class T>
std::ostream& operator<<(std::ostream& out, const arrayList<T>& x)
{
	x.output(out);
	return out;
}

template<class T>
T& arrayList<T>::operator[](int a)
{
	if (a >= listSize)
	{
		throw 4;
	}
	if (element[a] == 0)
	{
		throw 5;
	}
	return element[a];
}

template<class T>
void arrayList<T>::Specified_Upper()
{
	if (listSize >= arrayLength && upper >= listSize)
	{
		changeLength1D(element, arrayLength, upper);
		arrayLength = upper;
	}
	else if (listSize >= arrayLength)
	{
		changeLength1D(element, arrayLength, 2 * arrayLength);
		arrayLength *= 2;
	}
}

template<class T>
void arrayList<T>::Set_Upper(int a)
{
	upper = a;
}

template<class T>
void arrayList<T>::push_back(int a)
{
	if (listSize == arrayLength)
	{
		Specified_Upper();
	}
	std::copy_backward(element + listSize, element + listSize, element + listSize + 1);
	element[listSize] = a;
	listSize++;
}

template<class T>
void arrayList<T>::pop_back(int a)
{
	for (int i = 0; i < a; i++)
	{
		element[--listSize].~T();
	}
	check_length();
}

template<class T>
void arrayList<T>::reserve(int a)
{
	arrayLength = std::max(capacity(), a);
	check_length();
}

template<class T>
void arrayList<T>::swap(int a,int b)
{
	checkIndex(a);
	T temp;
	temp = element[b];
	element[b] = element[a];
	element[a] = temp;
}

template<class T>
void arrayList<T>::setSize(int newsize)
{
	if (arrayLength <= newsize)
	{
		changeLength1D(element, arrayLength, newsize);
	}
	else
	{
		for (int i = listSize - 1; i >= newsize; i--)
		{
			erase(i);
		}
	}
	arrayLength = newsize;
}

template<class T>
void arrayList<T>::set(int a, int b)
{
	checkIndex(a);
	element[a] = element[b];
}

template<class T>
void arrayList<T>::clear()
{
	for (int i = listSize; i > 0; i--)
	{
		element[--listSize] = 0;
	}
	arrayLength = 0;
}

template<class T>
void arrayList<T>::removeRange(int a, int b)
{
	for (int i = b; i >= a; i--)
	{
		erase(i);
	}
	check_length();
}

template<class T>
int arrayList<T>::lastIndexof(int a)
{
	int s = (int)(std::find(element, element + listSize, a) - element);
	if (s == listSize)
	{
		return -1;
	}
	return s;	
}

template<class T>
void arrayList<T>::check_length()
{
	while ((listSize <= arrayLength / 4) && (std::max(arrayLength / 2, initialCapacity) != arrayLength))
	{
		arrayLength = std::max(arrayLength / 2, initialCapacity);
		T *a = new T[arrayLength];
		std::copy(element, element + listSize, a);
		delete[] element;
		element = a;
	}
}

template<class T>
void arrayList<T>::reverse()
{
	T *a = new T[listSize];
	for (int i = 0; i < listSize; i++)
	{
		a[listSize - i - 1] = element[i];
	}
	for (int i = 0; i < listSize; i++)
	{
		element[i] = a[i];
	}
}

template<class T>
void arrayList<T>::leftShift(int a)
{
	for (int i = 0; i < listSize - a; i++)
	{
		swap(i, i+a);
	}
	pop_back(a);
}

template<class T>
void arrayList<T>::circularShift(int a)
{
	T *b = new T[listSize + a];
	std::copy(element, element + a, b + listSize - a);
	std::copy(element + a, element + listSize, b);
	std::copy(b, b + listSize, element);
}

template<class T>
void arrayList<T>::half()
{
	int newsize = (int)ceil((float)listSize / 2);
	for (int i = 0, j = 0; i < newsize; i++, j++)
	{
		std::copy(element + 2 * i, element + 2 * i + 1, element + j);
	}
	pop_back(listSize - newsize);
	check_length();
}

template<class T>
bool arrayList<T>::operator==(const arrayList<T>& x) const
{
	if (x.size() != size())
	{
		return 0;
	}
	for (int i = 0; i < std::min(x.size(), size()); i++)
	{
		if (x.element[i] != element[i])
		{
			return 0;
		}
	}
	return 1;
}

template<class T>
bool arrayList<T>::operator!=(const arrayList<T>& x) const
{
	for (int i = 0; (i < std::min(x.size(), size())) && (x.size() == size()); i++)
	{
		if (x.element[i] != element[i])
		{
			return 1;
		}
	}
	return 0;
}

template<class T>
bool arrayList<T>::operator<(const arrayList<T>& y) const
{
	if (y.size() > size())
	{
		return 1;
	}
	for (int i = 0; i < std::min(y.size(), size()) ; i++)
	{
		if (y.element[i] > element[i])
		{
			return 1;
		}
		else if(y.element[i] < element[i])
		{
			return 0;
		}
	}
	return 0;
}

template<class T>
bool arrayList<T>::operator>(const arrayList<T>& y) const
{
	if (y.size() > size())
	{
		return 0;
	}
	for (int i = 0; i < std::min(y.size(), size()); i++)
	{
		if (y.element[i] > element[i])
		{
			return 0;
		}
		else if (y.element[i] < element[i])
		{
			return 1;
		}
	}
	return 1;
}

template<class T>
void changeLength1D(T *&a, int oldLength, int newLength)
{
	if (newLength < 0)
	{
		throw 3;
	}
	T* temp = new T[newLength]();
	int number = std::min(oldLength, newLength);
	std::copy(a, a + number, temp);
	delete [] a;
	a = temp;
}

template<class T>
void changeLength2D(T ** &a, int oldLengthR, int oldLengthS, int newLengthR, int newLengthS)
{
	if (newLengthR < 0 || newLengthS < 0)
	{
		throw 3;
	}
	T **temp = new T *[newLengthR];
	for (int i = 0; i < newLengthR; i++)
	{
		temp[i] = new T[newLengthS];
	}
	int Rows = std::min(oldLengthR, newLengthR);
	int Size = std::min(oldLengthS, newLengthS);
	for (int i = 0; i < Rows; i++)
	{
		for (int j = 0; j < Size; j++)
		{
			temp[i][j] = a[i][j];
		}
	}
	for (int i = 0; i < Rows; i++)
	{
		delete [] a[i];
	}
	a = temp;
}

template<class T>
void reverse(arrayList<T> &x)
{
	T *a = new T[x.size()];
	for (int i = 0; i < x.size(); i++)
	{
		a[x.size() - i - 1] = x[i];
	}
	for (int i = 0; i < x.size(); i++)
	{
		x[i] = a[i];
	}
}

template<class T>
void half(arrayList<T> &x)
{
	int newsize = (int)ceil((float)x.size() / 2);
	for (int i = 0, j = 0; i < newsize; i++, j++)
	{
		std::copy(&x[0] + 2 * i, &x[0] + 2 * i + 1, &x[0] + j);
	}
	x.pop_back(x.size() - newsize);
	x.check_length();
}

template<class T>
void arrayList<T>::meld(arrayList<T> a, arrayList<T> b)
{
	if (listSize != 0)
	{
		throw 6;
	}
	listSize = 0;
	arrayLength = a.arrayLength + b.arrayLength;
	initialCapacity = arrayLength;
	for (int i = 0; i < arrayLength; i++)
	{
		if (i % 2 == 0)
		{
			if ((int)i / 2 == a.listSize)
			{
				this->check_length();
				continue;
			}
			else
			{
				element[i] = a.element[i/2];
			}
		}
		else
		{
			if ((int)i / 2 == b.listSize)
			{
				this->check_length();
				continue;
			}
			else
			{
				element[i] = b.element[i/2];
			}
		}
		listSize++;
		this->check_length();
	}
}