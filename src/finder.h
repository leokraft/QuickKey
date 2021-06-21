
#ifndef FINDER_H
#define FINDER_H

#include <QWidget>
#include "characters.h"

class QLineEdit;
class QGroupBox;
class QPushButton;
class QVBoxLayout;

class Finder : public QWidget {

    Q_OBJECT

    public:
        Finder(QWidget *parent = nullptr);
        
    private:
        QLineEdit *searchLine;
        QPushButton *settingsButton;
        QVBoxLayout *contentLayout;

        Characters *characters;

        void copyFirstItem();
        void applySearch(const QString &searchText);
        void deleteOldItems();
};
#endif