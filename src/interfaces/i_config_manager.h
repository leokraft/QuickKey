#ifndef I_CONFIG_MANAGER_H
#define I_CONFIG_MANAGER_H

#include <string>

class IConfigManager {
    public:
        IConfigManager(){}
        virtual ~IConfigManager(){}
        virtual void writeConfig(const std::string key, const std::string value) = 0;
        virtual std::string getConfig(const std::string key) = 0;
};

#endif