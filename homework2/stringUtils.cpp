#include "stringUtils.h"
#include <iostream>
#define DELIMITER "<->"

std::string getValidatedInputString()
{
    std::string inputString;
    std::cin >> inputString;
    return inputString;
}

int stringToIntWithValidation(std::string numberString)
{
    int guessNumber = -1;
    try
    {
        guessNumber = std::stoi(numberString);
    }
    catch (const std::exception &e)
    {
        guessNumber = INT32_MIN;
    }
    return guessNumber;
}

std::list<std::string> splitString(std::string original, std::string delimiter)
{
    std::list<std::string> result;
    int position = 0;
    std::string token;
    while (((position = original.find(delimiter)) != std::string::npos))
    {
        token = original.substr(0, position);
        result.push_back(token);
        original.erase(0, position + delimiter.length());
    }
    if (original.size() != 0)
    {
        result.push_back(original);
    }
    return result;
}