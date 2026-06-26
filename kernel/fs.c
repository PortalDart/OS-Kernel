#include "kernel.h"
#include <stdint.h>
#include <stdbool.h>

//sector 11 ->

struct fileEntry {
    char name[32];
    uint32_t start_sector;
    uint32_t size_bytes
}

void fs() {
    struct fileEntry fe;
}
