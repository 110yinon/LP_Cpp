#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <json/json.h>

using namespace std;
using namespace Json;

#pragma once
class GUI {
private:
    int filesNum = 0;
    int choosenFile = NULL;
    string* arr = NULL;
    string directory = "";
    Value jsonData;

public:
	// ctor
	// gets directory to looks for json files
	GUI(string drctr);

    
private:
    // count the json files in the folder
    // updates the filesNum member
    void countFiles();

    // set the json file names in the arr above
    // we get arr of the folder's files names 
    void storeFiles();

public:
    // print the files to the screen
    void showFiles();

    // allow to select the file to work on
    // the function return 0 to OK or 1 to Error
    int selectFile();

    // prints the whole json data (arr of obj) of the selected file
    void showFileContent();

    // A function that starts the first interaction with the user
    // the function return 1 to continue or 0 to exit
    int welcome();

    // allow to select which json obj to output from the arr of objs
    // the function return 0 to OK or 1 to Error
    int userObjectToOutput();

private:
    // creating of the file and set the obj inside it
    // the func return the output file name
    string createOutputFile(Value userObj);

};


