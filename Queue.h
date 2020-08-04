#pragma once

#include <iostream>
#include "Node.h"

using namespace std;

class Queue
{
private:
    int Length;
    Node* head, * tail;
public:
    Queue();
    ~Queue();
    void MakeEmpty();
    bool IsEmpty();
    Vertex First();
    void EnQueue(Vertex i_Data);
    Vertex DeQueue();
};

