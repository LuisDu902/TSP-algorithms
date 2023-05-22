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
    void init();
    static void end();

    void toyGraphs();
    void realWorldGraphs();
    void extraGraphs();

    void operations();

    void bruteForce();

private:

    Supervisor* supervisor;

};
#endif //DA_MENU_H
