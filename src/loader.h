
#ifndef LOADER_H
#define LOADER_H

#include <QString>
#include <QStringList>

#include <string>
#include <list>

class Loader {

    public:
        Loader();
        QString next();
        void setFilter(QStringList tags);

    private:

        QStringList searchTags;
        std::list<std::pair<QString, QStringList>> unicodeData;
        std::list<std::pair<QString, QStringList>>::iterator currentIter;

        bool matchesPartial(QStringList &itemTags, QStringList &searchTag);
};
#endif