#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "raylib.h"
#include "raymath.h"

#include "../Game/game.hpp"

struct CameraController {
    Camera2D camera;
    float minZoom;
    float maxZoom;
    
    void Initialize(int screenWidth, int screenHeight, const Map& gameMap);
    void Update(const Map& gameMap);
    void ClampToMap(const Map& gameMap);
    float GetCameraZoom();
};

#endif