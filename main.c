/*******************************************************************************************
*
*   SNAKE!
*   Simple snake using a grid based system.
*   Played with Shaders. Snake changes color based on time passed to shader uniform.
*   Johan Buys
*
********************************************************************************************/

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

void drawPostProcessing(Shader shader, RenderTexture2D target)
{
    BeginShaderMode(shader);
        // NOTE: Render texture must be y-flipped due to default OpenGL coordinates (left-bottom)
        DrawTextureRec(target.texture, (Rectangle){0, 0, (float)target.texture.width, (float)-target.texture.height}, (Vector2){0, 0}, WHITE);
    EndShaderMode();
}

void drawRunning(Grid grid, unsigned char score) {
    char scoreCharBuffer[10];
    drawGrid(grid);
    DrawFPS(10, 10);
    sprintf(scoreCharBuffer, "SCORE: %d", score);
    int size = MeasureText(scoreCharBuffer, 20);
    DrawText(scoreCharBuffer, screenWidth - (size + 20), 10, 20, RED);
}

void drawToTexture(RenderTexture2D target, Grid grid)
{
    BeginTextureMode(target); // Enable drawing to texture
        ClearBackground(BLACK);   // Clear texture background
        drawRunning(grid, score);
    EndTextureMode();
}

void drawIntro() {
    const char text[] = "Press enter to START!";
    int size = MeasureText(text, 50);
    ClearBackground(BLACK);
    DrawText(text, (screenWidth - size) / 2, screenHeight / 2, 50, RED);
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
    Shader shader = LoadShader(0, TextFormat("resources/bloom.fs", 100));
    RenderTexture2D target = LoadRenderTexture(screenWidth, screenHeight);

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
                // drawRunning(grid, score);
                drawToTexture(target, grid);
                drawPostProcessing(shader, target);
                break;

            default:
                break;
            }
        EndDrawing();
            //----------------------------------------------------------------------------------
        
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    UnloadShader(shader);
    UnloadRenderTexture(target);
    freeSnake(&player);
    freeGrid(&grid);
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}