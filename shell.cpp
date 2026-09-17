#include "keyboard.h"

static int strcmp(const char* s1, const char* s2) {
    while (*s1 && (*s1 == *s2)) {
        s1++;
        s2++;
    }
    return *(const unsigned char*)s1 - *(const unsigned char*)s2;
}

static volatile char* const VGA = (char*)0xB8000;
static int cursor_row = 7, cursor_col = 0; 

static void update_cursor() {
    unsigned short pos = cursor_row * 80 + cursor_col;
    outb(0x3D4, 0x0F);
    outb(0x3D5, (unsigned char)(pos & 0xFF));
    outb(0x3D4, 0x0E);
    outb(0x3D5, (unsigned char)((pos >> 8) & 0xFF));
}

static void clear_screen() {
    for (int i = 0; i < 80 * 25; i++) {
        VGA[i * 2] = ' ';
        VGA[i * 2 + 1] = 0x07;
    }
    cursor_row = 0;
    cursor_col = 0;
    update_cursor();
}

static void print(const char* s, unsigned char color = 0x0F) {
    while (*s) {
        if (*s == '\n') {
            cursor_row++;
            cursor_col = 0;
        } else {
            int idx = (cursor_row * 80 + cursor_col) * 2;
            VGA[idx] = *s;
            VGA[idx + 1] = color;
            cursor_col++;
        }
        s++;
    }
    update_cursor();
}

static void print_char(char c) {
    if (c == '\n') {
        cursor_row++;
        cursor_col = 0;
    } else if (c == '\b') {
        if (cursor_col > 0) {
            cursor_col--;
            int idx = (cursor_row * 80 + cursor_col) * 2;
            VGA[idx] = ' ';
            VGA[idx + 1] = 0x07;
        }
    } else {
        int idx = (cursor_row * 80 + cursor_col) * 2;
        VGA[idx] = c;
        VGA[idx + 1] = 0x0F;
        cursor_col++;
    }
    update_cursor();
}

static void print_prompt() {
    print("> ");
}

static void reboot() {
    unsigned char good = 0x02;
    while (good & 0x02)
        good = inb(0x64);
    outb(0x64, 0xFE);
    asm volatile ("hlt");
}

void shell_start() {
    print("Welcome to MyOS shell! Type 'help' for commands.\n");
    print_prompt();

    char buffer[64];
    int pos = 0;

    while (1) {
        uint8_t sc = keyboard_read_scan_code();
        char c = keyboard_scan_code_to_ascii(sc);

        if (!c) continue;

        if (c == '\n') {
            buffer[pos] = 0;
            print("\n");

            if (pos == 0) {
                print_prompt();
                continue;
            }

            if (!strcmp(buffer, "help")) {
                print("Available commands:\n");
                print("  help   - Show this list\n");
                print("  clear  - Clear the screen\n");
                print("  about  - Show author info\n");
                print("  reboot - Restart system\n");
                print("  hi/hello - Say hello to the OS\n");
                print("  thanks - The OS will thank you back\n");
            } 
            else if (!strcmp(buffer, "clear")) {
                clear_screen();
                print_prompt();
            } 
            else if (!strcmp(buffer, "about")) {
                print("This is MyOS, created by group 2\n");
                print("Operating System Module - Class N03\n");
                print("Lecturer: Dr. Le Hoang Anh\n");
            } 
            else if (!strcmp(buffer, "reboot")) {
                print("Rebooting...\n");
                reboot();
            } 
            else if (!strcmp(buffer, "hi") || !strcmp(buffer, "hello")) {
                print("Hello! Welcome to MyOS!\n");
            } 
            else if (!strcmp(buffer, "thanks") || !strcmp(buffer, "thank you")) {
                print("You are welcome!\n");
            } 
            else {
                print("Unknown command: ");
                print(buffer);
                print("\n");
            }

            pos = 0;
            print_prompt();
        } 
        else if (c == '\b') {
            if (pos > 0) {
                pos--;
                print_char('\b');
            }
        } 
        else {
            if (pos < (int)sizeof(buffer) - 1) {
                buffer[pos++] = c;
                print_char(c);
            }
        }
    }
}