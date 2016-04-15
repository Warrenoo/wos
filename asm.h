#define SEG_NULLASM                                            \
        .word 0, 0;                                            \
        .byte 0, 0, 0, 0

#define SEG_ASM(type,base,lim)                                 \
        .word (((limit) >> 12) & 0xffff), ((base) & 0xffff);   \
        .byte (((base) >> 16) & 0xff), (0x90 | (type)),        \
            (0xC0 | (((limit) >> 28) & 0xf)), (((base) >> 24) & 0xff)

#define STA_X    0x8
#define STA_E    0x4
#define STA_C    0x4
#define STA_W    0x2
#define STA_R    0x2
#define STA_A    0x1
