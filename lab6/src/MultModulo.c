#include "MultModulo.h"
int64_t MultModulo(int64_t a, int64_t b, int64_t mod) {
  int64_t result = 0;
  a = a % mod;
  while (b > 0) {
    if (b % 2 == 1)
      result = (result + a) % mod;
    a = (a * 2) % mod;
    b /= 2;
  }
  return result % mod;
}