#include "console.h"

inline
int32_t pow(int32_t x, int32_t y) {

  int32_t result = 1;

  while(y-- > 0)
    result *= x;

  return result;
}
