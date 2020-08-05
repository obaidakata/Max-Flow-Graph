#pragma once
#include <iostream>
#include "Quantity.h"
using namespace std;
#define Vertex int
class MaxHeap
{
private:
	pair<Vertex, Quantity>* m_Data;
	int* m_Places;
	int m_MaxSize;
	int m_HeapSize;
	bool m_Allocated;

	int left(int nude);
	int right(int node);
	int parent(int node);
	void fixHeap(int node);
	void copyPair(pair<Vertex, Quantity>& i_One, pair<Vertex, Quantity>& i_Two);
	void swapPair(pair<Vertex, Quantity>& i_One, pair<Vertex, Quantity>& i_Two);
public:
	MaxHeap(Quantity* A, int n);
	~MaxHeap();
	pair<Vertex, Quantity> Max();
	pair<Vertex, Quantity>& DeleteMax();
	void Insert(pair<Vertex, Quantity> i_Item);
	void MakeEmpty();
	bool IsEmpty();
	void IncreaseKey(Vertex i_U, Quantity i_NewValue);
};