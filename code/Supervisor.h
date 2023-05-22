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

    Supervisor(std::string chosenGraph);

private:

    void createGraph(std::string chosenGraph);
    void createNodes(std::string chosenGraph);
    void createEdges(std::string chosenGraph);
    bool isRealGraph(std::string chosenGraph);

    Graph graph;
};

#endif //DA_SUPERVISOR_H
