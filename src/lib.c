#include <lib.h>

u8 aoc_interval_contains(interval_t inverval, u64 number)
{
  for (u64 i = inverval.start; i <= inverval.end; ++i)
  {
    if (number == i)
      return 1;
  }
  return 0;
}