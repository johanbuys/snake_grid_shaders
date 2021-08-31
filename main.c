/*******************************************************************************************
*
*   raylib [core] example - Basic 3d example
*
*   Welcome to raylib!
*
*   To compile example, just press F5.
*   Note that compiled executable is placed in the same folder as .c file
*
*   You can find all basic examples on C:\raylib\raylib\examples folder or
*   raylib official webpage: www.raylib.com
*
*   Enjoy using raylib. :)
*
*   This example has been created using raylib 1.0 (www.raylib.com)
*   raylib is licensed under an unmodified zlib/libpng license (View raylib.h for details)
*
*   Copyright (c) 2013-2020 Ramon Santamaria (@raysan5)
*
********************************************************************************************/

#define SQUARE_SIZE 31



#include "raylib.h"
#include "utils.h"
#include "snake.h"
#include "grid.h"

#define STB_DS_IMPLEMENTATION
#include "stb_ds.h"

#define GLSL_VERSION 100

const int screenWidth = 800;
const int screenHeight = 800;
const int WIDTH = 10;
const int HEIGHT = 10;
unsigned char score = 0;

typedef enum
{
    INTRO = 0,
    RUNNING,
    GAME_OVER
} GameState;


void drawRunning(Grid grid, unsigned char score) {
    char scoreCharBuffer[10];
    drawGrid(grid);
    DrawFPS(10, 10);
    sprintf(scoreCharBuffer, "SCORE: %d", score);
    int size = MeasureText(scoreCharBuffer, 20);
    DrawText(scoreCharBuffer, screenWidth - (size + 20), 10, 20, RED);
}

void drawIntro() {
    int size = MeasureText("Press [Enter] to GO! READY?", 20);
    ClearBackground(WHITE);
    DrawText("Press enter to GO! READY?", (screenWidth - size) / 2, screenHeight / 2, 20, RED);
}

void drawGameOver(unsigned char score)
{
    char scoreCharBuffer[10];
    ClearBackground(BLACK);
    int size = MeasureText("GAME OVER!", 50);
    DrawText("GAME OVER!", (screenWidth - size) / 2, screenHeight / 2, 50, RED);
    size = MeasureText("Press [Enter] To Retry", 20);
    DrawText("Press [Enter] To Retry", (screenWidth - size) / 2, screenHeight / 2 + 70, 20, GREEN);
    sprintf(scoreCharBuffer, "SCORE: %d", score);
    size = MeasureText(scoreCharBuffer, 20);
    DrawText(scoreCharBuffer, (screenWidth - size) / 2, screenHeight / 2 + 90, 20, RED);
}

void init(Grid *grid, Snake *player)
{
    score = 0;
    initGrid(grid, 10, 10, screenWidth, screenHeight);
    initSnake(player, grid, 5, 5);
    Vector2 startPos = getRandomPos(0, 9);
    while (getGridValueAtIndex(*grid, startPos.x, startPos.y))
    {
        startPos = getRandomPos(0, 9);
    }
    setGridValueAtIndex(grid, startPos.x, startPos.y, 2);
}

int main()
{
    // Initialization
    //--------------------------------------------------------------------------------------
    Snake player;
    Grid grid;
    GameState state = INTRO;

    static unsigned long int framecount = 0;

    init(&grid, &player);
    InitWindow(screenWidth, screenHeight, "Snake");
    SetTargetFPS(60); // Set our game to run at 60 frames-per-second
    

        //--------------------------------------------------------------------------------------

        // Main game loop
    while (!WindowShouldClose()) // Detect window close button or ESC key
    {
        // int delta = GetFrameTime();
        // Update
        //----------------------------------------------------------------------------------
        if (IsKeyDown(KEY_RIGHT))
        {
            if (player.velocity.x != -1)
            {
                player.velocity = (Vector2){1, 0};
            }
        }
        if (IsKeyDown(KEY_LEFT))
        {
            if (player.velocity.x != 1)
            {
                player.velocity = (Vector2){-1, 0};
            }
        }
        if (IsKeyDown(KEY_UP))
        {
            if (player.velocity.y != 1)
            {
                player.velocity = (Vector2){0, -1};
            }
        }
        if (IsKeyDown(KEY_DOWN))
        {
            if (player.velocity.y != -1)
            {
                player.velocity = (Vector2){0, 1};
            }
        }
        if (state == INTRO && IsKeyDown(KEY_ENTER))
        {
            state = RUNNING;
        }
        if (state == GAME_OVER && IsKeyDown(KEY_ENTER))
        {
            init(&grid, &player);
            state = RUNNING;
        }
        if (state == RUNNING && (framecount % 10) == 0) {
            CollisionType moveResult = moveSnake(&player, &grid);
            if (moveResult == NO_COLLISION) {
                printf("NO collisions");
            }
            if (moveResult == WALL || moveResult == SELF)
            {
                state = GAME_OVER; 
            }
            if (moveResult == FOOD)
            {
                score++;
            }
        }
       
        framecount++;
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();
            ClearBackground(BLACK);
            switch (state)
            {
            case INTRO:
                drawIntro();
                break;
            case GAME_OVER:
                drawGameOver(score);
                break;
            case RUNNING:
                drawRunning(grid, score);
                break;

            default:
                break;
            }
        EndDrawing();
            //----------------------------------------------------------------------------------
        
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    freeSnake(&player);
    freeGrid(&grid);
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}