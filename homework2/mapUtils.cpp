#include "mapUtils.h"
#include "stringUtils.h"
#include <string>
#define DELIMITER "<->"

void addRecordToMap(std::map<int, std::string> &recordsMap, std::string name, const int number)
{
    std::string &currentNumbersPerson = recordsMap[number];
    if (currentNumbersPerson.length() == 0)
        currentNumbersPerson = name;
    else
        currentNumbersPerson = (currentNumbersPerson + DELIMITER + name);
}

void readFileIntoMap(std::map<int, std::string> &recordsMap, std::fstream &i_file) {
    std::string line;
    while (std::getline(i_file, line)) {
        std::list<std::string> nameAndPoints = splitString(line, " - ");
        std::string playerName = nameAndPoints.front();
        int numberOfPoints = stringToIntWithValidation(nameAndPoints.back());
        std::cout << numberOfPoints << std::endl;
        addRecordToMap(recordsMap, playerName, numberOfPoints);
    }
}


void writeMapToFile(std::map<int, std::string> recordsMap, std::fstream &i_file)
{
    if (i_file.is_open())
    {
        readFileIntoMap(recordsMap, i_file);
        std::map<int, std::string>::iterator it = recordsMap.begin();
        while (it != recordsMap.end())
        {
            int attemptsNumber = it->first;
            std::string playersNames = it->second;
            std::list<std::string> playersNamesList = splitString(playersNames, std::string{DELIMITER});
            for (std::string playersName : playersNamesList)
            {
                std::string resultString = playersName + " - " + std::to_string(attemptsNumber);
                i_file << resultString << std::endl;
            }
            it++;
        }
    }
    else 
    {
        std::cout << "File was not opened correctly";
    }
}