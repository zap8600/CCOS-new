#ifndef ARCH_I686_IO_H
#define ARCH_I686_IO_H

#include <stdint.h>

void outb(uint16_t port, uint8_t val);
uint8_t inb(uint16_t port);
void outw(uint16_t port, uint16_t val);
uint16_t inw(uint16_t port);
void io_wait(void);

#endif
