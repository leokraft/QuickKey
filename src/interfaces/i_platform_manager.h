#ifndef I_PLATFORM_MANAGER_H
#define I_PLATFORM_MANAGER_H

#include <string>
#include <QWidget>

class IPlatformManager {
    public:
        IPlatformManager(){}
        virtual ~IPlatformManager(){}
        virtual void setHotkey(std::string hotkey, WId winId) = 0;
};

#endif