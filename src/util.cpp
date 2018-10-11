#include "util.h"

bool ezc::has_suffix(std::string src, std::string suffix){
    return src.size() > suffix.size() &&
        src.compare(src.size() - suffix.size(), suffix.length(), suffix) ==0;
}