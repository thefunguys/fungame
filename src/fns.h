#ifndef FNS_H
#define FNS_H

#include <sstream>
#include <string>
#include <vector>

#define EPS 0.005

// grumble grumble floating point approxamation
inline bool close_to_zero(double n) {
    return n <= EPS && n >= -EPS;
}

inline std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems) {
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}


inline std::vector<std::string> split(const std::string &s, char delim) {
    std::vector<std::string> elems;
    split(s, delim, elems);
    return elems;
}

#endif
