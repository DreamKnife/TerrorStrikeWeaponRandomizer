#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib> // for rand() and srand() and exit()
#include <ctime> // for time()
#include <array>

// https://www.mathsisfun.com/binary-decimal-hexadecimal-converter.html to convert hex address to decimal

// should the hex address be stored as "int"s ?

const std::string g3sg1{"SASWeapons.G3SG1_Wpn"};
const std::string m4a1{"SASWeapons.M4A1_Wpn"};
const std::string m60{"SASWeapons.M60_Wpn"};
const std::string mac11{"SASWeapons.MAC11_Wpn"};

struct weaponSlot
{
    int filePosition;
    int length;
};

// SASGame.u
const weaponSlot defaultMP5 {0x030E95, 21};
const weaponSlot defaultAK47 {0x03126E, 19};

// SASChars.u
// the weapon slots for sas troopers. these are sets of two - the address of the position in the file
// and the length of the entry
const std::array<weaponSlot, 25> sasTroopers {
0xE5D7, 22, 0xE736, 27, 0xE89F, 24, 0xEA1B, 28, 0xED0B, 26, 0xEE72, 26, // trooper a
0xFCDC, 22, 0xFD95, 27, 0xFF04, 24, 0x010083, 28, 0x010373, 26, 0x0104E0, 26, 0x01064A, 26, // trooper b
0x010B95, 22, 0x010CFA, 27, 0x010E69, 24, 0x010FEB, 28, 0x0112DB, 26, 0x011448, 26, // trooper c
0x011C37, 22, 0x011D98, 27, 0x011F03, 24, 0x012084, 28, 0x012378, 26, 0x0124E1, 26 // trooper (no a,b, or c, just "trooper")
};

// the weapon slots for terrorists. these are sets of two - the address of the position in the file
// and the length of the entry
const std::array<weaponSlot, 43> terrorists {
0x01415C, 19, 0x014455, 19, 0x01474E, 22, 0x014A4A, 20, 0x014D44, 18, // scripted embassy (5)
0x015240, 25, 0x0153E0, 18, 0x01556D, 20, 0x0156EB, 18, 0x015A1F, 22, 0x015BAD, 20, 0x015D4E, 20, 0x015EEB, 21, // embassy (8)
0x0162DE, 21, 0x016487, 25, 0x016778, 18, 0x0168FF, 21, 0x016A7B, 20, 0x016BF6, 19, 0x016DBB, 20, 0x016F41, 20, 0x0170CE, 18, // farm (9)
0x0173F5, 25, 0x01754B, 22, 0x0176D4, 20, 0x01783C, 24, 0x0179CC, 19, 0x017B3B, 21, 0x017CC9, 20, 0x017E48, 18, 0x017FE4, 18, // parliment (9)
0x018445, 25, 0x01859A, 24, 0x018706, 20, 0x01887E, 18, 0x0189E3, 21, 0x018B67, 20, 0x018D0F, 18, 0x018EB3, 25, 0x01902B, 24, 0x0191C1, 18, 0x019351, 20, 0x0194E3, 20 // metro (12)
};


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
    switch (getRandomNumber(0, 3))
    {
        case 0:
            return g3sg1;
        case 1:
            return m4a1;
        case 2:
            return m60;
        case 3:
            return mac11;
        default:
            std::cerr << "Error: unhandled case in getRandomWeapon()" << '\n';
    }
}

// takes a gun slot and fills it with a random gun
void assignGun(std::fstream &file, int slotAddress, int slotLength)
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

    // *** THIS LINE FOR DEBUGGING
    //std::cout << tempWeapon;
    // ***

    int lengthDifference{slotLength - tempWeapon.length()}; // calculate length difference

    // add empty spaces to the weapon as many times as needed to match the length
    // of the slot it's going to fill
    for (int i{0}; i < lengthDifference; ++i)
        {
            tempWeapon.push_back(0x00);
        }

    file << tempWeapon; // write the prepared weapon string to the file

    if (!file.good())
        {
            std::cerr << "Error processing" << file << '\n';
        }
}

int main()
{
    srand(static_cast<unsigned int>(time(0))); // set initial seed value to system clock for random numbers
    getRandomNumber(0, 3); // call getRandomNumber() once and throw away because the first call doesn't seem to come out random
    std::fstream sasGame("C:\\Program Files (x86)\\Konami\\The Regiment\\system\\SASGame.u");
    std::fstream sasChars("C:\\Program Files (x86)\\Konami\\The Regiment\\system\\SASChars.u");

    // if file fails to open print error and exit
    if (!sasGame)
    {
        std::cerr << "Error opening SASGame.u" << '\n';
        exit(1);
    }

    // if file fails to open print error and exit
    if (!sasChars)
    {
        std::cerr << "Error opening SASChars.u" << '\n';
        exit(1);
    }

    assignGun(sasGame, defaultMP5.filePosition, defaultMP5.length);
    assignGun(sasGame, defaultAK47.filePosition, defaultAK47.length);


    for (auto &element : sasTroopers)
    {
        assignGun(sasChars, element.filePosition, element.length);
        std::cout << std::hex << std::uppercase << element.filePosition << " , " << std::dec << element.length << '\n';
    }

    for (auto &element : terrorists)
    {
        assignGun(sasChars, element.filePosition, element.length);
        std::cout << std::hex << std::uppercase << element.filePosition << " , " << std::dec << element.length << '\n';
    }


    /* for reading the weapon slot
    sasGame.seekg(200341, std::ios::beg); //SASWeapons.HK_MP5K_Wpn
    //while ()
    char strInput;
    sasGame >> strInput;
    std::cout << strInput;
    */

    return 0;
}
