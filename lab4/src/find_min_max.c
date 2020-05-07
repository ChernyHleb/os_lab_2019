#include "find_min_max.h"

#include <limits.h>

struct MinMax GetMinMax(int *array, unsigned int begin, unsigned int end) {
  struct MinMax min_max;
  min_max.min = INT_MAX;
  min_max.max = INT_MIN;

  // your code here
    int i, *p = array + begin;
    for(i = begin; i<end; i++)
    {
        if(*p < min_max.min)
            min_max.min = *p;
        else
        if(*p > min_max.max)
            min_max.max = *p;

        p++;
    }


  return min_max;
}
