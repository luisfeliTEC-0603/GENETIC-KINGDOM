#include "gameTextures.hpp"

Texture2D GameTextures::ground;
Texture2D GameTextures::whizardTowerBase;
Texture2D GameTextures::whizardForTower;
Texture2D GameTextures::archerForTower;
Texture2D GameTextures::archerTowerBase;
Texture2D GameTextures::artilleryTowerBase;


void InitTextures(){

    GameTextures::ground = LoadTexture("Assets/ground.png");
    GameTextures::whizardTowerBase = LoadTexture("Assets/WhizardTower/CyanWell.png");
    GameTextures::whizardForTower = LoadTexture("Assets/AllAssetsPreview.png");
    GameTextures::archerForTower = LoadTexture("Assets/AllAssetsPreview.png"); 
    GameTextures::archerTowerBase = LoadTexture("Assets/ArcherTower/CyanHuts.png");
    GameTextures::artilleryTowerBase = LoadTexture("Assets/AllAssetsPreview.png");
}
void UnloadAllTextures(){

    UnloadTexture(GameTextures::whizardTowerBase);
    UnloadTexture(GameTextures::whizardForTower);
    UnloadTexture(GameTextures::ground);
}