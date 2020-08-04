#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Queue.h"
#include "Edge.h"
#include "VertexArray.h"
#include "Quantity.h"
#include "MaxHeap.h"
using namespace std;

class SimpleDirectedGraphWithWeights
{
private:
    bool m_IsAllocated = false;
    int m_NumberOfVeretex;
    int m_NumberOfEdges;
    Vertex m_VertexS;
    Vertex m_VertexT;
    Edge** m_EdgesMatrix = nullptr;
    Quantity* distanceFromStart = nullptr;
    Quantity* Weights = nullptr;
    MaxHeap* m_MaxHeap = nullptr;
    VertexArray* parents = nullptr;

    //Utiles
    void printEdgesMatrix();
    const char* vertexOutOfRange(const char* i_VertexName, Vertex i_VertexVAlue);
    void checkIfVertexOutOfRange(const char* i_VertexName, Vertex i_VertexValue);
    void checkIfVertexOutOfEdgesMatrix(Vertex i_VertexValue);

    // Used in both algorithms
    int getMinFlowInPath(VertexArray* i_Path);
    void initFlowInGraph(int i_value);
    void updatePathEdges(VertexArray* i_Path, int i_Value);
    

    // For FBS only
    VertexArray* getPathBFS();
    VertexArray* BFSShortestPathTree(Vertex i_Start);

    //For dijkstra only
    VertexArray* getPathDijkstra();
    VertexArray* dijkstra();
    void relax(Vertex i_U, Vertex i_V);
    void initializeSingleSource(Quantity* i_Whiehts, VertexArray* i_Parents);

public:
    SimpleDirectedGraphWithWeights(const char* i_FilePath);
    ~SimpleDirectedGraphWithWeights();
    void GetMaxFlowBFS(int& o_MaxFlow, int& o_NumberOfIteration);
    void GetMaxFlowDijkstra(int& o_MaxFlow, int& o_NumberOfIteration);
    void GetMinCut(VertexArray& i_S, VertexArray& i_T);
    void MakeEmptyGraph();
    bool IsAdjacent(Vertex i_U, Vertex i_V);
    Queue* GetAdjList(Vertex i_U);
    Queue* GetResidualGraphEdgeAdjList(Vertex i_U);
    void AddEdge(Vertex i_U, Vertex i_V, int i_Capacity);
    void RemoveEdge(Vertex i_U, Vertex i_V);
};
