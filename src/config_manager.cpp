#include "config_manager.h"


void Config_Manager::checkConfig(){
    std::string path = appdata;
    std::string appdataPath = path.append("\\QuickKey");

    std::ifstream ifile; //start filereader
    ifile.open(appdataPath + "\\config.ini"); //open filereader
    if(ifile) 
    {
        std::cout<<"file exists\n";
    } 
    else 
    {
        std::cout<<"file doesn't exist\n";
        
        if (CreateDirectoryA (appdataPath.c_str(), NULL) ||
            ERROR_ALREADY_EXISTS == GetLastError())
        {
            std::string defaultConfigPath = WinPathManager::executablePath + "/default_Config.ini";
            std::string configPath = appdataPath + "/config.ini";
            BOOL b = CopyFileA(defaultConfigPath.c_str(), configPath.c_str(), true);
            if (!b) {
                std::cout << "Error: " << GetLastError() << std::endl;
            } else {
                std::cout << "Okay " << std::endl;
            }
        }
        else
        {
            printf("FAILED TO CREATE DIRECOTRY \n");
            // Failed to create directory.
        }
    }
}