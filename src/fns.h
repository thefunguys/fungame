#ifndef FNS_H
#define FNS_H
#define DEBUG_APP

#include <sstream>
#include <string>
#include <vector>

#define EPS 0.005

// grumble grumble floating point approxamation
inline bool close_to_zero(double n) {
    return n <= EPS && n >= -EPS;
}
#ifdef DEBUG_APP
#define dbpf(...) printf(__VA_ARGS__)
#else
#define dbpf(...)
#endif

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
