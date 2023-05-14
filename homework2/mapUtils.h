#ifndef MAP_UTILS_H
#define MAP_UTILS_H

#include <map>
#include <string>
#include <iostream>
#include <fstream>
#include <list>
#include "stringUtils.h"

void addRecordToMap(std::map<int, std::string> &recordsMap, std::string name, const int number);
void writeMapToFile(std::map<int, std::string> recordsMap, std::fstream &i_file);
void readFileIntoMap(std::map<int, std::string> &recordsMap, std::fstream &i_file);

#endif