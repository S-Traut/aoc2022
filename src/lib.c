#include <lib.h>

aoc_file_t get_data(const char *path)
{
  FILE *file;
  long fsize;
  char *buffer;

  file = fopen(path, "rb");
  if (NULL == file)
  {
    printf("ERROR: file NULL\n");
    exit(1);
  }

  fseek(file, 0, SEEK_END);
  fsize = ftell(file);
  rewind(file);

  buffer = (char *)malloc(sizeof(char) * fsize);
  if (NULL == buffer)
    exit(1);

  fread(buffer, 1, fsize, file);

  return (aoc_file_t){
      .data = buffer,
      .size = fsize,
  };
}

void aoc_clear_buffer(char *BUFFER, size_t size)
{
  for (size_t i = 0; i < size; ++i)
  {
    BUFFER[i] = 0;
  }
}