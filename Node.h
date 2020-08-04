#pragma once
#include <iostream>
using namespace std;

#define Vertex int

class Node
{
private:
    Vertex m_Data;
    Node* m_Next;

public:
    Vertex GetData();
    Node* GetNext();
    void SetNext(Node* i_Next);
    Node();
    Node(Vertex i_Data, Node* i_Ptr = nullptr);
    void InsertAfter(Node* i_NewNode);
    Node* DeleteAfter();
};

