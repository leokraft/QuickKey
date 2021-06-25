
#ifndef FINDER_H
#define FINDER_H

#include <QWidget>
#include <string>
class QLineEdit;
class QGroupBox;
class QPushButton;
class QVBoxLayout;

class Finder : public QWidget {

    Q_OBJECT

    public:
        Finder(std::string executable_folder, QWidget *parent = nullptr);
        void setSearchBarFocus();
        
    private:
        QLineEdit *searchBar;
        QPushButton *settingsButton;
        QVBoxLayout *contentLayout;
        std::string executable_folder;

        void copyFirstItem();
        void applySearch(const QString &searchText);
        void deleteOldItems();
};
#endif