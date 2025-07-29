#include <stddef.h>
#include <stdint.h>
#include "strlen.h"
#include "kernel.h"

/* Check if the compiler thinks you are targeting the wrong operating system. */
#if defined(__linux__)
#error "You are not using a cross-compiler, you will most certainly run into trouble"
#endif

/* This tutorial will only work for the 32-bit ix86 targets. */
#if !defined(__i386__)
#error "This tutorial needs to be compiled with a ix86-elf compiler"
#endif

/* Hardware text mode color constants. */
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

static inline uint8_t vga_entry_color(const enum vga_color fg, const enum vga_color bg) {
	return fg | bg << 4;
}

static inline uint16_t vga_entry(unsigned char uc, uint8_t uc_color) {
	return uc | uc_color << 8;
}

#define VGA_MEMORY_LOCATION 0xB8000

uint16_t* const VGA_MEMORY = (uint16_t*)VGA_MEMORY_LOCATION;

#define VGA_WIDTH 80
#define VGA_HEIGHT 25
#define TAB_WIDTH 4

uint16_t cursor_row = 0;
uint16_t cursor_column = 0;


inline void clear() {
	cursor_column = 0;
	cursor_row = 0;

	for (size_t i = 0;i < VGA_HEIGHT * VGA_WIDTH; i++) {
		VGA_MEMORY[i] = vga_entry(' ', VGA_COLOR_BLACK);
	}
}

void scroll() {
	size_t row = 1;
	size_t column = 0;

	uint16_t destination_index = (row - 1) * VGA_WIDTH + column;
	uint16_t index = row * VGA_WIDTH + column;

	for (size_t i = 0;i < VGA_WIDTH * VGA_HEIGHT - VGA_WIDTH; i++) {

		destination_index = (row - 1) * VGA_WIDTH + column;
		index = row * VGA_WIDTH + column;

		VGA_MEMORY[destination_index] = VGA_MEMORY[index];

		if (column == VGA_WIDTH - 1) {
			row++;
			column = 0;
		}
		else {
			column++;
		}
	}

	row = VGA_HEIGHT - 1;

	for (size_t j = 0;j < VGA_WIDTH;j++) {
		VGA_MEMORY[((VGA_HEIGHT - 1) * VGA_WIDTH) + j] = vga_entry(' ', VGA_COLOR_BLACK);
	}

	column = 0;
	cursor_row = row;
	cursor_column = column;
}

void char_printk(const char c, size_t text_color, size_t background_color) {
	uint16_t index = cursor_row * VGA_WIDTH + cursor_column;

	switch (c) {
		case '\n':
			cursor_row++;
			cursor_column = 0;
			index = cursor_row * VGA_WIDTH + cursor_column;
			break;
		case '\b':
			if (cursor_column > 0) {
				cursor_column--;
				index = cursor_row * VGA_WIDTH + cursor_column;
				VGA_MEMORY[index] = vga_entry(' ', vga_entry_color(text_color, background_color));
			}
			break;
		default:
			index = cursor_row * VGA_WIDTH + cursor_column;
			VGA_MEMORY[index] = vga_entry(c, vga_entry_color(text_color, background_color));
			cursor_column++;
	}

	if (cursor_row >= VGA_HEIGHT) {
		scroll();
		cursor_row = VGA_HEIGHT - 1;
		cursor_column = 0;
	}
	if (cursor_column >= VGA_WIDTH) {
		scroll();
	}
}

void printk(const char *buffer, uint8_t text_color, uint8_t background_color) {
	size_t length = strlen(buffer);

	for (size_t i = 0;i < length; i++) {

		uint16_t index = cursor_row * VGA_WIDTH + cursor_column;

		switch (buffer[i]) {
			case '\n':
				cursor_column = 0;
				cursor_row++;
				break;
			case '\r':
				cursor_column = 0;
				break;
			case '\t':

				for (size_t j = 0; j < TAB_WIDTH;j++) {
					VGA_MEMORY[index] = vga_entry(' ', vga_entry_color(text_color, background_color));
					cursor_column++;
					index = cursor_row * VGA_WIDTH + cursor_column;

					if (cursor_column == VGA_WIDTH) {
						cursor_column = 0;
						cursor_row++;
					}

					if (cursor_row == VGA_HEIGHT) {
						cursor_row = 0;
					}
				}
				break;
			case '\\':
				VGA_MEMORY[index] = vga_entry('\\', vga_entry_color(text_color, background_color));
				cursor_column++;
				break;
			case '\'':
				VGA_MEMORY[index] = vga_entry('\'', vga_entry_color(text_color, background_color));
				cursor_column++;
				break;
			case '\"':
				VGA_MEMORY[index] = vga_entry('\"', vga_entry_color(text_color, background_color));
				cursor_column++;
				break;
			case '\?':
				VGA_MEMORY[index] = vga_entry('?', vga_entry_color(text_color, background_color));
				cursor_column++;
				break;
			default:
				VGA_MEMORY[index] = vga_entry(buffer[i], vga_entry_color(text_color, background_color));
				cursor_column++;
		}

		if (cursor_column == VGA_WIDTH) {
			cursor_column = 0;
			cursor_row++;
		}

		if (cursor_row == VGA_HEIGHT) {
			scroll();
		}
	}
}

int kernel_main() {
	clear();
	keyboard();
	return 0;
}