#include "asm.h"
#define CR0_PE 1    // 保护模式标志位
#define SEG_KCODE 1 // 内核代码
#define SEG_KDATE 2 // 内核数据

.code16             # 设定为16位操作模式
.globl start        # 设定入口为start


# (0x7c00~0x7d00)
start:
  cli               # 关闭中断

  # 设置段寄存器为0值 %ds, %es, %ss
  xorw    %ax, %ax
  movw    %ax, %ds
  movw    %ax, %es
  movw    %ax, %ss

# 虚拟地址 segment:offset 可能产生21位物理地址，但 Intel 8088 只能向内存传递20位地址，所以它截断了地址的最高位：0xffff0 + 0xffff = 0x10ffef，但在8088上虚拟地址 0xffff:0xffff 则是引用物理地址 0x0ffef。早期的软件依赖硬件来忽略第21位地址位，所以当 Intel 研发出使用超过20位物理地址的处理器时，IBM 就想出了一个技巧来保证兼容性。那就是，如果键盘控制器输出端口的第2位是低位，则物理地址的第21位被清零；否则，第21位可以正常使用。引导加载器用 I/O 指令控制端口 0x64 和 0x60 上的键盘控制器，使其输出端口的第2位为高位，来使第21位地址正常工作。
seta20.1:
  inb     $0x64, %al
  testb   $0x2, %al
  jnz     seta20.1

  movb    $0xd1, %al
  outb    %al, $0x64

seta20.2
  inb     $0x64, %al
  testb   $0x2, %al
  jnz     seta20.1

  movb    $0xdf, %al
  outb    %al, $0x60

  lgdt    gdtdesc                       # 引导加载器执行lgdt把指向gdt的指针gdtdesc加载到GDT中

  # 开启保护模式
  movl    %cr0, %eax
  orl     %CR0_PE, %eax
  movl    %eax, %cr0

  ljmp    %(SEG_KCODE<<3), $start32

.code32
start32:
  # 设置保护模式下的数据段
  movw    $(SEG_KDATE<<3), %ax
  movw    %ax, %ds
  movw    %ax, %es
  movw    %ax, %ss
  movw    $0, %ax
  movw    %ax, %fs
  movw    %ax, %gs

  # 已start代码其实地址作为栈顶创建一个栈,向远离start的地址区域增长(0x7c00~0x0000)
  movl    $start, %esp
  # 调用c函数bootmain
  call    bootmain

  # 如果调用程序返回，说明程序出错，将错误信息打印到端口0x8a00中(模拟器中有效)
  movw    $0x8a00, %ax
  movw    %ax, %dx
  outw    %ax, %dx
  movw    $0x8ae0, %ax
  outw    %ax, %dx

# loop循环
spin:
  jmp     spin

# 加载GDT
.p2align 2
gdt:
  SEG_NULLASM                           # 空段
  SEG_ASM(STA|STA_R, 0x0, 0xffffffff)   # 代码段
  SEG_ASM(STA_W, 0x0, 0xffffffff)       # 数据段

gdtdesc:
  .word   (gdtdesc - gdt - 1)
  .long   gdt
