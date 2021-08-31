#include "raylib.h"
#include "stb_ds.h"
#include "grid.h"

#ifndef SNAKE_H
#define SNAKE_H
typedef struct
{
  /* data */
  Vector2 *segments;
  Vector2 velocity;
  int score;
  int speed;
} Snake;

typedef enum 
{
  NO_COLLISION = 0,
  WALL,
  SELF,
  FOOD
} CollisionType;

void initSnake(Snake *snake, Grid *grid, int x, int y) {
  snake->velocity = (Vector2){1, 0};
  snake->segments = NULL;
  Vector2 head = (Vector2){.x = x, .y = y };
  arrput(snake->segments, head);
  Vector2 seg1 = (Vector2){.x = x - 1, .y = y };
  arrput(snake->segments, seg1);
  setGridValueAtIndex(grid, head.x, head.y, 1);
  setGridValueAtIndex(grid, seg1.x, seg1.y, 1);
  // unsigned int len = arrlenu(snake->segments);
}

CollisionType moveSnake(Snake *snake, Grid *grid) {
  CollisionType collision = NO_COLLISION;

  if (snake->velocity.x != 0 || snake->velocity.y != 0)
  {
    unsigned int len = arrlenu(snake->segments);
    Vector2 head = (Vector2){.x = snake->segments[0].x + snake->velocity.x, .y = snake->segments[0].y + snake->velocity.y };
    int newHeadPos = getGridValueAtIndex(*grid, head.x, head.y);
    switch (newHeadPos)
    {
    case 1:
      DrawText("COLLIDE", 50, 50, 20, RED);
      collision = SELF;
      break;
    case 2:
    {
      collision = FOOD;
      Vector2 food = (Vector2){.x = head.x + (snake->velocity.x * (len - 1)), .y = head.y + (snake->velocity.x * (len - 1))};
      arrput(snake->segments, food);

      Vector2 startPos = getRandomPos(0, 9);

      // set new foood
      while (getGridValueAtIndex(*grid, startPos.x, startPos.y))
      {
        startPos = getRandomPos(0, 9);
      }
      setGridValueAtIndex(grid, startPos.x, startPos.y, 2);
      break;
    }

    
    default:
      break;
    }

    if (head.x >= grid->width || head.y >= grid->height || head.x < 0 || head.y < 0) {
      DrawText("COLLIDE", 50, 50, 20, RED);
      collision = WALL;
    } else {
      setGridValueAtIndex(grid, snake->segments[len - 1].x, snake->segments[len - 1].y, 0);
      arrpop(snake->segments);
      arrins(snake->segments, 0, head);
    }

    for (int k = 0; k < len; k++)
    {
      Vector2 seg = snake->segments[k];
      setGridValueAtIndex(grid, seg.x, seg.y, 1);
    }
  }


  // if (hadSomeFood == 1) {
  //   return 2;
  // } else {
  //   return 0;
  // }
  return collision;
}

void freeSnake(Snake *snake) {
  arrfree(snake->segments);
}

#endif