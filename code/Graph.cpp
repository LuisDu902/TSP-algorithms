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

double Graph::distance(Vertex* v1, Vertex* v2){
    for (Edge* e: v1->getAdj())
        if (e->getDest() == v2)
            return e->getDistance();
    return haversine(v1->getLatitude(),v1->getLongitude(),v2->getLatitude(),v2->getLongitude());
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
            v2->setPath(edge);
            v2->setPathCost(v1->getPathCost() + distance);
            v2->setVisited(true);
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
        v->setDegree(0);
    }
    PriorityQueue q;

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

void Graph::nearestNeighborTSP(std::vector<Vertex *> &tour, double &distance) {
    for (auto v : vertexSet)
        v->setVisited(false);

    Vertex* currentVertex = vertexSet[0];
    currentVertex->setVisited(true);

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

    distance += currentVertex->getAdj()[0]->getDistance();
    tour.push_back(vertexSet[0]);
}

void Graph::christofidesTSP(std::vector<Vertex *> &tour, double &dist) {

    prim();

    std::vector<Vertex*> oddVertexes = oddDegreeVertexes();
    perfectMatching(oddVertexes);

    std::stack<Vertex*> circuit = eulerianCircuit();

    tour = hamiltonianCycle(circuit);
    tour.push_back(vertexSet[0]);

    for (int i = 0; i < tour.size()-1; i++){
        if (tour[i]->getId() < tour[i+1]->getId())
            dist += tour[i+1]->getAdj()[tour[i]->getId()]->getDistance();
        else
            dist += tour[i]->getAdj()[tour[i+1]->getId()]->getDistance();
    }

    twoOpt(tour, dist);

}

std::vector<Vertex*> Graph::oddDegreeVertexes() {
    std::vector<Vertex*> oddVertexes;
    for (Vertex* v: vertexSet)
        if (v->getDegree() % 2 != 0)
            oddVertexes.push_back(v);
    return oddVertexes;
}

void Graph::matchVertexes(Edge* e){
    e->getDest()->setVisited(true);
    e->getOrig()->setVisited(true);
    auto e1 = e->getDest()->addMstEdge(e->getOrig(), e->getDistance());
    auto e2 = e->getOrig()->addMstEdge(e->getDest(), e->getDistance());
    e1->setReverse(e2);
    e2->setReverse(e1);
}

void Graph::perfectMatching(const std::vector<Vertex*>& oddVertexes){
    for (auto v: oddVertexes)
        v->setVisited(false);

    std::vector<Edge*> edges;
    int explored = 0;
    bool isOdd, isNew;

    for (int i = 0; i < oddVertexes.size()-1; i++) {
        Vertex* v = oddVertexes[i];
        for (Edge *e: v->getAdj()) {
            isOdd = e->getDest()->getDegree() % 2 != 0;
            if (e->getDest()->getId() > v->getId() && isOdd)
                edges.push_back(e);
        }
    }
    std::sort(edges.begin(), edges.end(), [](const Edge* a, const Edge* b) {
        return a->getDistance() < b->getDistance();
    });

    for (auto edge : edges){
        isNew = !edge->getDest()->isVisited() && !edge->getOrig()->isVisited();
        if (isNew) {
            matchVertexes(edge);
            explored += 2;
        }
        if (explored == oddVertexes.size()) return;
    }
}

std::stack<Vertex*> Graph::eulerianCircuit() {
    for (auto v: vertexSet) {
        for (auto e: v->getMstAdj()) {
            e->setSelected(false);
            e->getReverse()->setSelected(false);
        }
    }
    std::stack<Vertex*> circuit;
    Vertex* startingNode = vertexSet[0];
    heirholzer(startingNode, circuit);
    return circuit;
}

void Graph::heirholzer(Vertex* v, std::stack<Vertex*> &circuit){
    for (auto e: v->getMstAdj()) {
        if (!e->isSelected()) {
            e->setSelected(true);
            e->getReverse()->setSelected(true);
            heirholzer(e->getDest(), circuit);
        }
    }
    circuit.push(v);
}

