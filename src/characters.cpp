#include "characters.h"
#include <map>

/**Store list of characters with respective tags.
 * On construction read file and create binary matrix. (Rows=Tags, Columns=Chars)
 * 
 * Given a list of tags fin all chars using ALL those tags.
 * 
 * On adding new tag, add new row to matrix and tag to tag list of char.
 * 
 * On deleting custom tag remove matrix row and entry from char.
 * 
 * Maybe add custom grouping?
 * Maybe add custom chars or even strings?
 */

QStringList Characters::getByTags(QStringList tags) {

    QStringList searchMatches;

    std::map<QString, QStringList> charMap = {{"α",{"Alpha"}}, {"β",{"Beta"}}, {"γ",{"Gamma"}}, {"δ",{"Delta"}}, {"ε",{"Epsilon"}}, {"ζ",{"Zeta"}}, {"η",{"Eta"}}, {"θ",{"Theta"}}};

    if (tags.isEmpty()) {
        for (auto [character, charTags] : charMap) {
            searchMatches.push_back(character);
        }
        return searchMatches;
    }

    for (auto [character, charTags] : charMap) {
        if (allTagsContained(charTags, tags)) {
            searchMatches.push_back(character);
        }
    }

    return searchMatches;
}

bool Characters::allTagsContained(QStringList charTags, QStringList searchTags) {

    for (QString tag : searchTags) {
        for (QString charTag : charTags) {
            // FIXME what about multiple unfinished tags?
            if (!charTag.toLower().startsWith(tag.toLower())) {
                return false;
            }
        }
    }

    return true;
}