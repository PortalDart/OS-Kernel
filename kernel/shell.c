#include "kernel.h"
#include "string.h"

extern char character;

size_t text_color = VGA_COLOR_LIGHT_GREY;
size_t background_color = VGA_COLOR_BLACK;

char buffer[1000];

size_t i = 0;

enum tokens {
  TOKEN_ECHO,
  TOKEN_HELP,
  TOKEN_INFO,
  TOKEN_PARAMETER,
  TOKEN_CLEAR,
  TOKEN_ENTER,
  TOKEN_PANIC,
  TOKEN_READDISK,
  TOKEN_WRITEDISK,
  TOKEN_TESTDISK,
  TOKEN_BEEP,
  TOKEN_TEXTCOLOR,
  TOKEN_BACKGROUNDCOLOR,
  TOKEN_UNKNOWN
};

struct tokenType {
  enum tokens tokens;
  char *parameter;
};

void clear_buffer() {
  for (size_t j = 0; j < i; j++) {
    buffer[j] = 0;
  }
  i = 0;
}

void command() {
  if (character == '\n') {
    char_printk(character, text_color, background_color);
    buffer[i] = '\n';
    shell();
    clear_buffer();
  } else if (character == '\b') {
    if (i > 0) {
      i--;
      buffer[i] = '\0';
      char_printk(character, text_color, background_color);
    }
  } else {
    buffer[i] = character;
    i++;
    char_printk(character, text_color, background_color);
  }
}

enum tokens get_token(const char *c) {
  if (strncmp(c, "echo\n", 4) == 0) {
    return TOKEN_ECHO;
  } 
  else if (strcmp(c, "info\n") == 0) {
    return TOKEN_INFO;
  } 
  else if (strcmp(c, "panic\n") == 0) {
    return TOKEN_PANIC;
  } 
  else if (strcmp(c, "\n") == 0) {
    return TOKEN_ENTER;
  } 
  else if (strcmp(c, "clear\n") == 0) {
    return TOKEN_CLEAR;
  } 
  else if (strcmp(c, "help\n") == 0) {
    return TOKEN_HELP;
  } 
  else if (strcmp(c, "textcolor\n") == 0 || strcmp(c, "textcolor") == 0) {
      return TOKEN_TEXTCOLOR;
  }
  else if (strcmp(c, "backgroundcolor\n") == 0 || strcmp(c, "backgroundcolor") == 0) {
      return TOKEN_BACKGROUNDCOLOR;
  }
  else if (strcmp(c, "readdisk\n") == 0 || strcmp(c, "readdisk") == 0) {
    return TOKEN_READDISK;
  } 
  else if (strcmp(c, "writedisk\n") == 0 || strcmp(c, "writedisk") == 0) {
    return TOKEN_WRITEDISK;
  } 
  else if (strcmp(c, "testdisk\n") == 0 || strcmp(c, "testdisk") == 0) {
    return TOKEN_TESTDISK;
  } 
  else if(strcmp(c, "beep\n") == 0 || strcmp(c, "beep") == 0) {
      return TOKEN_BEEP;
  }
  else {
    return TOKEN_UNKNOWN;
  }
}

