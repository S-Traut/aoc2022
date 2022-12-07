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

void aoc_change_directory(fs_file_t **fs, char *file_name)
{
  fs_file_t *current = *fs;
  file_name[strcspn(file_name, "\n")] = 0;
  for (u32 i = 0; i < current->file_count; ++i)
  {
    if (!strcmp(file_name, current->files[i].name))
      *fs = current->files + i;
  }
}

void aoc_fs_add_file(fs_file_t *fs, fs_file_t file)
{
  u64 name_length = strlen(file.name) - 1;
  char *name = malloc(sizeof(char) * name_length);
  memcpy(name, file.name, sizeof(char) * name_length);
  file.name = name;

  if (fs->buffer_size == 0)
  {
    fs->files = malloc(sizeof(fs_file_t));
    fs->buffer_size++;
  }
  else if (fs->file_count + 1 > fs->buffer_size)
  {
    fs_file_t *tmp = malloc(sizeof(fs_file_t) * (fs->buffer_size * 2));
    memcpy(tmp, fs->files, sizeof(fs_file_t) * fs->file_count);
    free(fs->files);
    fs->files = tmp;
    fs->buffer_size *= 2;
  }

  memcpy(fs->files + fs->file_count, &file, sizeof(fs_file_t));
  fs->file_count++;
}

void aoc_make_space_string(int size)
{
  if (!size)
    return;

  for (int i = 0; i < size; ++i)
    printf(" ");
}

u64 aoc_fs_sum(fs_file_t *fs)
{
  u64 sum = 0;
  for (u32 i = 0; i < fs->file_count; ++i)
  {
    if (fs->files[i].type == 0)
    {
      sum += aoc_fs_sum(fs->files + i);
    }
    else
      sum += fs->files[i].size;
  }

  if (sum < 100000)
    return sum;

  return 0;
}

void aoc_fs_print(fs_file_t *fs, int level)
{
  aoc_make_space_string(level);
  printf("> %s:\n", fs->name);
  for (u32 i = 0; i < fs->file_count; ++i)
  {
    if (fs->files[i].type == 0)
    {
      aoc_fs_print(fs->files + i, level + 1);
      continue;
    }
    aoc_make_space_string(level + 2);
    printf("%d - %s\n", fs->files[i].size, fs->files[i].name);
  }

  u64 sum = aoc_fs_sum(fs);
  printf("%d\n", sum);
}
