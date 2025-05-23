#include "raylib.h"
#include <stdio.h>
#include "InformationScreen.hpp"

void ShowInformationScreen(Information& info) {
    int CELL_SIZE = 16;
    int spacing = 3 * CELL_SIZE;

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BLACK);

        // General Game Info
        DrawText(TextFormat("Wave Number: %d", info.waveNum), 50, 30, 20, RAYWHITE);
        DrawText(TextFormat("Mutation Probability: %d%%", info.prob), 50, 60, 20, RAYWHITE);
        DrawText(TextFormat("Mutations: %d", info.mutaciones), 50, 90, 20, RAYWHITE);

        // Title
        DrawText("Towers:", 50, 140, 20, RAYWHITE);

        const char* towerNames[3] = { "Archer", "Wizard", "Artillery" };

        int startX = 4 * CELL_SIZE;
        int startY = 10 * CELL_SIZE;

        for (int i = 0; i < 3; ++i) {
            float xPos = startX + i * (7 * CELL_SIZE + spacing);
            float yPos = startY;

            char typeText[32];
            sprintf(typeText, "%s", towerNames[i]);
            int typeTextWidth = MeasureText(typeText, 16);
            DrawText(typeText, xPos + (CELL_SIZE * 2) - (typeTextWidth / 2), yPos, 16, RAYWHITE);

            yPos += CELL_SIZE + 5;

            for (int level = 1; level <= 3; ++level) {
                char levelText[32];
                sprintf(levelText, "Level %d", level);
                int levelTextWidth = MeasureText(levelText, 16);
                DrawText(levelText, xPos + (CELL_SIZE * 2) - (levelTextWidth / 2), yPos, 16, RAYWHITE);

                char amountText[32];
                sprintf(amountText, "%d", info.towers[i][level]);
                int amountTextWidth = MeasureText(amountText, 16);
                DrawText(amountText, xPos + (CELL_SIZE * 2) - (amountTextWidth / 2), yPos + CELL_SIZE + 5, 16, RAYWHITE);

                yPos += CELL_SIZE + 18;
            }
        }

        int tableX = 400;  // <- ANTES estaba más lejos, lo movemos a la izquierda

        DrawText("Wave:", tableX, 30, 20, RAYWHITE);
        DrawText("Deads:", tableX, 60, 20, RAYWHITE);
        
        if (info.waveNum > 1) {
            int offset = 100; // espacio desde texto hasta primer número
        
            for (int i = 1; i < info.waveNum; ++i) {
                int xPos = tableX + offset + (i - 1) * 50;  // espacio entre números
        
                DrawText(TextFormat("%d", i), xPos, 30, 20, RAYWHITE);        // número de oleada
                DrawText(TextFormat("%d", 5 + i), xPos, 60, 20, RAYWHITE);    // muertes
            }
        }

        // Fits info - debajo de torres
        int fitsStartY = startY + 3 * (2 * CELL_SIZE) + 50; // debajo de las torres
        int fitsStartX = 50;

        // Labels de tipos
        DrawText("Type", fitsStartX, fitsStartY, 20, RAYWHITE);

        const char* typeNames[4] = { "Orcs", "DarkMage", "Undead", "Assasin" };

        for (int i = 0; i < 4; ++i) {
            int xPos = fitsStartX + 110 + i * 110;
            DrawText(typeNames[i], xPos, fitsStartY, 20, RAYWHITE);
        }

        // Fits label
        DrawText("Fit", fitsStartX, fitsStartY + 40, 20, RAYWHITE);

        // Valores de fits
        for (int i = 0; i < 4; ++i) {
            int xPos = fitsStartX + 110 + i * 110;
            DrawText(TextFormat("%d", info.fits[i]), xPos, fitsStartY + 40, 20, RAYWHITE);
        }

        if (IsKeyPressed(KEY_N)) {
            break;
        }

        EndDrawing();
    }
}
