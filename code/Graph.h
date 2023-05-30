#ifndef DA_GRAPH_H
#define DA_GRAPH_H

#include "VertexEdge.h"
#include <stack>
#include <cmath>

class Graph {
public:

    Vertex *findVertex(const int &id) const;
    void addVertex(const int &id, const double &longitude = 0, const double &latitude = 0);
    void addEdge(Vertex* &v1, Vertex* &v2, double distance) const;

    std::vector<Vertex *> getVertexSet() const;
    std::stack<int> savePath(Vertex* v1);
    void tspBT(std::stack<int> &bestPath, double &minDist);
    void tspBTRec(int curVertex, int curIndex, double &minDist, std::stack<int> &bestPath);
    std::vector<Vertex *> prim();
    double distance(double lat1, double lon1, double lat2, double lon2);
private:
    std::vector<Vertex *> vertexSet;
};
#endif //DA_GRAPH_H
