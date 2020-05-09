#include "arr_sum.h"

struct SumArgs {
  int *array;
  int begin;
  int end;
};

int Sum(const struct SumArgs *args) {
  int sum = 0;
  for (int i = args->begin; i < args->end; i++)
  {
    sum+=args->array[i];
  } 
  return sum;
}