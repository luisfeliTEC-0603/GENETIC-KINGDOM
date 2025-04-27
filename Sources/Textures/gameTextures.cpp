#include "gameTextures.hpp"

Texture2D GameTextures::ground;

void InitTextures(){

    GameTextures::ground = LoadTexture("Assets/ground.png");
}

void UnloadAllTextures(){

    UnloadTexture(GameTextures::ground);
}