#include <stack>
#include "Supervisor.h"

Supervisor::Supervisor(std::string chosenGraph) {
    if (isRealGraph(chosenGraph)){
        createNodes(chosenGraph);
        createEdges(chosenGraph);
    }
    else {
        createGraph(chosenGraph);
    }
}

bool Supervisor::isRealGraph(std::string chosenGraph){
    chosenGraph.pop_back();
    return chosenGraph == "../data/Real-world Graphs/graph";
}

void Supervisor::createNodes(std::string chosenGraph) {
    std::ifstream myFile;
    std::string line, field;
    int id;
    double longitude, latitude;
    myFile.open(chosenGraph.append("/nodes.csv"));
    getline(myFile, line);

    while (getline(myFile,line)){
        std::istringstream iss(line);
        getline(iss,field,',');
        id = std::stoi(field);
        getline(iss,field,',');
        longitude = std::stod(field);
        getline(iss,field,',');
        latitude = std::stod(field);

        graph.addVertex(id, longitude, latitude);
    }
    myFile.close();

}

void Supervisor::createGraph(std::string chosenGraph) {

    std::ifstream myFile;
    std::string line, field;
    int orig, dest;
    double distance;
    myFile.open(chosenGraph);
    getline(myFile, line);

    while (getline(myFile,line)){
        std::istringstream iss(line);
        getline(iss,field,',');
        orig = std::stoi(field);
        getline(iss,field,',');
        dest = std::stoi(field);
        getline(iss,field,',');
        distance = std::stod(field);

        if (graph.findVertex(orig) == nullptr) graph.addVertex(orig);
        if (graph.findVertex(dest) == nullptr) graph.addVertex(dest);

        Vertex* v1 = graph.findVertex(orig);
        Vertex* v2 = graph.findVertex(dest);

        graph.addEdge(v1, v2, distance);
    }
    myFile.close();
}


void Supervisor::createEdges(std::string chosenGraph) {

    std::ifstream myFile;
    std::string line, field;
    int orig, dest;
    double distance;
    myFile.open(chosenGraph.append("/edges.csv"));
    getline(myFile, line);

    std::vector<Vertex*> vertexSet = graph.getVertexSet();

    while (getline(myFile,line)){
        std::istringstream iss(line);
        getline(iss,field,',');
        orig = std::stoi(field);
        getline(iss,field,',');
        dest = std::stoi(field);
        getline(iss,field,',');
        distance = std::stod(field);

        Vertex* v1 = vertexSet[orig];
        Vertex* v2 = vertexSet[dest];

        graph.addEdge(v1, v2, distance);
    }
    myFile.close();
}

Graph Supervisor::getGraph() const{
    return graph;
}