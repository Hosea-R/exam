#include "get_next_line.h"

int ft_strlen(char *str)
{
    int i = 0;
    while (str[i])
    {
        i++;
    }
    return (i);
}

char *ft_strdup(char *str)
{
    char *dup = malloc(ft_strlen(str) + 1);
    int i = 0;
    while (str[i])
    {
        dup[i] = str[i];
        i++;
    }
    dup[i] = '\0';
    return (dup);
}

char *ft_strjoin(char *s1, char *s2)
{
    char *join = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
    int i = 0;
    int j = 0;
    while (s1[i])
    {
        join[i] = s1[i];
        i++;
    }
    while (s2[j])
    {
        join[i] = s2[j];
        i++;
        j++;
    }
    join[i] = '\0';
    free(s1);
    return (join);
}

char *ft_strrchr(char *all, int c)
{
    int i = ft_strlen(all) - 1;
    while (i >= 0)
    {
        if (all[i] == (char)c)
            return (all + i);
        i--;
    }
    return (NULL);
}

char *ft_substr(char *str, int len)
{
    char *sub = malloc(len + 1);
    int i = 0;
    while (i < len)
    {
        sub[i] = str[i];
        i++;
    }
    sub[i] = '\0';
    return(sub);
}

char *ft_clean(char *all)
{
    char *new;
    int i = 0;
    while (all[i] && all[i] != '\n')
        i++;
    if (!all[i])
    {
        free(all);
        return (NULL);
    }
    new = ft_strdup(all + i + 1);
    free(all);
    return (new);
}

char *ft_read(int fd, char *all)
{
    char *temp;
    int i = BUFFER_SIZE;
    while ((temp = malloc(BUFFER_SIZE + 1)))
    {
        i = read(fd, temp, BUFFER_SIZE);
        if (i <= 0 || !temp[0])
        {
            free(temp);
            return (i < 0 || !ft_strlen(all) ? (free(all), NULL) : all);
        }
        temp[i] = '\0';
        all = ft_strjoin(all, temp);
        if (ft_strrchr(all, 10))
        {
            free(temp);
            return (all);
        }
        free(temp);
    }
    return (free(all), NULL);
}

char *get_next_line(int fd)
{
    static char* all;
    char *line;
    int i = 0;
    if (fd < 0 || BUFFER_SIZE <= 0)
        return (NULL);
    all = all ? all : ft_strdup("");
    all = ft_read(fd, all);
    if (!all)
    {
        return(NULL);
    }
    
    while (all[i] && all[i] != '\n')
        i++;
    line = ft_substr(all, all[i] == '\n' ? i + 1 : i);
    all = ft_clean(all);
    return (line);
}

// int	main(void)
// {
// 	int		fd;
// 	char	*next_line;
// 	int		count;

// 	count = 0;
// 	fd = open("test.txt", O_RDONLY);
// 	while (1)
// 	{
// 		next_line = get_next_line(fd);
// 		if (next_line == NULL)
// 			break ;
// 		count++;
// 		printf("[%d] : %s\n", count, next_line);
// 		free(next_line);
// 		next_line = NULL;
// 	}
// 	close(fd);
// 	return (0);
// }