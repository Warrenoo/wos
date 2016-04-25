#include "common.h"

// 从端口写一个字节
inline void outb(uint16_t port, uint8_t value) {
   __asm volatile ("outb %1, %0" : : "dN" (port), "a" (value));
}

// 从端口读一个字节
inline uint8_t inb(uint16_t port)
{
    uint8_t byte;
    __asm volatile("inb %1, %0" : "=a" (byte) : "dN" (port));
    return byte;
}

// 从端口读一个字
inline uint16_t inw(uint16_t port)
{
    uint16_t word;

    __asm volatile ("inw %1, %0" : "=a" (word) : "dN" (port));

    return word;
}
