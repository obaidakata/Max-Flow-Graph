#include "Node.h"

Vertex Node::GetData()
{ 
    return m_Data; 
}

Node* Node::GetNext()
{ 
    return m_Next;
}

void Node::SetNext(Node* i_Next)
{
    m_Next = i_Next;
}

Node::Node()
{
    m_Next = nullptr;
}

Node::Node(Vertex i_Data, Node* i_Ptr)
{
    m_Data = i_Data;
    m_Next = i_Ptr;
}

void Node::InsertAfter(Node* i_NewNode)
{
    i_NewNode->m_Next = m_Next;
    m_Next = i_NewNode;
}

Node* Node::DeleteAfter()
{
    Node* temp = m_Next;
    if (m_Next == nullptr)
    {
        return nullptr;
    }

    m_Next = temp->m_Next;
    return temp;
}