#ifndef STRING_H
#define STRING_H

#include <stdint.h>
#include <stddef.h>

char* strtok(char* str, const char* delim);
size_t strlen(const char* str);
int strncmp(const char *a, const char *b, size_t n);
int strcmp(const char *a, const char *b);
bool isDigit(const char *buffer);
int atoi(const char *s);

#endif //STRING_H
