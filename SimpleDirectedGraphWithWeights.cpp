#include "SimpleDirectedGraphWithWeights.h"

/// Private Methouds---------------------------------------------------------

//Utiles
void SimpleDirectedGraphWithWeights::printEdgesMatrix()
{
    for (int i = 0; i < m_NumberOfVeretex; i++)
    {
        for (int j = 0; j < m_NumberOfVeretex; j++)
        {
            //string s = m_EdgesMatrix[i][j].IsExists() ? "True" : "False";
            cout << m_EdgesMatrix[i][j].GetCapacity() << '\t';
        }

        cout << endl;
    }
}

const char* SimpleDirectedGraphWithWeights::vertexOutOfRange(const char* i_VertexName, Vertex i_VertexVAlue)
{
    char* str = new char[50];
    sprintf_s(str, 50,"Invalid input: vertex (%s) with value (%d) shoud be between 1 and (%d). \n", i_VertexName, i_VertexVAlue, m_NumberOfVeretex);
    return str;
}

void SimpleDirectedGraphWithWeights::checkIfVertexOutOfRange(const char* i_VertexName, Vertex i_VertexValue)
{
    if (i_VertexValue < 1 || i_VertexValue > m_NumberOfVeretex)
    {
        const char* str = vertexOutOfRange(i_VertexName, i_VertexValue);
        throw new exception(str);
    }
}

void SimpleDirectedGraphWithWeights::checkIfVertexOutOfEdgesMatrix(Vertex i_VertexValue)
{
    if (i_VertexValue < 0 || i_VertexValue > m_NumberOfVeretex -1)
    {
        throw new exception("Vertex value out of edges matrix ");
    }
}


// Used in both algorithms--------------------------------------------------------

int SimpleDirectedGraphWithWeights::getMinFlowInPath(VertexArray* i_Path)
{
    if (i_Path != nullptr && i_Path->Size() > 1)
    {
        int min = m_EdgesMatrix[(*i_Path)[1]][(*i_Path)[0]].GetResidualGraphCapacity();
        int value;
        int numOfPairs = i_Path->Size() - 1;
        Vertex u, v;
        for (Vertex i = 1; i < numOfPairs; i++)
        {
            u = (*i_Path)[i + 1];
            v = (*i_Path)[i];
            value = m_EdgesMatrix[u][v].GetResidualGraphCapacity();
            if (min > value)
            {
                min = value;
            }
        }

        return min;
    }
    else
    {
        throw new exception("Path invalid");
    }
}

void SimpleDirectedGraphWithWeights::initFlowInGraph(int i_value)
{
    for (Vertex u = 0; u < m_NumberOfVeretex; u++)
    {
        for (Vertex v = 0; v < m_NumberOfVeretex; v++)
        {
            m_EdgesMatrix[u][v].SetFlow(i_value);
        }
    }
}

void SimpleDirectedGraphWithWeights::updatePathEdges(VertexArray* i_Path, int i_Value)
{
    if (i_Path != nullptr)
    {
        int pathLength = i_Path->Size() - 1;
        Vertex u, v;
        for (int i = 0; i < pathLength; i++)
        {
            u = (*i_Path)[i + 1];
            v = (*i_Path)[i];
            m_EdgesMatrix[u][v].AddFlow(i_Value);
            m_EdgesMatrix[v][u].SetFlow(-m_EdgesMatrix[u][v].GetFlow());
        }
    }
    else
    {
        throw new exception("Path invalid");
    }
}

void SimpleDirectedGraphWithWeights::GetMinCut(VertexArray& i_S, VertexArray& i_T)
{
    BFSShortestPathTree(m_VertexS);
    for (int i = 0; i < m_NumberOfVeretex; i++)
    {
        if (distanceFromStart[i] == Quantity::Inifinity)
        {
            i_T.PushBack(i);
        }
        else
        {
            i_S.PushBack(i);
        }
    }
}

// For FBS only----------------------------------------------------------------

VertexArray* SimpleDirectedGraphWithWeights::getPathBFS()
{
    VertexArray* out = BFSShortestPathTree(m_VertexS);
    VertexArray* toReturn = nullptr;
    if (out != nullptr)
    {
        toReturn = out->GetRangeFromPath(m_VertexS, m_VertexT);
        delete out;
    }

    if (distanceFromStart != nullptr)
    {
        delete distanceFromStart;
    }

    return toReturn;
}

