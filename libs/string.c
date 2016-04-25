#include "string.h"
#include "console.h"

inline
void memcpy(uint8_t *dest, const uint8_t *src, uint32_t len) {
  uint8_t *tmp = dest;
  const uint8_t *tmp_src = src;
  for (; len != 0; len--) {
    *tmp++ = *tmp_src++;
  }
}

inline
void memset(void *dest, uint8_t val, uint32_t len) {
  uint8_t *tmp = (uint8_t *)dest;

  for (; len != 0; len--) {
    *tmp++ = val;
  }
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
  *(tmp+1) = '\n';

  return dest;
}

inline
int strlen(const char *src) {
  int len = 0;
  const char *tmp = src;

  while (*tmp++) {
    len++;
  }
  return len;
}
