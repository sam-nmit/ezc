#pragma once

#include <cstdio>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <array>
#include <vector>

#include <stdio.h>
#include <tchar.h>

 #include <windows.h>

#ifdef __linux__ 
    //linux code goes here
#elif _WIN32
    #include <windows.h>
#else

#endif

namespace ezc{

bool exec(std::string cmd);
std::vector<std::string> getfiles();

}



