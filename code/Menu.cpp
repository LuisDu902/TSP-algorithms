#include "Menu.h"

Menu::Menu() {
    printf("\n");
    printf("\033[44m===========================================================\033[0m\t\t");
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
    supervisor = new Supervisor(filePath, false);
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
    supervisor = new Supervisor(filePath, false);
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
    supervisor = new Supervisor(filePath, true);
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
                bruteForce();
                break;
            case 3:
                bruteForce();
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
    std::stack<int> path;
    double dist;

    std::chrono::steady_clock::time_point startTime = std::chrono::steady_clock::now();

    supervisor->getGraph().tspBT(path, dist);

    std::chrono::steady_clock::time_point endTime = std::chrono::steady_clock::now();

    std::chrono::duration<double, std::milli> duration = std::chrono::duration_cast<std::chrono::duration<double, std::milli>>(endTime - startTime);

    double time = duration.count();

    std::cout << "\n Path: 0 --> ";
    while (!path.empty()){
        std::cout << path.top() << " --> ";
        path.pop();
    }
    std::cout << "0\n Distance: " << dist << '\n';
    std::cout << " Execution Time: " << time << " milliseconds\n\n";
}

void Menu::end() {
    printf("\n");
    printf("\033[46m===========================================================\033[0m\n");
}