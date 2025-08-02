#include "kernel.h"



void boot_logo() {
    clear(VGA_COLOR_RED, VGA_COLOR_GREEN);
    printk("                                                                                ", VGA_COLOR_RED, VGA_COLOR_GREEN);
    printk("                                                                                ", VGA_COLOR_RED, VGA_COLOR_GREEN);
    printk("                                                                               ", VGA_COLOR_RED, VGA_COLOR_GREEN);
    printk("                                                                                ", VGA_COLOR_RED, VGA_COLOR_GREEN);
    printk("                                                                                ", VGA_COLOR_RED, VGA_COLOR_GREEN);
    printk("                                                                                ", VGA_COLOR_RED, VGA_COLOR_GREEN);
    printk("                                                                                ", VGA_COLOR_RED, VGA_COLOR_GREEN);
    printk("                            \xDB\xDB\xDB\xDB\xDB\xDB\xBB  \xDB\xDB\xDB\xDB\xDB\xDB\xBB \xDB\xDB\xDB\xDB\xDB\xDB\xDB\xBB \n", VGA_COLOR_RED, VGA_COLOR_GREEN);
    printk("                           \xDB\xDB\xC9\xCD\xCD\xDB\xDB\xBB\xDB\xDB\xC9\xCD\xCD\xCD\xDB\xDB\xBB\xDB\xDB\xC9\xCD\xCD\xCD\xCD\xBC \n", VGA_COLOR_RED, VGA_COLOR_GREEN);
    printk("                           \xDB\xDB\xBA  \xDB\xDB\xBA\xDB\xDB\xBA   \xDB\xDB\xBA\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xBB \n", VGA_COLOR_RED, VGA_COLOR_GREEN);
    printk("                           \xDB\xDB\xBA  \xDB\xDB\xBA\xDB\xDB\xBA   \xDB\xDB\xBA\xC8\xCD\xCD\xCD\xCD\xDB\xDB\xBA \n", VGA_COLOR_RED, VGA_COLOR_GREEN);
    printk("                           \xDB\xDB\xDB\xDB\xDB\xDB\xC9\xBC\xC8\xDB\xDB\xDB\xDB\xDB\xDB\xC9\xBC\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xBA  \n", VGA_COLOR_RED, VGA_COLOR_GREEN);
    printk("                           \xC8\xCD\xCD\xCD\xCD\xCD\xBC  \xC8\xCD\xCD\xCD\xCD\xCD\xBC \xC8\xCD\xCD\xCD\xCD\xCD\xCD\xBC \n", VGA_COLOR_RED, VGA_COLOR_GREEN);
    printk("                                                                                ", VGA_COLOR_RED, VGA_COLOR_GREEN);
    printk("                                                                                ", VGA_COLOR_RED, VGA_COLOR_GREEN);
    printk("                    D I S K   O P E R A T I N G   S Y S T E M ", VGA_COLOR_RED, VGA_COLOR_GREEN);
    printk("                                                                                ", VGA_COLOR_RED, VGA_COLOR_GREEN);
    printk("                                                                                ", VGA_COLOR_RED, VGA_COLOR_GREEN);
    printk("                                                                                ", VGA_COLOR_RED, VGA_COLOR_GREEN);
    printk("                                                                                ", VGA_COLOR_RED, VGA_COLOR_GREEN);
    printk("                                                                                ", VGA_COLOR_RED, VGA_COLOR_GREEN);
    printk("                                                                                ", VGA_COLOR_RED, VGA_COLOR_GREEN);
    printk("                                                                                ", VGA_COLOR_RED, VGA_COLOR_GREEN);
    printk("                                                                                ", VGA_COLOR_RED, VGA_COLOR_GREEN);
    printk("                                                                                ", VGA_COLOR_RED, VGA_COLOR_GREEN);
}