// ooop_lab1a.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Message.h"
#include "Methods.h"
#include "Mode.h"
#include <vector>

using namespace std;

int MessageLog::count = 0;

namespace test {
    int main_test(int argc, char* argv[]);
}

int main()
{
    //test::main_test(argc, argv);
    Functions function;
    MessageLog message;

    function.log.clear();

    Functions::defineId();

    bool check = true;

    while (check) {
        cout << "Choose mode\n"
            << "1 - Interactive\n"
            << "2 - Demonstration\n"
            << "3 - benchmark\n"
            << "4 - exit\n";
        short action;
        cin >> action;
        switch (action) {
        case 1: check = interactive(function);
            break;
        case 2: check = demonstration();
            break;
        case 3: check = benchmark();
            break;
        case 4: check = false;
            break;
        default: cout << "Choose correct number\n";
        }
    }
    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
