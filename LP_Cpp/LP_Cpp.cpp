// LP_Cpp.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <json/json.h>
#include <filesystem>

using namespace std;
using namespace Json;

namespace fs = std::filesystem;

int main()
{
    cout << "LightPoint - a HomeAssignment!\n\n";

    // read the data from json file
    ifstream myFile("./myjsonsfiles/ruUsers.json");    
    Value jsonData;
    Reader reader;

    // parase the file data to json object
    reader.parse(myFile, jsonData);

    // printing the whole json obj (arr of users objs)
    cout << "\ndata from json file:" << jsonData << endl;

    // getting the last user obj from the json arr
    Value lastUserObj = jsonData[jsonData.size() - 1];
    
    // printing the last user:
	cout << "\nLast user in the array:" << endl << lastUserObj << endl;

    // creating a directory that stores the json files
    fs::create_directory("./outputs");

    // create a file and writing the json user obj to it:
    ofstream LastUserFile("./outputs/LastUserFile.txt");

    LastUserFile << lastUserObj;
    LastUserFile.close();    

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
