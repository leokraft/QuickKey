#include <iostream>
#include <windows.h>
#include <QAction>
#include <QMenu>
#include <QSystemTrayIcon>
#include <QApplication>
#include <QFile>

#include "mainwindow.h"
#include "finder.h"
#include "settings.h"


MainWindow::MainWindow(QWidget *parent) : QStackedWidget(parent) {

    // register hotkey to the window of this widget
    // Virtual-Key Codes -> https://docs.microsoft.com/en-us/windows/win32/inputdev/virtual-key-codes
    bool success = RegisterHotKey(HWND(this->winId()), 1, MOD_CONTROL, 0x59);

    Finder *finder = new Finder;
    Settings *settings = new Settings;

    this->addWidget(finder);
    this->addWidget(settings);

    this->createTrayIcon();
}

void MainWindow::activate() {
    this->show();
    this->activateWindow();
}

bool MainWindow::nativeEvent(const QByteArray &eventType, void *message, qintptr *result) {

    Q_UNUSED(result);
    Q_UNUSED(eventType);

    MSG *msg = static_cast<MSG *>(message);
    if (msg->message == WM_HOTKEY) {
        std::cout << "Global shortcut pressed..." << std::endl;
        activate();
        return true;
    }

    return false;
}

void MainWindow::changeEvent(QEvent *event) {   

    QWidget::changeEvent(event);
    if (event->type() == QEvent::ActivationChange) {
        if(!this->isActiveWindow()) {
            std::cout << "I am shy..." << std::endl;
            this->hide();
        }
    }
}

void MainWindow::closeEvent(QCloseEvent *event) {
    std::cout << "Hi and Bye..." << std::endl;
    this->hide();
    event->ignore();
}

void MainWindow::createTrayIcon() {

    QAction *openAction = new QAction(tr("&Open"), this);
    connect(openAction, &QAction::triggered, this, &MainWindow::activate);

    QAction *quitAction = new QAction(tr("&Exit"), this);
    connect(quitAction, &QAction::triggered, QApplication::instance(), &QApplication::quit);

    QMenu *trayIconMenu = new QMenu(this);

    trayIconMenu->addAction(openAction);
    trayIconMenu->addSeparator();
    trayIconMenu->addAction(quitAction);

    QSystemTrayIcon *trayIcon = new QSystemTrayIcon(this);
    
    trayIcon->setIcon(QIcon(":/qicon.svg"));
    trayIcon->setContextMenu(trayIconMenu);

    trayIcon->show();
}