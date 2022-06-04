#include "get_next_line.h"

int str_len(const char *s)
{
    int i = 0;
    while (s[i])
        i++;
    return (i);
}

char *str_chr(char *s, int c)
{
    int i;

    i = 0;
    while (s[i])
    {
        if (s[i] == (char)c)
            return (&s[i]);
        i++;
    }
    if ((char)c == '\0')
        return (&s[i]);
    return ((void *) 0);
}

char    *str_n_dup(const char *s, int n)
{
    int len = 0;
    int i = 0;
    while (s[i] && len < n)
        len++;
    char    *tmp = malloc(sizeof(*tmp) * (len + 1));
    i = 0;
    while (i < len)
    {
        tmp[i] = s[i];
        i++;
    }
    tmp[i] = '\0';
    return (tmp);
}

char    *str_dup(const char *s)
{
    char    *tmp;
    int len;

    len = str_len(s);
    tmp = malloc(sizeof(*tmp) * (len + 1));
    int i = 0;
    while (i < len)
    {
        tmp[i] = s[i];
        i++;
    }
    tmp[i] = '\0';
    return (tmp);
}

char	*str_join(char const *s1, char const *s2)
{
    char *s;
    int i;
    int j;

    if (!s1 || !s2)
        return ((void *) 0);
    s = malloc(sizeof(*s) * (str_len(s1) + str_len(s2) + 1));
    i = -1;
    while (s1[++i])
        s[i] = s1[i];
    j = -1;
    while (s2[++j])
        s[i + j] = s2[j];
    s[i + j] = '\0';
    return (s);
}

int	ft_read(int fd, char **reminder)
{
    char	buff[BUFFER_SIZE + 1];
    char	*tmp;
    int r;

    if (!*reminder)
    {
        *reminder = malloc(sizeof(**reminder) * 1);
        *reminder[0] = '\0';
    }
    r = 1;
    while (!str_chr(*reminder, '\n') && r > 0)
    {
        r = read(fd, buff, BUFFER_SIZE);
        if (r == -1)
            return (-1);
        buff[r] = '\0';
        tmp = str_join(*reminder, buff);
        free(*reminder);
        *reminder = tmp;
    }
    return (r);
}

char	*extract_word(char **reminder)
{
    char    *line;
    char    *tmp;

    int len = 0;
    while (reminder[0][len] != '\0' && reminder[0][len] != '\n')
        len++;
    line = (void *) 0;
    tmp = (void *) 0;
    if (len > 0 && reminder[0][len] == '\0')
        line = str_dup(*reminder);
    else if (reminder[0][len] == '\n')
    {
        line = str_n_dup(*reminder, len + 1);
        tmp = str_dup(*reminder + len + 1);
    }
    free(*reminder);
    *reminder = tmp;
    return (line);
}

char *get_next_line(int fd)
{
    static char *reminder;
    char    *line;
    int r;

    if (fd < 0 || BUFFER_SIZE <= 0)
        return ((void *) 0);
    r = ft_read(fd, &reminder);
    line = (void *) 0;
    if (r != -1)
    {
        line = extract_word(&reminder);
    }
    else
    {
        free(reminder);
        reminder = (void *) 0;
    }
    return (line);
}

int main(void)
{
    char    *line;

    line = get_next_line(0);
    while (line != (void *) 0)
    {
        write(1, line, str_len(line));
        free(line);
        line = get_next_line(0);
    }
    return (0);
}