#include <stddef.h>
#include "kernel.h"
#include "inb.h"

char ascii[100] = {0};

#define KEYBOARD_DATA_PORT 0x60
#define KEYBOARD_STATUS_PORT 0x64

void ascii_init() {
    ascii[0x1E] = 'a';
    ascii[0x30] = 'b';
    ascii[0x2E] = 'c';
    ascii[0x20] = 'd';
    ascii[0x12] = 'e';
    ascii[0x21] = 'f';
    ascii[0x22] = 'g';
    ascii[0x23] = 'h';
    ascii[0x17] = 'i';
    ascii[0x24] = 'j';
    ascii[0x25] = 'k';
    ascii[0x26] = 'l';
    ascii[0x32] = 'm';
    ascii[0x31] = 'n';
    ascii[0x18] = 'o';
    ascii[0x19] = 'p';
    ascii[0x10] = 'q';
    ascii[0x13] = 'r';
    ascii[0x1F] = 's';
    ascii[0x14] = 't';
    ascii[0x16] = 'u';
    ascii[0x2F] = 'v';
    ascii[0x11] = 'w';
    ascii[0x2D] = 'x';
    ascii[0x15] = 'y';
    ascii[0x2C] = 'z';
    ascii[0x02] = '1';
    ascii[0x03] = '2';
    ascii[0x04] = '3';
    ascii[0x05] = '4';
    ascii[0x06] = '5';
    ascii[0x07] = '6';
    ascii[0x08] = '7';
    ascii[0x09] = '8';
    ascii[0x0A] = '9';
    ascii[0x0B] = '0';
    ascii[0x1C] = '\n';  // Enter
    ascii[0x39] = ' ';   // Space
    ascii[0x0E] = '\b';  // Backspace
}

char character;

void keyboard() {
    ascii_init();
    while (1) {
        if (inb(KEYBOARD_STATUS_PORT) & 1) {
            uint8_t byte = inb(KEYBOARD_DATA_PORT);
            if (!(byte & 0x80)) {
                char_printk(ascii[byte], 15, 0);
                character = ascii[byte];
            }
        }
    }
}


