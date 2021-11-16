#include "hotkey.h"
#include "settings.h"

#include <QString>

#include <cstdio>

Hotkey::Hotkey() {
    hotkeyTextBox = new HotkeyView;
}

void Hotkey::keyDown(int code) {

    keyboardEventHandler(code, true, code);

    if (internalSettings.isValid()) {
        
        lastValidHotkeySettings = internalSettings.clone();
        registerHotkeySettings();
        hotkeyTextBox->setText(QString::fromStdString(lastValidHotkeySettings.toString()));
    }
}

void Hotkey::keyUp(int code) {
    keyboardEventHandler(code, false, 0);
}

void Hotkey::keyboardEventHandler(int code, bool state, int keycodeState) {
    
    switch (code) {
        case VK_LWIN:
        case VK_RWIN:
            internalSettings.win = state;
            break;
        case VK_CONTROL:
        case VK_LCONTROL:
        case VK_RCONTROL:
            internalSettings.ctrl = state;
            break;
        case VK_MENU:
        case VK_LMENU:
        case VK_RMENU:
            internalSettings.alt = state;
            break;
        case VK_SHIFT:
        case VK_LSHIFT:
        case VK_RSHIFT:
            internalSettings.shift = state;
            break;
        default:
            internalSettings.code = keycodeState;
            break;
    }
}

LRESULT CALLBACK Hotkey::hookProc(int nCode, WPARAM wParam, LPARAM lParam) {

    if (nCode == HC_ACTION) {
        // params are valid

        int code = ((KBDLLHOOKSTRUCT*)lParam)->vkCode;
        switch (wParam) {

            case WM_KEYDOWN:
            case WM_SYSKEYDOWN:
                getInstance().keyDown(code);
                break;
            case WM_KEYUP:
            case WM_SYSKEYUP:
                getInstance().keyUp(code);
                break;
        }

        return 1;
    }

    // first parameter hhk is ignored according to documentation
    return CallNextHookEx(NULL, nCode, wParam, lParam);
}

bool Hotkey::isActive() {
    return hotkeyTextBox->hasFocus();
}

void Hotkey::setHotkey(std::string hotkeyString) {
    // TODO handle invalid string
    hotkeySettings = HotkeySettings(hotkeyString);
    internalSettings = HotkeySettings();
    lastValidHotkeySettings = HotkeySettings(hotkeyString);

    registerHotkeySettings();
    printf(("Set hotkey: " + hotkeySettings.toString()).c_str());
    putchar('\n');
    hotkeyTextBox->setText(QString::fromStdString(hotkeySettings.toString()));
}

void Hotkey::gettingFocus() {
    hookHandle = SetWindowsHookEx(WH_KEYBOARD_LL, hookProc, 0, 0);
}

void Hotkey::losingFocus() {
    UnhookWindowsHookEx(hookHandle);
    Settings::getInstance().setHotkey(hotkeySettings.toString());
}

void Hotkey::registerHotkeySettings() {

    printf(("Trying to register hotkey: " + lastValidHotkeySettings.toString() + "\n").c_str());

    HWND winId = HWND(hotkeyTextBox->window()->winId());
    UINT fsModifiers = lastValidHotkeySettings.getFSModifier();
    
    // register hotkey to the window with the given window id
    // Virtual-Key Codes -> https://docs.microsoft.com/en-us/windows/win32/inputdev/virtual-key-codes
    if (!RegisterHotKey(winId, id, fsModifiers, lastValidHotkeySettings.code)) {

        printf("\nFailed to register hotkey.\n");

    } else {
        
        id = id == 2? 1 : 2;

        printf("Succeeded to register hotkey.\n");

        if (!UnregisterHotKey(winId, id)) {
            printf("Failed to unregister hotkey with id %d.\n", id);
            //TODO what has to be done in this case?
        }
        hotkeySettings = lastValidHotkeySettings.clone();
    }
}