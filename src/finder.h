
#ifndef FINDER_H
#define FINDER_H

#include <QWidget>
#include "loader.h"

class QLineEdit;
class QGroupBox;
class QPushButton;
class QVBoxLayout;

class Finder : public QWidget {

    Q_OBJECT

    public:
        Finder(QWidget *parent = nullptr);
        void setSearchBarFocus();
        
    private:
        QLineEdit *searchBar;
        QPushButton *settingsButton;
        QVBoxLayout *contentLayout;

        Loader loader;

        void copyFirstItem();
        void applySearch(const QString &searchText);
        void deleteOldItems();
        void simulatedPasteKeybind();
};
#endif