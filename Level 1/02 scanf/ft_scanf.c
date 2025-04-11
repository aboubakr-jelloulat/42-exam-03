#include <stdarg.h>
#include <stdio.h>
#include <ctype.h>

static long long ft_atol(const char *str)
{
    long i = 0;
    long result = 0;
    int sign = 1;

    while (isspace(str[i]))
        i++;
    
    if (str[i] == '-' || str[i] == '+')
    {
        if (str[i] == '-')
            sign = -1;
        i++;
    }
    while (str[i])
    
        if (str[i] >= '0' && str[i] <= '9')
        {
            result = (result * 10) + str[i] - '0';
            i++;
        }
    
    return (result * sign);
}

int match_space(FILE *f)
{
    int ch;

    while ((ch = fgetc(f)) != EOF)
    {
        if (!isspace(ch))
            return (ungetc(ch, f),  1);
       
    }
    return -1;
}

int match_char(FILE *f, char c)
{
    return (fgetc(f) == c);
}

int scan_char(FILE *f, va_list ap)
{
    char *c_ptr = va_arg(ap, char*);
    int  ch = fgetc(f);

    if (ch != EOF)
    {
        return (*c_ptr = ch, 1);
    }
    return 0;
}

int scan_int(FILE *f, va_list ap)
{
    char    buffer[42];
    int     index = 0;
    int     *i_ptr = va_arg(ap, int*);
    int     ch;

    match_space(f);

    while (isdigit(ch = fgetc(f)) && index < sizeof(buffer))
        buffer[index++] = ch;
    
    if (index > 0)
    {
        buffer[index] = 0;
        *i_ptr = ft_atol(buffer);

        if (ch != EOF)
            ungetc (ch, f);
        return 1;
    }
       
    return (0);
}

int scan_string(FILE *f, va_list ap)
{
    char    *str_ptr = va_arg(ap, char *);
    int     ch;
    int     index = 0;

    match_space(f);

    while ((ch = fgetc(f)) != EOF && !isspace(ch) && index < 99) // 99 No overflow 🔐  byte number u pass - 1 for '\0'
        str_ptr[index++] = ch;
    
    str_ptr[index] = '\0';

    return (index > 0) ? 1  : 0;
}


int	match_conv(FILE *f, const char **format, va_list ap)
{
	switch (**format)
	{
		case 'c':
			return scan_char(f, ap);
		case 'd':
			match_space(f);
			return scan_int(f, ap);
		case 's':
			match_space(f);
			return scan_string(f, ap);
		case EOF:
			return -1;
		default:
			return -1;
	}
}

int ft_vfscanf(FILE *f, const char *format, va_list ap)
{
	int nconv = 0;

	int c = fgetc(f);
	if (c == EOF)
		return EOF;
	ungetc(c, f);

	while (*format)
	{
		if (*format == '%')
		{
			format++;
			if (match_conv(f, &format, ap) != 1)
				break;
			else
				nconv++;
		}
		else if (isspace(*format))
		{
			if (match_space(f) == -1)
				break;
		}
		else if (match_char(f, *format) != 1)
			break;
		format++;
	}
	if (ferror(f))
		return EOF;
	return nconv;
}


int ft_scanf(const char *format, ...)
{
	va_list ap;
	va_start(ap, format);
	int ret = ft_vfscanf(stdin, format, ap);
	va_end(ap);
	return (ret);
}

#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int     number;
    char    letter;
    char    string[100];

    //  ******* my scanf *******

    ft_scanf("%d  %c  %s ", &number, &letter, string);

    printf ("\nnumber = %d \nletter = %c \nstring = %s", number, letter, string);

    // **** real scanf ******

    scanf("%d %c %s", &number, &letter, string);

    printf("\nnumber = %d\nletter = %c\nstring = %s\n", number, letter, string);


    return 0;
}
