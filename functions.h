#ifndef FUNCTIONS_H
#define FUNCTIONS_H

int getRandomNumber(int min, int max);

std::string getRandomWeapon();

void assignGun(std::fstream &file, long slotAddress, short slotLength);

#endif // FUNCTIONS_H
