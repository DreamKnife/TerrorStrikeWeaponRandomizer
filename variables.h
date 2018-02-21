#ifndef VARIABLES_H
#define VARIABLES_H

#include <array>

const std::string ak47{"SASWeapons.AK47_Wpn"};
const std::string ak74{"SASWeapons.AK_74_Wpn"};
const std::string g3sg1{"SASWeapons.G3SG1_Wpn"};
const std::string mp5klss{"SASWeapons.HK_MP5K_LS_S_Wpn"};
const std::string mp5k{"SASWeapons.HK_MP5K_Wpn"};
const std::string mp5sdlss{"SASWeapons.HK_MP5SD_LS_S_Wpn"};
const std::string mp5lss{"SASWeapons.HK_MP5_LS_S_Wpn"};
const std::string mp5sd{"SASWeapons.HK_MP5_SD_Wpn"};
const std::string mp5{"SASWeapons.HK_MP5_Wpn"};
const std::string m1100t{"SASWeapons.M1100T_Wpn"};
const std::string m4a1{"SASWeapons.M4A1_Wpn"};
const std::string m60{"SASWeapons.M60_Wpn"};
const std::string mac11{"SASWeapons.MAC11_Wpn"};
const std::string sigswat{"SASWeapons.SIGSWAT_Wpn"};
const std::string socom{"SASWeapons.SOCOM_Wpn"};
const std::string p226{"SASWeapons.Sigp226_Wpn"};
const std::string aug{"SASWeapons.Steyr_AUG_Wpn"};
const std::string uzi{"SASWeapons.Uzi_Wpn"};

struct weaponSlot
{
    long filePosition;
    short length;
};

// SASGame.u
const weaponSlot defaultMP5 {0x030E95, 21};
const weaponSlot defaultAK47 {0x03126E, 19};

// SASChars.u
const short defaultP226Address {0x731F};

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

#endif // VARIABLES_H