void Graph::twoOpt(std::vector<Vertex*>& tour, double& dist) {
    bool improved = true;
    double dAB, dAC, dCD, dBD;
    Vertex* vertexA; Vertex* vertexB; Vertex* vertexC; Vertex* vertexD;
    int n = 3;
    while (improved && n--) {
        improved = false;

        for (int i = 0; i < tour.size() - 2; i++) {
            vertexA = tour[i];
            vertexB = tour[i + 1];

            dAB = (vertexA->getId() > vertexB->getId()) ? vertexA->getAdj()[vertexB->getId()]->getDistance() : vertexB->getAdj()[vertexA->getId()]->getDistance();
            for (int j = i + 2; j < tour.size()-1; j++) {
                vertexC = tour[j];
                vertexD = tour[j + 1];
                dCD = (vertexC->getId() > vertexD->getId()) ? vertexC->getAdj()[vertexD->getId()]->getDistance() : vertexD->getAdj()[vertexC->getId()]->getDistance();
                dAC = (vertexA->getId() > vertexC->getId()) ? vertexA->getAdj()[vertexC->getId()]->getDistance() : vertexC->getAdj()[vertexA->getId()]->getDistance();
                dBD = (vertexB->getId() > vertexD->getId()) ? vertexB->getAdj()[vertexD->getId()]->getDistance() : vertexD->getAdj()[vertexB->getId()]->getDistance();

                double currentDistance = dAB + dCD;
                double newDistance = dAC + dBD;

                if (newDistance < currentDistance) {
                    std::reverse(tour.begin() + i + 1, tour.begin() + j + 1);
                    improved = true;
                    vertexA = tour[i];
                    vertexB = tour[i + 1];
                    dAB = (vertexA->getId() > vertexB->getId()) ? vertexA->getAdj()[vertexB->getId()]->getDistance() : vertexB->getAdj()[vertexA->getId()]->getDistance();
                }
            }
        }
    }
    dist = 0;
    for (int i= 0; i < tour.size()-1; i++){
        if (tour[i]->getId() < tour[i+1]->getId())
            dist += tour[i+1]->getAdj()[tour[i]->getId()]->getDistance();
        else
            dist += tour[i]->getAdj()[tour[i+1]->getId()]->getDistance();
    }
}

std::vector<Vertex*> Graph::hamiltonianCycle(std::stack<Vertex*> circuit){
    for (auto v: vertexSet)
        v->setVisited(false);

    std::vector<Vertex*> tour;
    Vertex* cur;
    while (!circuit.empty()){
        cur = circuit.top();
        if (!cur->isVisited()){
            cur->setVisited(true);
            tour.push_back(cur);
        }
        circuit.pop();
    }
    return tour;
}

void Graph::nearestInsertion(std::vector<Vertex *>& tour,double &dist){

    for (auto vertex : vertexSet) {
        vertex->setVisited(false);
        vertex->setPath(nullptr);
        vertex->setPathCost(std::numeric_limits<double>::infinity());
    }

    tour.push_back(vertexSet[0]);
    vertexSet[0]->setVisited(true);

    while (tour.size() < vertexSet.size()) {
        Vertex* currentNode = nullptr;
        Edge* nextNode = nullptr;
        double minDistance = std::numeric_limits<double>::infinity();
            for (auto e : tour[tour.size()-1]->getAdj()) {
                if (!e->getDest()->isVisited()) {
                    double distance = e->getDistance();
                    if (distance < minDistance) {
                        minDistance = distance;
                        currentNode = tour[tour.size()-1];
                        nextNode = e;
                    }
                }
            }

        auto it = std::find(tour.begin(), tour.end(), currentNode);
        tour.insert(it + 1, nextNode->getDest());
        nextNode->getDest()->setVisited(true);
        nextNode->getDest()->setPath(nextNode);
        nextNode->getDest()->setPathCost(minDistance);
    }
    tour.push_back(vertexSet[0]);
    for (int i= 0; i < tour.size()-1; i++){
        if (tour[i]->getId() < tour[i+1]->getId())
            dist += tour[i+1]->getAdj()[tour[i]->getId()]->getDistance();
        else
            dist += tour[i]->getAdj()[tour[i+1]->getId()]->getDistance();
    }

    twoOpt(tour,dist);

}