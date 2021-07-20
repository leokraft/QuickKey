#ifndef SETTINGS_H
# define SETTINGS_H

#include <QWidget>
#include <string>

class Settings : public QWidget {

    Q_OBJECT

    public:
        static Settings& getInstance()
        {
            static Settings instance;
            return instance;
        }
        enum Theme {LIGHT, DARK};
        Settings(Settings const&) = delete;
        void operator=(Settings const&) = delete;
        void setTheme(Theme theme);
        void setExecutableDir(std::string executableDir);

    private:
        Settings() {}

        std::string executableDir = "";
        const std::string BASE_STYLE_PATH = "/style/base.qss";
        const std::string DARK_STYLE_PATH = "/style/dark.qss";
};

#endif