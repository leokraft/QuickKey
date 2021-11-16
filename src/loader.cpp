#include <sstream>
#include <fstream>
#include <algorithm>
#include <QFontDatabase>
#include <set>

#include "loader.h"
#include "main_window.h"
#include "win_path_manager.h"

Loader::Loader() {

    //create stream
    // TODO handle this (WinPathManager) diffrently to respect interface
    std::string FILE_NAME = WinPathManager::executablePath + "/resources/DerivedName.txt";
    std::ifstream infile;
    infile.open(FILE_NAME, std::ifstream::in);

    std::string tempLine;
    std::string unicodeHexString;
    QString unicode;
    
    // parse unicode textfile and save as pair list <unicode, tags>
    while (std::getline(infile, tempLine)) {

        if (tempLine[0] == '#') {
            // ignore comments
            continue;
        }

        std::istringstream iline(tempLine);

        std::getline(iline, unicodeHexString, ';');

        std::istringstream string_to_hex(unicodeHexString);

        // convert string of hex values to 4-byte int representing ucs4
        uint32_t unicodeHex;
        string_to_hex >> std::hex >> unicodeHex;

        // interpret uint32_t as ucs4 encoding to get representation
        unicode = QString::fromUcs4(&unicodeHex, 1);

        // TODO check if unicode is displayable?

        std::string unicodeTag;
        QStringList unicodeTags;

        while (std::getline(iline, unicodeTag, ' ')) {

            unicodeTags.append(QString::fromStdString(unicodeTag));

        }
        
        unicodeData.push_back(std::make_pair(unicode, unicodeTags));
    }
    
    currentIter = unicodeData.begin();
}

QString Loader::next() {

    QString validNext = NULL;
    while (validNext.isEmpty() && currentIter != unicodeData.end()) {

        QStringList itemTags = (*currentIter).second;
        
        // if no search tag is given we want to return all items
        if ((!searchTags.isEmpty()) && !matchesPartial(itemTags, searchTags)) {
            currentIter++;
            continue;
        }

        validNext = (*currentIter).first;
        currentIter++;
    }

    return validNext;
}

bool Loader::matchesPartial(QStringList &itemTags, QStringList &searchTags) {

    // checks whether every search tag is present in items tags
    // it is sufficient if the tag is only present as a prefix of an item tag
    for (QString searchTag : searchTags) {

        auto present = std::find_if(itemTags.begin(), itemTags.end(),
            [searchTag](QString itemTag) {
                return itemTag.toLower().startsWith(searchTag.toLower());
            });
        
        if (present == itemTags.end()) {
            return false;
        }
    }

    return true;
}

void Loader::setFilter(QStringList tags) {
    this->searchTags = tags;
    // reset iterator to strat searching from the beginning again
    currentIter = unicodeData.begin();
}