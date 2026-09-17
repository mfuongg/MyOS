#pragma once
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

uint8_t inb(uint16_t port);
void outb(uint16_t port, uint8_t val);
uint8_t keyboard_read_scan_code();
char keyboard_scan_code_to_ascii(uint8_t scan_code);

#ifdef __cplusplus
}
#endif