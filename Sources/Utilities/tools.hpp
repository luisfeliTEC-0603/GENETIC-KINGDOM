/**
 * @file Sources/Utilities/tools.hpp
 * @brief Random number generation utilities for game development
 */

#ifndef TOOLS_H
#define TOOLS_H

#include <stdexcept>
#include <random>

/**
 * @class RandomUtils
 * @param rd true random number generator for seeding
 * @param gen mersenne Twister random engine
 * 
 * @brief static utility class for random number generation
 * 
 * @public init() : initializes the random number engine
 * @public randomInt() : generates a random integer in [min, max]
 * @public randomFloat() : generates a random float in [min, max]
 * @public checkProbability() : checks if an event occurs with given probability
 */

class RandomUtils {
private:
    static std::random_device rd;
    static std::mt19937 gen;
    
public:
    static void init();
    static int randomInt(int min, int max);
    static float randomFloat(float min, float max);
    static bool checkProbability(float probability);
};

#endif