#ifndef __KEY_MAP_H__
#define __KEY_MAP_H__

#include <windows.h>
#include <string>
#include <map>

class KeyMap {

    public:

        static KeyMap& getInstance() {

            return instance;
        }

        KeyMap(KeyMap const&) = delete;
        void operator=(KeyMap const&) = delete;

        static std::string toString(int code);
        static int fromString(std::string vkString);

    private:
        KeyMap();

        static std::map<int, std::string> hashVKCtoString;
        static std::map<std::string, int> hashStringToVKC;
        static KeyMap instance;
};

#endif