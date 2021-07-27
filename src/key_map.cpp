#include "key_map.h"

std::map<int, std::string> KeyMap::hashVKCtoString = std::map<int, std::string>();
std::map<std::string, int> KeyMap::hashStringToVKC = std::map<std::string, int>();
KeyMap KeyMap::instance = KeyMap();

std::string KeyMap::toString(int code) {

    std::map<int, std::string>::iterator itr = hashVKCtoString.find(code);

    if( itr != hashVKCtoString.end() ) {
        
        return itr->second;
    }

    UINT charInt = MapVirtualKeyA(code, MAPVK_VK_TO_CHAR);
    return std::string((char*)&charInt);
}

int KeyMap::fromString(std::string vkString) {

    std::map<std::string, int>::iterator itr = hashStringToVKC.find(vkString);

    if( itr != hashStringToVKC.end() ) {
        
        return itr->second;
    }
    
    return VkKeyScanExW(tolower(*vkString.c_str()), GetKeyboardLayout(0));
}

KeyMap::KeyMap() {

    hashVKCtoString = std::map<int, std::string>{
        {VK_CANCEL, "Break"},
        {VK_BACK, "Backspace"},
        {VK_TAB, "Tab"},
        {VK_CLEAR, "Clear"},
        {VK_RETURN, "Enter"},
        {VK_SHIFT, "Shift"},
        {VK_CONTROL, "Ctrl"},
        {VK_MENU, "Alt"},
        {VK_PAUSE, "Pause"},
        {VK_CAPITAL, "Caps Lock"},
        {VK_ESCAPE, "Esc"},
        {VK_SPACE, "Space"},
        {VK_PRIOR, "PgUp"},
        {VK_NEXT, "PgDn"},
        {VK_END, "End"},
        {VK_HOME, "Home"},
        {VK_LEFT, "Left"},
        {VK_UP, "Up"},
        {VK_RIGHT, "Right"},
        {VK_DOWN, "Down"},
        {VK_SELECT, "Select"},
        {VK_PRINT, "Print"},
        {VK_EXECUTE, "Execute"},
        {VK_SNAPSHOT, "Print Screen"},
        {VK_INSERT, "Insert"},
        {VK_DELETE, "Delete"},
        {VK_HELP, "Help"},
        {VK_LWIN, "Win (Left)"},
        {VK_RWIN, "Win (Right)"},
        {VK_APPS, "Apps/Menu"},
        {VK_SLEEP, "Sleep"},
        {VK_NUMPAD0, "NumPad 0"},
        {VK_NUMPAD1, "NumPad 1"},
        {VK_NUMPAD2, "NumPad 2"},
        {VK_NUMPAD3, "NumPad 3"},
        {VK_NUMPAD4, "NumPad 4"},
        {VK_NUMPAD5, "NumPad 5"},
        {VK_NUMPAD6, "NumPad 6"},
        {VK_NUMPAD7, "NumPad 7"},
        {VK_NUMPAD8, "NumPad 8"},
        {VK_NUMPAD9, "NumPad 9"},
        {VK_SEPARATOR, "Separator"},
        {VK_F1, "F1"},
        {VK_F2, "F2"},
        {VK_F3, "F3"},
        {VK_F4, "F4"},
        {VK_F5, "F5"},
        {VK_F6, "F6"},
        {VK_F7, "F7"},
        {VK_F8, "F8"},
        {VK_F9, "F9"},
        {VK_F10, "F10"},
        {VK_F11, "F11"},
        {VK_F12, "F12"},
        {VK_F13, "F13"},
        {VK_F14, "F14"},
        {VK_F15, "F15"},
        {VK_F16, "F16"},
        {VK_F17, "F17"},
        {VK_F18, "F18"},
        {VK_F19, "F19"},
        {VK_F20, "F20"},
        {VK_F21, "F21"},
        {VK_F22, "F22"},
        {VK_F23, "F23"},
        {VK_F24, "F24"},
        {VK_NUMLOCK, "Num Lock"},
        {VK_SCROLL, "Scroll Lock"},
        {VK_LSHIFT, "Shift (Left)"},
        {VK_RSHIFT, "Shift (Right)"},
        {VK_LCONTROL, "Ctrl (Left)"},
        {VK_RCONTROL, "Ctrl (Right)"},
        {VK_LMENU, "Alt (Left)"},
        {VK_RMENU, "Alt (Right)"},
        {VK_BROWSER_BACK, "Browser Back"},
        {VK_BROWSER_FORWARD, "Browser Forward"},
        {VK_BROWSER_REFRESH, "Browser Refresh"},
        {VK_BROWSER_STOP, "Browser Stop"},
        {VK_BROWSER_SEARCH, "Browser Search"},
        {VK_BROWSER_FAVORITES, "Browser Favorites"},
        {VK_BROWSER_HOME, "Browser Home"},
        {VK_VOLUME_MUTE, "Volume Mute"},
        {VK_VOLUME_DOWN, "Volume Down"},
        {VK_VOLUME_UP, "Volume Up"},
        {VK_MEDIA_NEXT_TRACK, "Next Track"},
        {VK_MEDIA_PREV_TRACK, "Previous Track"},
        {VK_MEDIA_STOP, "Stop Media"},
        {VK_MEDIA_PLAY_PAUSE, "Play/Pause Media"},
        {VK_LAUNCH_MAIL, "Start Mail"},
        {VK_LAUNCH_MEDIA_SELECT, "Select Media"},
        {VK_LAUNCH_APP1, "Start App 1"},
        {VK_LAUNCH_APP2, "Start App 2"},
        {VK_PACKET, "Packet"},
        {VK_ATTN, "Attn"},
        {VK_CRSEL, "CrSel"},
        {VK_EXSEL, "ExSel"},
        {VK_EREOF, "Erase EOF"},
        {VK_PLAY, "Play"},
        {VK_ZOOM, "Zoom"},
        {VK_PA1, "PA1"},
        {VK_OEM_CLEAR, "Clear"},
        {0xFF, "Undefined"},
        {VK_KANA, "IME Kana"},
        {VK_HANGEUL, "IME Hangeul"},
        {VK_HANGUL, "IME Hangul"},
        {VK_JUNJA, "IME Junja"},
        {VK_FINAL, "IME Final"},
        {VK_HANJA, "IME Hanja"},
        {VK_KANJI, "IME Kanji"},
        {VK_CONVERT, "IME Convert"},
        {VK_NONCONVERT, "IME Non-Convert"},
        {VK_ACCEPT, "IME Kana"},
        {VK_MODECHANGE, "IME Mode Change"}
        };
    
    for ( const auto &myPair : hashVKCtoString ) {
        hashStringToVKC[myPair.second] = myPair.first;
    }
}