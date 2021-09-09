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
  // float u_time = 0.0f;
  // float u_res[2] = {(float)800, (float)800};
  // u_time = (float)GetTime();
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
        DrawRectangle(j * grid.cellSize, k * grid.cellSize, grid.cellSize, grid.cellSize, GREEN);

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