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
    std::cin.clear();
    int option;
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
    operations();
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
    operations();
}

void Menu::realWorldGraphs() {
    int option;
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
    operations();
}

void Menu::operations() {
    int option;
    while(true) {
        std::cout << " Choose your operation?\n\n"
                     " [1] Brute force\n"
                     " [2] Heuristics\n"
                     " [3] to be done\n\n"
                     " Option: ";

        std::cin >> option;
        switch (option) {
            case 1:
                bruteForce();
                break;
            case 2:
                triangularApproximation();
                break;
            case 3:
                //nearestNeighbor();
                christofides();
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
    std::cout << "\n Distance: " << dist << '\n';
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

    std::cout << "\n Distance: " << dist << '\n';
    std::cout << " Execution Time: " << time << " milliseconds\n\n";
}

void Menu::nearestNeighbor() {
    std::vector<Vertex *> tour;
    double dist;

    std::chrono::steady_clock::time_point startTime = std::chrono::steady_clock::now();

    supervisor->getGraph().nearestNeighborTSP(tour, dist);
  
    std::chrono::steady_clock::time_point endTime = std::chrono::steady_clock::now();

    std::chrono::duration<double, std::milli> duration = std::chrono::duration_cast<std::chrono::duration<double, std::milli>>(endTime - startTime);

    double time = duration.count();

    std::cout << "\n Path: ";
    for (Vertex* v : tour)
        std::cout << v->getId() << " ";

    std::cout << "0\n Distance: " << dist << '\n';
    std::cout << " Execution Time: " << time << " milliseconds\n\n";
  
}

void Menu::christofides(){
    std::queue<Vertex *> path;
    double dist = 0;

    std::chrono::steady_clock::time_point startTime = std::chrono::steady_clock::now();

    supervisor->getGraph().christofides(path, dist);

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

    std::cout << "\n Distance: " << dist << '\n';
    std::cout << " Execution Time: " << time << " milliseconds\n\n";

}

void Menu::end() {
    printf("\n");
    printf("===========================================================");
}