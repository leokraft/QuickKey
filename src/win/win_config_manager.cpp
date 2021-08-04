#include <windows.h>
#include "win_config_manager.h"
#include <iostream>
#include <fstream>

WinConfigManager::WinConfigManager(){

    std::ifstream ifile; //start filereader
    ifile.open(appdataPath + "\\config.ini"); //open filereader
    if(ifile) 
    {
        std::cout<<"Config file exists\n";
    } 
    else 
    {
        std::cout<<"Config file doesn't exist\n";
        
        if (CreateDirectoryA (appdataPath.c_str(), NULL) ||
            ERROR_ALREADY_EXISTS == GetLastError())
        {
            std::string defaultConfigPath = WinPathManager::executablePath + "/default_config.ini";
            std::string configPath = appdataPath + "/config.ini";
            BOOL success = CopyFileA(defaultConfigPath.c_str(), configPath.c_str(), true);
            if (!success) {
                std::cout << "Error: " << GetLastError() << std::endl;
            } else {
                std::cout << "Okay " << std::endl;
            }
        }
        else
        {
            printf("FAILED TO CREATE DIRECOTRY\n");
            // Failed to create directory.
        }
    }
}

void WinConfigManager::writeConfig(const std::string key, const std::string value) {

    BOOL success = WritePrivateProfileStringA(
        "config",
        key.c_str(),
        value.c_str(),
        (appdataPath + "./config.ini").c_str()
    );
}

std::string WinConfigManager::getConfig(const std::string key) {

    int size = 64;
    char buffer[size];
    GetPrivateProfileStringA(
        "config",
        key.c_str(),
        "",
        buffer,
        size,
        (appdataPath + "/config.ini").c_str()
    );

    return std::string(buffer);
}