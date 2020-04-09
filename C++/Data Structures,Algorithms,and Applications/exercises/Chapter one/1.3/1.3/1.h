template<class T>
void make2dArray(T ** &x, int numberOfRows, T* rowSize)
{
	x = new T *[numberOfRows];
	for (int i = 0; i < numberOfRows; i++)
	{
		x[i] = new T[rowSize[i]];
	}
}

template<class T>
void delete1dArray(T * &x)
{
	delete[] x;
}

template<class T>
void delete2dArray(T ** &x, int numberOfRows)
{
	for (int i = 0; i < numberOfRows; i++)
	{
		delete[] x[i];
	}
	delete[] x;
	x = NULL;
}

template<class T>
void changeLength1D(T *&a, int oldLength, int newLength)
{
	T *b;
	b= new T [newLength];
	int len = (newLength < oldLength ? newLength : oldLength);
	for (int i = 0; i < len; i++)
	{
		b[i] = a[i];
	}
	delete1dArray(a);
	a = b;
}

template<class T>
void changeLength2D(T ** &a, int oldLengthR, int oldLengthS, int newLengthR, int newLengthS)
{
	T **b;
	b = new T *[newLengthR];
	for (int i = 0; i < newLengthR; i++)
	{
		b[i] = new T [newLengthS];
	}
	int Rows= (newLengthR < oldLengthR ? newLengthR : oldLengthR);
	int Size= (newLengthS < oldLengthS ? newLengthS : oldLengthS);
	for (int i = 0; i < Rows; i++)
	{
		for (int j = 0; j < Size; j++)
		{
			b[i][j] = a[i][j];
		}
	}
	delete2dArray(a, oldLengthR);
	a = b;
}

