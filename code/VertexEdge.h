#ifndef DA_VERTEXEDGE_H
#define DA_VERTEXEDGE_H

#include <iostream>
#include <vector>
#include <limits>
#include <algorithm>

#define INF std::numeric_limits<int>::max()

/********************** Vertex ****************************/

class Edge;

class Vertex {
public:
    Vertex(int id, double longitude, double latitude);

    void addEdge(Vertex *d, double distance);

    int getId() const;
    std::vector<Edge *> getAdj() const;
    double getPathCost() const;
    Edge* getPath() const;
    bool isVisited() const;

    void setVisited(bool visited);
    void setPathCost(double pathCost);
    void setPath(Edge *path);

private:
    int id;
    std::vector<Edge *> adj;
    bool visited = false;
    double longitude;
    double latitude;
    double pathCost = 0;
    Edge *path = nullptr;
};

/********************** Edge ****************************/

class Edge {
public:
    Edge(Vertex *orig, Vertex *dest, double distance);

    Vertex * getDest() const;
    Vertex * getOrig() const;

    double getDistance() const;

private:
    Vertex * dest;
    Vertex *orig;
    double distance;
};

#endif //DA_VERTEXEDGE_H
