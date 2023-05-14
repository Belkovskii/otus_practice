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

const std::string enterName = "Welcome to GUESS NUMBER!!!\nTo exit press Ctrl+C any time\n Please enter your name: ";
const std::string enterNumber = "\nEnter your number: ";
const std::string wrongRange = "\nERROR: Wrong number. Choose in range 0-100";
const std::string chooseBiggerThan = "\nChoose something greater than ";
const std::string chooseSmallerThan = "\nChoose something smaller than ";
const std::string youWin = "\nYou Win!!!\n\n";
const std::string notNumeric = "\nERROR: characters in input. Please enter numeric symbols only\n";

int getRandomNumber();

int main()
{
    // prepare game data
    int answerNumber = getRandomNumber();
    std::map<int, std::string> recordsMap;
    int attemptCounter = 0;
    std::string playerName;
    bool doExitGame = false;
    int guessNumber = -1;
    // start game
    std::cout << enterName;
    std::cin >> playerName;
    while (!doExitGame)
    {
        std::cout << enterNumber;
        guessNumber = stringToIntWithValidation(getValidatedInputString());
        if (guessNumber == INT32_MIN)
        {
            std::cout << notNumeric << std::endl;
        }
        else if (guessNumber > 100 || guessNumber < 0)
        {
            std::cout << wrongRange << std::endl;
        }
        else if (guessNumber < answerNumber)
        {
            std::cout << chooseBiggerThan << guessNumber << std::endl;
            attemptCounter++;
        }
        else if (guessNumber > answerNumber)
        {
            std::cout << chooseSmallerThan << guessNumber << std::endl;
            attemptCounter++;
        }
        else
        {
            std::cout << youWin << std::endl;
            doExitGame = true;
        }
    }
    // fix results in file
    if (doExitGame && guessNumber == answerNumber)
    {
        addRecordToMap(recordsMap, playerName, attemptCounter);
        std::fstream file{"game_records.txt"};
        writeMapToFile(recordsMap, file);
    }
    return 0;
}

int getRandomNumber()
{
    std::srand(std::time(nullptr));
    return std::rand() % 100;
}