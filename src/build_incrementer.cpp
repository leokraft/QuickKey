#include <fstream>
#include <iostream>
#include <windows.h>


#include "build_incrementer.h"

using namespace std;


void BuildIncrementer::foo(){

    string searchString = "VERSION_BUILD = ";
    string replaceString = "VERSION_BUILD = ";

    //2 instances of filein neede, because fileout would write only half after fetching build number
    ifstream fileinBuild("./quickkey.pro"); 
    ifstream filein("./quickkey.pro");
    ofstream fileout("./fileout.txt");


    if(!fileinBuild || !fileout || !filein){
        cout << "Error opening files!" << endl;
        return;
    }

    string line;
    string buildVersion;
    int buildNumber;
    while(std::getline(fileinBuild, line)){
        if(line.find(searchString) != string::npos){
            buildVersion = line.substr(line.find("= ")+2);
            searchString +=  buildVersion;
            buildNumber = std::stoi(buildVersion);
            buildNumber += 1;
            replaceString +=  std::to_string(buildNumber);
            printf(replaceString.c_str());
            printf("\n");
            break;
        }
    }

    fileinBuild.close();

    string inbuf;
    do{
        getline(filein, inbuf);

        int spot = inbuf.find(searchString);
        if(spot>=0){
            string tempstring = inbuf.substr(0, spot);
            tempstring += replaceString;
            tempstring += inbuf.substr(spot + searchString.length(), inbuf.length());
            inbuf = tempstring;
        }

        //if end of file is reached, no newline is added
        if(filein.eof()){
            fileout << inbuf;
            break;
        }

        fileout << inbuf << "\n";
        
    } while (!filein.eof());

    filein.close();
    fileout.close();

    string outFile = "./fileout.txt";
    string infile = "./quickkey.pro";

    printf(outFile.c_str());

    BOOL success = CopyFileA(outFile.c_str(), infile.c_str(), false);
    if (!success) {
        std::cout << "Error: " << GetLastError() << std::endl;
    } else {
        std::cout << "Okay " << std::endl;
        std::remove(outFile.c_str());
    }

}