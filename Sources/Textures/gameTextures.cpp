#include "gameTextures.hpp"

Texture2D GameTextures::ground;
Texture2D GameTextures::whizardTowerBase;
Texture2D GameTextures::whizardForTower;


void InitTextures(){

    GameTextures::ground = LoadTexture("Assets/ground.png");
    GameTextures::whizardTowerBase = LoadTexture("Assets/WhizardTower/CyanWell.png");
    GameTextures::whizardForTower = LoadTexture("Assets/AllAssetsPreview.png");
}
void UnloadAllTextures(){

    UnloadTexture(GameTextures::whizardTowerBase);
    UnloadTexture(GameTextures::whizardForTower);
    UnloadTexture(GameTextures::ground);
}