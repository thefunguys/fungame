#ifndef SPLIT_H
#define SPLIT_H

#include <sstream>
#include <string>
#include <vector>

std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems);
std::vector<std::string> split(const std::string &s, char delim);
#endif
