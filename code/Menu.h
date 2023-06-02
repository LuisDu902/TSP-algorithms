#ifndef DA_MENU_H
#define DA_MENU_H

#include <iostream>
#include <climits>
#include <list>
#include <atomic>
#include <thread>
#include <unordered_set>

#include "Supervisor.h"

class Menu {
public:

    Menu();

    /**
     * Initial menu where the user is able to choose what type of graph they want to create:
     * (1) Toy-Graphs
     * (2) Real-world Graphs
     * (3) Extra-Fully-Connected Graphs
     */
    void init();

    /**
     * Closes the menu and ends the program
     */
    static void end();

    /**
     * Toy Graphs menu where the user is able to choose what toy graph they want to create:
     * (1) Shipping
     * (2) Stadiums
     * (3) Tourism
     */
    void toyGraphs();

    /**
     * Real-World Graphs menu where the user is able to choose what real world graph they want to create:
     * (1) Graph1
     * (2) Graph2
     * (3) Graph3
     */
    void realWorldGraphs();

    /**
     * Extra Graphs menu where the user is able to choose what extra graph they want to create
     */
    void extraGraphs();

    /**
     * Operations menu where the user is able to choose what operation they want to perform:
     * (1) Brute Force
     * (2) Heuristics
     * (3) to be done
     */
    void operations(bool smallGraph, bool completeGraph);

    /**
     * Performs the brute-force approach to solve the traveling salesman problem (TSP) on the graph.
     * Prints the optimal path, its distance, and the execution time.
     */
    void bruteForce();
    void heuristics();

    void nearestNeighbor();
private:

    Supervisor* supervisor;

    void triangularApproximation();

    void christofides();
};
#endif //DA_MENU_H
