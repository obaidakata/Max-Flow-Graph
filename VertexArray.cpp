#include "VertexArray.h"


bool VertexArray::inRange(int i_Index)
{
    return (i_Index < m_Capacity) && (i_Index >= 0);
}

VertexArray::VertexArray(int i_Capacity)
{
    m_Capacity = i_Capacity;
    m_Arr = new Vertex[m_Capacity];
    m_Size = 0;
}

VertexArray::~VertexArray()
{
    if (m_Arr != nullptr)
    {
        delete [] m_Arr;
    }
}

Vertex& VertexArray::operator[](int i_Index)
{
    if (inRange(i_Index))
    {
        return m_Arr[i_Index];
    }
    else
    {
        throw new exception("index out of range");
    }
}

int VertexArray::Size()
{
    return m_Size;
}

void VertexArray::PushBack(Vertex i_ToAdd)
{
    if (m_Size >= m_Capacity)
    {
        Vertex* temp = new Vertex[m_Capacity * 2];
        for (int i = 0; i < m_Capacity; i++)
        {
            temp[i] = m_Arr[i];
        }

        delete[] m_Arr;
        m_Arr = temp;
        m_Arr[m_Size] = i_ToAdd;
        m_Capacity *= 2;
    }
    else
    {
        m_Arr[m_Size] = i_ToAdd;
    }
    m_Size++;
}

VertexArray* VertexArray::GetPath(Vertex i_Start, Vertex i_End)
{
    if (!inRange(i_Start) || !inRange(i_End) || i_Start > i_End)
    {
        char* str = new char[50];
        sprintf_s(str, 50, "out of range %d %d", i_Start, i_End);
        throw new exception(str);
    }

    // need fix what if there is no path
    // from End to start( check infinite)
    VertexArray* toReturn = new VertexArray();
    if (m_Arr[i_End] != i_Start)
    {
        Vertex i = i_End;
        toReturn->PushBack(i_End);
        while (inRange(i) && i != i_Start)
        {
            i = m_Arr[i];
            toReturn->PushBack(i);
        }
    }

    return toReturn;
}

bool VertexArray::IsAccessible(Vertex i_Start, Vertex i_End)
{
    if (!inRange(i_Start) || !inRange(i_End) || i_Start > i_End)
    {
        cout << "out of range" << i_Start << " " << i_End << endl;
        exit(1);
    }

    bool isAccessible = false;
    int i = i_End;
    while (i >= 0 && i != i_Start)
    {
        i = m_Arr[i];
    }

    return isAccessible;
}

ostream& operator<<(ostream& i_Out, const VertexArray& i_VertexArray)
{
    int size = i_VertexArray.m_Size - 1;
    int i = 0;
    for (;i < size ;i++)
    {
        i_Out << i_VertexArray.m_Arr[i] + 1 << ", ";
    }
    i_Out << i_VertexArray.m_Arr[i] + 1;
    return i_Out;
}
