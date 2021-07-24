#ifndef HOTKEY_SETTINGS_H
#define HOTKEY_SETTINGS_H

#include <string>
#include <windows.h>

class HotkeySettings {

    public:
        HotkeySettings(){}
        HotkeySettings(std::string hotkeyString);
        HotkeySettings(bool win, bool ctrl, bool alt, bool shift, int code);

        // modifier keys
        bool win = false;
        bool ctrl = false;
        bool alt = false;
        bool shift = false;

        // virtual-key code
        int code = 0;
        
        std::string toString();
        UINT getFSModifier();
        bool isValid();
        HotkeySettings clone();
};
#endif