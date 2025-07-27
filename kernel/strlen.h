#ifndef STRLEN_H
#define STRLEN_H



inline size_t strlen(const char* str)
{
    size_t len = 0;
    while (str[len])
        len++;
    return len;
}
#endif //STRLEN_H
