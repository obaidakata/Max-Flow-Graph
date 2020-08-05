#pragma once

#include <iostream>
#include "Node.h"

using namespace std;

class Queue
{
private:
    int m_Length;
    Node* m_Head, * m_Tail;
public:
    Queue();
    ~Queue();
    void MakeEmpty();
    bool IsEmpty();
    Vertex First();
    void EnQueue(Vertex i_Data);
    Vertex DeQueue();
    int Length();
};

