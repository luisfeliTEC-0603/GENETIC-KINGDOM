#include "GeneticAlg.hpp"
#include <iostream>

GeneticManager::GeneticManager() {};

void GeneticManager::changeGenetic() {
    for (int i = 0; i < 4; ++i) {
        int type = newStats[i][0];
        int health = newStats[i][1];
        int speed  = newStats[i][2];

        switch (type) {
            case 0:
                orc[0] = health;
                orc[1] = speed;
                break;
            case 1:
                darkmage[0] = health;
                darkmage[1] = speed;
                break;
            case 2:
                undead[0] = health;
                undead[1] = speed;
                break;
            case 3:
                assasin[0] = health;
                assasin[1] = speed;
                break;
        }
    }
}
void GeneticManager::IncreaseMutation() {
    mutation++;
}

void GeneticManager::changeNewStat(int type, int health, int speed) {
    for (int i = 0; i < 4; ++i) {
        if (newStats[i][0] == type) {
            if (health > newStats[i][1]) {
                newStats[i][1] = health;
            }
            if (speed > newStats[i][2]) {
                newStats[i][2] = speed;
            }
            break; 
        }
    }
}

int GeneticManager::getHealthFrom(int type) {
    for (int i = 0; i < 4; ++i) {
        if (newStats[i][0] == type) {
            return newStats[i][1]; // health position
        }
    }
    return -1; // if not found
}

int GeneticManager::getSpeedFrom(int type) {
    for (int i = 0; i < 4; ++i) {
        if (newStats[i][0] == type) {
            return newStats[i][2]; // speed position
        }
    }
    return -1; // if not found
}

int GeneticManager::getProbMut() {
    return probMut;
}

void GeneticManager::printNewStats() const {
    std::cout << "=== New Enemy Stats ===" << std::endl;
    for (int i = 0; i < 4; ++i) {
        std::cout << "Type " << newStats[i][0]
                  << " | Health: " << newStats[i][1]
                  << " | Speed: " << newStats[i][2]
                  << std::endl;
    }
    std::cout << "=======================" << std::endl;
}

