#include "Queue.h"

Queue::Queue()
{
    Length = 0;
    head = new Node();
    tail = head;
}

Queue::~Queue()
{
    MakeEmpty();
}

void Queue::MakeEmpty()
{
    Node* current = head;
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
    return (Length == 0);
}

Vertex Queue::First()
{
    if (IsEmpty())
    {
        throw new exception("Error: Queue Empty");
    }

    return head->GetNext()->GetData();
}

void Queue::EnQueue(Vertex i_Data)
{
    Node* newNode = new Node(i_Data);
    tail->InsertAfter(newNode);
    tail = newNode;
    Length++;
}

Vertex Queue::DeQueue()
{
    if (IsEmpty())
    {
        throw new exception("Error: Queue Empty");
    }
    else
    {
        Node* temp = head->DeleteAfter();
        Vertex toBeReturned = temp->GetData();
        if (tail == temp)
        {
            tail = head;
        }

        delete temp;
        Length--;
        return toBeReturned;
    }
}
