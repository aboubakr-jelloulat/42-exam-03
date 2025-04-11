/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajelloul <ajelloul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 17:00:38 by ajelloul          #+#    #+#             */
/*   Updated: 2025/04/11 17:00:39 by ajelloul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>

#ifndef     BUFFER_SIZE
# define    BUFFER_SIZE 42
#endif

static int ft_strlen(const char *s)
{
    int i = 0; 

    while (s[i])
        i++;
    return i;
}

static char *ft_strndup(const char *str)
{
    char    *new;
    int     i = 0;

    new = (char *)malloc(sizeof(char) * ft_strlen(str) + 1);
    if (!new)    return NULL;

    while (str[i])
    {
        new[i] = str[i];
        i++;
    }
    new[i] = '\0';
    return (new);
}

char *get_next_line(int fd)
{
    if (fd < 0 || BUFFER_SIZE < 1)
        return NULL;

    static char buffer[BUFFER_SIZE + 1];
    static int         bytes = 0, pos = 0; // static 
    char        line[5000]; // + 2k

    int i = 0;
    while(1)
    {
        if (pos >= bytes)
        {
            bytes = read(fd, buffer, BUFFER_SIZE);
            if (bytes <= 0)
                break ;
            pos = 0;
        }
        line[i++] = buffer[pos++];
        if (buffer[pos - 1] == '\n')
            break ;
    }
    if (!i) return NULL;
    line[i] = '\0';
    return ft_strndup(line);
}

#include <stdio.h>
#include <fcntl.h>

int main(void)
{
    char *line;

    for (int fd = open("file.txt", O_CREAT | O_RDWR, 0777), i = 0; ; i++)
    {
        line = get_next_line(fd);
        if (!line)
            break;
        printf ("\nline %d : %s\n", i, line);
        free (line);
    }

    return 0;
}
