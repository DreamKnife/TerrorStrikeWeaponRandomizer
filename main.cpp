#include <iostream>
#include <fstream>
#include <cstdlib> // for rand() and srand() and exit()
#include <ctime> // for time()
#include "variables.h"
#include "functions.h"
#include <conio.h>


int main()
{
    srand(static_cast<unsigned int>(time(0))); // set initial seed value to system clock for random numbers
    getRandomNumber(0, 3); // call getRandomNumber() once and throw away because the first call doesn't seem to come out random
    //std::fstream sasGame("C:\\Program Files (x86)\\Konami\\The Regiment\\system\\SASGame.u");
    //std::fstream sasChars("C:\\Program Files (x86)\\Konami\\The Regiment\\system\\SASChars.u");
    std::fstream sasGame("SASGame.u");
    std::fstream sasChars("SASChars.u");

    // if file fails to open print error and exit
    if (!sasGame)
    {
        std::cerr << "Error opening SASGame.u.  Please confirm this executable is in the same directory as the file SASGame.u." << '\n';
        getch();
        exit(1);
    }

    // if file fails to open print error and exit
    if (!sasChars)
    {
        std::cerr << "Error opening SASChars.u  Please confirm this executable is in the same directory as the file SASChars.u." << '\n';
        getch();
        exit(1);
    }

    assignGun(sasGame, defaultMP5.filePosition, defaultMP5.length);
    assignGun(sasGame, defaultAK47.filePosition, defaultAK47.length);

    // handle the sas trooper sidearm here - only two possibilities
    switch (getRandomNumber(0, 1))
    {
        case 0:
            sasChars.seekg(defaultP226Address, std::ios::beg);
            sasChars << p226; // put the p226 back in
            break;
        case 1:
            sasChars.seekg(defaultP226Address, std::ios::beg);
            std::string tempWeapon{socom};
            tempWeapon.push_back(0x00);
            tempWeapon.push_back(0x00);
            sasChars << tempWeapon; // create a copy of the socom, pad it, and put it in
            break;
    }

    // set guns for the sas troopers
    for (auto &element : sasTroopers)
    {
        assignGun(sasChars, element.filePosition, element.length);
        //std::cout << std::hex << std::uppercase << element.filePosition << " , " << std::dec << element.length << '\n';
    }

    // set guns for the terrorists
    for (auto &element : terrorists)
    {
        assignGun(sasChars, element.filePosition, element.length);
        //std::cout << std::hex << std::uppercase << element.filePosition << " , " << std::dec << element.length << '\n';
    }

    std::cout << "Done.";
    getch();

    return 0;
}
