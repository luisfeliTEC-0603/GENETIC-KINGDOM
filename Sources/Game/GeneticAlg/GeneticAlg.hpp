#ifndef GENETICALG_HPP
#define GENETICALG_HPP

class GeneticManager {
private:
    // General data
    int mutation = 0;
    int probMut = 65;

    // Saves incoming stats from enemies
    int newStats[4][3] = {
        {0, 30, 10},
        {1, 20, 15},
        {2, 40, 15},
        {3, 15, 25}
    };

    // Initial condition of each enemy type
    int orc[2] = {30, 10}; // Type0, health, speed
    int darkmage[2] = {20, 15}; // Type1, health, speed
    int undead[2]= {40, 15}; // Type2, health, speed
    int assasin[2] = {15, 25}; // Type3, health, speed

public:
    GeneticManager();
    void changeGenetic();
    void changeNewStat(int type, int healt, int speed); // used every time enemy is added
    void printNewStats() const;


    void IncreaseMutation();
    int getHealthFrom(int type);
    int getSpeedFrom(int type); 
    int getProbMut();
};


#endif


