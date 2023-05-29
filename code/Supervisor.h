#ifndef DA_SUPERVISOR_H
#define DA_SUPERVISOR_H

#include <fstream>
#include <istream>
#include <sstream>
#include <iostream>
#include <vector>
#include <unordered_map>
#include <list>

#include "Graph.h"

class Supervisor{
public:


    Graph getGraph() const;

    /**
     * Initializes the graph according to the chosen path.
     *
     * @param path The file path where the graph data is located.
     * @param isRealGraph  A boolean flag indicating whether the graph is a real graph or not.
     */
    Supervisor(std::string path, bool isRealGraph);

private:

    /**
     * @brief Reads graph data from a CSV file and creates a graph.
     *
     * This function reads data from a CSV file and creates a graph based on the data.
     *
     * @param chosenGraph The file path to the directory containing the graph CSV file.
     *
     * @par Time complexity
     * O(V * E), where V is the number of vertexes and E the number of edges in the graph.
     */
    void createGraph(std::string chosenGraph);

    /**
     * @brief Reads node data from a CSV file and creates vertices in the graph.
     *
     * This function reads node data from a CSV file and creates vertices in the graph based on the data.
     *
     * @param chosenGraph The file path to the directory containing the nodes CSV file.
     *
     * @par Time complexity
     * O(V), where V is the number of vertexes to create.
     */
    void createNodes(std::string chosenGraph);

    /**
     * @brief Reads edges data from a CSV file and creates edges in the graph.
     *
     * This function reads edges data from a CSV file and creates edges in the graph based on the data.
     *
     * @param chosenGraph The file path to the directory containing the nodes CSV file.
     *
     * @par Time complexity
     * O(E), where E the number of edges to create.
     */
    void createEdges(std::string chosenGraph);

    Graph graph;
};

#endif //DA_SUPERVISOR_H
