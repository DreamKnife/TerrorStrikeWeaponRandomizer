#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib> // for exit()

// https://www.mathsisfun.com/binary-decimal-hexadecimal-converter.html to convert hex address to decimal

int main()
{
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

    sasGame.seekg(200341, std::ios::beg); //SASWeapons.HK_MP5K_Wpn

    int chCount{0};
    //char currentChar;
    std::string m4a1{"SASWeapons.M4A1_Wpn"};
    m4a1.push_back(0x00);
    m4a1.push_back(0x00);
    sasGame << m4a1;
    while (chCount < 21) //21 is length of SASWeapons.HK_MP5_Wpn
    {

        //sasGame.seekg(sasGame.tellg(), std::ios::beg);
        //sasGame << '!';

        /* for reading the weapon slot
        char strInput;
        sasGame >> strInput;
        std::cout << strInput;
        */

        chCount++;
        if (!sasGame.good())
        {
            std::cerr << "Error processing sasGame." << '\n';
        }
        //sasGame.seekg(1, std::ios::cur);
    }

    return 0;
}
