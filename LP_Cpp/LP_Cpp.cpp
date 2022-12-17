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
    int filesNum = 0;
    int choosenFile = NULL;
    string* arr = NULL;
    string directory = "";
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
    
    
    // the function return 0 to OK or 1 to Error
    int selectFile() {        
        cout << endl << "Select file: ";
        cin >> choosenFile;
        if (choosenFile + 1 > filesNum) return 1;        
        return 0;
    }

    void showFileContent() {
        system("cls");
        cout << "The file " << "'" + arr[choosenFile] + "'" << " is choosen." << endl;
        // read the data from json file
        ifstream myFile("./" + directory + "/"+ arr[choosenFile]);
        Reader reader;

        // parase the file data to json object
        reader.parse(myFile, jsonData);              

        // printing the whole json obj (arr of users objs)
        cout << "\n> file data:" << endl << jsonData << endl;

        //printing the amount of user objs in the arr
        cout << "> Total amount of user objects in this file: " << jsonData.size() << endl;
    }
    
    // the function return 1 to continue or 0 to exit
    int welcome() {
        int select = 0;
        
        while (select != 1) {
            system("cls");
            cout << "********************************" << endl;
            cout << "  welcome to the gui feature" << endl;
            cout << "********************************" << endl << endl;

            //cout << "Press any key to continue, press 0 to EXIT: ";
            cout << "Select option: " << endl;
            cout << 0 << "\t" << "EXIT" << endl;
            cout << 1 << "\t" << "Continue" << endl;

            cout << endl << "You choose: ";
            cin >> select;
            if (select == 0) {
                cout << "Bye Bye" << endl;
                return 0;
            }

        }
        return 1;
    }

    // the function return 0 to OK or 1 to Error
    int userObjectToOutput() {
        int users = jsonData.size();
        
        int select = -2;
        cout << "> Select user object to output:" << endl;
        
        if (users != 1)
            cout << "0-" << users - 2 << "\t" << "User no.index" << endl;
        
        
        cout << "'-1'" << "\t" << "Last user in the array" << endl;

        cout << endl << "> You choose: ";
        cin >> select;
               
        if (select == -1 || users == 1) {
            // getting the last user obj from the json arr
            Value lastUserObj = jsonData[jsonData.size() - 1];
            string outputFileName = createOutputFile(lastUserObj);
            cout << "> Succesfuly output Last User to '" + outputFileName + "' file " << endl;
            return 0;
        }

        if (select + 2 <= users) {
            Value userObj = jsonData[select];
            string outputFileName = createOutputFile(userObj);
            cout << "> Succesfuly output the no." << select << " user obj to '" + outputFileName + "' file " << endl;
            return 0;
        }
        // user select the wrong number of index
        return 1;
        
    }
    
    // the func return the output file name
    string createOutputFile(Value userObj) {
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
        string outputFileName = "./outputs/" + timeStr + "__userFile.txt";
        ofstream LastUserFile(outputFileName);

        LastUserFile << userObj;
        LastUserFile.close();
        return outputFileName;
    }


};

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
	


    




    // getting the last user obj from the json arr
    //Value lastUserObj = jsonData[jsonData.size() - 1];
    
    // printing the last user:
	//cout << "\nLast user in the array:" << endl << lastUserObj << endl;

    

    

    




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
