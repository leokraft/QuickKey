
#ifndef LOADER_H
#define LOADER_H

#include <QString>
#include <QStringList>
#include <fstream>

class Loader {

    public:
        Loader(QStringList tags);
        QString next();
        bool hasNext();
        void setFilter(QStringList tags);
    private:
        std::ifstream infile;
        QStringList tags;
};
#endif