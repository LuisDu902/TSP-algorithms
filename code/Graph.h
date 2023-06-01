#ifndef DA_GRAPH_H
#define DA_GRAPH_H

#include "VertexEdge.h"
#include <stack>
#include <queue>
#include <cmath>
#include <climits>
#include <set>
#include <unordered_set>
class Graph {
public:

    std::vector<Vertex *> getVertexSet() const;

    /**
     * @brief Finds and returns a vertex in the graph based on the provided ID.
     *
     * This function searches for a vertex with the specified ID in the graph's vertex set and returns a pointer to the found vertex.
     *
     * @param id The ID of the vertex to find.
     *
     * @return A pointer to the found vertex if it exists, or nullptr if the vertex is not found.
     *
     * @par Time complexity
     * O(V), where V the number of vertexes in the graph.
     */
    Vertex *findVertex(const int &id) const;

    /**
     * @brief Adds a new vertex to the graph with the specified ID, longitude, and latitude.
     *
     * This function creates a new vertex object with the provided ID, longitude, and latitude, and adds it to the graph's vertex set.
     *
     * @param id The ID of the vertex to find.
     * @param longitude The longitude coordinate of the vertex (default value: 0).
     * @param latitude The latitude coordinate of the vertex (default value: 0).
     *
     * @par Time complexity
     * O(1)
     */
    void addVertex(const int &id, const double &longitude = 0, const double &latitude = 0);

    /**
     * @brief Adds an edge between two vertices in the graph with the specified distance.
     *
     * This function adds an edge between the two provided vertices with the specified distance.
     *
     * @param v1 A pointer to the first vertex of the edge.
     * @param v2 A pointer to the second vertex of the edge.
     * @param distance The distance of the edge between the two vertices.
     *
     * @par Time complexity
     * O(1)
     */
    void addEdge(Vertex* &v1, Vertex* &v2, double distance) const;

    /**
     * @brief Saves the path from a specified vertex to the source vertex as a stack of vertex IDs.
     *
     * This function traverses the path from the specified vertex to the source vertex and saves the vertexes in a stack.
     *
     * @param v1 A pointer to the vertex from which to start traversing the path.
     *
     * @return A stack of vertexes representing the path.
     *
     * @par Time complexity
     * O(n), where n is the length of the path from the specified vertex to the source vertex.
     */
    std::stack<Vertex*> savePath(Vertex* v1);

    /**
     * @brief Solves the Traveling Salesman Problem (TSP) using backtracking.
     *
     * This function applies the backtracking algorithm to solve the TSP on the graph.
     * It finds the shortest Hamiltonian cycle that visits all vertices exactly once.
     *
     * @param bestPath Stack that will store the vertexes of the best path found.
     * @param minDist Minimum distance of the best path found.
     *
     * @par Time complexity
     * O(V!), where V is the number of vertexes in the graph.
     */
    void tspBT(std::stack<Vertex*> &bestPath, double &minDist);

    /**
     * @brief Recursive function for the TSP backtracking algorithm.
     *
     * This function is called recursively to explore all possible paths and find the best Hamiltonian cycle.
     * It uses backtracking to prune unnecessary branches based on the current minimum distance.
     *
     * @param curVertex The ID of the current vertex being visited.
     * @param curIndex The index of the current vertex in the path.
     * @param minDist The minimum distance found so far.
     * @param bestPath The stack that stores the vertexes of the best path found.
     *
     * @par Time complexity
     * O(V!), where V is the number of vertexes in the graph.
     */
    void tspBTRec(int curVertex, int curIndex, double &minDist, std::stack<Vertex*> &bestPath);

    void triangularApproximation(std::queue<Vertex*> &tour, double &dist);

    void prim();

    double haversine(double lat1, double lon1, double lat2, double lon2);

    std::queue<Vertex *> preOrderTraversal();
  
    void preOrder(Vertex *vertex, std::queue<Vertex *> &l);
  
    double distance(Vertex *v1, Vertex *v2);
  
    void nearestNeighborTSP(std::vector<Vertex *> &tour, double &distance);

    void christofides(std::vector<Vertex *> &tour, double &distance);

private:
    std::vector<Vertex *> vertexSet;

    void updateMst(Vertex *v);

    std::unordered_set<Vertex*> oddDegreeVertexes();
    void perfectMatching(const std::unordered_set<Vertex *>& oddVertexes);

    void matchVertexes(Edge *e);

    std::stack<Vertex *> eurelianCircuit();

    void dfs(Vertex *v, std::stack<Vertex *> &circuit);

    std::vector<Vertex *> hamiltonianCycle(std::stack<Vertex *> circuit);

    void twoOpt(std::vector<Vertex *> &tour, double &dist);
};

#endif //DA_GRAPH_H
