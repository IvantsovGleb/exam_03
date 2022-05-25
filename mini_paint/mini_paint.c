#include "mini_paint.h"

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

int is_in(float x, float y, t_circle circle)
{
    float dist = sqrtf(powf(x - circle.x, 2.) + powf(y - circle.y, 2.));
    if (dist <= circle.radius)
    {
        if ((circle.radius - dist) < 1.00000000)
            return (2);
        return (1);
    }
    return (0);
}

int    draw_circle(FILE *file, t_zone *info, char *map)
{
    t_circle    tmp;
    int ret;

    while ((ret = fscanf(file, "%c %f %f %f %c\n", &tmp.type, &tmp.x, &tmp.y, &tmp.radius, &tmp.c)) == 5)
    {
        if (tmp.radius <= 0.00000000 || (tmp.type != 'c' && tmp.type != 'C'))
            return (0);
        int y = 0;
        while (y < info->height)
        {
            int x = 0;
            while (x < info->width)
            {
                int     in = is_in((float)x, (float)y, tmp);
                if ((tmp.type == 'c' && in == 2) || (tmp.type == 'C' && in))
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
        if (!draw_circle(file, &info, map))
            return (clear_all(file, map));
        draw_map(&info, map);
        fclose(file);
        free(map);
    }
    else
        return (s_err("Error: argument\n"));
    return (0);
}