VertexArray* SimpleDirectedGraphWithWeights::BFSShortestPathTree(Vertex i_Start)
{
    Queue q, * ResidualGraphEdgeAdjacent;
    distanceFromStart = new Quantity[m_NumberOfVeretex];
    parents = new VertexArray(m_NumberOfVeretex);

    q.EnQueue(i_Start);
    distanceFromStart[i_Start] = 0;

    Vertex u, uAdjacent;
    while (!q.IsEmpty())
    {
        u = q.DeQueue();
        ResidualGraphEdgeAdjacent = GetResidualGraphEdgeAdjList(u);
        if (ResidualGraphEdgeAdjacent != nullptr)
        {
            while (!ResidualGraphEdgeAdjacent->IsEmpty())
            {
                uAdjacent = ResidualGraphEdgeAdjacent->DeQueue();
                if (distanceFromStart[uAdjacent] == Quantity::s_Infinite)
                {
                    distanceFromStart[uAdjacent] = distanceFromStart[u] + 1;
                    (*parents)[uAdjacent] = u;
                    q.EnQueue(uAdjacent);
                }
            }

            delete ResidualGraphEdgeAdjacent;
        }
    }

    if (distanceFromStart[m_VertexT] == Quantity::s_Infinite)
    {
        delete parents;
        parents = nullptr;
    }
    ResidualGraphEdgeAdjacent = nullptr;
    return parents;
}

//For dijkstra only ---------------------------------------------------------------

VertexArray* SimpleDirectedGraphWithWeights::getPathDijkstra()
{
    VertexArray* out = dijkstra();
    VertexArray* toReturn = nullptr;
    if (out != nullptr)
    {
        toReturn = out->GetRangeFromPath(m_VertexS, m_VertexT);
        delete out;
    }

    if (distanceFromStart != nullptr)
    {
        delete distanceFromStart;
    }

    return toReturn;
}

VertexArray* SimpleDirectedGraphWithWeights::dijkstra()
{
    Weights = new Quantity[m_NumberOfVeretex];
    parents = new VertexArray(m_NumberOfVeretex);
    initializeSingleSource(Weights, parents);

    m_MaxHeap = new MaxHeap(Weights, m_NumberOfVeretex);
    Vertex u;
    Queue* uAdjList;
    Vertex v;
    while (!m_MaxHeap->IsEmpty())
    {
        u = m_MaxHeap->DeleteMax().first;
        uAdjList = GetResidualGraphEdgeAdjList(u);
        while (uAdjList != nullptr && !uAdjList->IsEmpty())
        {
            v = uAdjList->DeQueue();
            relax(u, v);
        }
        delete uAdjList;
    }

    if (Weights[m_VertexT] == Quantity::s_NegInifinity)
    {
        delete parents;
        parents = nullptr;
    }

    delete  m_MaxHeap;
    m_MaxHeap = nullptr;
    return parents;
}

void SimpleDirectedGraphWithWeights::relax(Vertex i_U, Vertex i_V)
{
    checkIfVertexOutOfEdgesMatrix(i_U);
    checkIfVertexOutOfEdgesMatrix(i_V);
    Quantity capacityUV = m_EdgesMatrix[i_U][i_V].GetResidualGraphCapacity();
    Quantity min = Weights[i_U] < capacityUV ? Weights[i_U] : capacityUV;
    if (min > Weights[i_V])
    {
        Weights[i_V] = min;
        (*parents)[i_V] = i_U;
        m_MaxHeap->IncreaseKey(i_V, min);
    }
}

void SimpleDirectedGraphWithWeights::initializeSingleSource(Quantity* i_Whiehts, VertexArray* i_Parents)
{
    for (int i = 0; i < m_NumberOfVeretex; i++)
    {
        i_Whiehts[i] = Quantity::s_NegInifinity;
    }

    i_Whiehts[m_VertexS] = Quantity::Inifinity;
}

//Public Methouds-----------------------------------------------------------------------

SimpleDirectedGraphWithWeights::SimpleDirectedGraphWithWeights(const char* i_FilePath)
{
    ifstream myFile(i_FilePath);
    if (myFile.is_open())
    {
        myFile >> m_NumberOfVeretex;
        if (m_NumberOfVeretex <= 1)
        {
            throw new exception("Invalid input: number of vertex below 0.");
        }

        myFile >> m_NumberOfEdges;
        if (m_NumberOfEdges < 0)
        {
            throw new exception("Invalid input: number of Edges below 0.");
        }

        myFile >> m_VertexS;
        checkIfVertexOutOfRange("s", m_VertexS);
        m_VertexS--;

        myFile >> m_VertexT;
        checkIfVertexOutOfRange("t", m_VertexT);
        m_VertexT--;
        
        
        

        MakeEmptyGraph();

        int source, destination, capacity;
        for (int i = 0; i < m_NumberOfEdges; i++)
        {
            myFile >> source;  // cout << source << endl;
            myFile >> destination; //cout << destination << endl;
            myFile >> capacity; //cout << capacity << endl;
            AddEdge(source, destination, capacity); 
        }
    }
    else
    {
        throw new exception("Unable to open the file");
    }

    myFile.close();
}

