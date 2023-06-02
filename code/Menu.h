#ifndef DA_MENU_H
#define DA_MENU_H

#include <iostream>
#include <climits>
#include <thread>

#include "Supervisor.h"

class Menu {
public:

    Menu();

    /**
     * Initial menu where the user is able to choose what type of graph they want to create:
     * <pre><b>(1)</b> Toy-Graphs</pre>
     * <pre><b>(2)</b> Real-world Graphs</pre>
     * <pre><b>(3)</b> Extra-Fully-Connected Graphs</pre>
     */
    void init();

    /**
     * Closes the menu and ends the program
     */
    static void end();


private:

    Supervisor* supervisor;

    /**
    * Toy Graphs menu where the user is able to choose what toy graph they want to create:
    * <pre><b>(1)</b> Shipping</pre>
    * <pre><b>(2)</b> Stadiums</pre>
    * <pre><b>(3)</b> Tourism</pre>
    */
    void toyGraphs();

    /**
     * Real-World Graphs menu where the user is able to choose what real world graph they want to create:
     * <pre><b>(1)</b> Graph1</pre>
     * <pre><b>(2)</b> Graph2</pre>
     * <pre><b>(3)</b> Graph3</pre>
     */
    void realWorldGraphs();

    /**
     * Extra Graphs menu where the user is able to choose what extra graph they want to create
     */
    void extraGraphs();

    /**
     * Operations menu where the user is able to choose what operation they want to perform:
     * <pre><b>(1)</b> Brute Force</pre>
     * <pre><b>(2)</b> Heuristics</pre>
     * <pre><b>(3)</b> Christofides with 2-opt</pre>
     * <pre><b>(4)</b> Nearest neighbour</pre>
     * <pre><b>(5)</b> Nearest insertion</pre>
     */
    void operations(bool smallGraph, bool completeGraph);

    /**
     * Performs the brute-force approach to solve the traveling salesman problem (TSP) on the graph.\n
     * Prints the optimal path, its distance, and the execution time.
     */
    void bruteForce();

    /**
     * Performs the nearest neighbor algorithm to solve the traveling salesman problem (TSP).\n
     * Prints the path, its distance, and the execution time.
     */
    void nearestNeighbor();

    /**
     * Performs the triangular approximation algorithm to solve the traveling salesman problem (TSP).\n
     * Prints the path, its distance, and the execution time.
     */
    void triangularApproximation();

    /**
     * Performs the christofides algorithm combined with 2-opt to solve the traveling salesman problem (TSP).\n
     * Prints the path, its distance, the execution time and the improvements compared to the triangular approximation. .
     */
    void christofides();

    void nearestInsertion();
};
#endif //DA_MENU_H
