/* AMB START */

// Amberchain code distributed under the GPLv3 license, see COPYING file.

#include "amber/strencodings.h"

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

/* AMB END */