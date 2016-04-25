#include "common.h"
#include "console.h"

#define COLOR(blink, bg, depth, ag) (((blink) << 7) | ((bg) << 4) | ((depth) << 3) | (ag))

static uint16_t *display_address = (uint16_t *)0xB8000;

// 屏幕显示坐标
static uint8_t cursor_x = 0;
static uint8_t cursor_y = 0;

static void move_cursor() {
  uint16_t cursorLocation = cursor_y * 80 + cursor_x;

  outb(0x3D4, 14);                    // 告诉 VGA 我们要设置光标的高字节
  outb(0x3D5, cursorLocation >> 8);   // 发送高 8 位
  outb(0x3D4, 15);                    // 告诉 VGA 我们要设置光标的低字节
  outb(0x3D5, cursorLocation);        // 发送低 8 位
}

// 清屏，使用黑底白字空格符覆盖全屏
void console_clear() {
  uint8_t attribute_byte = COLOR(0, 0, 0, 7);
  uint16_t blank = 0x20 | (attribute_byte << 8);
  for (int i = 0; i < 80 * 25; i++) {
    display_address[i] = blank;
  }

  cursor_x = 0;
  cursor_y = 0;
  move_cursor();
}

static void scroll()
{
  // attribute_byte 被构造出一个黑底白字的描述格式
  uint8_t attribute_byte = COLOR(0, 0, 0, 7);
  uint16_t blank = 0x20 | (attribute_byte << 8);  // space 是 0x20

  // cursor_y 到 25 的时候，就该换行了
  if (cursor_y >= 25) {
    for (int i = 0 * 80; i < 24 * 80; i++) {
      display_address[i] = display_address[i+80];
    }
    // 最后的一行数据现在填充空格，不显示任何字符
    for (int i = 24 * 80; i < 25 * 80; i++) {
      display_address[i] = blank;
    }
    // 向上移动了一行，所以 cursor_y 现在是 24
    cursor_y = 24;
  }
}

void console_putc_color(char c, real_color_t back, real_color_t fore)
{
    uint8_t back_color = (uint8_t)back;
    uint8_t fore_color = (uint8_t)fore;

    uint8_t attribute_byte = COLOR(0, back_color, 0, fore_color);
    uint16_t attribute = attribute_byte << 8;

    // 0x08 是退格键的 ASCII 码
    // 0x09 是tab 键的 ASCII 码
    if (c == 0x08 && cursor_x) {
        cursor_x--;
    } else if (c == 0x09) {
        cursor_x = (cursor_x+8) & ~(8-1);
    } else if (c == '\r') {
        cursor_x = 0;
    } else if (c == '\n') {
        cursor_x = 0;
        cursor_y++;
    } else if (c >= ' ') {
        display_address[cursor_y*80 + cursor_x] = c | attribute;
        cursor_x++;
    }

    // 每 80 个字符一行，满80就必须换行了
    if (cursor_x >= 80) {
        cursor_x = 0;
        cursor_y ++;
    }

    // 如果需要的话滚动屏幕显示
    scroll();

    // 移动硬件的输入光标
    move_cursor();
}


void console_write(char *cstr)
{
    char *tmp = cstr;
    while (*tmp) {
        console_putc_color(*tmp++, rc_black, rc_green);
    }
}

void console_write_color(char *cstr, real_color_t back, real_color_t fore)
{
    char *tmp = cstr;
    while (*tmp) {
        console_putc_color(*tmp++, back, fore);
    }
}

