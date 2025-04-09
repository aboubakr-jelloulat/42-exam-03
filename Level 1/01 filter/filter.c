#include "filter.h"

int ft_strlen(char *str)
{
	int i = 0;
	for ( ; str[i]; i++)
	return i;
}


void ft_filter(char *src, char *replace, int srcLength)
{
	replaceLength =

	for (int i = 0; src[i]; )
	{
		
	}

}

int main(int ac, char **av)
{
	char buffer[bufferSize + 1];
	int  bytes_read = 0;

	if (ac != 2)
		return 1;

	while (1)
	{
		bytes_read = read(0, buffer, bufferSize);

		if (!bytes_read)
			break ;
		else if (bytes_read > 0)
		{
			ft_filter(buffer, av[1], bytes_read);
			write(1, buffer, bytes_read);
		}
		else
			return (perror("Error: "), 1);

	}


	return 0;
}
