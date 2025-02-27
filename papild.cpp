// skirtas kad tikrinti ar string'e yra tik raides
#include "papild.h"
#include <cctype>

bool tikrintiRaides(const std::string& str) {
    for (char c : str) {
        if (!std::isalpha(c)) {
            return false;
        }
    }
    return true;
}