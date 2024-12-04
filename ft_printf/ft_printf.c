#include "ft_printf.h"

int ft_print_string(char *str)
{
    int length = 0;
    if (!str) str = "(null)";
    for (size_t i = 0; str[i]; i++)
    {
        write(1, &str[i], 1);
        length++;
    }
    return length;
}

void ft_putnbr(int d)
{
    if (d == -2147483648)
    {
        write(1, "-2147483648", 11);
        return;
    }
    if (d < 0)
    {
        write(1, "-", 1);
        d = -d;
    }
    if (d > 9)
        ft_putnbr(d / 10);
    char c = d % 10 + '0';
    write(1, &c, 1);
}

int ft_print_int(int d)
{
    int length = 0;
    int n = d;
    if (d <= 0) length++;
    while (n && ++length) n /= 10;
    ft_putnbr(d);
    return length;
}

void ft_puthex(unsigned int x)
{
    char *hex = "0123456789abcdef";
    if (x > 15)
        ft_puthex(x / 16);
    char c = hex[x % 16];
    write(1, &c, 1);    
}

int ft_print_hex(unsigned int x)
{
    int length = 1;
    unsigned int u = x;
    while (u >>= 4)
        length++;
    ft_puthex(x);
    return length;    
}

int ft_conversions(int c, va_list ap)
{
    if (c == 's') return ft_print_string(va_arg(ap, char *));
    if (c == 'd') return ft_print_int(va_arg(ap, int));
    if (c == 'x') return ft_print_hex(va_arg(ap, unsigned int));
    return 0;
}

int ft_printf(const char *str, ...)
{
    va_list ap;
    int length = 0;
    va_start(ap, str);
    for (int i = 0; str[i]; i++)
    {
        if (str[i] == '%' && str[++i])
            length += ft_conversions(str[i], ap);
        else
        {
            write(1, &str[i], 1);
            length++;
        }
    }
    va_end(ap);
    return length;
}

int main(void)
{
    ft_printf("%d\n", 42);
    return (0);
}