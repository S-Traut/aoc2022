#include <stdio.h>
#include <stdlib.h>

typedef unsigned int u32;

typedef struct aoc_file_t
{
  char *data;
  size_t size;
} aoc_file_t;

aoc_file_t get_data(const char *path);
void aoc_clear_buffer(char *BUFFER, size_t size);