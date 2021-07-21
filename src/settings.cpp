#include <QFile>
#include <QApplication>
#include <QFormLayout>
#include <QString>
#include <QComboBox>

#include "settings.h"
#include "i_path_manager.h"
#include "win_path_manager.h"

Settings::Settings() {

    // initialization
    config = new WinConfigManager;
    
    std::string theme = config->getConfig("theme");
    
    setTheme(stringToThemeEnum(theme));

    // gui
    QComboBox *themeSelector = new QComboBox;
    themeSelector->addItems({"Dark", "Light"});
    connect(themeSelector,QComboBox::currentTextChanged,[this](const QString &text){
        Theme theme = stringToThemeEnum(text.toStdString());
        setTheme(theme);
        config->writeConfig("Theme", text.toStdString());
    });

    QComboBox *positionSelector = new QComboBox;
    positionSelector->addItems({"Primary monitor", "Mouse cursor monitor", "Focused window"});
    connect(positionSelector,QComboBox::currentTextChanged,[this](const QString &text){
        config->writeConfig("Position", text.toStdString());
    });

    QFormLayout *layout = new QFormLayout;
    layout->addRow(tr("&Theme:"), themeSelector);
    layout->addRow(tr("&Position:"), positionSelector);
    this->setLayout(layout);
}

Settings::Theme Settings::stringToThemeEnum(std::string string) {

    // convert string to upper case
    std::transform(string.begin(), string.end(), string.begin(),
                    [](unsigned char c){ return std::toupper(c); }
                  );

    if (string == "DARK") {
        return DARK;
    } else if (string == "LIGHT") {
        return LIGHT;
    }

    return NONE;
}

std::string Settings::themeEnumToString(Settings::Theme theme) {

    switch (theme) {
        case DARK: return "Dark";
        case LIGHT: return "Light";
        default: return NULL;
    }
}

Settings::Position Settings::stringToPositionEnum(std::string string) {

    // convert string to upper case
    std::transform(string.begin(), string.end(), string.begin(),
                    [](unsigned char c){ return std::toupper(c); }
                  );

    if (string == "PRIMARY MONITOR") {
        return PRIMARY_MONITOR;
    } else if (string == "MOUSE CURSOR MONITOR") {
        return MOUSE_CURSOR;
    } else if (string == "FOCUSED WINDOW") {
        return FOCUSED_WINDOW;
    }

    return UNDEFINED;
}

std::string Settings::positionEnumToString(Settings::Position position) {

    switch (position) {
        case PRIMARY_MONITOR: return "Primary monitor";
        case MOUSE_CURSOR: return "Mouse cursor monitor";
        case FOCUSED_WINDOW: return "Focused window";
        default: return NULL;
    }
}

void Settings::setTheme(Theme theme) {

    std::string executablePath = WinPathManager::executablePath;

    // load base styling of components
    QFile baseStyleFile( QString::fromStdString(executablePath + BASE_STYLE_PATH));
    baseStyleFile.open( QFile::ReadOnly );
    QString style(baseStyleFile.readAll());

    QString themeStylePath;
    if (theme == DARK) {
        
        themeStylePath = QString::fromStdString(executablePath + DARK_STYLE_PATH);

    } else if (theme == LIGHT) {
        themeStylePath = QString::fromStdString(executablePath + LIGHT_STYLE_PATH);

    } else {
        //default to dark theme for the moment
        themeStylePath = QString::fromStdString(executablePath + DARK_STYLE_PATH);
    }

    QFile themeStyleFile(themeStylePath);
    themeStyleFile.open( QFile::ReadOnly );
    style.append(themeStyleFile.readAll());
    
    qApp->setStyleSheet(style);
}