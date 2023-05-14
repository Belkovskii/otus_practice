#ifndef STRING_UTILS_H
#define STRING_UTILS_H

#include <string>
#include <iostream>
#include <conio.h>
#include <list>


std::string getValidatedInputString();

int stringToIntWithValidation(std::string numberString);

std::list<std::string> splitString(std::string original, std::string delimiter);

#endif