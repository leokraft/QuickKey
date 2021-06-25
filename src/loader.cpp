#include "loader.h"
#include <string>
#include <sstream>

#include <iostream>

Loader::Loader(QStringList tags) : tags(tags) {

    //create stream
    std::string FILE_NAME = "src/resources/DerivedName.txt";
    infile.open(FILE_NAME, std::ifstream::in);

}

bool Loader::hasNext() {
    return infile.peek()!=EOF;
}

QString Loader::next() {

    std::string tempLine;
    QString unicode;
    QStringList unicodeTags;
    QStringList searchTags;

    do {
        do {
            if (!std::getline(infile, tempLine)) {
                return NULL;
            }
        } while(tempLine[0] == '#');

        std::istringstream iline(tempLine);

        std::string unicodeHexString;
        std::getline(iline, unicodeHexString, ';');

        std::istringstream string_to_hex(unicodeHexString);

        uint unicodeHex;
        string_to_hex >> std::hex >> unicodeHex;

        unicode = QString::fromUcs4(&unicodeHex, 1);

        std::string unicodeTag;
        unicodeTags.clear();

        searchTags = tags;
        searchTags.detach();
        
        while (std::getline(iline, unicodeTag, ' ')) {
            if (unicodeTag != "") {

                for (int i = 0; i < searchTags.size(); i++) {
                    
                    // FIXME what about multiple unfinished tags?
                    if (QString::fromStdString(unicodeTag).toLower().startsWith(searchTags.at(i).toLower())) {
                        searchTags.remove(i);
                    }
                }
            }
        }

    } while (!searchTags.isEmpty());
    
    
    return unicode;
}