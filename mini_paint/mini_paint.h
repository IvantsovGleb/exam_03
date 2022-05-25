#ifndef MINI_PAINT_H
#define MINI_PAINT_H

typedef struct s_zone
{
    int width;
    int height;
    char back_c;
}   t_zone;

typedef struct s_circle
{
    char    type;
    float   x;
    float   y;
    float   radius;
    char    c;
}   t_circle;

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <math.h>

#endif