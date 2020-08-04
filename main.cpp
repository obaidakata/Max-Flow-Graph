#include <iostream>
#include <stdlib.h>
#include "SimpleDirectedGraphWithWeights.h"
using namespace std;

int main(int argc, const char* argv[])
{
    try
    {
        SimpleDirectedGraphWithWeights graphhBFS(argv[1]);
        int maxFlowBFS = 0, numberOfIterationBFS = 0;
        VertexArray sBFS, tBFS;
        graphhBFS.GetMaxFlowBFS(maxFlowBFS, numberOfIterationBFS);
        graphhBFS.GetMinCut(sBFS, tBFS);
        cout << "BFS Method:" << endl;
        cout << "MaxFlow = " << maxFlowBFS << endl;
        cout << "Min cut: S = " << sBFS << ". T = " << tBFS << endl;
        cout << "Number of iteration = " << numberOfIterationBFS << endl;

        SimpleDirectedGraphWithWeights graphDijkstra(argv[1]);
        int maxFlowDijkstra = 0, numberOfIterationDijkstra = 0;
        VertexArray sDijkstr, tDijkstr;
        graphDijkstra.GetMaxFlowDijkstra(maxFlowDijkstra, numberOfIterationDijkstra);
        graphDijkstra.GetMinCut(sDijkstr, tDijkstr);
        cout << "Greedy Method:" << endl;
        cout << "MaxFlow = " << maxFlowDijkstra << endl;
        cout << "Min cut: S = " << sDijkstr << ". T = " << tDijkstr << endl;
        cout << "Number of iteration = " << numberOfIterationDijkstra << endl;
    }
    catch (exception* ex)
    {
        cout << "Exception :"<< ex->what() << endl;
        delete ex;
        cout << "Press any key to close this window . . ." << endl;
        char x;
        cin >> x;
        exit(4154);
    }
    return 0;
}
