#ifndef GET_NEXT_LINE_H
    #define GET_NEXT_LINE_H

#ifndef BUFFER_SIZE
    #define BUFFER_SIZE 10
#endif

#include <stdlib.h>
#include <unistd.h>

char *get_next_line(int fd);
char *ft_free(char **str);
char *ft_strchr(const char *s, int c);
char *ft_strjoin(char *s1, char *s2);
size_t ft_strlen(const char *s, char c);
char *ft_substr(const char *src, size_t start, size_t len);

#endif