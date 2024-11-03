#include "get_next_line.h"

char *ft_free(char **str)
{
    free (*str);
    *str = NULL;
    return (NULL);
}


char *ft_strchr(const char *s, int c)
//ft_strchr: String character, searches for the first occurrence of a character 'c' in a string 's'.

//const char *: 
//1. Constant character *, meaning the data being pointed to cannot be modified through this pointer.
//2. Safety: Marking a pointer as const char* tells the compiler and other developers that this data should not be modified. 
//////////// It prevents accidental changes to data that should be immutable, such as a constant string or shared resource.
//////////// Const char* is commonly used when the function only needs to read a string.

//Why use "int c" instead of "char c":
//1. Compatibility with Extended ASCII(0-255) and EOF(-1): 
/////If c were a char, there would be no way to distinguish between the EOF value -1 and the valid character 255.
//2. Compatibility and consistency with the C standard library:
/////According to the C standard, characters passed to standard library functions are promoted to int.
{
    size_t i;

    i = 0;
    while (s[i] != '\0')
    {
        if (((unsigned char *)s)[i] == (unsigned char)c)
        //(unsigned char): To keep the value type in the comparition consistent.
            return ((char *)(s + i));
            //(char *): To keep the return value type consistent
            //s + i: Pointer arithmetic, move the pointer to the position we want.
        i++;
    }
    return (NULL);
}

char* ft_strjoin(char *s1, char*s2)
{
    char *new_str;
    size_t length;
    size_t i;
    size_t j;

    if (!s1)
//Why do we only check s1 here?
//Cause this utility function is used in "buffer = strjoin(buffer, temp_buffer)". 
//s1 represents buffer, which is likely to be NULL at the initail state.
//s2 represents temp_buffer, which receices new data directly from the function read.
//Since read guarantees it will either write a valid string or return 0 or -1. s2 should not be NULL.
    {
        s1 = (char *)malloc(sizeof(char));
        if (!s1)
            return(NULL);
        //Remember to add error handling every time you use malloc.
        s1[0] = '\0';
        //Equivalent to s1[0] = 0.
    }
    length = ft_strlen(s1, '\0') + ft_strlen(s2, '\0');
    new_str = (char *)malloc(sizeof(char) * (length + 1));
    //lenth + 1: For '\0' at the end of the new_str. This follows C convention.
    if (!new_str)
        return (ft_free(&s1));
        //Remember to free the memory every time you use malloc.
        //Remember to add error handling every time you use malloc.
    i = 0;
    j = 0;
    while (s1[i] != '\0')
    {
        new_str[i] = s1[i];
        i++;
    }
    while (s2[j] != '\0')
    {
        new_str[i + j] = s2[j];
        j++;
    }
    new_str[i + j] = '\0';
    free(s1);
    //Remember to free the memory every time you use malloc.
    return(new_str);
}

size_t ft_strlen(const char *s, char c)
{
    size_t i;

    i = 0;
    if (!s)
        return(0);
        //Since the purpose of the function is to return a size, we return 0 here instead of NULL.
    while (s[i] && s[i] != c)
        i++;
    return (i);
}

char *ft_substr(const char *src, size_t start, size_t len)
{
    char *dst;
    size_t src_len;
    size_t i;

    if (!src)
        return (NULL);
    if (start >= ft_strlen(src, '\0'))
    //In common situation: For the index is out of bounds.
    //In get_next_line:
    //The condition will be (i + 1) >= ft_strlen(buffer, '\0')
    //If there is no '\n' in the buffer, then 'i' will be the index of the last character of the buffer.
    //Therefore, 'start', which equals (i + 1), will be out of bounds.
    {
        dst = (char *)malloc(sizeof(char));
        if (!dst)
            return (NULL);
        dst[0] = '\0';
        return (dst);
    }
    src_len = ft_strlen(src, '\0');
    if (len > (src_len - start))
        len = src_len - start;
    //In common situation: For the len is out of bounds.
    //In get_next_line:
    //Len = ft_strlen(buffer, '\0') - （i + 1), which is always true.
    dst = (char *)malloc(sizeof(char) * (len + 1));
    if(!dst)
        return (NULL);
    i = 0;
    while(i < len && start < src_len && src[start])
    {
        dst[i++] = src[start++];
    }
    dst[i] = '\0';
    return(dst);
}

