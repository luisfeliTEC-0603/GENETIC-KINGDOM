#include "gameTextures.hpp"

Texture2D GameTextures::ground;

void InitTextures(){

    GameTextures::ground = LoadTexture("Assets/ground.png");
    GameTextures::whizardTowerBase = LoadTexture("Assets/WhizardTower/CyanWell.png");
    GameTextures::whizardForTower = LoadTexture("Assets/AllAssetsPreview.png");
}
void UnloadAllTextures(){

    UnloadTexture(GameTextures::ground);
}