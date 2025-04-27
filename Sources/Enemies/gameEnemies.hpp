/*
Cada enemigo tiene atributos como: 
• Vida 
• Velocidad 
• Resistencia a flechas 
• Resistencia a la magia 
• Resistencia a la artillería
*/

#ifndef ENEMY_HPP
#define ENEMY_HPP

#include "raylib.h"

struct Enemy {
    Vector2 position;
    Vector2 size;
    Color color;
};

#endif