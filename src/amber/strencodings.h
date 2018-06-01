/* AMB START */

// Amberchain code distributed under the GPLv3 license, see COPYING file.

#ifndef AMBER_STRENCODINGS_H
#define AMBER_STRENCODINGS_H

#include <stdlib.h>
#include <string>

using namespace std;

string HexToStr(string hex) {
    int len = hex.length();
    string returnValue;
    for (int i = 0; i < len; i+=2) {
        string byte = hex.substr(i, 2);
        char character = (char) (int)strtol(byte.c_str(), NULL, 16);
        returnValue.push_back(character);
    }
    return returnValue;
}

#endif

/* AMB END */