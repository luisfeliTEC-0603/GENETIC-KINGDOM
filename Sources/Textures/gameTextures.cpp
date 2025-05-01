#include "gameTextures.hpp"

Texture2D GameTextures::ground;
Texture2D GameTextures::keep;
Texture2D GameTextures::wizardTowerBase;
Texture2D GameTextures::wizardForTower;
Texture2D GameTextures::archerForTower;
Texture2D GameTextures::archerTowerBase;
Texture2D GameTextures::artilleryTowerBase;
Texture2D GameTextures::tree;

void InitTextures(){

    GameTextures::ground = LoadTexture("Assets/Scene/Nature/Ground.png");
    GameTextures::keep = LoadTexture("Assets/Scene/Buildings/Keep.png");
    GameTextures::wizardTowerBase = LoadTexture("Assets/Towers/WizardTower/CyanWell.png");
    GameTextures::wizardForTower = LoadTexture("Assets/AllAssetsPreview.png");
    GameTextures::archerForTower = LoadTexture("Assets/AllAssetsPreview.png"); 
    GameTextures::archerTowerBase = LoadTexture("Assets/Towers/ArcherTower/CyanHuts.png");
    GameTextures::artilleryTowerBase = LoadTexture("Assets/AllAssetsPreview.png");
    GameTextures::tree = LoadTexture("Assets/Scene/Nature/Trees.png");
}
void UnloadAllTextures(){

    UnloadTexture(GameTextures::wizardTowerBase);
    UnloadTexture(GameTextures::wizardForTower);
    UnloadTexture(GameTextures::archerForTower);
    UnloadTexture(GameTextures::archerTowerBase);
    UnloadTexture(GameTextures::artilleryTowerBase);
    UnloadTexture(GameTextures::ground);
    UnloadTexture(GameTextures::keep);
    UnloadTexture(GameTextures::tree);
}