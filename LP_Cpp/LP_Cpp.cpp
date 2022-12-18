// LP_Cpp.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <json/json.h>
#include <filesystem>
#include <ctime>
#include "Gui.h"

using namespace std;
using namespace Json;

namespace fs = std::filesystem;

int main()
{
    cout << "LightPoint - a HomeAssignment!\n\n";

    GUI* gui = new GUI("myjsonsfiles");
           

    if (gui->welcome() == 0) return 0;
	
	gui->showFiles();
    int wrongChoice = 0;
    wrongChoice = gui->selectFile();

    while (wrongChoice) {
        gui->showFiles();
        wrongChoice = gui->selectFile();
    }
    
    wrongChoice = 1;
    while (wrongChoice) {
        gui->showFileContent();
        wrongChoice = gui->userObjectToOutput();
    }

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
