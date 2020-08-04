#include "Edge.h"
Edge::~Edge()
{
    if (m_Flow != nullptr)
    {
        delete m_Flow;
    }
}

void Edge::SetCapacity(int i_Capcity)
{
    m_Capcity = i_Capcity;
}

int Edge::GetCapacity()
{
    return m_Capcity;
}

void Edge::SetFlow(int i_Amount)
{
    if (m_Capcity >= 0)
    {
        if (i_Amount < m_Capcity)
        {
            m_Flow = new int(i_Amount);
        }
    }
    else
    {
        throw new exception("Amount  >= capacity");
    }
}

int Edge::GetFlow()
{
    return *m_Flow;
}

void Edge::AddFlow(int i_Amount)
{
    int finalFlow = *m_Flow + i_Amount;
    if (finalFlow <= m_Capcity)
    {
        *m_Flow = finalFlow;
    }
    else
    {
        throw new exception("Flow > Capacity");
    }
}

bool Edge::IsExists()
{
    return (m_Capcity != 0);
}

bool Edge::IsResidualGraphEdgeExists()
{
    // problem need fix no ocurate
    return (m_Flow != nullptr) && ((m_Capcity - *m_Flow) > 0);
}

int Edge::GetResidualGraphCapacity()
{
    return (m_Capcity - *m_Flow);
}