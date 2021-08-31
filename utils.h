#include <stdio.h>
#include <stdlib.h>
#include "raylib.h"

unsigned int randV(unsigned int min, unsigned int max)
{
  int r;
  const unsigned int range = 1 + max - min;
  const unsigned int buckets = RAND_MAX / range;
  const unsigned int limit = buckets * range;

  /* Create equal size buckets all in a row, then fire randomly towards
     * the buckets until you land in one of them. All buckets are equally
     * likely. If you land off the end of the line of buckets, try again. */
  do
  {
    r = rand();
  } while (r >= limit);

  return min + (r / buckets);
}

Vector2 getRandomPos(unsigned int min, unsigned int max)
{
  int x = randV(min, max);
  int y = randV(min, max);
  Vector2 vec = {x, y};
  return vec;
}
