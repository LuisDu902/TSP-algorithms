#ifndef DA_GRAPH_H
#define DA_GRAPH_H

#include "VertexEdge.h"

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
     * @brief Adds an edge between two vertexes in the graph with the specified distance.
     *
     * This function adds an edge between the two provided vertexes with the specified distance.
     *
     * @param v1 A pointer to the first vertex of the edge.
     * @param v2 A pointer to the second vertex of the edge.
     * @param distance The distance of the edge between the two vertexes.
     *
     * @par Time complexity
     * O(1)
     */
    void addEdge(Vertex* &v1, Vertex* &v2, double distance) const;

    /**
     * @brief Solves the Traveling Salesman Problem (TSP) using backtracking.
     *
     * This function applies the backtracking algorithm to solve the TSP on the graph.
     * It finds the shortest Hamiltonian cycle that visits all vertexes exactly once.
     *
     * @param bestPath Stack that will store the vertexes of the best path found.
     * @param minDist Minimum distance of the best path found.
     *
     * @par Time complexity
     * O(V!), where V is the number of vertexes in the graph.
     */
    void tspBT(std::stack<Vertex*> &bestPath, double &minDist);

    /**
     * @brief Solves the Traveling Salesman Problem (TSP) using triangular approximation algorithm
     *
     * This function applies the triangular approximation algorithm to the graph, which consists in :\n
     * <pre><b>(1)</b> Constructing a minimum spanning tree (MST) of the graph using Prim's algorithm.</pre>
     * <pre><b>(2)</b> Traversing the tree using a pre-order traversal.</pre>
     * <pre><b>(3)</b> Computing a Hamiltonian cycle that visits all vertexes exactly once based on the pre-order.</pre>
     *
     * @param tour The queue to store the resulting tour.
     * @param dist The reference variable to accumulate the total distance of the tour.
     *
     * @par Time complexity
     * O(E * log(V)), where V is the number of vertexes and E the number of edges in the graph.
     */
    void triangularApproximation(std::queue<Vertex*> &tour, double &dist);

    /**
     * @brief Solves the Traveling Salesman Problem (TSP) using nearest neighbor algorithm
     *
     * This function applies the nearest neighbor algorithm to the graph, which consists in:\n
     * <pre><b>(1)</b> Initializing all vertexes as unvisited.</pre>
     * <pre><b>(2)</b> Selecting the first vertex, setting it as the current vertex. Mark it as visited.</pre>
     * <pre><b>(3)</b> Finding out the shortest edge connecting the current vertex u and an unvisited vertex v.</pre>
     * <pre><b>(4)</b> Setting v as the current vertex. Mark v as visited.</pre>
     * <pre><b>(5)</b> Repeating steps 3 and 4 until all the vertexes are visited.</pre>
     *
     * @param tour The vector to store the resulting tour.
     * @param distance The reference variable to accumulate the total distance of the tour.
     *
     * @par Time complexity
     * O(E + V), where V is the number of vertexes and E the number of edges in the graph.
     */
    void nearestNeighborTSP(std::vector<Vertex *> &tour, double &distance);

    /**
     * @brief Solves the Traveling Salesman Problem (TSP) using christofides algorithm combined with 2-opt
     *
     * This function applies the christofides algorithm to the graph, which consists in:\n
     * <pre><b>(1)</b> Constructing a minimum spanning tree (MST) of the graph using Prim's algorithm.</pre>
     * <pre><b>(2)</b> Identifying the vertexes with odd degrees in the MST.</pre>
     * <pre><b>(3)</b> Constructing a minimum-weight perfect matching among the odd-degree vertexes.</pre>
     * <pre><b>(4)</b> Computing an Eulerian circuit in the graph by combining the MST edges and matching edges.</pre>
     * <pre><b>(5)</b> Obtaining a Hamiltonian cycle by removing duplicate vertexes from the circuit.</pre>
     * <pre><b>(6)</b> Improving the tour using the 2-opt optimization algorithm.</pre>
     *
     * @param tour The vector to store the resulting tour.
     * @param distance The reference variable to accumulate the total distance of the tour.
     *
     * @par Time complexity
     * O(E * log(V)), where V is the number of vertexes and E the number of edges in the graph.
     */
    void christofidesTSP(std::vector<Vertex *> &tour, double &distance);

