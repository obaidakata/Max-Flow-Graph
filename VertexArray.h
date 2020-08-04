#pragma once
#include <iostream>

using namespace std;
#define Vertex int

class VertexArray
{
private:
    Vertex* m_Arr = nullptr;
    int m_Size = 0;
    int m_Capacity;
    bool inRange(int i_Index);
public:
    VertexArray(int i_Capacity = 1);
    ~VertexArray();
    Vertex& operator[](int i_Index);
    int Size();
    void PushBack(Vertex i_ToAdd);
    VertexArray* GetPath(Vertex i_Start, Vertex i_End);
    bool IsAccessible(Vertex i_Start, Vertex i_End);
    friend ostream& operator<<(ostream& i_Out, const VertexArray& i_VertexArray);
};