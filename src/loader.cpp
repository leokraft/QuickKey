#include "loader.h"
#include <sstream>
#include "main_window.h"
#include "win_path_manager.h"

Loader::Loader(QStringList tags) : tags(tags) {

    //create stream
    // TODO handle this (WinPathManager) diffrently to respect interface
    std::string FILE_NAME = WinPathManager::executablePath + "/resources/DerivedName.txt";
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
        } while(tempLine[0] == '#'); // ignore comments starting with #

        std::istringstream iline(tempLine);

        std::string unicodeHexString;
        std::getline(iline, unicodeHexString, ';');

        std::istringstream string_to_hex(unicodeHexString);

        // convert string of hex values to 4-byte int representing ucs4
        uint32_t unicodeHex;
        string_to_hex >> std::hex >> unicodeHex;

        // interpret uint32_t as ucs4 encoding to get representation
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