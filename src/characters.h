#ifndef CHARACTERS_H
#define CHARACTERS_H

#include <list>
#include <string>
#include <vector>
#include <QList>
#include <QStringList>

class Characters {
    private:
        std::vector<std::vector<bool>> connectionMatrix;
        bool allTagsContained(QStringList charTags, QStringList searchTags);
    public:
        QStringList getByTags(QStringList tags);
};
#endif