#include <windows.h>
#include "win_config_manager.h"
#include "win_path_manager.h"

void WinConfigManager::writeConfig(const std::string key, const std::string value) {

    BOOL success = WritePrivateProfileStringA(
        "config",
        key.c_str(),
        value.c_str(),
        (WinPathManager::executablePath + "./config.ini").c_str()
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
        (WinPathManager::executablePath + "/config.ini").c_str()
    );

    return std::string(buffer);
}