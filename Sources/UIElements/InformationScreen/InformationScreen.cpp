#include "raylib.h"
#include <stdio.h>
#include "InformationScreen.hpp"

void ShowInformationScreen(Information& info) {
    int CELL_SIZE = 16;
    int spacing = 3 * CELL_SIZE; 

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BLACK);

        // Title 
        DrawText("Towers:", 50, 50, 20, RAYWHITE);

        int startX = 4 * CELL_SIZE; // Start at x
        int startY = 5 * CELL_SIZE; // Start at y

        // Names of towers depending on number
        const char* towerNames[3] = { "Archer", "Wizard", "Artillery" };

        // Display towers
        for (int i = 0; i < 3; ++i) {  // 3 because there are 3 types of towers
            float xPos = startX; // constant while deploying towrs since it is vertical.
            float yPos = startY + i * (7 * CELL_SIZE + spacing); // Adjust y tower posicion

            // Show type (Archer, Wizard, Artillery)
            char typeText[32];
            sprintf(typeText, "%s", towerNames[i]);
            int typeTextWidth = MeasureText(typeText, 16);
            DrawText(typeText, xPos + (CELL_SIZE / 2) - (typeTextWidth / 2), yPos, 16, RAYWHITE);

            // Shpow levels (Level 1, Level 2, Level 3)
            yPos += CELL_SIZE + 5; // Move down for levels (below type)

            for (int level = 1; level <= 3; ++level) {
                char levelText[32];
                sprintf(levelText, "Level %d", level);
                int levelTextWidth = MeasureText(levelText, 16);

                // Draw level in corresponding position
                DrawText(levelText, xPos + (CELL_SIZE / 2) - (levelTextWidth / 2), yPos, 16, RAYWHITE);

                // Show the quantities of each level
                char amountText[32];
                sprintf(amountText, "%d", info.towers[i][level]);
                int amountTextWidth = MeasureText(amountText, 16);

                // Draw the amounts under each level
                DrawText(amountText, xPos + (CELL_SIZE / 2) - (amountTextWidth / 2), yPos + CELL_SIZE + 5, 16, RAYWHITE);

                // Move the position to the next level
                yPos += CELL_SIZE + 18; // Adjust the spacing between levels
            }
        }

        if (IsKeyPressed(KEY_N)) {
            break; // Close with N
        }

        EndDrawing();
    }
}
