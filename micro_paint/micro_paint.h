#ifndef MICRO_PAINT_H
#define MICRO_PAINT_H

typedef struct s_zone
{
    int width;
    int height;
    char back_c;
}   t_zone;

typedef struct s_rectangle
{
    char    type;
    float   x;
    float   y;
    float   width;
    float   height;
    char    c;
}   t_rectangle;

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <math.h>

#endif