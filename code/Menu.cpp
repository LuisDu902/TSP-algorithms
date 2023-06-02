#include "Menu.h"

Menu::Menu() {
    printf("\n");
    printf("===========================================================");
    std::cout << "\n\n" << " Welcome!\n (Press [0] whenever you wish to go back)\n\n";
}

void Menu::init() {
    int option;
    while(true) {
        std::cout << " Choose your graph?\n\n"
                     " [1] Toy-Graphs\n"
                     " [2] Real-world Graphs\n"
                     " [3] Extra-Fully-Connected Graphs\n"
                     " [4] Exit\n\n Option: ";

        std::cin >> option;
        switch (option) {
            case 1:
                toyGraphs();
                break;
            case 2:
                realWorldGraphs();
                break;
            case 3:
                extraGraphs();
                break;
            case 4:
                return;
            default:
                std::cout << "\n Invalid input, try again. \n\n";
        }
    }
}

void Menu::toyGraphs() {
    int option;
    bool isComplete = true;
    std::string filePath = "../data/Toy-Graphs/";
    while(true){
        std::cout << "\n What graph?\n\n"
                     " [1] Shipping\n"
                     " [2] Stadiums\n"
                     " [3] Tourism\n\n"
                     " Option: ";

        std::cin >> option;
        switch (option) {
            case 1:
                filePath.append("shipping.csv");
                isComplete = false;
                break;
            case 2:
                filePath.append("stadiums.csv");
                break;
            case 3:
                filePath.append("tourism.csv");
                break;
            case 0:
                std::cout << "\n";
                return;
            default:
                std::cout << "\n Invalid input, try again. \n";
                continue;
        }
        break;
    }
    supervisor = new Supervisor(filePath);
    operations(true, isComplete);
}


void Menu::extraGraphs() {
    int option;
    std::unordered_set<int> s{25, 50, 75, 100, 200, 300, 400, 500, 600, 700, 800, 900};
    std::string filePath = "../data/Extra_Fully_Connected_Graphs/edges_";
    while(true){
        std::cout << "\n Choose the number of nodes\n\n"
                     " Number: ";

        std::cin >> option;
        if (s.find(option) != s.end()){
            filePath.append(std::to_string(option)).append(".csv");
            break;
        }
        else if (option == 0){
            std::cout << "\n";
            return;
        }
        else{
            std::cout << "\n Invalid input, try again. \n";
        }
    }
    supervisor = new Supervisor(filePath);
    operations(false, true);
}

void Menu::realWorldGraphs() {
    int option;
    bool isComplete = false;
    std::string filePath = "../data/Real-world Graphs/";
    while(true){
        std::cout << "\n What graph?\n\n"
                     " [1] graph1\n"
                     " [2] graph2\n"
                     " [3] graph3\n\n"
                     " Option: ";

        std::cin >> option;
        switch (option) {
            case 1:
                filePath.append("graph1");
                isComplete = true;
                break;
            case 2:
                filePath.append("graph2");
                break;
            case 3:
                filePath.append("graph3");
                break;
            case 0:
                std::cout << "\n";
                return;
            default:
                std::cout << "\n Invalid input, try again. \n";
                continue;
        }
        break;
    }
    supervisor = new Supervisor(filePath);
    operations(false, isComplete);
}

void Menu::operations(bool smallGraph, bool completeGraph) {
    int option;
    while(true) {
        std::cout << " Choose your operation?\n\n"
                     " [1] Brute force\n"
                     " [2] Triangular approximation\n"
                     " [3] Christofides with 2-opt\n"
                     " [4] Nearest neighbour\n"
                     " [5] Nearest insertion\n\n"
                     " Option: ";

        std::cin >> option;
        switch (option) {
            case 1:
                if (smallGraph) bruteForce();
                else std::cout << " This graph is too large to use brute force!!!\n";
                break;
            case 2:
                if (!smallGraph || completeGraph) triangularApproximation();
                else std::cout << " This graph is not fully connected and we can't calculate the distances\n";
                break;
            case 3:
                if (completeGraph) christofides();
                else std::cout << " This graph is not fully connected\n";
                break;
            case 4:
                if (completeGraph) nearestNeighbor();
                else std::cout << " This graph is not fully connected\n";
                break;
            case 5:
                if (completeGraph) christofides();
                else std::cout << " This graph is not fully connected\n";
                break;
            case 0:
                std::cout << "\n";
                return;
            default:
                std::cout << "\n Invalid input, try again. \n\n";
                continue;
        }
    }
}

