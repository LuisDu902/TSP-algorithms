#include "Graph.h"

Vertex * Graph::findVertex(const int &id) const {
    for (Vertex* vertex : vertexSet)
        if (vertex->getId() == id)
            return vertex;
    return nullptr;
}

void Graph::addVertex(const int &id, const double &longitude, const double &latitude){
    auto* v = new Vertex(id, longitude, latitude);
    vertexSet.push_back(v);
}

void Graph::addEdge(Vertex* &v1, Vertex* &v2, double distance) const{
    v1->addEdge(v2, distance);
    v2->addEdge(v1, distance);
}

std::vector<Vertex *> Graph::getVertexSet() const {
    return this->vertexSet;
}

void Graph::tspBT(std::vector<Vertex *> &bestPath) {
    for(Vertex* v: vertexSet){
        v->setPathCost(INF);
        v->setPath(nullptr);
        v->setVisited(false);
    }
    Vertex* startingNode = findVertex(0);
    startingNode->setPathCost(0);

    double minDist = INF;

    tspBTRec(0, minDist, bestPath);
}

void Graph::tspBTRec(int curIndex, double &minDist, std::vector<Vertex *> &bestPath) {
    if (curIndex == vertexSet.size()){
        //...
        return;
    }

}