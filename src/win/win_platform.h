#ifndef WIN_PLATFORM_H
#define WIN_PLATFORM_H

#include "i_platform_manager.h"

class WinPlatform : public IPlatformManager {
    public:
        WinPlatform(){}
        ~WinPlatform(){}
        void setHotkey(std::string hotkey, WId winId);
};

#endif