void shell() {
  struct tokenType tokenType;

  char *token = strtok(buffer, " ");
  char *args = strtok(NULL, "");

  tokenType.tokens = get_token(token);
  tokenType.parameter = args;

  switch (tokenType.tokens) {
  case TOKEN_ECHO:
    printk(args, text_color, background_color);
    break;
  case TOKEN_UNKNOWN:
    printk("Unknown command: ", VGA_COLOR_RED, background_color);
    printk(token, text_color, background_color);
    break;
  case TOKEN_PANIC:
    kernel_panic();
    break;
  case TOKEN_INFO:
    printk("Kernel version 0.0.3", text_color, background_color);
    break;
  case TOKEN_CLEAR:
    clear(text_color, background_color);
    break;
  case TOKEN_ENTER:
    printk("$ ", text_color, background_color);
    break;
  case TOKEN_TEXTCOLOR:
    if (args != NULL) {
        char *p = args;
        while (*p && *p != '\n') p++;
        *p = '\0';
    }
    if (isDigit(args)) {
        int color = atoi(args);
        if (color < 16) {
          text_color = color;
          clear(text_color, background_color);
        }
    }
    break;
  case TOKEN_BACKGROUNDCOLOR:
    if (args != NULL) {
        char *p = args;
        while (*p && *p != '\n') p++;
        *p = '\0';
    }
    if (isDigit(args)) {
        int color = atoi(args);
        if (color < 16) {
          background_color = color;
          clear(text_color, background_color);
        }
    }
    break;
  case TOKEN_HELP:
    printk("================GENERIC================\n", text_color, background_color);
    printk("| echo - prints a string              |\n", text_color, background_color);
    printk("| info - displays kernel version      |\n", text_color, background_color);
    printk("| clear - clears the screen           |\n", text_color, background_color);
    printk("| help - prints all commands          |\n", text_color, background_color);
    printk("| color - changes text color          |\n", text_color, background_color);
    printk("================DISK===================\n", text_color, background_color);
    printk("| readdisk - reads disk at address    |\n", text_color, background_color);
    printk("| writedisk - writes disk at address  |\n", text_color, background_color);
    printk("================SOUND==================\n", text_color, background_color);
    printk("| beep - plays a given frequency      |\n", text_color, background_color);
    printk("=======================================\n", text_color, background_color);
    break;
  case TOKEN_READDISK: {
    uint32_t sector = 100;
    if (args != NULL) {
      uint32_t parsed_sector = 0;
      char *p = args;
      if (*p >= '0' && *p <= '9') {
        while (*p >= '0' && *p <= '9') {
          parsed_sector = parsed_sector * 10 + (*p - '0');
          p++;
        }
        sector = parsed_sector;
      }
    }
    uint8_t read_buf[512];
    for (int j = 0; j < 512; j++)
      read_buf[j] = 0;
    if (read_disk(sector, read_buf) == 0) {
      read_buf[511] = '\0'; // Ensure string is null-terminated
      printk((char *)read_buf, text_color, background_color);
      printk("\n", text_color, background_color);
    } else {
      printk("Disk read failed\n", text_color, background_color);
    }
    break;
  }
  case TOKEN_WRITEDISK: {
    uint32_t sector = 100;
    char *text_to_write = args;
    if (args != NULL) {
      uint32_t parsed_sector = 0;
      char *p = args;
      if (*p >= '0' && *p <= '9') {
        while (*p >= '0' && *p <= '9') {
          parsed_sector = parsed_sector * 10 + (*p - '0');
          p++;
        }
        sector = parsed_sector;
        if (*p == ' ')
          p++;
        text_to_write = p;
      }
    }
    uint8_t write_buf[512];
    for (int j = 0; j < 512; j++)
      write_buf[j] = 0;
    if (text_to_write != NULL) {
      for (int j = 0;
           j < 511 && text_to_write[j] != '\0' && text_to_write[j] != '\n';
           j++) {
        write_buf[j] = text_to_write[j];
      }
    }
    if (write_disk(sector, write_buf) == 0) {
      printk("Disk write successful\n", text_color, background_color);
    } else {
      printk("Disk write failed\n", text_color, background_color);
    }
    break;
  }
  case TOKEN_TESTDISK:
    extern void test_disk();
    test_disk();
    break;
  case TOKEN_BEEP:
    printk(args, text_color, background_color);
    if (args != NULL) {
        char *p = args;
        while (*p && *p != '\n') p++;
        *p = '\0';
    }
    if (isDigit(args)) {
        int freq = atoi(args);
        beep(freq);
        sleep(400);
        stop_beep();
    }
    break;
  default:
    break;
  }
}
