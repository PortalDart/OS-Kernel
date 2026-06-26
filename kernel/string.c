#include "string.h"
#include <stdint.h>
#include <stddef.h>

int strcmp(const char *a, const char *b) {
    while (*a && (*a == *b)) {
        a++;
        b++;
    }
    return *(const unsigned char *)a - *(const unsigned char *)b;
}

int strncmp(const char *a, const char *b, size_t n) {
    for (size_t i = 0; i < n; i++) {
        if (a[i] != b[i]) {
            return (unsigned char)a[i] - (unsigned char)b[i];
        }
        if (a[i] == '\0') {
            return 0;
        }
    }
    return 0;
}

size_t strlen(const char* str)
{
    size_t len = 0;
    while (str[len])
        len++;
    return len;
}

char* strtok(char* str, const char* delim) {
    static char* next = 0;  // Keeps track of next position
    char* token_start;
    int i;

    if (str)
        next = str;  // Initialize on first call

    if (!next)
        return 0;    // No more tokens

    // Skip leading delimiters
    while (*next) {
        int is_delim = 0;
        for (i = 0; delim[i]; i++) {
            if (*next == delim[i]) {
                is_delim = 1;
                break;
            }
        }
        if (!is_delim)
            break;
        next++;
    }

    if (*next == 0) {
        next = 0;
        return 0;
    }

    // Start of token
    token_start = next;

    // Find the end of the token
    while (*next) {
        int is_delim = 0;
        for (i = 0; delim[i]; i++) {
            if (*next == delim[i]) {
                is_delim = 1;
                break;
            }
        }
        if (is_delim) {
            *next = 0;  // Terminate token
            next++;
            return token_start;
        }
        next++;
    }

    // Last token
    next = 0;
    return token_start;
}

bool isDigit(const char *buffer) {
    while(*buffer) {
        if (*buffer < '0' || *buffer > '9') {
            return false;
        }
        buffer++;
    }
    return true;
}

int atoi(const char *s) {
    if (!s || !*s) return 0;

    int result = 0;
    int sign = 1;

    // skip leading whitespace
    while (*s == ' ' || *s == '\t') s++;

    // handle sign
    if (*s == '-') {
        sign = -1;
        s++;
    } else if (*s == '+') {
        s++;
    }

    // convert digits
    while (*s >= '0' && *s <= '9') {
        result = result * 10 + (*s - '0');
        s++;
    }

    return sign * result;
}
