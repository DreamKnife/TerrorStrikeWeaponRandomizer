#include <string>
#include <cstdlib> // for rand() and srand() and exit()
#include <ctime> // for time()
#include <iostream>
#include <fstream>
#include "variables.h"

// Generate a random number between min and max (inclusive)
// Assumes srand() has already been called
// Assumes max - min <= RAND_MAX
// from http://www.learncpp.com/cpp-tutorial/59-random-number-generation/
int getRandomNumber(int min, int max)
{
    static const double fraction = 1.0 / (static_cast<double>(RAND_MAX) + 1.0);  // static used for efficiency, so we only calculate this value once
    // evenly distribute the random number across our range
    return min + static_cast<int>((max - min + 1) * (rand() * fraction));
}

// returns random gun as std::string
std::string getRandomWeapon()
{
    switch (getRandomNumber(0, 15))
    {
        case 0:
            return ak47;
        case 1:
            return ak74;
        case 2:
            return g3sg1;
        case 3:
            return mp5klss;
        case 4:
            return mp5k;
        case 5:
            return mp5sdlss;
        case 6:
            return mp5lss;
        case 7:
            return mp5sd;
        case 8:
            return mp5;
        case 9:
            return m1100t;
        case 10:
            return m4a1;
        case 11:
            return m60;
        case 12:
            return mac11;
        case 13:
            return sigswat;
        case 14:
            return aug;
        case 15:
            return uzi;
        default:
            std::cerr << "Error: unhandled case in getRandomWeapon()" << '\n';
    }
}

// takes a gun slot and fills it with a random gun
void assignGun(std::fstream &file, long slotAddress, short slotLength)
{

    // if slot address is less than or equal to 0 it's definitely invalid, report an error and back out
    if (slotAddress <= 0)
    {
        std::cerr << "Error: invalid slot address passed to assignGun()" << file << '\n';
        return;
    }

    file.seekg(slotAddress, std::ios::beg);
    std::string tempWeapon{getRandomWeapon()};

    // loop that checks randomly selected gun is smaller than slot and chooses again if not
    while (tempWeapon.length() > slotLength)
    {
        tempWeapon = getRandomWeapon();
    }

    short lengthDifference{slotLength - tempWeapon.length()}; // calculate length difference

    // add empty spaces to the weapon as many times as needed to match the length
    // of the slot it's going to fill
    for (short i{0}; i < lengthDifference; ++i)
        {
            tempWeapon.push_back(0x00);
        }

    file << tempWeapon; // write the prepared weapon string to the file

    if (!file.good())
        {
            std::cerr << "Error processing" << file << '\n';
        }
}
