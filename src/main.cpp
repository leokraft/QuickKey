#include <iostream>
#include <windows.h>
#include <QtWidgets>
#include "finder.h"
#include "flowlayout.h"

int main(int argc, char *argv[]) {

    std::cout << "I am alive..." << std::endl;

    // NULL -> messages are posted to the message queue of the calling thread and must be processed in the message loop
    // Virtual-Key Codes -> https://docs.microsoft.com/en-us/windows/win32/inputdev/virtual-key-codes
    bool success = RegisterHotKey(NULL, 1, MOD_CONTROL, 0x59);
    
    /**
     * TODOS
     * 
     * Function to bind hotkey 
     * Unbind hotkey on exit
     * 
     * Simple window using Qt?
     * Hotkey input in window
     * 
     * open window on hotkey
     * close window on focus loss (?)
     * 
     * run app in tray/background
     * add app to autostart
     * 
     * get list of special characters
     * copy character into clipboard
     * remember last focus???
     * return to last focus?
     */
    if (success) {
        
        MSG msg = {0};
        bool flag = false;
        while (!flag && GetMessage(&msg, NULL, 0, 0) != 0) {
            if (msg.message == WM_HOTKEY) {

                std::cout << "Wild hotkey found!" << std::endl;

                QApplication app(argc, argv);

                Finder finder;
                finder.show();
                
                app.exec();
                flag = true;   
            };
        };

        if (UnregisterHotKey(NULL, 1)) {
            std::cout << "Unregister successful." << std::endl;
        };

        return 0;
    };

    std::cout << "Failed to setup hotkey.\nExiting..." << std::endl;
    return 1;
    
};

/* FOCUS
 When the keyboard focus changes from one window to another,
 the system sends a WM_KILLFOCUS message to the window that has lost the focus,
 and then sends a WM_SETFOCUS message to the window that has gained the focus.

 The user can activate a top-level window by clicking it,
 selecting it using the ALT+TAB or ALT+ESC key combination,
 or selecting it from the Task List.
 A thread can activate a top-level window by using the SetActiveWindow function.
 It can determine whether a top-level window it created is active by using the GetActiveWindow function.



 Applications can use a hot key control to make it easy for the user to choose a hot key. 
 Hot key controls are typically used to define a hot key that activates a window;
 they do not use the RegisterHotKey and UnregisterHotKey functions.
 Instead, an application that uses a hot key control typically sends the WM_SETHOTKEY message to set the hot key.
 Whenever the user presses the hot key, the system sends a WM_SYSCOMMAND message specifying SC_HOTKEY.
 For more information about hot key controls, see "Using Hot Key Controls" in Hot Key Controls.
*/