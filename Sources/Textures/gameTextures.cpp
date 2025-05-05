#include "gameTextures.hpp"

Texture2D GameTextures::ground;
Texture2D GameTextures::keep;
Texture2D GameTextures::tree;
Texture2D GameTextures::cabin;
Texture2D GameTextures::grass;
Texture2D GameTextures::boat;
Texture2D GameTextures::shore;

Texture2D GameTextures::wizardTowerBase;
Texture2D GameTextures::wizardForTower;
Texture2D GameTextures::archerForTower;
Texture2D GameTextures::archerTowerBase;
Texture2D GameTextures::artilleryTowerBase;
Texture2D GameTextures::kinTower;

Texture2D GameTextures::orc;
Texture2D GameTextures::darkMage;
Texture2D GameTextures::undead;
Texture2D GameTextures::assassin;

void InitTextures(){

    GameTextures::ground = LoadTexture("Assets/Scene/Nature/Ground.png");
    GameTextures::keep = LoadTexture("Assets/Scene/Buildings/Keep.png");
    GameTextures::tree = LoadTexture("Assets/Scene/Nature/Trees.png");
    GameTextures::cabin = LoadTexture("Assets/Scene/Buildings/Cabin.png");
    GameTextures::grass = LoadTexture("Assets/Scene/Nature/Grass.png");
    GameTextures::boat = LoadTexture("Assets/Items/Boat.png");
    GameTextures::shore = LoadTexture("Assets/Scene/Nature/Shore.png");

    GameTextures::wizardTowerBase = LoadTexture("Assets/Towers/WizardTower/CyanWell.png");
    GameTextures::wizardForTower = LoadTexture("Assets/AllAssetsPreview.png");
    GameTextures::archerForTower = LoadTexture("Assets/AllAssetsPreview.png"); 
    GameTextures::archerTowerBase = LoadTexture("Assets/Towers/ArcherTower/CyanHuts.png");
    GameTextures::artilleryTowerBase = LoadTexture("Assets/AllAssetsPreview.png");
    GameTextures::kinTower = LoadTexture("Assets/Towers/KinTower/KinTower.png");

    GameTextures::orc = LoadTexture("Assets/Enemies/Orc.png");
    GameTextures::darkMage = LoadTexture("Assets/Enemies/DarkMage.png");
    GameTextures::undead = LoadTexture("Assets/Enemies/Undead.png");
    GameTextures::assassin = LoadTexture("Assets/Enemies/Assassin.png");
}
void UnloadAllTextures(){

    UnloadTexture(GameTextures::ground);
    UnloadTexture(GameTextures::keep);
    UnloadTexture(GameTextures::tree);
    UnloadTexture(GameTextures::cabin);
    UnloadTexture(GameTextures::grass);
    UnloadTexture(GameTextures::boat);
    UnloadTexture(GameTextures::shore);

    UnloadTexture(GameTextures::wizardTowerBase);
    UnloadTexture(GameTextures::wizardForTower);
    UnloadTexture(GameTextures::archerForTower);
    UnloadTexture(GameTextures::archerTowerBase);
    UnloadTexture(GameTextures::artilleryTowerBase);
    UnloadTexture(GameTextures::kinTower);

    UnloadTexture(GameTextures::orc);
    UnloadTexture(GameTextures::darkMage);
    UnloadTexture(GameTextures::undead);
    UnloadTexture(GameTextures::assassin);
}