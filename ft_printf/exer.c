#include "ft_printf.h"

static int ft_putstr(char *s)
{   
    int len = 0;

    if (!s)
        s = "(null)";
    while (s[len])
        len++;
    return (write(1, s, len));
}

static int ft_putnbr_base(long n, char *base, int base_len)
{
    char buf[20];
    int i = 0, len = 0;

    if (n == 0)
        return (write(1, "0", 1));
    if (n < 0)
    {
        len += write(1, "-", 1);
        n = -n;
    }
    while (n > 0)
    {
        buf[i++] = base[n % base_len];
        n /= base_len;
    }
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
    {
        if (*str == '%' && (*(str + 1) == 's' || *(str + 1) == 'd' || *(str + 1) == 'x'))
        {
            str++;
            if (*str == 's')
                len += ft_putstr(va_arg(args, char *));
            else if (*str == 'd')
                len += ft_putnbr_base(va_arg(args, int), "0123456789", 10);
            else if (*str == 'x')
                len += ft_putnbr_base(va_arg(args, unsigned int), "0123456789abcdef", 16);
        }
        else
            len += write(1, str, 1);
        str++;
    }
    va_end(args);
    return (len);
}

int main(void)
{
    ft_printf("String: %s\n", "Hello");
    ft_printf("Decimal: %d\n", 42);
    ft_printf("Hex: %x\n", 255);
    ft_printf("Null string: %s\n", NULL);
    ft_printf("Negative: %d\n", -123);
    ft_printf("Tsisy ninin\n");
}
