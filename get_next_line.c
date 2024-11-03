#include "get_next_line.h"

static char *ft_get_buffer(int fd, char *buffer)
{
    char *temp_buffer;
    ssize_t chars;

    chars = 1;
    temp_buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
    if (!temp_buffer)
        return (ft_free(&buffer));
    //Use "ft_free(&buffer)" instead of "NULL": 
    //Since ft_read_buf may be called multiple times, read_buf might already contain some data
    //when the function starts(especially if it’s being used to accumulate data across multiple calls,
    //as in a line-reading function). In that case, we also need to free it.
    while (!buffer || ((buffer && chars) > 0 && !ft_strchr(buffer, '\n')))
    //"buffer > 0":
    //check if it's uninitialized (i.e., if it doesn't point to any allocated memory). 
    //This works because pointers in C can hold a "null" value, 
    //typically represented by NULL or 0, to indicate that they don't point to a valid memory address.
    {
        chars = read(fd, temp_buffer, BUFFER_SIZE);
        if (chars < 0)//For error
        {
            free (temp_buffer);
            return (ft_free(&buffer));
        }
        if (chars == 0)//For reaching the end of the file
            break;
        temp_buffer[chars] = '\0';
        buffer = ft_strjoin(buffer, temp_buffer);
    }
    free (temp_buffer);
    //Remember to free the buffer asap.
    if (!buffer)
        return (NULL);
    //For nothing left to read.
    return (buffer);
}

static char *ft_get_oneline(char *buffer)
{
    char *oneline;
    size_t len;

    len = ft_strlen(buffer, '\n');
    //The index will stop right before '\n'
    if (buffer[len] == '\n')
        len++;
    //Since oneline need to include '\n', we need to check if there's a '\n' here.
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
    //To find the index of the first '\n'
    if (!buffer[i] || !buffer[i + 1])
    //!buffer[i]: For no content at all;
    //!buffer[i + 0]: For no content after the first '\n', meaning there is no nextline. 
    {
        refresh_buffer = NULL;
    //For the error handling————Set the pointer to NULL address, indicating the error.
        return (ft_free(&buffer));
    }
    refresh_buffer = ft_substr(buffer, (i + 1), (ft_strlen(buffer, '\0') - (i + 1)));
    //To refresh the buffer, excluding the oneline we've already extracted.
    if (!refresh_buffer)
        return (ft_free(&buffer));
    ft_free (&buffer);
    //Why ft_free here?
    //Free buffer and set the pointer to NULL address, since it will be used in the future loop.
    return (refresh_buffer);
}

char *get_next_line(int fd)
{
    char *oneline;
    static char *buffer;
    //Static Variables: A variable declared as static inside a function maintains its value between function calls. 
    if (fd < 0 || BUFFER_SIZE <= 0)
        return (NULL);
    //Error: Invalid file descriptor or buffer size.
    buffer = ft_get_buffer(fd, buffer);
    //First step: Set the buffer, and read data(including our target line) from the file descriptor and adds it to buffer.
    if (!buffer)
        return (NULL);
    //Error: Fail to set the buffer————the return value of ft_get_buffer is NULL.
    oneline = ft_get_oneline(buffer);
    //Second step: Extract the target line from the buffer as the return value.
    if (!oneline)
        return (ft_free(&buffer));
    //Error: Fail to extract the line————the return value of ft_get_one_line is NULL.
    //Memory-Free: Free the buffer we set earlier.
    buffer = ft_refresh_buffer(buffer);
    //Third step: Move the buffer pointer to the start of the next line in buffer.
    return (oneline);
}
