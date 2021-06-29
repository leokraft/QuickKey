#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QStackedWidget>
#include <QEvent>
#include <QCloseEvent>
#include <QSystemTrayIcon>

#include "finder.h"
#include "settings.h"

class MainWindow : public QStackedWidget {

    Q_OBJECT

    public:
        MainWindow(std::string executable_dir, QWidget *parent = nullptr);
        static std::string EXECUTABLE_DIR;
    protected:
        void closeEvent(QCloseEvent *event);
        void showEvent(QShowEvent* event);
        void changeEvent(QEvent *event);
        bool nativeEvent(const QByteArray &eventType, void *message, qintptr *result);
        void iconActivated(QSystemTrayIcon::ActivationReason reason);
    private:
        Finder *finder;
        Settings *settings;
        QSystemTrayIcon *trayIcon;
        bool isTrayExit;

        void createTrayIcon();
        void activate();
        void trayExit();
};

#endif