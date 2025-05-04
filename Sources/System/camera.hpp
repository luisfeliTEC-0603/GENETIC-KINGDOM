/**
 * @file Sources/System/camera.hpp
 * @brief 2D Camera controller for game world navigation
 */

#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "raylib.h"
#include "raymath.h"

#include "../Game/game.hpp"

/**
 * @struct CameraController
 * @brief manages a 2D camera with zooming and map boundary constraints
 * 
 * @param camera raylib Camera2D instance being controlled
 * @param minZoom minimum allowable zoom level (closest)
 * @param maxZoom maximum allowable zoom level (farthest)
 * 
 * @def Initialize : initialize the camera with proper viewport and map constraints
 * @arg screenWidth : the width of the game window in pixels
 * @arg screenHeight : the height of the game window in pixels
 * @arg gameMap : reference to the game map for boundary calculations
 * 
 * @def Update : updates camera position and zoom based on input
 * @arg gameMap : reference to the game map for boundary checks
 * @ref  https://github.com/raysan5/raylib/blob/master/examples/core/core_2d_camera_mouse_zoom.c
 * 
 * @def ClampToMap : constrains camera view to stay within map boundaries
 * @arg gameMap : reference to the game map for boundary calculations
 * 
 * @def GetCameraZoom : gets the current camera zoom level
 * @return current zoom value
 */

struct CameraController {
    Camera2D camera;
    float minZoom;
    float maxZoom;
    
    void Initialize(int screenWidth, int screenHeight, const Map& gameMap);
    void Update(const Map& gameMap);
    void ClampToMap(const Map& gameMap);
    float GetCameraZoom();
};

/**
 * @def GetMouseCell : converts mouse screen position to game world grid coordinates
 * @param camera The camera currently viewing the game world
 * @param map The game map for coordinate reference
 * @return Vector2 containing grid cell coordinates under mouse cursor
 */

Vector2 GetMouseCell(const Camera2D& camera, const Map& map);

#endif