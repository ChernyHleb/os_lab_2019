#ifndef ARR_SUM_H
#define ARR_SUM_H

struct SumArgs {
  int *array;
  int begin;
  int end;
};

int Sum(const struct SumArgs *args);

#endif