#include "VertexEdge.h"

/********************** Vertex ****************************/

Vertex::Vertex(int id, double longitude, double latitude): id(id), longitude(longitude), latitude(latitude) {}

void Vertex::addEdge(Vertex *d, double distance) {
    Edge* newEdge = new Edge(this, d, distance);
    adj.push_back(newEdge);
}

bool Vertex::operator<(Vertex & vertex) const {
    return this->pathCost < vertex.pathCost;
}

int Vertex::getId() const{
    return this->id;
}

std::vector<Edge *> Vertex::getAdj() const{
    return this->adj;
}

double Vertex::getPathCost() const {
    return this->pathCost;
}

Edge *Vertex::getPath() const {
    return this->path;
}

bool Vertex::isVisited() const{
    return this->visited;
}

void Vertex::setVisited(bool visited){
    this->visited = visited;
}

void Vertex::setPathCost(double pathCost) {
    this->pathCost = pathCost;
}

void Vertex::setPath(Edge *path) {
    this->path = path;
}


/********************** Edge ****************************/

Edge::Edge(Vertex *orig, Vertex *dest, double distance): orig(orig), dest(dest), distance(distance){}

Vertex * Edge::getDest() const{
    return this->dest;
}
Vertex * Edge::getOrig() const{
    return this->orig;
}
double Edge::getDistance() const{
    return this->distance;
}