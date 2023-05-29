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

std::stack<int> Graph::savePath(Vertex* v){
    std::stack<int> path;
    while (v->getPath() != nullptr) {
        path.push(v->getId());
        v = v->getPath()->getOrig();
    }
    return path;
}

void Graph::tspBT(std::stack<int> &bestPath, double &minDist) {
    for(Vertex* v: vertexSet)
        v->setVisited(false);

    Vertex* startingNode = vertexSet[0];

    startingNode->setVisited(true);
    startingNode->setPathCost(0);
    startingNode->setPath(nullptr);

    minDist = INF;

    tspBTRec(0, 0, minDist, bestPath);
}

void Graph::tspBTRec(int curVertex, int curIndex, double &minDist, std::stack<int> &bestPath) {
    Vertex* v1 = findVertex(curVertex);

    if (curIndex == vertexSet.size() - 1){
        double cost = v1->getPathCost();
        bool hasCon = false;
        for (auto e: v1->getAdj()) {
            if (e->getDest()->getId() == 0) {
                hasCon = true;
                cost += e->getDistance();
                break;
            }
        }
        if (hasCon && cost < minDist) {
            minDist = cost;
            bestPath = savePath(v1);
        }
        return;
    }
    for(Edge* edge : v1->getAdj()) {
        Vertex* v2 = edge->getDest();
        double distance = edge->getDistance();
        if(!v2->isVisited() && v1->getPathCost() + distance < minDist) {
            v2->setVisited(true);
            v2->setPath(edge);
            v2->setPathCost(v1->getPathCost() + distance);
            tspBTRec(v2->getId(), curIndex+1,minDist,bestPath);
            v2->setVisited(false);
        }
    }
}