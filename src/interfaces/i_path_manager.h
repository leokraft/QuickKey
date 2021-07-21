#ifndef I_PATH_MANAGER_H
#define I_PATH_MANAGER_H

#include <string>

class IPathManager {
    public:
        IPathManager(){}
        virtual ~IPathManager(){}
        virtual void initExecutablePath(const std::string called_cmd) = 0;
};

#endif