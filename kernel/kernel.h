#ifndef KERNEL_H
#define KERNEL_H
#include <stddef.h>
#include <stdint.h>

extern char character;

void printk(const char *buffer, uint8_t text_color, uint8_t background_color);
void char_printk(const char c, size_t text_color, size_t background_color);
inline void clear();
void keyboard();
void ascii_init();

#endif
