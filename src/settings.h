#ifndef SETTINGS_H
#define SETTINGS_H

#include <QWidget>
#include <string>
#include "i_config_manager.h"
#include "win_config_manager.h"

class Settings : public QWidget {

    Q_OBJECT

    public:
        static Settings& getInstance() {

            static Settings instance;
            return instance;
        }

        Settings(Settings const&) = delete;
        void operator=(Settings const&) = delete;

        // TODO maybe bidirectional hashmap for <Enum, String>
        enum Theme {LIGHT, DARK, NONE}; // NONE has to be at the end since our iterator skips the last enum
        enum Position {PRIMARY_MONITOR, MOUSE_CURSOR, FOCUSED_WINDOW, UNDEFINED};
        
        void setTheme(Theme theme);
        void initHotkey();
        void setHotkey(std::string hotkeyString);

    private:
        Settings();

        Theme stringToThemeEnum(std::string string);
        std::string themeEnumToString(Settings::Theme theme);
        Settings::Position stringToPositionEnum(std::string string);
        std::string positionEnumToString(Settings::Position position);

        const std::string BASE_STYLE_PATH = "/style_sheets/base.qss";
        const std::string DARK_STYLE_PATH = "/style_sheets/dark.qss";
        const std::string LIGHT_STYLE_PATH = "/style_sheets/light.qss";

        IConfigManager *config;
};

#endif