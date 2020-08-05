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

	if ((leftNode < m_HeapSize) && (m_Data[leftNode].second > m_Data[node].second))
	{
		max = leftNode;
	}
	else
	{
		max = node;
	}

	if ((rightNode < m_HeapSize) && (m_Data[rightNode].second > m_Data[max].second))
	{
		max = rightNode;
	}

	if (max != node)
	{
		swapPair(m_Data[node], m_Data[max]);
		fixHeap(max);
	}
}

MaxHeap::MaxHeap(Quantity* A, int i_N) :m_Data(new pair<Vertex, Quantity>[i_N])
{
	m_MaxSize = m_HeapSize = i_N;
	m_Places = new int[i_N];
	m_Allocated = true;

	for (int i = 0; i < m_HeapSize; i++)
	{
		m_Data[i].first = i;
		m_Data[i].second = A[i];
		m_Places[i] = i;
	}
		

	for (int i = m_HeapSize / 2 - 1; i >= 0; i--)
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
	if (m_HeapSize < 0)
	{
		throw new exception("Heap Empty");
	}
	return m_Data[0];
}

pair<Vertex, Quantity>& MaxHeap::DeleteMax()
{
	if (m_HeapSize < 1)
	{
		throw new exception("Heap Empty");
	}
	pair<Vertex, Quantity> max = m_Data[0];
	m_HeapSize--;
	copyPair(m_Data[0], m_Data[m_HeapSize]);
	m_Places[m_Data[m_HeapSize].first] = 0;
	fixHeap(0);
	return max;
}

void MaxHeap::Insert(pair<Vertex, Quantity> i_Item)
{
	if (m_HeapSize == m_MaxSize)
	{
		throw new exception("Heap full");
	}

	int i = m_HeapSize;
	while ((i > 0) && (m_Data[parent(i)].second > i_Item.second))
	{
		copyPair(m_Data[i], m_Data[parent(i)]);
		i = parent(i);
		m_HeapSize++;
	}
	copyPair(m_Data[i], i_Item);
}

void MaxHeap::MakeEmpty()
{
	if (m_Allocated)
	{
		delete[] m_Data;
		delete[] m_Places;
	}
	m_Allocated = !m_Allocated;
}

bool MaxHeap::IsEmpty()
{
	return (m_HeapSize < 1);
}

void MaxHeap::copyPair(pair<Vertex, Quantity>& i_One, pair<Vertex, Quantity>& i_Two)
{
	i_One.first = i_Two.first;
	i_One.second = i_Two.second;
}

void MaxHeap::swapPair(pair<Vertex, Quantity>& i_One, pair<Vertex, Quantity>& i_Two)
{
	int tempIndex = m_Places[i_One.first];
	m_Places[i_One.first] = m_Places[i_Two.first];
	m_Places[i_Two.first] = tempIndex;

	pair<Vertex, Quantity> temp;
	copyPair(temp, i_One);
	copyPair(i_One, i_Two);
	copyPair(i_Two, temp);
}

void MaxHeap::IncreaseKey(Vertex i_U, Quantity i_NewValue)
{
	if(i_U < 0 || i_U > m_MaxSize)
	{
		throw new exception("Vertex undefined");
	}

	int i = m_Places[i_U];
	if (m_Data[i].second > i_NewValue)
	{
		throw new exception("Expect that new value largest the the old value");
	}
	else
	{
		
		m_Data[i].second = i_NewValue;
		while (i != 0 && m_Data[parent(i)].second < m_Data[i].second)
		{
			swapPair(m_Data[i], m_Data[parent(i)]);
			i = parent(i);
		}
	}

	
}