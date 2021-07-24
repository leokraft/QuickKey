#ifndef HOTKEY_H
#define HOTKEY_H

#include <windows.h>
#include "hotkey_settings.h"
#include "hotkey_view.h"

class Hotkey {

    public:

        static Hotkey& getInstance() {
            static Hotkey instance;
            return instance;
        }

        Hotkey(Hotkey const&) = delete;
        void operator=(Hotkey const&) = delete;

        static LRESULT CALLBACK hookProc(int nCode, WPARAM wParam, LPARAM lParam);
        bool isActive();
        void gettingFocus();
        void losingFocus();
        void setHotkey(std::string hotkeyString);
        HotkeyView *hotkeyTextBox;

    private:
        Hotkey();
        HotkeySettings lastValidHotkeySettings;
        HotkeySettings internalSettings;
        HotkeySettings hotkeySettings;

        int id = 1;
        HHOOK hookHandle;

        void keyDown(int code);
        void keyUp(int code);
        void keyboardEventHandler(int code, bool state, int keycodeState);
        void registerHotkeySettings(); 
};
#endif