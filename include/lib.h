#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned long u64;

typedef struct interval_t
{
  u64 start;
  u64 end;
  u64 length;
} interval_t;

u8 aoc_interval_contains(interval_t inverval, u64 number);