#ifndef WIN_PATH_MANAGER_H
# define WIN_PATH_MANAGER_H

#include <string>
#include "i_path_manager.h"

class WinPathManager : public IPathManager {
    private: 
        const char *appdata = getenv("APPDATA");
        std::string path = appdata;        
    public:
        WinPathManager(){}
        ~WinPathManager(){}
        void initExecutablePath(const std::string called_cmd);

        static std::string executablePath;
        std::string configPath = path.append("\\QuickKey");
};

#endif