private:
    std::vector<Vertex *> vertexSet;

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

    /**
     *  @brief Applies Prim's algorithm to find a minimum spanning tree in the graph.
     *
     * This function applies Prim's algorithm to the graph, starting from the first vertex in the vertexSet.
     * It initializes the necessary data structures and maintains a priority queue to track the minimum
     * path costs. The minimum spanning tree is constructed by iteratively adding the minimum cost edges.
     *
     *  @par Time complexity
     *  O(E * log(V)), where V is the number of vertexes and E the number of edges in the graph.
     */
    void prim();

    /**
     * @brief Calculates the distance between two vertexes using the Haversine formula.
     *
     * The Haversine formula is used to compute the great-circle distance between two points given their
     * latitude and longitude coordinates. The function takes the latitude and longitude of the two points (vertexes)
     * as parameters and returns the distance between them in meters.
     *
     * @param lat1 Latitude of the first vertex.
     * @param lon1 Longitude of the first vertex.
     * @param lat2 Latitude of the second vertex.
     * @param lon2 Longitude of the second vertex.
     *
     * @return The distance between the two vertex in meters.
     *
     * @par Time complexity
     * O(1)
     */
    double haversine(double lat1, double lon1, double lat2, double lon2);

    /**
     * @brief Performs a pre-order traversal of the minimum spanning tree rooted at 0.
     *
     * The function performs a pre-order traversal of the minimum spanning tree rooted at 0, using a depth-first search algorithm.
     *
     * @return A queue containing the vertexes in the order of pre-order traversal.
     *
     * @par Time complexity
     * O(V), where V is the number of vertexes in the graph.
     */
    std::queue<Vertex *> preOrderTraversal();

    /**
     * @brief Performs a pre-order traversal of the minimum spanning tree rooted at 0.
     *
     * The function recursively traverses the minimum spanning tree rooted at 0 in pre-order.
     * It adds each visited vertex to the `l` queue, indicating the order of traversal.
     * The function performs the traversal using a depth-first search algorithm.
     *
     * @param vertex Pointer to the root vertex of the minimum spanning tree.
     * @param l Reference to the queue used to store the order of traversal.
     *
     * @par Time complexity
     * O(V), where V is the number of vertexes in the graph.
     */
    void preOrder(Vertex *vertex, std::queue<Vertex *> &l);

    /**
     * @brief Calculates the distance between two vertexes in the graph.
     *
     * The function first checks if there is an edge between the two vertexes. If an edge is found,
     * the distance is retrieved from the edge. If there is no direct edge, the function calculates the
     * distance using the haversine formula.
     *
     * @param v1 Pointer to the first vertex.
     * @param v2 Pointer to the second vertex.
     *
     * @return The distance between the two vertexes.
     *
     * @par Time complexity
     * O(n), where n is the number of adjacent edges of vertex v1.
     */
    double distance(Vertex *v1, Vertex *v2);

    /**
     * @brief Updates the minimum spanning tree (MST) when a new edge is added.
     *
     * The function updates the MST by adding two new MST edges between the vertex `v` and its predecessor vertex `w` in the MST .
     *
     * @param v Pointer to the new vertex added to the MST.
     *
     * @par Time complexity
     * O(1)
     */
    void updateMst(Vertex *v);

    /**
      * @brief Calculates the set of vertexes with an odd degree in the mst.
      *
      * The function iterates over each vertex in the `vertexSet` and checks if its degree is odd.
      * If a vertex has an odd degree, it is added to the `oddVertexes` set. Finally, the function
      * returns the vertexes with odd degrees.
      *
      * @return A vector of vertexes with odd degrees.
      *
      * @par Time complexity
      * O(V), where V is the number of vertexes in the graph.
      */
    std::vector<Vertex*> oddDegreeVertexes();

    /**
     * @brief Performs a perfect matching among the odd-degree vertexes in the mst using a greedy algorithm.
     *
     * The function performs a perfect matching among all the odd-degree vertexes in the mst using a greedy algorithm.
     * Firstly, all the edges that connect odd-degree vertexes are sorted in ascending order based on their distance.
     * It then iteratively selects the lightest weight edge from the sorted set and matches two unmatched vertexes
     * until all vertexes are matched.
     *
     * @param oddVertexes A vector of odd-degree vertexes to be matched.
     *
     * @par Time complexity
     * O(E * log(E)), where E is the number of edges in the graph.
     */
    void perfectMatching(const std::vector<Vertex *>& oddVertexes);

    /**
     * @brief Matches two vertexes by adding corresponding edges between them.
     *
     * This function matches two odd-degree vertexes by adding a bidirectional edge to connect them.
     *
     * @param e The edge connecting the two vertexes to be matched.
     *
     * @par Time complexity
     * O(1)
     */
    void matchVertexes(Edge *e);

    /**
     * @brief Finds an Eulerian circuit in the graph using Hierholzer's algorithm.
     *
     * The function computes an eulerian circuit using Hierholzer's algorithm.
     *
     * @return A stack of vertexes representing the Eulerian circuit in the graph.
     *
     * @par Time complexity
     * O(E), where E is the number of edges in the graph
     */
    std::stack<Vertex *> eulerianCircuit();

    /**
     * @brief Recursively performs Hierholzer's algorithm to construct an Eulerian circuit in the graph.
     *
     * This function iterates through the adjacency list of vertex `v` and selects each unvisited edge
     * and its reverse edge. For each selected edge, it marks the edges as visited. Then, the function recursively
     * calls itself on the destination vertex of the selected edge. This process continues until all edges
     * have been visited. Finally, it pushes the current vertex `v` onto the stack `circuit`.
     *
     * @param v The current vertex in the recursive step of Hierholzer's algorithm.
     * @param circuit The stack to store the vertexes in the Eulerian circuit.
     *
     * @par Time complexity
     * O(E), where E is the number of edges in the graph
     */
    void heirholzer(Vertex *v, std::stack<Vertex *> &circuit);

    /**
     * @brief Constructs a Hamiltonian cycle from an Eulerian circuit.
     *
     * This function computes a Hamiltonian cycle from an Eulerian circuit, by ignoring the repeated vertexes.
     *
     * @param circuit The stack representing an Eulerian circuit in the graph.
     * @return A vector of vertexes representing a Hamiltonian cycle in the graph.
     *
     * @par Time complexity
     * O(V), where V is the number of vertexes in the graph
     */
    std::vector<Vertex *> hamiltonianCycle(std::stack<Vertex *> circuit);

    /**
     * @brief Applies the 2-opt optimization heuristic to improve a tour by removing intersecting edges.
     *
     * This function applies the 2-opt optimization heuristic to improve a given tour.
     * It iteratively takes 2 edges from the tour, reconnect these edges with each other and calculate
     * new travel distance. If this modification has led to a shorter total travel distance the current route is updated.
     * The algorithm continues to build on the improved route and repeats the steps until the tour in optimal
     * or the maximum number of iterations has been reached.

     * @param tour The vector representing the tour to be optimized.
     * @param dist The initial distance of the tour, which will be updated with the improved distance.
     *
     * @par Time complexity
     * O(V³), where V is the number of vertexes in the graph
     */
    void twoOpt(std::vector<Vertex *> &tour, double &dist);
};

#endif //DA_GRAPH_H
