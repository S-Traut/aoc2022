/*
Advent Of Code 2022 - Stéphane Traut
This version is pretty rough and not scalable, and can be optimized / clean up

It basically just loop through each characters of the input string, after each line return it
increase the current elf_value, if there is 2 line return it take the elf value and check for its
order in the TOP 3.
*/

#include <lib.h>

int main(void)
{
  aoc_file_t input = get_data("./data/d1.txt");
  char BUFFER[10] = {0};
  u32 buffer_index = 0;
  int elf_value = 0;
  int first, second, third;

  for (size_t i = 0; i < input.size; ++i)
  {
    char current_char = input.data[i];
    char next_char = input.data[i + 1];

    if (next_char == '\0' || '\n' == current_char && '\n' == next_char)
    {
      elf_value += atoi(BUFFER);

      // (TODO) Unscalable might be better to make it in a better way..
      if (elf_value > first)
      {
        third = second;
        second = first;
        first = elf_value;
      }
      else if (elf_value > second)
      {
        third = second;
        second = elf_value;
      }
      else if (elf_value > third)
      {
        third = elf_value;
      }

      elf_value = 0;
      aoc_clear_buffer(BUFFER, 10);
      buffer_index = 0;
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

  printf("top 3: %d %d %d\n", first, second, third);
  printf("sum: %d\n", first + second + third);

  free(input.data);
}
