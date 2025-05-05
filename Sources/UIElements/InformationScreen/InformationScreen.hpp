#ifndef INFORMATIONSCREEN_HPP
#define INFORMATIONSCREEN_HPP

#include <vector>
#include <array>   
#include "raylib.h"

struct Information {
    int generations;
    std::vector<std::array<int, 2>> diedInWaves; // list of arrays that contains 2 ints. First int is wave number and second int is enemies that diesd
    std::array<std::array<int, 4>, 3> towers;


};

void ShowInformationScreen(Information& info);

#endif
