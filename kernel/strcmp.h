#ifndef STRCMP_H
#define STRCMP_H
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



#endif //STRCMP_H
