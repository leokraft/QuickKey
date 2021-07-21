#ifndef WIN_CONFIG_MANAGER_H
#define WIN_CONFIG_MANAGER_H

#include <string>
#include "i_config_manager.h"

class WinConfigManager : public IConfigManager {
    public:
        WinConfigManager(){}
        ~WinConfigManager(){}
        void writeConfig(const std::string key, const std::string value);
        std::string getConfig(const std::string key);
};

#endif