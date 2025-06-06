#include "tools.hpp"

// Initialize static members
std::random_device RandomUtils::rd;
std::mt19937 RandomUtils::gen(rd());

void RandomUtils::init() {
    gen.seed(rd()); 
    gen.discard(1000);
}
int RandomUtils::randomInt(int min, int max) {
    std::uniform_int_distribution<> distrib(min, max);
    return distrib(gen);
}

float RandomUtils::randomFloat(float min, float max) {
    std::uniform_real_distribution<float> distrib(min, max);
    return distrib(gen);
}

bool RandomUtils::checkProbability(float probability) {
    return randomFloat(0.0f, 1.0f) < probability;
}