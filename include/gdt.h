#ifndef INCLUDE_GDT_H_
#define INCLUDE_GDT_H_

#include "types.h"

// 段描述符
typedef
struct gdt_entry_t {
  uint16_t limit_low;      // 段长 平坦模型4g
  uint16_t base_low;       // 端基地址 15~0
  uint8_t  base_middle;   // 段基地址 23 ～ 16
  uint8_t  access;        // 段存在位、描述符特权级、描述符类型、描述符子类别
  uint8_t  granularity;   // 其他标志、段界限 19 ～ 16
  uint8_t  base_high;     // 段基地址 31 ～ 24
} __attribute__((packed)) gdt_entry_t;

// GDTR 全局段描述符表描述符
typedef
struct gdt_ptr_t {
  uint16_t limit;  // 表长
  uint32_t base;   // 全局描述符表 32 位基地址
} __attribute__((packed)) gdt_ptr_t;

void init_gdt();

// GDT 加载到 GDTR 的函数[汇编实现]
extern void gdt_flush(uint32_t);

#endif