SimpleDirectedGraphWithWeights::~SimpleDirectedGraphWithWeights()
{
    MakeEmptyGraph();
}

void SimpleDirectedGraphWithWeights::GetMaxFlowBFS(int& o_MaxFlow, int& o_NumberOfIteration)
{
    initFlowInGraph(0);

    VertexArray* path = getPathBFS();
    int residualCapacity;
    o_NumberOfIteration = 0;
    o_MaxFlow = 0;
    while (path != nullptr && path->Size() != 0)
    {
        o_NumberOfIteration++;
        residualCapacity = getMinFlowInPath(path);
        o_MaxFlow += residualCapacity;
        updatePathEdges(path, residualCapacity);
        path = getPathBFS();
    }
}

void SimpleDirectedGraphWithWeights::GetMaxFlowDijkstra(int& o_MaxFlow, int& o_NumberOfIteration)
{
    initFlowInGraph(0);
    VertexArray* path = getPathDijkstra();
    int residualCapacity;
    o_NumberOfIteration = 0;
    o_MaxFlow = 0;
    while (path && path->Size() != 0)
    {
        o_NumberOfIteration++;
        residualCapacity = getMinFlowInPath(path);
        o_MaxFlow += residualCapacity;
        updatePathEdges(path, residualCapacity);
        path = getPathDijkstra();
    }
}

void SimpleDirectedGraphWithWeights::MakeEmptyGraph()
{
    if (m_IsAllocated)
    {
        if (m_EdgesMatrix != nullptr)
        {
            for (int i = 0; i < m_NumberOfVeretex; i++)
            {
                delete [] m_EdgesMatrix[i];
            }

            delete [] m_EdgesMatrix;
        }
        if (distanceFromStart != nullptr)
        {
            delete distanceFromStart;
        }
        if (Weights != nullptr)
        {
            delete Weights;
        }
        if (m_MaxHeap != nullptr)
        {
            delete m_MaxHeap;
        }
        if (parents != nullptr)
        {
            delete parents;
        }
    }
    else
    {
        m_EdgesMatrix = new Edge*[m_NumberOfVeretex];
        for (int i = 0; i < m_NumberOfVeretex; i++)
        {
            m_EdgesMatrix[i] = new Edge[m_NumberOfVeretex];
            for (int j = 0; j < m_NumberOfVeretex; j++)
            {
                m_EdgesMatrix[i][j].SetCapacity(0);
            }

        }
    }

    m_IsAllocated = !m_IsAllocated;
}

bool SimpleDirectedGraphWithWeights::IsAdjacent(Vertex i_U, Vertex i_V)
{
    return m_EdgesMatrix[i_U][i_V].IsExists();
}

Queue* SimpleDirectedGraphWithWeights::GetAdjList(Vertex i_U)
{
    Queue* adjacentQueue = new Queue();
    for (int i = 0; i < m_NumberOfVeretex; i++)
    {
        if (m_EdgesMatrix[i_U][i].IsExists())
        {
            adjacentQueue->EnQueue(Vertex(i));
        }
    }

    return adjacentQueue;
}

Queue* SimpleDirectedGraphWithWeights::GetResidualGraphEdgeAdjList(Vertex i_U)
{
    checkIfVertexOutOfEdgesMatrix(i_U);
  
    Queue* adjacentQueue = new Queue();
    for (Vertex v = 0; v < m_NumberOfVeretex; v++)
    {
        if (m_EdgesMatrix[i_U][v].IsResidualGraphEdgeExists())
        {
            adjacentQueue->EnQueue(v);
        }
    }

    if (adjacentQueue->Length() == 0)
    {
        delete adjacentQueue;
        return nullptr;
    }
    else
    {
        return adjacentQueue;
    }
}

void SimpleDirectedGraphWithWeights::AddEdge(Vertex i_U, Vertex i_V, int i_Capacity)
{
    checkIfVertexOutOfRange("u", i_U);
    checkIfVertexOutOfRange("v", i_V);
    m_EdgesMatrix[i_U - 1][i_V - 1].SetCapacity(i_Capacity);
}

void SimpleDirectedGraphWithWeights::RemoveEdge(Vertex i_U, Vertex i_V)
{
    checkIfVertexOutOfEdgesMatrix(i_U);
    checkIfVertexOutOfEdgesMatrix(i_V);
    m_EdgesMatrix[i_U][i_V].SetCapacity(0);
}
