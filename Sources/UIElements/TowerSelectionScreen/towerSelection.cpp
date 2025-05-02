#include "towerSelection.hpp"

int ShowScreen() {
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BLACK);

        Rectangle menuRect = { 400, 250, 220, 190 };
        DrawRectangleRec(menuRect, DARKGRAY);

        Rectangle button1 = { menuRect.x + 20, menuRect.y + 20, 180, 30 };
        Rectangle button2 = { menuRect.x + 20, menuRect.y + 60, 180, 30 };
        Rectangle button3 = { menuRect.x + 20, menuRect.y + 100, 180, 30 };
        Rectangle button4 = { menuRect.x + 20, menuRect.y + 140, 180, 30 };

        DrawRectangleRec(button1, LIGHTGRAY);
        DrawText("Archer Tower", button1.x + 10, button1.y + 5, 20, BLACK);

        DrawRectangleRec(button2, LIGHTGRAY);
        DrawText("Wizard Tower", button2.x + 10, button2.y + 5, 20, BLACK);

        DrawRectangleRec(button3, LIGHTGRAY);
        DrawText("Artillery Tower", button3.x + 10, button3.y + 5, 20, BLACK);

        DrawRectangleRec(button4, LIGHTGRAY);
        DrawText("Cancel", button4.x + 10, button4.y + 5, 20, BLACK);

        EndDrawing();

        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            Vector2 mouse = GetMousePosition();
            if (CheckCollisionPointRec(mouse, button1)) return 1;
            if (CheckCollisionPointRec(mouse, button2)) return 2;
            if (CheckCollisionPointRec(mouse, button3)) return 3;
            if (CheckCollisionPointRec(mouse, button4)) return 4;
        }
    }

    return 0;
}

