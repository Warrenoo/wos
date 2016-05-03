#include "console.h"
#include "string.h"
#include "math.h"

inline
void tostring(char *str, int32_t val) {
  char *str_p = str;

  if (val < 0) {
    *str_p++ = '-';
    val = -val;
  } else if (val == 0) {
    *str_p++ = '0';
  }

  while (val > 0) {
    *str_p++ = '0' + (val % 10);

    val = val / 10;
  }

  *str_p = '\0';

  /* 翻转 */
  if (str[0] == '-') {
    invert(str+1);
  } else {
    invert(str);
  }
}

inline
int32_t toint(const char *str) {
  const char *str_p = str;

  int length = strlen(str);

  int32_t result = 0;

  int negative = 1;

  for(int i = length - 1; i >= 0; i--) {
    if (i == 0 && str_p[0] == '-') {
      negative = -1;
      continue;
    }

    result += (str_p[i] - '0') * pow(10, length - i - 1);
  }

  result *= negative;

  return result;
}

inline
void invert(char *str) {
  int length = strlen(str);
  char str_t[length+1];

  strcpy(str_t, str);
  char *str_p = str;

  for (int i = length - 1; i >= 0; i--)
    *str_p++ = str_t[i];
}

inline
void memcpy(uint8_t *dest, const uint8_t *src, uint32_t len) {
  uint8_t *tmp = dest;
  const uint8_t *tmp_src = src;
  for (; len != 0; len--)
    *tmp++ = *tmp_src++;
}

inline
void memset(void *dest, uint8_t val, uint32_t len) {
  uint8_t *tmp = (uint8_t *)dest;

  for (; len != 0; len--)
    *tmp++ = val;
}

inline
void bzero(void *dest, uint32_t len) {
  memset(dest, 0, len);
}

inline
int strcmp(const char *str1, const char *str2) {
  if (strlen(str1) != strlen(str2))
    return 0;

  for (int i = 0; i < strlen(str1); i++) {
    if (*(str1 + i) != *(str2 + i))
      return 0;
  }

  return 1;
}

inline
char *strcpy(char *dest, const char *src) {
  char *tmp = dest;
  const char *tmp_src = src;

  while(*tmp_src) {
    *tmp++ = *tmp_src++;
  }

  return dest;
}

inline
char *strcat(char *dest, const char *src) {
  char *tmp = dest + strlen(dest);
  const char *tmp_src = src;

  while(*tmp_src) {
    *tmp++ = *tmp_src++;
  }
  *tmp = '\0';

  return dest;
}

inline
int strlen(const char *src) {
  int len = 0;
  const char *tmp = src;

  while (*tmp++)
    len++;

  return len;
}
