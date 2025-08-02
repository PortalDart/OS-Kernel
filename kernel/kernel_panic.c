#include "kernel.h"

#define fg VGA_COLOR_BLACK
#define bg VGA_COLOR_LIGHT_BLUE

void kernel_panic() {
    clear(fg, bg);
    printk("   :(                                                                             \n", fg, bg);
    printk("Your PC ran into a problem                          \n", fg, bg);
    printk("and needs to restart.                               \n", fg, bg);
    printk("We're just collecting some                          \n", fg, bg);
    printk("error info, and then we'll restart for you.         \n", fg, bg);
    printk("                                                                                \n", fg, bg);
    printk("(0% complete)                                       \n", fg, bg);
    printk("                                                                                \n", fg, bg);
    printk("For more information about this issue               \n", fg, bg);
    printk("and possible fixes, visit                           \n", fg, bg);
    printk("https://github.com/CppHacker-dev/OS-Kernel          \n", fg, bg);
    printk("                                                                                \n", fg, bg);
    printk("if you call a support person, give them this info:  \n", fg, bg);
    printk("Stop Code: KERNEL_FATAL_ERROR                       \n", fg, bg);
    printk("Fault: PAGE_FAULT_IN_NONPAGED_AREA                  \n", fg, bg);



    for (;;) {
        asm volatile("cli; hlt");
    }
}

