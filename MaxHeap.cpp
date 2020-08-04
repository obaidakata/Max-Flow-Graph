#include "MaxHeap.h"


int MaxHeap::left(int node)
{
	return (2 * node + 1);
}

int MaxHeap::right(int node)
{
	return (2 * node + 2);
}

int MaxHeap::parent(int node)
{
	return (node - 1) / 2;
}

void MaxHeap::fixHeap(int node)
{
	int max;
	int leftNode = left(node);
	int rightNode = right(node);

	if ((leftNode < heapSize) && (data[leftNode].second > data[node].second))
	{
		max = leftNode;
	}
	else
	{
		max = node;
	}

	if ((rightNode < heapSize) && (data[rightNode].second > data[max].second))
	{
		max = rightNode;
	}

	if (max != node)
	{
		swapPair(data[node], data[max]);
		fixHeap(max);
	}
}

MaxHeap::MaxHeap(Quantity* A, int i_N) :data(new pair<Vertex, Quantity>[i_N])
{
	maxSize = heapSize = i_N;
	allocated = true;

	for (int i = 0; i < heapSize; i++)
	{
		data[i].first = i;
		data[i].second = A[i];
	}
		

	for (int i = heapSize / 2 - 1; i >= 0; i--)
	{
		fixHeap(i);
	}
}

MaxHeap::~MaxHeap()
{
	MakeEmpty();
}

pair<Vertex, Quantity> MaxHeap::Max()
{
	if (heapSize < 0)
	{
		throw new exception("Heap Empty");
	}
	return data[0];
}

pair<Vertex, Quantity>& MaxHeap::DeleteMax()
{
	if (heapSize < 1)
	{
		throw new exception("Heap Empty");
	}
	pair<Vertex, Quantity> max = data[0];
	heapSize--;
	copyPair(data[0], data[heapSize]);
	fixHeap(0);
	return max;
}

void MaxHeap::Insert(pair<Vertex, Quantity> i_Item)
{
	if (heapSize == maxSize)
	{
		throw new exception("Heap full");
	}

	int i = heapSize;
	while ((i > 0) && (data[parent(i)].second > i_Item.second))
	{
		copyPair(data[i], data[parent(i)]);
		i = parent(i);
		heapSize++;
	}
	copyPair(data[i], i_Item);
}

void MaxHeap::MakeEmpty()
{
	if (allocated)
	{
		delete[] data;
	}
	allocated = !allocated;
}

bool MaxHeap::IsEmpty()
{
	return (heapSize < 1);
}

void MaxHeap::copyPair(pair<Vertex, Quantity>& i_One, pair<Vertex, Quantity>& i_Two)
{
	i_One.first = i_Two.first;
	i_One.second = i_Two.second;
}

void MaxHeap::swapPair(pair<Vertex, Quantity>& i_One, pair<Vertex, Quantity>& i_Two)
{
	pair<Vertex, Quantity> temp;
	copyPair(temp, i_One);
	copyPair(i_One, i_Two);
	copyPair(i_Two, temp);
}

void MaxHeap::IncreaseKey(Vertex i_U, Quantity i_NewValue)
{
	int i = 0;
	for (; i < heapSize; i++)
	{
		if (data[i].first == i_U)
		{
			if (data[i].second > i_NewValue)
			{
				throw new exception("Expect that new value largest the the old value");
			}
			else
			{
				data[i].second = i_NewValue;
			}
			
			break;
		}
	}

	while (i != 0 && data[parent(i)].second < data[i].second)
	{
		swapPair(data[i], data[parent(i)]);
		i = parent(i);
	}
}