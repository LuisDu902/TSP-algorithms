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
    auto e1 = v1->addEdge(v2, distance);
    auto e2 = v2->addEdge(v1, distance);
    e1->setReverse(e2);
    e2->setReverse(e1);
}

std::vector<Vertex *> Graph::getVertexSet() const {
    return this->vertexSet;
}

std::stack<Vertex*> Graph::savePath(Vertex* v){
    std::stack<Vertex*> path;
    path.push(vertexSet[0]);
    while (v->getPath() != nullptr) {
        path.push(v);
        v = v->getPath()->getOrig();
    }
    path.push(vertexSet[0]);
    return path;
}

void Graph::tspBT(std::stack<Vertex*> &bestPath, double &minDist) {
    for(Vertex* v: vertexSet)
        v->setVisited(false);

    Vertex* startingNode = vertexSet[0];

    startingNode->setVisited(true);
    startingNode->setPathCost(0);
    startingNode->setPath(nullptr);

    minDist = INF;
    tspBTRec(0, 0, minDist, bestPath);
}

void Graph::tspBTRec(int curVertex, int curIndex, double &minDist, std::stack<Vertex*> &bestPath) {
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
   auto e1 = w->addMstEdge(v, v->getPath()->getDistance());
   auto e2 = v->addMstEdge(w, v->getPath()->getDistance());
   e1->setReverse(e2);
   e2->setReverse(e1);
}

void Graph::prim() {
    if (vertexSet.empty()) return;
    for (auto v: vertexSet){
        v->setVisited(false);
        v->setPath(nullptr);
        v->setPathCost(INF);
        v->setMstAdj({});
        v->setMstIncoming({});
        v->setDegree(0);
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
}

void Graph::triangularApproximation(std::queue<Vertex*> &tour, double &dist) {
    prim();
    tour = preOrderTraversal();
    tour.push(vertexSet[0]);

    std::queue<Vertex*> aux = tour;
    Vertex* cur = aux.front();
    aux.pop();
    Vertex* next = aux.front();
    while (!aux.empty()){
        dist += distance(cur, next);
        cur = next;
        aux.pop();
        next = aux.front();
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
    return rad * c * 1000;

}

void Graph::preOrder(Vertex* vertex, std::queue<Vertex *> &l) {
    l.push(vertex);
    vertex->setVisited(true);
    for (Edge* edge : vertex->getMstAdj()) {
        Vertex* w = edge->getDest();
        if (!w->isVisited())
            preOrder(w,l);
    }
}


std::queue<Vertex *> Graph::preOrderTraversal() {
    std::queue<Vertex *> l;

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

void Graph::christofides() {

    /* (1) Prim algorithm to get a MST - T */
    prim();

    /* (2) Get all the vertexes with odd degree in T */
    std::unordered_set<Vertex*> oddVertexes = oddDegreeVertexes();

    /* (3) Add a minimum-weight perfect-matching of the odd vertices in T */
    perfectMatching(oddVertexes);

    /* (4) Find a Eulerian Circuit */
    std::vector<Vertex*> circuit = eurelianCircuit();

    /* (5) Transform the Circuit into a Hamiltonian Cycle */

}
/*0(E)*/
std::vector<Vertex*> Graph::eurelianCircuit() {
    for (auto v: vertexSet)
        for (auto e : v->getMstAdj()) {
            e->setSelected(false);
            e->getReverse()->setSelected(false);
        }
    std::vector<Vertex*> circuit;
    Vertex* startingNode = vertexSet[0];
    dfs(startingNode, circuit);
}

void Graph::dfs(Vertex* v, std::vector<Vertex*> &circuit){
    for (auto e: v->getMstAdj()) {
        if (!e->isSelected()) {
            e->setSelected(true);
            e->getReverse()->setSelected(true);
            std::cout << e->getOrig()->getId() << '\n';
            dfs(e->getDest(), circuit);

        }
    }
    circuit.push_back(v);
}

std::unordered_set<Vertex*> Graph::oddDegreeVertexes() {
    std::unordered_set<Vertex*> oddVertexes;
    for (Vertex* v: vertexSet)
        if (v->getDegree() % 2 != 0)
            oddVertexes.insert(v);
    return oddVertexes;
}

void Graph::matchVertexes(Edge* e){
    e->getDest()->setVisited(true);
    e->getOrig()->setVisited(true);
    e->getDest()->addMstEdge(e->getOrig(), e->getDistance());
    e->getOrig()->addMstEdge(e->getDest(), e->getDistance());
}

void Graph::perfectMatching(const std::unordered_set<Vertex*>& oddVertexes){
    for (auto v: oddVertexes)
        v->setVisited(false);

    std::set<Edge*, Edge::cmp> edges;
    int explored = 0;
    bool isOdd, isNew;

    for (Vertex* v: oddVertexes) {
        for (Edge *e: v->getAdj()) {
            isOdd = oddVertexes.find(e->getDest()) != oddVertexes.end();
            if (e->getDest()->getId() > v->getId() && isOdd)
                edges.insert(e);
        }
    }

    for (auto edge : edges){
        isNew = !edge->getDest()->isVisited() && !edge->getOrig()->isVisited();
        if (isNew) {
            matchVertexes(edge);
            explored += 2;
        }
        if (explored == oddVertexes.size()) return;
    }
}