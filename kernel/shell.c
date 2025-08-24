#include "kernel.h"
#include "strcmp.h"
#include "strlen.h"

extern char character;

size_t text_color = VGA_COLOR_LIGHT_GREY;
size_t background_color = VGA_COLOR_BLACK;

char buffer[1000];

size_t i = 0;

enum tokens {
    TOKEN_ECHO,
    TOKEN_HELP,
    TOKEN_INFO,
    TOKEN_PARAMETER,
    TOKEN_UNKNOWN
};

struct tokenType {
    enum tokens tokens;
    char *parameter;
};

void command() {
    buffer[i] = character;
    i++;
    if (character == '\n') {
        shell();
        for (size_t j = 0; j < i; j++) {
            buffer[j] = 0;
        }
        i = 0;
    }
    if (character == '\b') {
        i--;
        buffer[i] = 0;
        char_printk(' ', VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
    }
}

//shit
enum tokens get_token(const char *c) {
    if (strncmp(c, "echo", 4) == 0) {
        return TOKEN_ECHO;
    }
    else if (strncmp(c, "info", 4) == 0) {
        return TOKEN_INFO;
    }
    else if (strncmp(c, "help", 4) == 0) {
        return TOKEN_HELP;
    }
    return TOKEN_UNKNOWN;
}

void shell(){
    struct tokenType tokenType;

    char *token = strtok(buffer, " ");
    char *args = strtok(NULL, "");

    tokenType.tokens = get_token(token);
    tokenType.parameter = args;

    switch (tokenType.tokens) {
        case TOKEN_ECHO:
            printk(args, VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
            goto print;
            break;
        case TOKEN_UNKNOWN:
            printk("Unknown command \n", VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
            printk(token, VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
            goto print;
            break;
        case TOKEN_INFO:
            printk("Kernel version 0.0.2 \n", VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
            goto print;
            break;
        case TOKEN_HELP:
            printk("#####################################\n", VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
            printk("# echo - prints a string            #\n", VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
            printk("# info - displays kernel version    #\n", VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
            printk("#####################################\n", VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
            goto print;
            break;
        default:
            goto print;
    }

    print:
        printk("$ ", VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
}


