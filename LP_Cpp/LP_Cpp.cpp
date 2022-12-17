// LP_Cpp.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <json/json.h>
#include <filesystem>
#include <ctime>

using namespace std;
using namespace Json;

namespace fs = std::filesystem;

class GUI {
public:
    string directory = "";
    int filesNum = 0;
    int choosenFile = NULL;
    string* arr = NULL;
    Value jsonData;


    GUI(string drctr) {
        directory = drctr;
        countFiles();
        storeFiles();
    }

    void countFiles() {
        //int filesNum = 0;
        for (fs::directory_entry p : fs::directory_iterator(directory)) {
            filesNum++;
            //std::cout << p.path().filename() << '\n';
        }
        arr = new string[filesNum];
    }

    void storeFiles() {        
        int index = 0;
        for (fs::directory_entry p : fs::directory_iterator(directory)) {
            arr[index] = p.path().filename().string();
            index++;
            /*std::cout << p.path().filename().string() << '\n';*/
        }
    }

    void showFiles() {
        system("cls");
        cout << "your files:" << endl;
        for (int i = 0; i < filesNum; i++)
        {
            cout << i << "\t" << arr[i] << endl;
        }
    }
    
    
    
    void selectFile() {
        cout << endl << "choose a file: ";
        //int choosenFile;
        cin >> choosenFile;
        cout << "'" + arr[choosenFile] + "'" << " is choosen." << endl;
    }

    void showFileContent() {
        // read the data from json file
        ifstream myFile("./" + directory + "/"+ arr[choosenFile]);
        Reader reader;

        // parase the file data to json object
        reader.parse(myFile, jsonData);              

        // printing the whole json obj (arr of users objs)
        cout << "\ndata from json file:" << jsonData << endl;

        //printing the amount of user objs in the arr
        cout << "Total amount of users in this file: " << jsonData.size();
    }
    
    void kuni() {
        // getting the last user obj from the json arr
        Value lastUserObj = jsonData[jsonData.size() - 1];
    }
    


};

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
       
    // added time stamp to the last user json file name
    time_t now = time(0);
    tm* ltm = localtime(&now);

    string year = to_string(ltm->tm_year - 100);
    string month = to_string(1 + ltm->tm_mon);
    string day = to_string(ltm->tm_mday);
    string hour = to_string(ltm->tm_hour);
    string min = to_string(ltm->tm_min);
    string sec = to_string(ltm->tm_sec);

    string timeStr = day + "_" + month + "_" + year + "_" + hour + min + sec;

    // create a file and writing the json user obj to it:
    /*ofstream LastUserFile("./outputs/" + timeStr + "__LastUserFile.txt");   
    
    LastUserFile << lastUserObj;
    LastUserFile.close();*/

    GUI *gui = new GUI("myjsonsfiles");
    cout << gui->filesNum << endl;
    /*gui->showFiles();
    gui->selectFile();

    gui->showFileContent();*/
    /*gui.countFiles();
    gui.storeFiles();
    gui.showFiles();*/

    




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
