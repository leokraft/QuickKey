#ifndef WIN_PATH_MANAGER_H
# define WIN_PATH_MANAGER_H

#include <string>
#include "i_path_manager.h"

class WinPathManager : public IPathManager {
    public:
        WinPathManager(){}
        ~WinPathManager(){}
        void initExecutablePath(const std::string called_cmd);

        static std::string executablePath;
};

#endif
