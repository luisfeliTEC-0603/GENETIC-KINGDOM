#ifndef TOOLS_H
#define TOOLS_H

#include <random>

class RandomUtils {
private:
    static std::random_device rd;
    static std::mt19937 gen;
    
public:
    // Initialize the random engine
    static void init();
    
    // Get random integer between min and max (inclusive)
    static int randomInt(int min, int max);
    
    // Get random float between min and max (inclusive)
    static float randomFloat(float min, float max);
    
    // Check if an event occurs with given probability (0.0 to 1.0)
    static bool checkProbability(float probability);
};

#endif