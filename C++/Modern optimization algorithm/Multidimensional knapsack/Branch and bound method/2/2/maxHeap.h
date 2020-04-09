template<class T>
class maxHeap
{
public:
	~maxHeap() {};
	int heapSize;
	T* heap = new T[8000000]();
	T top() { return heap[1]; };
	void push(const T& theElement);
	void pop();
};

template<class T>
void maxHeap<T>::push(const T& theElement)
{
	int currentNode = ++heapSize;
	while (currentNode != 1 && heap[currentNode / 2] < theElement)
	{
		heap[currentNode] = heap[currentNode / 2];
		currentNode /= 2;
	}

	heap[currentNode] = theElement;
};

template<class T>
void maxHeap<T>::pop()
{
	if (heapSize == 0)
	{
		throw - 1;
	}
	heap[1].~T();
	T lastElement = heap[heapSize--];
	int currentNode = 1, child = 2;
	while (child <= heapSize)
	{
		if (child < heapSize && heap[child] < heap[child + 1])
		{
			child++;
		}
		if (lastElement >= heap[child])
		{
			break;
		}
		heap[currentNode] = heap[child];
		currentNode = child;
		child *= 2;
	}
	heap[currentNode] = lastElement;
}
