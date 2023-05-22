#ifndef DA_GRAPH_H
#define DA_GRAPH_H

#include "VertexEdge.h"

class Graph {
public:

    Vertex *findVertex(const int &id) const;
    void addVertex(const int &id, const double &longitude = 0, const double &latitude = 0);
    void addEdge(Vertex* &v1, Vertex* &v2, double distance) const;

    std::vector<Vertex *> getVertexSet() const;

    void tspBT(std::vector<Vertex*> &bestPath);
    void tspBTRec(int curIndex, double &minDist, std::vector<Vertex*> &bestPath);

private:
    std::vector<Vertex *> vertexSet;
};
#endif //DA_GRAPH_H
