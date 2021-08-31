#include "stb_ds.h"
#include "raylib.h"

#ifndef GRID_H
#define GRID_H

typedef struct 
{
  unsigned int width;
  unsigned int height;
  unsigned int cellSize;
  unsigned char *data;
  unsigned int size;
} Grid;

void initGrid(Grid *grid, unsigned int width, unsigned int height, unsigned int screenWidth, unsigned int screenHeight)
{
  grid->width = width;
  grid->height = height;
  grid->size = width * height;
  grid->data = NULL;
  grid->cellSize = screenWidth/width;

  for (int k = 0; k < grid->size; k++)
  {
    arrput(grid->data, 0);
  }

}

unsigned char getGridValueAtIndex(Grid grid, int x, int y)
{
  if (x >= grid.width || y >= grid.height)
  {
    return -1;
  }
  return grid.data[grid.width * y + x];
}

void setGridValueAtIndex(Grid *grid, unsigned int x, unsigned int y, unsigned char value)
{
  grid->data[grid->width * y + x] = value;
}

void drawGrid(Grid grid) {
  Shader shader = LoadShader(0, TextFormat("resources/test.fs", 100));
  // Get variable (uniform) location on the shader to connect with the program
  // NOTE: If uniform variable could not be found in the shader, function returns -1
  int u_timeLoc = GetShaderLocation(shader, "u_time");
  int u_resLoc = GetShaderLocation(shader, "u_res");


  float u_time = 0.0f;
  float u_res[2] = {(float)800, (float)800};
  u_time = (float)GetTime();
  SetShaderValue(shader, u_timeLoc, &u_time, SHADER_UNIFORM_FLOAT);
  SetShaderValue(shader, u_resLoc, &u_res, SHADER_UNIFORM_VEC2);
  for (int k = 0; k < grid.width; k++) {
    for (int j = 0; j < grid.height; j++) {
      Color color;
      color = WHITE;
      // if ((j + k) % 2 == 0) {
      //   color = BLUE;
      // }

      DrawRectangleLines(j * grid.cellSize, k * grid.cellSize, grid.cellSize, grid.cellSize, color);
      if (getGridValueAtIndex(grid, j, k) == 1)
      {
        BeginShaderMode(shader);
          DrawRectangle(j * grid.cellSize, k * grid.cellSize, grid.cellSize, grid.cellSize, RED);
        EndShaderMode();
      }
      else if (getGridValueAtIndex(grid, j, k) == 2) {
        DrawRectangle(j * grid.cellSize, k * grid.cellSize, grid.cellSize, grid.cellSize, GREEN);
      }
    }
  }
}

void freeGrid(Grid *grid) {
  arrfree(grid->data);
  grid = 0;
  free(grid);
  //UnloadShader()
}
#endif