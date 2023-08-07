#ifndef MAP_UTILS_H
#define MAP_UTILS_H

#include <map>
#include <string>
#include <iostream>
#include <fstream>
#include <list>
#include "stringUtils.h"

void addRecordToMap(std::multimap<int, std::string> &recordsMap, std::string name, const int number);
void writeMapToFile(std::multimap<int, std::string> recordsMap, std::string filePathAndName);
void readFileIntoMap(std::multimap<int, std::string> &recordsMap, std::string filePathAndName);

#endif