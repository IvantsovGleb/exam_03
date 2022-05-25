#include <stdarg.h>
#include <unistd.h>

int g_count = 0;

int str_len(const char *s)
{
    int i = 0;
    while (s[i++])
        ;
    return (i - 1);
}

void ft_putnbr(unsigned long n, int radix, char *alphabet)
{
    if (n >= radix)
        ft_putnbr(n / radix, radix, alphabet);
    write(1, &alphabet[n % radix], 1);
    g_count++;
}

int ft_printf(const char *fmt, ...)
{
    g_count = 0;
    va_list ap;
    va_start(ap, fmt);
    while (*fmt)
    {
        if (*fmt == '%')
        {
            fmt++;
            if (*fmt == 's')
            {
                char *s = va_arg(ap, char *);
                if (!s)
                {
                    s = "(null)";
                }
                g_count += write(1, s, str_len(s));
            }
            else if (*fmt == 'd')
            {
                long int d = va_arg(ap, int);
                if (d < 0)
                {
                    g_count += write(1, "-", 1);
                    d = -d;
                }
                ft_putnbr(d, 10, "0123456789");
            }
            else if (*fmt == 'x')
            {
                ft_putnbr(va_arg(ap, unsigned int), 16, "0123456789abcdef");
            }
            else if (*fmt == '%')
            {
                g_count += write(1, fmt, 1);
            }
            fmt++;
        }
        else
            g_count += write(1, fmt++, 1);
    }
    va_end(ap);
    return (g_count);
}