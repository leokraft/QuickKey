#ifndef CONFIGMANAGER_H
#define CONFIGMANAGER_H

#include <windows.h>

#include <dirent.h>
#include <errno.h>

#include <string>

#include <fstream>
#include <iostream>
#include <win_path_manager.h>

class Config_Manager
{
    private:
        const char *appdata = getenv("APPDATA");

    public:
        void checkConfig();
        Config_Manager(/* args */){};
        ~Config_Manager(){};
};

#endif