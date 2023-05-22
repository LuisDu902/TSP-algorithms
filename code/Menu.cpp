#include "Menu.h"

Menu::Menu() {

    printf("\n");
    printf("\033[44m===========================================================\033[0m\t\t");
    std::cout << "\n\n" << " Welcome!\n (Press [0] whenever you wish to go back)\n\n";
}

void Menu::init() {
    std::string option;
    while(true) {
        std::cout << " Choose your graph?\n\n"
                     " [1] Toy-Graphs\n"
                     " [2] Real-world Graphs\n"
                     " [3] Extra-Fully-Connected Graphs\n"
                     " [4] Exit\n\n Option: ";

        std::cin >> option;

        if (option == "1") {
            toyGraphs();
        }
        else if (option == "2") {
            realWorldGraphs();
        }
        else if (option == "3") {
            extraGraphs();
        }
        else if (option == "4") {
            return;
        }
        else if (option == "0")
            std::cout << "\n You can't go back any further!\n\n";
        else{
            std::cout << "\n Invalid input, try again. \n\n";
            std::cin.clear();
            std::cin.ignore(INT_MAX, '\n');
        }
    }
}

void Menu::toyGraphs() {
    std::string option;
    std::string filePath = "../data/Toy-Graphs/";
    while(true){
        std::cout << "\n What graph?\n\n"
                     " [1] Shipping\n"
                     " [2] Stadiums\n"
                     " [3] Tourism\n\n"
                     " Option: ";

        std::cin >> option;
        if (option == "1"){
           filePath.append("shipping.csv");
           break;
        }
        else if (option == "2"){
            filePath.append("stadiums.csv");
            break;
        }
        else if (option == "3"){
            filePath.append("tourism.csv");
            break;
        }
        else if (option == "0"){
            std::cout << "\n";
            return;
        }
        else{
            std::cout << "\n Invalid input, try again. \n";
            std::cin.clear();
            std::cin.ignore(INT_MAX, '\n');
        }
    }
    supervisor = new Supervisor(filePath);
    operations();
}


void Menu::extraGraphs() {
    std::string option;
    std::unordered_set<std::string> s{"25", "50", "75", "100", "200", "300", "400", "500", "600", "700", "800", "900"};
    std::string filePath = "../data/Extra_Fully_Connected_Graphs/edges_";
    while(true){
        std::cout << "\n Choose the number of nodes\n\n"
                     " Number: ";

        std::cin >> option;
        if (s.find(option) != s.end()){
            filePath.append(option).append(".csv");
            break;
        }
        else if (option == "0"){
            std::cout << "\n";
            return;
        }
        else{
            std::cout << "\n Invalid input, try again. \n";
            std::cin.clear();
            std::cin.ignore(INT_MAX, '\n');
        }
    }
    supervisor = new Supervisor(filePath);
    operations();
}

void Menu::realWorldGraphs() {
    std::string option;
    std::string filePath = "../data/Real-world Graphs/";
    while(true){
        std::cout << "\n What graph?\n\n"
                     " [1] graph1\n"
                     " [2] graph2\n"
                     " [3] graph3\n\n"
                     " Option: ";

        std::cin >> option;
        if (option == "1"){
            filePath.append("graph1");
            break;
        }
        else if (option == "2"){
            filePath.append("graph2");
            break;
        }
        else if (option == "3"){
            filePath.append("graph3");
            break;
        }
        else if (option == "0"){
            std::cout << "\n";
            return;
        }
        else{
            std::cout << "\n Invalid input, try again. \n";
            std::cin.clear();
            std::cin.ignore(INT_MAX, '\n');
        }
    }
    supervisor = new Supervisor(filePath);
    operations();
}

void Menu::operations() {
    std::string option;
    while(true) {
        std::cout << " Choose your operation?\n\n"
                     " [1] Brute force\n"
                     " [2] Heuristics\n"
                     " [3] to be done\n\n"
                     " Option: ";

        std::cin >> option;

        if (option == "1") {
            bruteForce();
        }
        else if (option == "2") {
            bruteForce();
        }
        else if (option == "3") {
            bruteForce();
        }
        else if (option == "0") {
            std::cout << "\n";
            return;
        }
        else{
            std::cout << "\n Invalid input, try again. \n\n";
            std::cin.clear();
            std::cin.ignore(INT_MAX, '\n');
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
    std::cout << "0\n Value: " << dist << '\n';
    std::cout << " Execution Time: " << time << " milliseconds\n\n";
}

void Menu::end() {
    printf("\n");
    printf("\033[46m===========================================================\033[0m\n");
}