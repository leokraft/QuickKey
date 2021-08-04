#include <string>
#include <stdexcept>
#include "win_path_manager.h"

std::string WinPathManager::executablePath;

std::string WinPathManager::configPath = std::string(getenv("APPDATA")).append("\\QuickKey");

void WinPathManager::initExecutablePath(const std::string called_cmd) {

    // Locate the executable name
    size_t n = called_cmd.rfind("\\"); // Windows

    // Handle potential errors (should never happen but it is for robustness purposes)
    if(n == std::string::npos) // if pattern not found
        throw std::invalid_argument("Invalid exe path. Pattern not found.");

    // Remove the executable name
    executablePath = called_cmd.substr(0, n);

}