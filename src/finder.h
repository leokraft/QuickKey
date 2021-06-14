
#ifndef FINDER_H
#define FINDER_H

#include <QWidget>

class QLabel;
class QLineEdit;
class QGroupBox;
class QPushButton;
class QVBoxLayout;

class Finder : public QWidget {

    Q_OBJECT

    public:
        Finder(QWidget *parent = nullptr);
        void addGroupBox(QGroupBox *group);

    private:
        QLineEdit *searchLine;
        QPushButton *settingsButton;
        QVBoxLayout *contentLayout;
};
#endif