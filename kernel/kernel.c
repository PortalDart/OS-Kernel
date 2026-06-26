#include "kernel.h"
#include "io.h"
#include "string.h"
#include <stddef.h>
#include <stdint.h>

#if defined(__linux__)
#error
#endif

#if !defined(__i386__)
#error
#endif

static inline uint8_t vga_entry_color(const enum vga_color fg,
                                      const enum vga_color bg) {
  return fg | bg << 4;
}

static inline uint16_t vga_entry(unsigned char uc, uint8_t uc_color) {
  return uc | uc_color << 8;
}

#define VGA_MEMORY_LOCATION 0xB8000

uint16_t *const VGA_MEMORY = (uint16_t *)VGA_MEMORY_LOCATION;

#define VGA_WIDTH 80
#define VGA_HEIGHT 25
#define TAB_WIDTH 4

uint16_t cursor_row = 0;
uint16_t cursor_column = 0;

void clear(const enum vga_color text, const enum vga_color background) {
  cursor_column = 0;
  cursor_row = 0;

  for (size_t i = 0; i < VGA_HEIGHT * VGA_WIDTH; i++) {
    VGA_MEMORY[i] = vga_entry(' ', vga_entry_color(text, background));
  }

  cursor_column = 0;
  cursor_row = 0;
}

void scroll() {
  size_t row = 1;
  size_t column = 0;

  uint16_t destination_index = (row - 1) * VGA_WIDTH + column;
  uint16_t index = row * VGA_WIDTH + column;

  for (size_t i = 0; i < VGA_WIDTH * VGA_HEIGHT - VGA_WIDTH; i++) {

    destination_index = (row - 1) * VGA_WIDTH + column;
    index = row * VGA_WIDTH + column;

    VGA_MEMORY[destination_index] = VGA_MEMORY[index];

    if (column == VGA_WIDTH - 1) {
      row++;
      column = 0;
    } else {
      column++;
    }
  }

  row = VGA_HEIGHT - 1;

  for (size_t j = 0; j < VGA_WIDTH; j++) {
    VGA_MEMORY[((VGA_HEIGHT - 1) * VGA_WIDTH) + j] =
        vga_entry(' ', VGA_COLOR_BLACK);
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
      VGA_MEMORY[index] =
          vga_entry(' ', vga_entry_color(text_color, background_color));
    }
    break;
  default:
    index = cursor_row * VGA_WIDTH + cursor_column;
    VGA_MEMORY[index] =
        vga_entry(c, vga_entry_color(text_color, background_color));
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

  for (size_t i = 0; i < length; i++) {

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
      for (size_t j = 0; j < TAB_WIDTH; j++) {
        VGA_MEMORY[index] =
            vga_entry(' ', vga_entry_color(text_color, background_color));
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
      VGA_MEMORY[index] =
          vga_entry('\\', vga_entry_color(text_color, background_color));
      cursor_column++;
      break;
    case '\'':
      VGA_MEMORY[index] =
          vga_entry('\'', vga_entry_color(text_color, background_color));
      cursor_column++;
      break;
    case '\"':
      VGA_MEMORY[index] =
          vga_entry('\"', vga_entry_color(text_color, background_color));
      cursor_column++;
      break;
    case '\?':
      VGA_MEMORY[index] =
          vga_entry('?', vga_entry_color(text_color, background_color));
      cursor_column++;
      break;
    default:
      VGA_MEMORY[index] =
          vga_entry(buffer[i], vga_entry_color(text_color, background_color));
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

void sleep(size_t time) {
  for (volatile size_t i = 0; i < 1000000 * time; i++) {
  }
}

void test_disk() {
  uint8_t write_buf[512];
  uint8_t read_buf[512];

  // Fill write buffer with a recognizable pattern
  for (int i = 0; i < 512; i++) {
    write_buf[i] = (uint8_t)(i & 0xFF);
  }

  uint32_t test_lba = 100; // pick a sector unlikely to hold important data

  // Write the pattern
  if (write_disk(test_lba, write_buf) != 0) {
    printk("write_disk failed\n", VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
    return;
  }
  printk("write_disk OK\n", VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);

  // Clear read buffer so we know it's actually being filled
  for (int i = 0; i < 512; i++) {
    read_buf[i] = 0;
  }

  // Read it back
  if (read_disk(test_lba, read_buf) != 0) {
    printk("read_disk failed\n", VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
    return;
  }
  printk("read_disk OK\n", VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);

  // Compare
  int ok = 1;
  for (int i = 0; i < 512; i++) {
    if (read_buf[i] != write_buf[i]) {
      ok = 0;
      break;
    }
  }

  if (ok) {
    printk("DISK TEST PASSED\n", VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
  } else {
    printk("DISK TEST FAILED: data mismatch\n", VGA_COLOR_LIGHT_GREY,
           VGA_COLOR_BLACK);
  }
}

int kernel_main() {
  clear(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
  boot_logo();
  sleep(10);
  clear(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);

  for(;;) {
    keyboard();
  }
  return 0;
}
