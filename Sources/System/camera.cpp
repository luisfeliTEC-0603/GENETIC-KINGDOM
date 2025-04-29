#include "camera.hpp"

void CameraController::Initialize(int screenWidth, int screenHeight, const Map& gameMap) {
    camera = { 0 };
    camera.target = { // Center the camera in target
        (gameMap.width * CELL_SIZE) / 2.0f,
        (gameMap.height * CELL_SIZE) / 2.0f
    };
    camera.offset = { screenWidth/2.0f, screenHeight/2.0f };
    camera.zoom = 2.5f; // Initial zoom

    // Limits based on Map : Empiric
    minZoom = 0.5f;
    maxZoom = 4.0f;
}

void CameraController::Update(const Map& gameMap) {

    // Based in RayLib Example:
    // https://github.com/raysan5/raylib/blob/master/examples/core/core_2d_camera_mouse_zoom.c

    // Mouse Drag
    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
        Vector2 delta = GetMouseDelta();
        delta = Vector2Scale(delta, -1.0f/camera.zoom);
        camera.target = Vector2Add(camera.target, delta);
    }

    // Zoom with MouseWheel
    float wheel = GetMouseWheelMove();
    if (wheel != 0) {
        Vector2 mouseWorldPos = GetScreenToWorld2D(GetMousePosition(), camera);
        camera.zoom += wheel * 0.1f;
        camera.zoom = Clamp(camera.zoom, minZoom, maxZoom);
        Vector2 mouseWorldPosAfter = GetScreenToWorld2D(GetMousePosition(), camera);
        camera.target = Vector2Add(camera.target, Vector2Subtract(mouseWorldPos, mouseWorldPosAfter));
    }

    ClampToMap(gameMap);
}

void CameraController::ClampToMap(const Map& gameMap) { // Limits Stableshment for Drag Movement

    // Full Map Dimensions
    float mapWidth = gameMap.width * CELL_SIZE;
    float mapHeight = gameMap.height * CELL_SIZE;
    
    Vector2 visibleArea = {
        (float)GetScreenWidth() / camera.zoom,
        (float)GetScreenHeight() / camera.zoom
    };
    
    // Identify the limits
    float minX = visibleArea.x / 2.0f;
    float maxX = mapWidth - visibleArea.x / 2.0f;
    float minY = visibleArea.y / 2.0f;
    float maxY = mapHeight - visibleArea.y / 2.0f;
    
    // Clamp Camera into Map
    camera.target.x = Clamp(camera.target.x, minX, maxX);
    camera.target.y = Clamp(camera.target.y, minY, maxY);
}

Vector2 GetMouseCell(const Camera2D& camera, const Map& map) {
    
    // Get mouse position in world coordinates
    Vector2 mouseWorldPos = GetScreenToWorld2D(GetMousePosition(), camera);
    
    // Convert to grid coordinates
    Vector2 cellPos = {
        floorf(mouseWorldPos.x / CELL_SIZE),
        floorf(mouseWorldPos.y / CELL_SIZE)
    };
    
    // Clamp to map bounds
    cellPos.x = Clamp(cellPos.x, 0, map.width - 1);
    cellPos.y = Clamp(cellPos.y, 0, map.height - 1);
    
    return cellPos;
}

float CameraController::GetCameraZoom() { return camera.zoom; } // Gets Zoom in Camera