#include "camera.hpp"

void CameraController::Initialize(int screenWidth, int screenHeight, const Map& gameMap) {
    camera = { 0 };
    camera.target = {
        (gameMap.width * CELL_SIZE) / 2.0f,
        (gameMap.height * CELL_SIZE) / 2.0f
    };
    camera.offset = { screenWidth/2.0f, screenHeight/2.0f };
    camera.zoom = 2.5f;
    minZoom = 0.5f;
    maxZoom = 4.0f;
}

void CameraController::Update(const Map& gameMap) {
    // Pan with mouse drag
    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
        Vector2 delta = GetMouseDelta();
        delta = Vector2Scale(delta, -1.0f/camera.zoom);
        camera.target = Vector2Add(camera.target, delta);
    }

    // Zoom with mouse wheel
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

void CameraController::ClampToMap(const Map& gameMap) {
    float mapWidth = gameMap.width * CELL_SIZE;
    float mapHeight = gameMap.height * CELL_SIZE;
    
    Vector2 visibleArea = {
        (float)GetScreenWidth() / camera.zoom,
        (float)GetScreenHeight() / camera.zoom
    };
    
    float minX = visibleArea.x / 2.0f;
    float maxX = mapWidth - visibleArea.x / 2.0f;
    float minY = visibleArea.y / 2.0f;
    float maxY = mapHeight - visibleArea.y / 2.0f;
    
    camera.target.x = Clamp(camera.target.x, minX, maxX);
    camera.target.y = Clamp(camera.target.y, minY, maxY);
}

float CameraController::GetCameraZoom() { return camera.zoom; }