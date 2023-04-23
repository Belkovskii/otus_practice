#include "mapUtils.h"
#include "stringUtils.h"
#define DELIMITER "<->"

void addRecordToMap(std::map<int, std::string> &recordsMap, std::string name, const int number)
{
    std::string &currentNumbersPerson = recordsMap[number];
    if (currentNumbersPerson.length() == 0)
        currentNumbersPerson = name;
    else
        currentNumbersPerson = (currentNumbersPerson + DELIMITER + name);
}


void writeMapToFile(std::map<int, std::string> recordsMap, std::fstream &i_file)
{
    if (i_file.is_open())
    {
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