
#ifndef LOADER_H
#define LOADER_H

#include <QString>
#include <QStringList>
#include <fstream>
#include <string>

class Loader {

    public:
        Loader(QStringList tags, std::string executable_folder);
        QString next();
        bool hasNext();
        void setFilter(QStringList tags);
    private:
        std::ifstream infile;
        QStringList tags;
};
#endif