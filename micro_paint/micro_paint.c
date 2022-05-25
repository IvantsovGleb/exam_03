//#include "micro_paint.h"

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

int str_len(const char *s)
{
    int i = 0;
    while (s[i++])
        ;
    return (i - 1);
}

int s_err(const char *s)
{
    if (s)
        write(1, s, str_len(s));
    return (1);
}

int clear_all(FILE *file, char *map)
{
    if (file)
        fclose(file);
    if (map)
        free(map);
    s_err("Error: Operation file corrupted\n");
    return (1);
}

char    *parse_first(FILE *file, t_zone *info)
{
    char    *tmp;

    if (fscanf(file, "%i %i %c\n", &info->width, &info->height, &info->back_c) != 3)
        return ((void *) 0);
    if (info->width > 0 && info->width <= 300 && info->height > 0 && info->height <= 300)
    {
        if (!(tmp = malloc(sizeof(char) * info->width * info->height)))
            return ((void *) 0);
        int i = 0;
        while (i < info->width * info->height)
            tmp[i++] = info->back_c;
        return (tmp);
    }
    return ((void *) 0);
}

int is_in_rectangle(float x, float y, t_rectangle rectangle)
{
    if ((x >= rectangle.x) && (x <= (rectangle.x + rectangle.width)) &&
            (y >= rectangle.y) && (y <= (rectangle.y + rectangle.height)))
    {
        if (((x - rectangle.x) < 1.0000000) || ((y - rectangle.y) < 1.0000000) ||
                ((rectangle.x + rectangle.width - x) < 1.0000000) || ((rectangle.y + rectangle.height - y) < 1.0000000))
            return (2);
        return (1);
    }
    return (0);
}

int     draw_rectangle(FILE *file, t_zone *info, char *map)
{
    t_rectangle tmp;
    int ret;

    while ((ret = fscanf(file, "%c %f %f %f %f %c\n", &tmp.type, &tmp.x, &tmp.y, &tmp.width, &tmp.height, &tmp.c)) == 6)
    {
        if (tmp.width <= 0.0000000 || tmp.height <= 0.000000 || (tmp.type != 'r' && tmp.type != 'R'))
            return (0);
        int y = 0;
        while (y < info->height)
        {
            int x = 0;
            while (x < info->width)
            {
                int is_in = is_in_rectangle((float)x, (float)y, tmp);
                if ((tmp.type == 'r' && is_in == 2) || (tmp.type == 'R' && is_in))
                    map[y * info->width + x] = tmp.c;
                x++;
            }
            y++;
        }
    }
    if (ret != -1)
        return (0);
    return (1);
}

void    draw_map(t_zone *info, char *map)
{
    int	i;

    i = 0;
    while (i < info->height)
    {
        write(1, map + (i * info->width), info->width);
        write(1, "\n", 1);
        i++;
    }
}

int main(int argc, char **argv)
{
    t_zone  info;
    FILE    *file = (void *) 0;
    char    *map;

    if (argc == 2)
    {
        info.width = 0;
        info.height = 0;
        info.back_c = 0;
        file = fopen(argv[1], "r");
        if (!file)
            return (clear_all((void *) 0, (void *) 0));
        if (!(map = parse_first(file, &info)))
            return (clear_all(file, (void *) 0));
        if (!draw_rectangle(file, &info, map))
            return (clear_all(file, map));
        draw_map(&info, map);
        fclose(file);
        free(map);
    }
    else
        return (s_err("Error: argument\n"));
    return (0);
}
