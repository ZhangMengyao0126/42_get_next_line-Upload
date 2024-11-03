#include "get_next_line.h"

static char *ft_get_buffer(int fd, char *buffer)
{
    char *temp_buffer;
    ssize_t chars;

    chars = 1;
    temp_buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
    if (!temp_buffer)
        return (ft_free(&buffer));
    while (!buffer || ((buffer && chars) > 0 && !ft_strchr(buffer, '\n')))
    {
        chars = read(fd, temp_buffer, BUFFER_SIZE);
        if (chars < 0)
        {
            free (temp_buffer);
            return (ft_free(&buffer));
        }
        if (chars == 0)
            break;
        temp_buffer[chars] = '\0';
        buffer = ft_strjoin(buffer, temp_buffer);
    }
    free (temp_buffer);
    if (!buffer)
        return (NULL);
    return (buffer);
}

static char *ft_get_oneline(char *buffer)
{
    char *oneline;
    size_t len;

    len = ft_strlen(buffer, '\n');
    if (buffer[len] == '\n')
        len++;
    oneline = ft_substr(buffer, 0, len);
    if (!oneline)
        return (NULL);
    return (oneline);
}

static char *ft_refresh_buffer(char *buffer)
{
    char *refresh_buffer;
    size_t i;

    i = 0;
    if (!buffer)
    {
        refresh_buffer = NULL;
        return (ft_free(&buffer));
    }
    while (buffer[i] && buffer[i] != '\n')
        i++;
    if (!buffer[i] || !buffer[i + 1])
    {
        refresh_buffer = NULL;
        return (ft_free(&buffer));
    }
    refresh_buffer = ft_substr(buffer, (i + 1), (ft_strlen(buffer, '\0') - (i + 1)));
    if (!refresh_buffer)
        return (ft_free(&buffer));
    ft_free (&buffer);
    return (refresh_buffer);
}

char *get_next_line(int fd)
{
    char *oneline;
    static char *buffer;
    if (fd < 0 || BUFFER_SIZE <= 0)
        return (NULL);
    buffer = ft_get_buffer(fd, buffer);
    if (!buffer)
        return (NULL);
    oneline = ft_get_oneline(buffer);
    if (!oneline)
        return (ft_free(&buffer));
    buffer = ft_refresh_buffer(buffer);
    return (oneline);
}
