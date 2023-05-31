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

void Graph::updateMst(Vertex* v){
   Vertex* w = v->getPath()->getOrig();
   w->addMstEdge(v, v->getPath()->getDistance());
   v->addMstEdge(w, v->getPath()->getDistance());
}

std::vector<Vertex *> Graph::prim() {
    if (vertexSet.empty()) return this->vertexSet;
    for (auto v: vertexSet){
        v->setVisited(false);
        v->setPath(nullptr);
        v->setPathCost(INF);
    }
    MutablePriorityQueue<Vertex> q;

    vertexSet[0]->setPathCost(0);
    q.insert(vertexSet[0]);
    while(!q.empty()){
        auto u = q.extractMin();
        u->setVisited(true);
        if (u->getPath() != nullptr) updateMst(u);
        for (auto e : u->getAdj()){
            auto w = e->getDest();
            if (!w->isVisited()){
                auto oldDist = e->getDest()->getPathCost();
                if (e->getDistance() < oldDist){
                    w->setPathCost(e->getDistance());
                    w->setPath(e);
                    if (oldDist == INF) q.insert(w);
                    else q.decreaseKey(w);
                }
            }
        }
    }
    return this->vertexSet;
}

void Graph::triangularApproximation(std::vector<Vertex*> &tour, double &dist) {
    prim();
    tour = preOrderTraversal();
    for (int i = 0; i < tour.size(); i++){
        Vertex* cur = tour[i];
        Vertex* next = tour[(i+1)%tour.size()];
        dist += distance(cur, next);
    }
}



double Graph::haversine(double lat1, double lon1, double lat2, double lon2) {
    double dLat = (lat2 - lat1) * M_PI / 180.0;
    double dLon = (lon2 - lon1) * M_PI / 180.0;

    // convert to radians
    lat1 = (lat1) * M_PI / 180.0;
    lat2 = (lat2) * M_PI / 180.0;

    // apply formula
    double a = pow(sin(dLat / 2), 2) + pow(sin(dLon / 2), 2) * cos(lat1) * cos(lat2);
    double rad = 6371;
    double c = 2 * asin(sqrt(a));
    return rad * c;

}

void Graph::preOrder(Vertex* vertex, std::vector<Vertex *> &l) {
    l.push_back(vertex);
    vertex->setVisited(true);
    for (Edge* edge : vertex->getMstAdj()) {
        Vertex* w = edge->getDest();
        if (!w->isVisited())
            preOrder(edge->getDest(),l);
    }
}


std::vector<Vertex *> Graph::preOrderTraversal() {
    std::vector<Vertex *> l;

    for (auto v : vertexSet)
        v->setVisited(false);

    Vertex* startingNode = vertexSet[0];

    preOrder(startingNode,l);
    return l;
}

double Graph::distance(Vertex* v1, Vertex* v2){
    for (Edge* e: v1->getAdj())
        if (e->getDest() == v2)
            return e->getDistance();
    return haversine(v1->getLatitude(),v1->getLongitude(),v2->getLatitude(),v2->getLongitude());
}


void Graph::nearestNeighborTSP(std::vector<Vertex *> &tour, double &distance) {
    for (auto v : vertexSet) v->setVisited(false);
    Vertex* startingVertex = vertexSet[0];
    startingVertex->setVisited(true);

    Vertex* currentVertex = startingVertex;
    while(true){
        tour.push_back(currentVertex);
        double minDist = INT_MAX;
        Vertex* nextVertex = nullptr;
        for (auto e : currentVertex->getAdj()){
            Vertex* neighbor = e->getDest();
            if (!neighbor->isVisited()){
                double dist = e->getDistance();
                if (dist < minDist){
                    minDist = dist;
                    nextVertex = neighbor;
                }
            }
        }
        if (nextVertex == nullptr) break;
        nextVertex->setVisited(true);
        distance += minDist;
        currentVertex = nextVertex;
    }
    if (currentVertex->getPath() == nullptr) {
        printf("Not a Hamiltonian path, sorry.");
    }
    else distance += currentVertex->getPath()->getDistance();

}
