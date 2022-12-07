#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned long u64;
typedef unsigned char bool;

#define AOC_TRUE 1
#define AOC_FALSE 0

typedef struct interval_t
{
  u64 start;
  u64 end;
  u64 length;
} interval_t;

typedef struct rucksack_t
{
  char *data;
  u64 size;
  u64 compartment_size;
} rucksack_t;

typedef struct cratestack_t
{
  char data[100];
  u16 size;
} cratestack_t;

typedef struct fs_file_t fs_file_t;
struct fs_file_t
{
  u8 type;
  char *name;
  fs_file_t *files;
  u32 buffer_size;
  u32 file_count;
  u64 size;
  fs_file_t *parent;
};

void aoc_change_directory(fs_file_t **fs, char *file_name);
void aoc_fs_add_file(fs_file_t *fs, fs_file_t file);
u64 aoc_fs_sum(fs_file_t *fs);
void aoc_fs_print(fs_file_t *fs, int level);
void aoc_make_space_string(int size);
u8 aoc_interval_contains(interval_t inverval, u64 number);