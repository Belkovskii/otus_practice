#include <iostream>
#include <fstream>
#include <random>
#include <stdlib.h>
#include <string>
#include <map>
#include <list>
#include <iterator>
#include "stringUtils.h"
#include "mapUtils.h"

const std::string enterName = "Welcome to GUESS NUMBER!!!\nTo exit press ESC any time\n Please enter your name: ";
const std::string enterNumber = "\nEnter your number: ";
const std::string wrongRange = "\nERROR: Wrong number. Choose in range 0-100";
const std::string chooseBiggerThan = "\nChoose something greater than ";
const std::string chooseSmallerThan = "\nChoose something smaller than ";
const std::string youWin = "\nYou Win!!!\n\n";
const std::string notNumeric = "\nERROR: characters in input. Please enter numeric symbols only\n";

int getRandomNumber();

int main()
{
    bool doExitGame = false;
    int answerNumber = -1;
    std::map<int, std::string> recordsMap;
    while (!doExitGame)
    {
        std::cout << enterName;
        std::string name = getEscValidatedInputString(doExitGame);
        int attemptCounter = 0;
        if (!doExitGame)
            answerNumber = getRandomNumber();
        while (!doExitGame)
        {
            std::cout << enterNumber;
            int guessNumber = stringToIntWithValidation(getEscValidatedInputString(doExitGame));
            if (!doExitGame)
            {
                attemptCounter++;
                if (guessNumber == INT32_MIN)
                    std::cout << notNumeric << std::endl;
                else if (guessNumber > 100 || guessNumber < 0)
                    std::cout << wrongRange << std::endl;
                else if (guessNumber < answerNumber)
                    std::cout << chooseBiggerThan << guessNumber << std::endl;
                else if (guessNumber > answerNumber)
                    std::cout << chooseSmallerThan << guessNumber << std::endl;
                else
                    std::cout << youWin << std::endl;
            }
            if (guessNumber == answerNumber)
            {
                addRecordToMap(recordsMap, name, attemptCounter);
                break;
            }
        }
    }
    std::fstream file{"game_records.txt", std::ios_base::in | std::ios_base::out | std::ios_base::trunc};
    writeMapToFile(recordsMap, file);
    return 0;
}

int getRandomNumber()
{
    std::srand(std::time(nullptr));
    return std::rand() % 100;
}