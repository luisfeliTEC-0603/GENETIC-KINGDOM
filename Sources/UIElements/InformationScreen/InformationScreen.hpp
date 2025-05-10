#ifndef INFORMATIONSCREEN_HPP
#define INFORMATIONSCREEN_HPP

#include <vector>
#include <array>   
#include "raylib.h"

struct Information {
    int waveNum = 1; // Same as generations, also we now enemies killed per round is 5 + round, 

    // Genetic Alg info
    int mutaciones;
    int prob = 65;

    // Fits of enemies
    std::vector<int> fits = {0,0,0,0};

    // Towers info
    std::array<std::array<int, 4>, 3> towers;


};

void ShowInformationScreen(Information& info);

#endif
