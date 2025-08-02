#include "kernel.h"
#include "strcmp.h"
#include "strlen.h"

extern char character;

size_t text_color = VGA_COLOR_LIGHT_GREY;
size_t background_color = VGA_COLOR_BLACK;

char buffer[1000];

size_t i = 0;

void command() {
    buffer[i] = character;
    i++;
    if (character == '\n') {
        printk("myos > ", VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
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

void shell(){
    if (strcmp(buffer, "test\n") == 0) {
        printk("\n", VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
        printk("test\n", VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
        printk("myos > ", VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
    }
    else if (strcmp(buffer, "help\n") == 0) {
        printk("\n", 15, VGA_COLOR_BLACK);
        printk("------------------------------------------------------\n", VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
        printk("| test - test command                                |\n", VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
        printk("| help - lists all commands                          |\n", VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
        printk("| sysinfo - prints kernel version                    |\n", VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
        printk("| clear - clears the screen                          |\n", VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
        printk("| panic - tells os to crash, only for testing        |\n", VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
        printk("|                                                    |\n", VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
        printk("| setcolor - sets text and background color          |\n", VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
        printk("| takes 2 parameters first one is text color         |\n", VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
        printk("| second one is background color                     |\n", VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
        printk("| not implemented yet                                |\n", VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
        printk("------------------------------------------------------\n", VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
        printk("myos > ", VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
    }
    else if (strcmp(buffer, "sysinfo\n") == 0) {
        printk("\n", 15, 0);
        printk("kernel version: 0.0.1\n", VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
        printk("myos > ", VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
    }
    else if (strcmp(buffer, "clear\n") == 0) {
        clear(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
        printk("myos > ", VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
    }

    else if (strcmp(buffer, "panic\n") == 0) {
        kernel_panic();
    }
    else if (strncmp(buffer, "setbackgroundcolor", 9)) {
        size_t length = strlen(buffer);
    }
    else if (strncmp(buffer, "settextcolor", 9)) {

    }
    else if (strcmp(buffer, "\n") == 0) {

    }
    else {
        printk("invalid command \n", VGA_COLOR_LIGHT_GREY ,VGA_COLOR_BLACK);
        printk("myos > ", VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
    }
}