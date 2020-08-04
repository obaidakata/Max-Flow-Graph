#pragma once
#include <iostream>
using namespace std;

struct Edge
{
private:
    int m_Capcity = 0;
    int* m_Flow = nullptr;

public:
    ~Edge();
    void SetCapacity(int i_Capcity);
    int GetCapacity();
    void SetFlow(int i_Amount);
    int GetFlow();
    void AddFlow(int i_Amount);
    bool IsExists();
    bool IsResidualGraphEdgeExists();
    int GetResidualGraphCapacity();
};
