#include "Supervisor.h"

Supervisor::Supervisor(std::string chosenGraph) {
    if (isRealGraph(chosenGraph)){
        createNodes(chosenGraph);
        createGraph(chosenGraph.append("/edges.csv"));
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

        graph.addEdge(orig, dest, distance);
    }
    myFile.close();
}
