#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "raylib.h"
#include "raymath.h"

#include "../Game/game.hpp"

// RayLib camera Related Functionalities
struct CameraController {
    Camera2D camera;
    float minZoom;
    float maxZoom;
    
    void Initialize(int screenWidth, int screenHeight, const Map& gameMap);
    void Update(const Map& gameMap);
    void ClampToMap(const Map& gameMap);
    float GetCameraZoom();
};

Vector2 GetMouseCell(const Camera2D& camera, const Map& map);

#endif