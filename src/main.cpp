#include <QApplication>
#include <string>
#include "mainwindow.h"
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

    // as seen in https://stackoverflow.com/questions/57626409/how-can-i-access-resources-in-c-without-setting-the-full-path
    const std::string called_cmd = argv[0];

    // Locate the executable name
    size_t n = called_cmd.rfind("\\"); // Windows

    // Handle potential errors (should never happen but it is for robustness purposes)
    if(n == std::string::npos) // if pattern not found
        return -1;

    // Remove the executable name
    std::string executableDir = called_cmd.substr(0, n);

    QApplication app(argc, argv);

    Settings::getInstance().setExecutableDir(executableDir);
    Settings::getInstance().setTheme(Settings::DARK);
    MainWindow mainWindow(executableDir);

    // mainWindow starts hidden
 
    return app.exec();
}

