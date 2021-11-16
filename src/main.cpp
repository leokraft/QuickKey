#include <QApplication>

#include "main_window.h"
#include "win_path_manager.h"
#include "settings.h"

/** 
 * START APP -> run exe or autostart on system start
 * ON START -> dont show window; show icon in system tray
 * OPEN APP -> CLICK icon in system tray; press app hotkey
 * HOTKEY -> DEFAULT ctrl + Y OR CUSTOM Hotkey
 * FOCUS -> focus search bar
 * ON TYPING -> update shown buttons
 * ON ENTER -> COPY first item; CLOSE window
 * ON ITEM CLICK -> COPY item
 * ON SETTINGS CLICK -> OPEN settings
 * 
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

int main(int argc, char *argv[]) {


    IPathManager *pathManager = new WinPathManager();
    pathManager->initExecutablePath(argv[0]);

    QApplication app(argc, argv);

    MainWindow mainWindow;

    // mainWindow starts hidden

    return app.exec();
}