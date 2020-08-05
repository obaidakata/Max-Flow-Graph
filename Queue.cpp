#include "Queue.h"

Queue::Queue()
{
    m_Length = 0;
    m_Head = new Node();
    m_Tail = m_Head;
}

Queue::~Queue()
{
    MakeEmpty();
}

void Queue::MakeEmpty()
{
    Node* current = m_Head;
    Node* next;

    while (current != nullptr)
    {
        next = current->GetNext();
        delete current;
        current = next;
    }
}

bool Queue::IsEmpty()
{
    return (m_Length == 0);
}

Vertex Queue::First()
{
    if (IsEmpty())
    {
        throw new exception("Error: Queue Empty");
    }

    return m_Head->GetNext()->GetData();
}

void Queue::EnQueue(Vertex i_Data)
{
    Node* newNode = new Node(i_Data);
    m_Tail->InsertAfter(newNode);
    m_Tail = newNode;
    m_Length++;
}

Vertex Queue::DeQueue()
{
    if (IsEmpty())
    {
        throw new exception("Error: Queue Empty");
    }
    else
    {
        Node* temp = m_Head->DeleteAfter();
        Vertex toBeReturned = temp->GetData();
        if (m_Tail == temp)
        {
            m_Tail = m_Head;
        }

        delete temp;
        m_Length--;
        return toBeReturned;
    }
}

int Queue::Length()
{
    return m_Length;
}
