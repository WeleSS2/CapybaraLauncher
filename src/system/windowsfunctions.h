#ifndef WINDOWSFUNCTIONS_H
#define WINDOWSFUNCTIONS_H

#include <iostream>
#include <string>
#include <stdexcept>
#include <Windows.h>
#include <fstream>
#include <filesystem>
#include <algorithm>

class WindowsFunctions {
    std::string steamPath;
    std::string gamePath;
public:
    bool getSteamPathFromRegistry();
    bool getGamePathFromSteam();
};

#endif // WINDOWSFUNCTIONS_H
