#include "get_next_line.h"

char *get_next_line(int fd)
{
    if (fd < 0 || BUFFER_SIZE <= 0)
        return (NULL);
    char *buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
    if (!buffer)
        return (NULL);
    char *line = malloc(sizeof(char) * 10000);
    if (!line)
    {
        free(buffer);
        return (NULL);
    }
    char *current = line;
    ssize_t bytes_read;
    while ((bytes_read = read(fd, buffer, 1)) > 0)
    {
        *current++ = *buffer;
        if (*buffer == '\n')
            break;
    }
    free(buffer);
    if (bytes_read < 0 || (bytes_read == 0 && current == line))
    {
        free(line);
        return (NULL);
    }
    *current = '\0';
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