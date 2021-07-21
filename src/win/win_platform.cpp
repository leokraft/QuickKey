#include <windows.h>
#include "win_platform.h"

void WinPlatform::setHotkey(std::string hotkey, WId winId) {
    // register hotkey to the window with the given window id
    // Virtual-Key Codes -> https://docs.microsoft.com/en-us/windows/win32/inputdev/virtual-key-codes
    RegisterHotKey(HWND(winId), 1, MOD_CONTROL, 0x59);
}