void Menu::bruteForce() {
    std::stack<Vertex*> path;
    double dist = 0;

    std::chrono::steady_clock::time_point startTime = std::chrono::steady_clock::now();

    supervisor->getGraph().tspBT(path, dist);

    std::chrono::steady_clock::time_point endTime = std::chrono::steady_clock::now();

    std::chrono::duration<double, std::milli> duration = std::chrono::duration_cast<std::chrono::duration<double, std::milli>>(endTime - startTime);

    double time = duration.count();

    std::cout << "\n Path: ";
    while (!path.empty()){
        std::cout << path.top()->getId() << " ";
        path.pop();
    }
    std::cout << "\n Distance: " << dist << " meters\n";
    std::cout << " Execution Time: " << time << " milliseconds\n\n";
}


void Menu::triangularApproximation(){
    std::queue<Vertex*> path;
    double dist = 0;

    std::chrono::steady_clock::time_point startTime = std::chrono::steady_clock::now();

    supervisor->getGraph().triangularApproximation(path, dist);

    std::chrono::steady_clock::time_point endTime = std::chrono::steady_clock::now();

    std::chrono::duration<double, std::milli> duration = std::chrono::duration_cast<std::chrono::duration<double, std::milli>>(endTime - startTime);

    double time = duration.count();


    if (path.size() <= 50) {
        std::cout << "\n Path: ";
        while (!path.empty()) {
            std::cout << path.front()->getId() << " ";
            path.pop();
        }
    }

    std::cout << "\n Distance: " << dist << " meters\n";
    std::cout << " Execution Time: " << time << " milliseconds\n\n";
}


void Menu::nearestNeighbor() {
    std::vector<Vertex *> tour;
    double dist = 0;

    std::chrono::steady_clock::time_point startTime = std::chrono::steady_clock::now();

    supervisor->getGraph().nearestNeighborTSP(tour, dist);
  
    std::chrono::steady_clock::time_point endTime = std::chrono::steady_clock::now();

    std::chrono::duration<double, std::milli> duration = std::chrono::duration_cast<std::chrono::duration<double, std::milli>>(endTime - startTime);

    double time = duration.count();

    if (tour.size() < 50) {
        std::cout << "\n Path: ";
        for (Vertex *v: tour)
            std::cout << v->getId() << " ";
    }

    std::cout << "\n Distance: " << dist << " meters\n";
    std::cout << " Execution Time: " << time << " milliseconds\n\n";
  
}

void Menu::christofides(){
    std::queue<Vertex*> tour;
    double triangular = 0;
    supervisor->getGraph().triangularApproximation(tour, triangular);

    std::vector<Vertex *> path;
    double dist = 0;

    std::chrono::steady_clock::time_point startTime = std::chrono::steady_clock::now();

    supervisor->getGraph().christofidesTSP(path, dist);

    std::chrono::steady_clock::time_point endTime = std::chrono::steady_clock::now();

    std::chrono::duration<double, std::milli> duration = std::chrono::duration_cast<std::chrono::duration<double, std::milli>>(endTime - startTime);

    double time = duration.count();

    if (path.size() <= 50) {
        std::cout << "\n Path: ";
        for (auto p : path)
            std::cout << p->getId() << " ";
    }

    std::cout << "\n Distance: " << dist << " meters\n";
    std::cout << " Execution Time: " << time << " milliseconds\n";
    std::cout << " Compared to triangular approximation, distance improved by " << ((triangular - dist) / triangular) * 100 << " %\n\n";
}

void Menu::end() {
    printf("\n");
    printf("===========================================================");
}