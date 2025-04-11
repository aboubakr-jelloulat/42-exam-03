#include <stdio.h>
#include <unistd.h>
#include <string.h>

#ifndef BUFFER_SIZE
#define BUFFER_SIZE 42
#endif


void    ReplaceString(char *UserInput, int ReplaceLenght)
{
    for (int i = 0; i < ReplaceLenght; i++)
        UserInput[i] = '*';
    
}

int CheckIsValidToReplace(char *Replace, char *UserInput)
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

void filter(char *Replace, char *UserInput)
{
    int ReplaceLenght = strlen(Replace);

    for (int i = 0; i < strlen(UserInput); )
    {

        if (CheckIsValidToReplace(Replace, &UserInput[i]))
        {
            ReplaceString(&UserInput[i], ReplaceLenght);
            i += ReplaceLenght;
        }
        else
            i++;
    }
}

int main(int ac, char **av)
{
    if (ac != 2)
        return 1;

    int bytes;
    char buffer[10240];
    while (1)
    {
        bytes = read(0, buffer, BUFFER_SIZE);

        switch (bytes)
        {
            case 0:
                break;

            case -1:
                return (perror("Error: "), 1);

            default:
                filter(av[1], buffer);
                printf("%s", buffer);
        }
    }

    return 0;
}
//