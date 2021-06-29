#include <windows.h>
#include <QAction>
#include <QMenu>
#include <QApplication>
#include <QFile>
#include <QPropertyAnimation>
#include <QParallelAnimationGroup>

#include "mainwindow.h"


std::string MainWindow::EXECUTABLE_DIR;

MainWindow::MainWindow(std::string executable_dir, QWidget *parent) : QStackedWidget(parent) {

    EXECUTABLE_DIR = executable_dir;

    // register hotkey to the window of this widget
    // Virtual-Key Codes -> https://docs.microsoft.com/en-us/windows/win32/inputdev/virtual-key-codes
    bool success = RegisterHotKey(HWND(this->winId()), 1, MOD_CONTROL, 0x59);
    
    // startup on focused window
    // IntPtr foregroundWindowHandle = NativeMethods.GetForegroundWindow();
    // Screen activeScreen = Screen.FromHandle(foregroundWindowHandle);

    // startup from cursor
    // Screen.FromPoint(System.Windows.Forms.Cursor.Position)

    this->setWindowFlags(Qt::CustomizeWindowHint);
    this->setMinimumSize(450, 250);

    finder = new Finder;
    settings = new Settings;

    this->addWidget(finder);
    this->addWidget(settings);

    this->createTrayIcon();
}

void MainWindow::activate() {

    this->show();
    this->activateWindow();
    finder->setSearchBarFocus();
}

bool MainWindow::nativeEvent(const QByteArray &eventType, void *message, qintptr *result) {

    Q_UNUSED(result);
    Q_UNUSED(eventType);

    MSG *msg = static_cast<MSG *>(message);
    if (msg->message == WM_HOTKEY) {
        if (!this->isVisible()) {
            activate();
        } else {
            this->hide();
        }
        return true;
    }

    return false;
}

void MainWindow::showEvent(QShowEvent* event) {

    QWidget::showEvent(event);

    HMONITOR hMonitor =  MonitorFromWindow(GetForegroundWindow(), MONITOR_DEFAULTTOPRIMARY);

    MONITORINFO mi;
    mi.cbSize = sizeof(mi);
    GetMonitorInfo(hMonitor, &mi);
    
    int winWidth = this->frameGeometry().width();
    int winHeight = this->frameGeometry().height();

    LONG monitorRight = mi.rcWork.right;
    LONG monitorBottom = mi.rcWork.bottom;

    QParallelAnimationGroup *showGroup = new QParallelAnimationGroup;

    QPropertyAnimation *slide = new QPropertyAnimation(this, "geometry");
    slide->setDuration(100);
    slide->setStartValue(QRect(monitorRight - winWidth, monitorBottom, winWidth, winHeight));
    slide->setEndValue(QRect(monitorRight - winWidth, monitorBottom - winHeight, winWidth, winHeight));
    slide->setEasingCurve(QEasingCurve::OutExpo);

    showGroup->addAnimation(slide);

    QPropertyAnimation *opacity = new QPropertyAnimation(this, "windowOpacity");
    opacity->setDuration(200);
    opacity->setStartValue(0);
    opacity->setEndValue(1);
    opacity->setEasingCurve(QEasingCurve::OutQuad);

    showGroup->addAnimation(opacity);

    showGroup->start();
}

void MainWindow::changeEvent(QEvent *event) {   

    QWidget::changeEvent(event);
    if (event->type() == QEvent::ActivationChange) {
        if(!this->isActiveWindow()) {
            this->hide();
        }
    }
}

void MainWindow::closeEvent(QCloseEvent *event) {

    if (!isTrayExit) {
        this->hide();
        event->ignore();
        return;
    }

    // exit has been caused by exit from tray

}

void MainWindow::trayExit() {
    isTrayExit = true;
    delete trayIcon;
    close();
}

void MainWindow::createTrayIcon() {

    QAction *openAction = new QAction(tr("&Open"), this);
    connect(openAction, &QAction::triggered, this, &MainWindow::activate);

    QAction *quitAction = new QAction(tr("&Exit"), this);
    connect(quitAction, &QAction::triggered, this, &MainWindow::trayExit);

    QMenu *trayIconMenu = new QMenu(this);

    trayIconMenu->addAction(openAction);
    trayIconMenu->addSeparator();
    trayIconMenu->addAction(quitAction);

    trayIcon = new QSystemTrayIcon(this);

    trayIcon->setIcon(QIcon(":/qicon.svg"));
    trayIcon->setContextMenu(trayIconMenu);

    connect(trayIcon, &QSystemTrayIcon::activated, this, &MainWindow::iconActivated);

    trayIcon->show();
    isTrayExit = false;
}

void MainWindow::iconActivated(QSystemTrayIcon::ActivationReason reason) {

    if (reason == QSystemTrayIcon::Trigger) {
        this->activate();
    }
}