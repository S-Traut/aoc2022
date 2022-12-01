#include <lib.h>

int get_elf_count(aoc_file_t input)
{
  int total = 0;
  for (size_t i = 0; i < input.size; ++i)
  {

    char current_char = input.data[i];
    char next_char = input.data[i + 1];

    if (next_char == '\0' || '\n' == current_char && '\n' == next_char)
      total++;
  }

  return total;
}

int main(void)
{
  aoc_file_t input = get_data("./data/d1.txt");
  u32 elf_count = get_elf_count(input);
  int elf_data[elf_count];
  u32 elf_index = 0;
  char BUFFER[10] = {0};
  u32 buffer_index = 0;
  int elf_value = 0;
  int max = 0;

  for (size_t i = 0; i < input.size; ++i)
  {
    char current_char = input.data[i];
    char next_char = input.data[i + 1];

    if (next_char == '\0' || '\n' == current_char && '\n' == next_char)
    {
      elf_value += atoi(BUFFER);
      elf_data[elf_index] = elf_value;

      elf_value = 0;
      aoc_clear_buffer(BUFFER, 10);
      buffer_index = 0;
      elf_index++;
      continue;
    }

    if ('\n' == current_char)
    {
      elf_value += atoi(BUFFER);
      aoc_clear_buffer(BUFFER, 10);
      buffer_index = 0;
    }
    else
    {
      BUFFER[buffer_index] = current_char;
      buffer_index++;
    }
  }

  int first, second, third;
  for (size_t i = 0; i < elf_count; i++)
  {

    if (elf_data[i] > first)
    {
      third = second;
      second = first;
      first = elf_data[i];
    }
    else if (elf_data[i] > second)
    {
      third = second;
      second = elf_data[i];
    }
    else if (elf_data[i] > third)
    {
      third = elf_data[i];
    }
  }

  printf("top 3: %d %d %d\n", first, second, third);
  printf("sum: %d\n", first + second + third);

  free(input.data);
}
