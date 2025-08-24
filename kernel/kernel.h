#ifndef KERNEL_H
#define KERNEL_H
#include <stddef.h>
#include <stdint.h>

extern char character;

#define KERNEL_VERSION_MAJOR 0
#define KERNEL_VERSION_MINOR 0
#define KERNEL_VERSION_PATCH 2

enum vga_color {
    VGA_COLOR_BLACK = 0,
    VGA_COLOR_BLUE = 1,
    VGA_COLOR_GREEN = 2,
    VGA_COLOR_CYAN = 3,
    VGA_COLOR_RED = 4,
    VGA_COLOR_MAGENTA = 5,
    VGA_COLOR_BROWN = 6,
    VGA_COLOR_LIGHT_GREY = 7,
    VGA_COLOR_DARK_GREY = 8,
    VGA_COLOR_LIGHT_BLUE = 9,
    VGA_COLOR_LIGHT_GREEN = 10,
    VGA_COLOR_LIGHT_CYAN = 11,
    VGA_COLOR_LIGHT_RED = 12,
    VGA_COLOR_LIGHT_MAGENTA = 13,
    VGA_COLOR_LIGHT_BROWN = 14,
    VGA_COLOR_WHITE = 15,
};

void printk(const char *buffer, uint8_t text_color, uint8_t background_color);
void char_printk(const char c, size_t text_color, size_t background_color);
void clear(const enum vga_color text, const enum vga_color background);
void keyboard();
void ascii_init();
void command();
void shell();
void boot_logo();
void sleep(size_t time);
void kernel_panic();
void read_disk(uint32_t lba, uint8_t *buffer);
void write_disk(uint32_t lba, uint8_t *buffer);

#endif
