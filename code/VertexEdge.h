#ifndef DA_VERTEXEDGE_H
#define DA_VERTEXEDGE_H

#include <iostream>
#include <vector>
#include <limits>
#include <algorithm>
#include <stack>
#include <queue>
#include <cmath>
#include <climits>
#include <set>
#include <unordered_set>
#include "PriorityQueue.h"

#define INF std::numeric_limits<int>::max()

/********************** Vertex ****************************/

class Edge;

class Vertex {
public:
    Vertex(int id, double longitude, double latitude);
    bool operator<(Vertex & vertex) const;

    Edge* addEdge(Vertex *d, double distance);
    Edge* addMstEdge(Vertex *d, double distance);

    int getId() const;
    std::vector<Edge *> getAdj() const;
    std::vector<Edge *> getMstAdj() const;
    double getPathCost() const;
    Edge* getPath() const;
    int getDegree() const;
    bool isVisited() const;
    double getLatitude() const;
    double getLongitude() const;

    void setVisited(bool visited);
    void setDegree(int degree);
    void setPathCost(double pathCost);
    void setPath(Edge *path);
    void setMstAdj(std::vector<Edge*> mstAdj);

    friend class PriorityQueue;

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
    Edge *getReverse() const;
    bool isSelected() const;

    void setSelected(bool selected);
    void setReverse(Edge *reverse);

protected:
    Vertex * dest;
    Vertex *orig;
    Edge *reverse = nullptr;
    double distance;
    bool selected = false;
};

#endif //DA_VERTEXEDGE_H
