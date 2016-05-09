[GLOBAL gdt_flush]

gdt_flush:
  mov eax, [esp+4]     ; 方法参数直接放入eax
  lgdt [eax]           ; 将参数地址加载到 GDTR 寄存器

  mov ax, 0x10         ; 加载数据段描述符
  mov ds, ax
  mov es, ax
  mov fs, ax
  mov gs, ax
  mov ss, ax

  jmp 0x08:.flush ; 清空流水线并串行化处理器

.flush:
  ret
