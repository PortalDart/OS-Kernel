#include <stdint.h>
#include "kernel.h"
#include "io.h"

#define BASE_CLOCK 1193180

void beep(uint32_t freq) {
    if (freq == 0) {
        freq = 1;   
    }
    uint32_t divisor = BASE_CLOCK / freq;
    outb(0x43, 0xB6);
    outb(0x42, divisor & 0xFF);
    outb(0x42, divisor >> 8);

    outb(0x61, inb(0x61) | 3);
}

void stop_beep() {
    outb(0x61, inb(0x61) & 0xFC);
} 
