#include "filter.h"

int	ft_strlen(const char *s)
{
	int i = 0;

	while (s[i])
		i++;
	return i;
}

void	ReplaceString(char *StringReplace, int ReplaceStringLenght)
{
	for (int i = 0; i < ReplaceStringLenght; i++)  
		StringReplace[i] = '*';
	
}

int	IsAccesableToReplace(char *UserInput, char *Replace)
{
	int i = 0;

	while (Replace[i] && UserInput[i])
	{
		if (UserInput[i] != Replace[i])
			return 0;
		i++;
	}
	return 1;
}

void solve(char *UserInput, char *Replace)
{
	int	ReplaceStringLenght = ft_strlen(Replace);

	for (int i = 0; UserInput[i]; )
	{
		if (IsAccesableToReplace(&UserInput[i], Replace))
		{
			ReplaceString(&UserInput[i], ReplaceStringLenght);
			i += ReplaceStringLenght;
		}
		else
			i++;

	}

}

int main(int ac, char **av)
{

	if (ac != 2)
		return 1;

	char	buffer[BUFFER_SIZE + 1];
	int		bytes;

	while (1)
	{
		bytes = read(0, buffer, BUFFER_SIZE);
		switch (bytes)
		{
			case 0 :
				break;
			
			case -1 :
				return (perror("Error: "), 1);
			
			default : 
				solve(buffer, av[1]);
				write (1, buffer, bytes);
		}
	}

	return 0;
}
