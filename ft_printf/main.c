#include <stdio.h>

int	ft_printf(char const *fmt, ...);

#ifndef FLAG
#define PR count += printf
#else
#define PR count += ft_printf
#endif

int main()
{
    int count = 0;

    PR("%d", 0);
    PR("%d", 42);
    PR("%d", 1);
    PR("%d", 5454);
    PR("%d", (int)2147483647);
    PR("%d", (int)2147483648);
    PR("%d", (int)-2147483648);
    PR("%d", (int)-2147483649);
    PR("%x", 0);
    PR("%x", 42);
    PR("%x", 1);
    PR("%x", 5454);
    PR("%x", (int)2147483647);
    PR("%x", (int)2147483648);
    PR("%x", (int)-2147483648);
    PR("%x", (int)-2147483649);
    PR("%s", "");
    PR("%s", "toto");
    PR("%s", "wiurwuyrhwrywuier");
    PR("%s", (void *) 0);
    PR("-%s-%s-%s-%s-", "", "toto", "wiurwuyrhwrywuier", (void *) 0);
    PR("%d%x%d%x%d%x%d%x", 0, 0, 42, 42, 2147483647, 2147483647, (int)-2147483648, (int)-2147483648);
    PR("-%d-%x-%d-%x-%d-%x-%d-%x-", 0, 0, 42, 42, 2147483647, 2147483647, (int)-2147483648, (int)-2147483648);
    PR("%s%s%s%s", "", "toto", "wiurwuyrhwrywuier", (void *) 0);
    PR("-%s-%s-%s-%s-", "", "toto", "wiurwuyrhwrywuier", (void *) 0);
    printf("count %d", count);
    return (0);
}