#ifndef DA_VERTEXEDGE_H
#define DA_VERTEXEDGE_H

#include <iostream>
#include <vector>
#include <limits>
#include <algorithm>
#include "MutablePriorityQueue.h"

#define INF std::numeric_limits<int>::max()

/********************** Vertex ****************************/

class Edge;

class Vertex {
public:
    Vertex(int id, double longitude, double latitude);
    bool operator<(Vertex & vertex) const;

    void addEdge(Vertex *d, double distance);
    void addMstEdge(Vertex *d, double distance);

    int getId() const;
    std::vector<Edge *> getAdj() const;
    std::vector<Edge *> getMstAdj() const;
    double getPathCost() const;
    Edge* getPath() const;
    int getDegree() const;
    bool isVisited() const;

    void setVisited(bool visited);
    void setPathCost(double pathCost);
    void setPath(Edge *path);

    friend class MutablePriorityQueue<Vertex>;

    double getLatitude();

    double getLongitude();

protected:
    int id;
    std::vector<Edge *> adj;
    std::vector<Edge *> mstAdj;
    bool visited = false;
    double longitude;
    double latitude;
    double pathCost = 0;
    int degree = 0;
    Edge *path = nullptr;
    int queueIndex = 0;

};

/********************** Edge ****************************/

class Edge {
public:
    Edge(Vertex *orig, Vertex *dest, double distance);

    Vertex * getDest() const;
    Vertex * getOrig() const;
    double getDistance() const;
protected:
    Vertex * dest;
    Vertex *orig;
    double distance;

};

#endif //DA_VERTEXEDGE_H
