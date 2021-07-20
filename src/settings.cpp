#include <QFile>
#include <QApplication>
#include "settings.h"

void Settings::setTheme(Theme theme) {

    // load base styling of components
    QFile baseStyleFile( QString::fromStdString(executableDir + BASE_STYLE_PATH));
    baseStyleFile.open( QFile::ReadOnly );
    QString style(baseStyleFile.readAll());

    if (theme == DARK) {
        
        QFile themeStyleFile( QString::fromStdString(executableDir + DARK_STYLE_PATH));
        themeStyleFile.open( QFile::ReadOnly );
        style.append(themeStyleFile.readAll());
    }
    
    qApp->setStyleSheet(style);
}

void Settings::setExecutableDir(std::string executableDir) {

    this->executableDir = executableDir;
}