#pragma once
#include "raylib.h"
#include <cmath>
#include <cstdlib> 

extern const int screenWidth;
extern const int screenHeight;
extern const int boardSize;
extern const int cellSize;

extern const Color playersColors[4];

Color LightenColor(Color color, float amount) {
    return {
        (unsigned char)(color.r + (255 - color.r) * amount),
        (unsigned char)(color.g + (255 - color.g) * amount),
        (unsigned char)(color.b + (255 - color.b) * amount),
        color.a
    };
}

void DrawStar(int centerX, int centerY, int radius, int points, Color color) {
    Vector2* vertices = new Vector2[points * 2];
    float angleStep = PI / points;

    for (int i = 0; i < points * 2; i++) {
        float angle = i * angleStep;
        float r = (i % 2 == 0) ? radius : radius / 2;
        vertices[i] = { centerX + r * cosf(angle), centerY + r * sinf(angle) };
    }

    for (int i = 0; i < points * 2; i++) {
        DrawLineV(vertices[i], vertices[(i + 1) % (points * 2)], color);
    }

    delete[] vertices;

}void DrawLudoBoard(Color fadeColor = BLANK) {
    // Draw base square

    Color redHomeColor = (fadeColor.r == playersColors[0].r && fadeColor.g == playersColors[0].g && fadeColor.b == playersColors[0].b)
        ? LightenColor(playersColors[0], 0.2f) : playersColors[0];
    Color greenHomeColor = (fadeColor.r == playersColors[1].r && fadeColor.g == playersColors[1].g && fadeColor.b == playersColors[1].b)
        ? LightenColor(playersColors[1], 0.4f) : playersColors[1];
    Color yellowHomeColor = (fadeColor.r == playersColors[2].r && fadeColor.g == playersColors[2].g && fadeColor.b == playersColors[2].b)
        ? LightenColor(playersColors[2], 0.4f) : playersColors[2];
    Color blueHomeColor = (fadeColor.r == playersColors[3].r && fadeColor.g == playersColors[3].g && fadeColor.b == playersColors[3].b)
        ? LightenColor(playersColors[3], 0.4f) : playersColors[3];


    DrawRectangle((screenWidth - boardSize) / 2, (screenHeight - boardSize) / 2, boardSize, boardSize, WHITE);
    // Draw safe zone
    DrawRectangle((screenWidth - boardSize + 2 * cellSize) / 2, (screenHeight - cellSize) / 2, 5 * cellSize, cellSize, playersColors[0]);
    DrawRectangle((screenHeight - cellSize) / 2, (screenWidth + 3 * cellSize) / 2, cellSize, 5 * cellSize, playersColors[3]);
    DrawRectangle((screenWidth + 3 * cellSize) / 2, (screenHeight - cellSize) / 2, 5 * cellSize, cellSize, playersColors[2]);
    DrawRectangle((screenHeight - cellSize) / 2, (screenHeight - boardSize + 2 * cellSize) / 2, cellSize, 5 * cellSize, playersColors[1]);

    //Draw stars in red home 
    DrawStar((screenWidth - boardSize + 3 * cellSize) / 2, (screenHeight - 2 * cellSize) / 2, 17.5, 5, playersColors[0]);
    DrawStar((screenWidth - boardSize + 5 * cellSize) / 2, (screenHeight + 2 * cellSize) / 2, 17.5, 5, BLACK);

    //Draw stars in green home
    DrawStar((screenWidth + 2 * cellSize) / 2, (screenHeight - boardSize + 3 * cellSize) / 2, 17.5, 5, playersColors[1]);
    DrawStar((screenWidth - 2 * cellSize) / 2, (screenHeight - boardSize + 5 * cellSize) / 2, 17.5, 5, BLACK);

    // draw stars in yellow home
    DrawStar((screenWidth + boardSize - 5 * cellSize) / 2, (screenHeight - 2 * cellSize) / 2, 17.5, 5, BLACK);
    DrawStar((screenWidth + boardSize - 3 * cellSize) / 2, (screenHeight + 2 * cellSize) / 2, 17.5, 5, playersColors[2]);

    // draw stars in blue home 
   
    DrawStar((screenWidth + 2 * cellSize) / 2, (screenHeight + boardSize - 5 * cellSize) / 2, 17.5, 5, BLACK);
    DrawStar((screenWidth - 2 * cellSize) / 2, (screenHeight + boardSize - 3 * cellSize) / 2, 17.5, 5, playersColors[3]);

    // Draw grid lines
    for (int i = 0; i <= 15; i++) {
        DrawLine((screenWidth - boardSize) / 2 + i * cellSize, (screenHeight - boardSize) / 2, (screenWidth - boardSize) / 2 + i * cellSize, (screenHeight + boardSize) / 2, BLACK);
        DrawLine((screenWidth - boardSize) / 2, (screenHeight - boardSize) / 2 + i * cellSize, (screenWidth + boardSize) / 2, (screenHeight - boardSize) / 2 + i * cellSize, BLACK);
    }

    // Draw home areas
    DrawRectangle((screenWidth - boardSize) / 2, (screenHeight - boardSize) / 2, cellSize * 6, cellSize * 6, redHomeColor); // Red Home
    DrawRectangle((screenWidth + boardSize) / 2 - cellSize * 6, (screenHeight - boardSize) / 2, cellSize * 6, cellSize * 6, greenHomeColor); // Green Home
    DrawRectangle((screenWidth - boardSize) / 2, (screenHeight + boardSize) / 2 - cellSize * 6, cellSize * 6, cellSize * 6, blueHomeColor); // Blue Home
    DrawRectangle((screenWidth + boardSize) / 2 - cellSize * 6, (screenHeight + boardSize) / 2 - cellSize * 6, cellSize * 6, cellSize * 6, yellowHomeColor); // Yellow Home

    // Inside home areas
    DrawRectangle((screenWidth - boardSize + 2 * cellSize) / 2, (screenHeight - boardSize + 2 * cellSize) / 2, cellSize * 4, cellSize * 4, RAYWHITE);
    DrawRectangle((screenWidth + 5 * cellSize) / 2, (screenHeight - boardSize + 2 * cellSize) / 2, cellSize * 4, cellSize * 4, RAYWHITE);
    DrawRectangle((screenWidth - boardSize + 2 * cellSize) / 2, (screenHeight + 5 * cellSize) / 2, cellSize * 4, cellSize * 4, RAYWHITE);
    DrawRectangle((screenWidth + 5 * cellSize) / 2, (screenHeight + 5 * cellSize) / 2, cellSize * 4, cellSize * 4, RAYWHITE);
    // inside home areas circle
    //circle of red
    DrawCircle((screenWidth - boardSize + 4 * cellSize) / 2, (screenHeight - boardSize + 4 * cellSize) / 2, 17, playersColors[0]);
    DrawCircle((screenWidth - boardSize + 8 * cellSize) / 2, (screenHeight - boardSize + 4 * cellSize) / 2, 17, playersColors[0]);
    DrawCircle((screenWidth - boardSize + 4 * cellSize) / 2, (screenHeight - boardSize + 8 * cellSize) / 2, 17, playersColors[0]);
    DrawCircle((screenWidth - boardSize + 8 * cellSize) / 2, (screenHeight - boardSize + 8 * cellSize) / 2, 17, playersColors[0]);
    // circle of blue
    DrawCircle((screenWidth - boardSize + 4 * cellSize) / 2, (screenHeight + 7 * cellSize) / 2, 17, playersColors[3]);
    DrawCircle((screenWidth - boardSize + 8 * cellSize) / 2, (screenHeight + 7 * cellSize) / 2, 17, playersColors[3]);
    DrawCircle((screenWidth - boardSize + 4 * cellSize) / 2, (screenHeight + 11 * cellSize) / 2, 17, playersColors[3]);
    DrawCircle((screenWidth - boardSize + 8 * cellSize) / 2, (screenHeight + 11 * cellSize) / 2, 17, playersColors[3]);
    // circle of green
    DrawCircle((screenWidth + 7 * cellSize) / 2, (screenHeight - boardSize + 4 * cellSize) / 2, 17, playersColors[1]);
    DrawCircle((screenWidth + 11 * cellSize) / 2, (screenHeight - boardSize + 4 * cellSize) / 2, 17, playersColors[1]);
    DrawCircle((screenWidth + 7 * cellSize) / 2, (screenHeight - boardSize + 8 * cellSize) / 2, 17, playersColors[1]);
    DrawCircle((screenWidth + 11 * cellSize) / 2, (screenHeight - boardSize + 8 * cellSize) / 2, 17, playersColors[1]);

    // circle of yellow
    DrawCircle((screenWidth + 7 * cellSize) / 2, (screenHeight + 7 * cellSize) / 2, 17, playersColors[2]);
    DrawCircle((screenWidth + 11 * cellSize) / 2, (screenHeight + 7 * cellSize) / 2, 17, playersColors[2]);
    DrawCircle((screenWidth + 7 * cellSize) / 2, (screenHeight + 11 * cellSize) / 2, 17, playersColors[2]);
    DrawCircle((screenWidth + 11 * cellSize) / 2, (screenHeight + 11 * cellSize) / 2, 17, playersColors[2]);

    // Draw center square
    DrawRectangle((screenWidth - cellSize * 3) / 2, (screenHeight - cellSize * 3) / 2, cellSize * 3, cellSize * 3, DARKGRAY);
    // divison of centre square
    // for red
    DrawTriangle({ (float)screenWidth / 2,(float)screenHeight / 2 }, { (float)(screenWidth - 3 * cellSize) / 2,(float)(screenHeight - 3 * cellSize) / 2 }, { (float)(screenWidth - 3 * cellSize) / 2,(float)(screenHeight + 3 * cellSize) / 2 }, playersColors[0]);
    // for blue
    DrawTriangle({ (float)screenWidth / 2,(float)screenHeight / 2 }, { (float)(screenWidth - 3 * cellSize) / 2,(float)(screenHeight + 3 * cellSize) / 2 }, { (float)(screenWidth + 3 * cellSize) / 2,(float)(screenHeight + 3 * cellSize) / 2 }, playersColors[3]);
    //for green
    DrawTriangle({ (float)(screenWidth + 3 * cellSize) / 2,(float)(screenHeight - 3 * cellSize) / 2 }, { (float)(screenWidth - 3 * cellSize) / 2,(float)(screenHeight - 3 * cellSize) / 2 }, { (float)screenWidth / 2,(float)screenHeight / 2 }, playersColors[1]);
    //for yellow
    DrawTriangle({ (float)(screenWidth + 3 * cellSize) / 2,(float)(screenHeight + 3 * cellSize) / 2 }, { (float)(screenWidth + 3 * cellSize) / 2,(float)(screenHeight - 3 * cellSize) / 2 }, { (float)screenWidth / 2,(float)screenHeight / 2 }, playersColors[2]);

}

