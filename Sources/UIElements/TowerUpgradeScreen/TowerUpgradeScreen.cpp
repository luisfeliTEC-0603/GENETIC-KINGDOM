#include "raylib.h"
#include <stdio.h>

bool UpgradeTower(int upgrade) {
    int cost = 0;
    if (upgrade == 0) cost = 50;
    else if (upgrade == 1) cost = 100;
    else if (upgrade == 2) cost = 150;
    else if (upgrade >= 3) return false; // Tower is maxed 

    char message[128];
    sprintf(message, "Deseas mejorar la torre al nivel %d?\nEl costo es de %d", upgrade + 1, cost);

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BLACK);

        // Cuadro de menú
        Rectangle menuRect = { 400, 250, 400, 180 };
        DrawRectangleRec(menuRect, DARKGRAY);

        // Texto del mensaje
        DrawText(message, menuRect.x + 20, menuRect.y + 20, 20, RAYWHITE);

        // Botones
        Rectangle buttonAccept = { menuRect.x + 40, menuRect.y + 110, 110, 30 };
        Rectangle buttonCancel = { menuRect.x + 180, menuRect.y + 110, 110, 30 };

        DrawRectangleRec(buttonAccept, LIGHTGRAY);
        DrawText("Aceptar", buttonAccept.x + 10, buttonAccept.y + 5, 20, BLACK);

        DrawRectangleRec(buttonCancel, LIGHTGRAY);
        DrawText("Cancelar", buttonCancel.x + 10, buttonCancel.y + 5, 20, BLACK);

        EndDrawing();

        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            Vector2 mouse = GetMousePosition();
            if (CheckCollisionPointRec(mouse, buttonAccept)) return true;
            if (CheckCollisionPointRec(mouse, buttonCancel)) return false;
        }
    }

    return false; // Si se cierra la ventana
}
