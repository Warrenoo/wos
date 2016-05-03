#ifndef INCLUDE_STRING_H_
#define INCLUDE_STRING_H_

#include "types.h"

inline void tostring(char *str, int32_t value);

inline int32_t toint(const char *str);

inline void invert(char *str);

inline void memcpy(uint8_t *dest, const uint8_t *src, uint32_t len);

inline void memset(void *dest, uint8_t val, uint32_t len);

inline void bzero(void *dest, uint32_t len);

inline int strcmp(const char *str1, const char *str2);

inline char *strcpy(char *dest, const char *src);

inline char *strcat(char *dest, const char *src);

inline int strlen(const char *src);

#endif  // INCLUDE_STRING_H_
