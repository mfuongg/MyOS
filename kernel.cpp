#include "shell.h"

extern "C" void kernel_main() {
    char* vidmem = (char*)0xB8000;
    for (int i = 0; i < 80 * 25; i++) {
        vidmem[i * 2] = ' ';
        vidmem[i * 2 + 1] = 0x07;
    }

    const char* lines[] = {
        "+=================================================+",
        "| HELLO, WORLD!                                   |",
        "| This is My OS                                   |",
        "| We are group 2                                  |",
        "| Students of Operating System Module - Class N03 |",
        "| Lecturer: Dr. Le Hoang Anh                      |",
        "+=================================================+"
    };

    int row = 0;
    for (int i = 0; i < 7; i++) {
        const char* s = lines[i];
        int col = 0;
        while (*s) {
            int idx = (row * 80 + col) * 2;
            vidmem[idx] = *s++;
            vidmem[idx + 1] = 0x0F;
            col++;
        }
        row++;
    }

    shell_start();
}