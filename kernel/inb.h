#ifndef INB_H
#define INB_H

static inline unsigned char inb(unsigned short port) {
    unsigned char ret;
    __asm__ volatile (
        "inb %1, %0"
        : "=a"(ret)
        : "Nd"(port)
    );
    return ret;
}

#endif //INB_H
