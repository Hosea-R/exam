#include "ft_printf.h"

static int ft_strlen(char *str)
{
    int i = 0;
    while (str[i])
        i++;
    return (i);
}
static int ft_putstr(char *s)
{
    if (!s)
        s = "(null)";
    return (write(1, s, ft_strlen(s)));
}

static int ft_putnbr_base(long n, char *base)
{
    char buf[20];
    int i = 0, len = 0, base_len = ft_strlen(base);

    if (n < 0 && base_len == 10)
        len += write(1, "-", 1), n = -n;
    if (n == 0)
        return (write(1, "0", 1));
    while (n)
        buf[i++] = base[n % base_len], n /= base_len;
    while (--i >= 0)
        len += write(1, &buf[i], 1);
    return (len);
}

int ft_printf(const char *str, ...)
{
    va_list args;
    int len = 0;

    va_start(args, str);
    while (*str)
        if (*str == '%' && *(++str))
            len += (*str == 's') ? ft_putstr(va_arg(args, char *)) :
                   (*str == 'd') ? ft_putnbr_base(va_arg(args, int), "0123456789") :
                   (*str == 'x') ? ft_putnbr_base(va_arg(args, unsigned int), "0123456789abcdef") : 
                   write(1, str, 1);
        else
            len += write(1, str, 1), str++;
    va_end(args);
    return (len);
}


#include <stdio.h>

int main(void)
{
    ft_printf("String: %s\n", "Hello!");
    ft_printf("Decimal: %d\n", 42);
    ft_printf("Hexadecimal: %x\n", 255);
    return 0;
}