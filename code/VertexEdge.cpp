#include "VertexEdge.h"

/********************** Vertex ****************************/

Vertex::Vertex(int id, double longitude, double latitude): id(id), longitude(longitude), latitude(latitude) {}

Edge* Vertex::addEdge(Vertex *d, double distance) {
    Edge* newEdge = new Edge(this, d, distance);
    adj.push_back(newEdge);
    return newEdge;
}

Edge* Vertex::addMstEdge(Vertex *d, double distance) {
    Edge* newEdge = new Edge(this, d, distance);
    mstAdj.push_back(newEdge);
    degree++;
    return newEdge;
}

bool Vertex::operator<(Vertex & vertex) const {
    return this->pathCost < vertex.pathCost;
}

int Vertex::getId() const{
    return this->id;
}
int Vertex::getDegree() const{
    return this->degree;
}

std::vector<Edge *> Vertex::getAdj() const{
    return this->adj;
}

std::vector<Edge *> Vertex::getMstAdj() const{
    return this->mstAdj;
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

void Vertex::setMstAdj(std::vector<Edge*> mstAdj){
    this->mstAdj = mstAdj;
}

void Vertex::setDegree(int degree){
    this->degree = degree;
}

void Vertex::setPathCost(double pathCost) {
    this->pathCost = pathCost;
}

void Vertex::setPath(Edge *path) {
    this->path = path;
}

double Vertex::getLatitude() const{
    return this->latitude;
}

double Vertex::getLongitude() const{
    return this->longitude;
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

bool Edge::isSelected() const {
    return this->selected;
}

void Edge::setSelected(bool selected) {
    this->selected = selected;
}

Edge *Edge::getReverse() const {
    return this->reverse;
}

void Edge::setReverse(Edge *reverse) {
    this->reverse = reverse;
}