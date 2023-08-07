#include "mapUtils.h"
#include "stringUtils.h"
#include <string>
#define DELIMITER "<->"

typedef std::pair<int, std::string> PointsToName;

void addRecordToMap(std::multimap<int, std::string> &recordsMap, std::string name, const int number)
{ 
    recordsMap.insert(PointsToName(number, name));
}

void readFileIntoMap(std::multimap<int, std::string> &recordsMap, std::string filePathAndName) {
    std::ifstream i_file;
    i_file.open(filePathAndName);
    if (i_file.is_open()) 
    {
        std::string line;
        while (std::getline(i_file, line)) 
        {
            std::list<std::string> nameAndPoints = splitString(line, " - ");
            std::string playerName = nameAndPoints.front();
            int numberOfPoints = stringToIntWithValidation(nameAndPoints.back());
            std::cout << numberOfPoints << std::endl;
            addRecordToMap(recordsMap, playerName, numberOfPoints);
        }
        i_file.close();
    }
}


void writeMapToFile(std::multimap<int, std::string> recordsMap, std::string filePathAndName)
{
    readFileIntoMap(recordsMap, filePathAndName);
    std::ofstream o_file;
    o_file.open(filePathAndName);
    if (o_file.is_open())
    {
        std::multimap<int, std::string>::iterator it = recordsMap.begin();
        while (it != recordsMap.end())
        {
            int attemptsNumber = it->first;
            std::string playersNames = it->second;
            std::list<std::string> playersNamesList = splitString(playersNames, std::string{DELIMITER});
            for (std::string playersName : playersNamesList)
            {
                std::string resultString = playersName + " - " + std::to_string(attemptsNumber);
                o_file << resultString << std::endl;
            }
            it++;
        }
        o_file.close();
    }
    else 
    {
        std::cout << "File was not opened correctly";
    }
}